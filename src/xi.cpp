/*
        xi - Riemann esp8266 Client
        github.com/klenov/xi
*/

#include "xi.h"

inline bool pb_string_callback(pb_ostream_t *stream, const pb_field_t *field, void * const *arg) {
  char *str = (char*) *arg;

  if (!pb_encode_tag_for_field(stream, field))
    return false;

  return pb_encode_string(stream, (uint8_t*)str, strlen(str));
}

inline bool pb_event_callback(pb_ostream_t *stream, const pb_field_t *field, void * const *arg) {
  RiemannEvent *riemann_event = (RiemannEvent*) *arg;

  if (!pb_encode_tag_for_field(stream, field))
    return false;

  return pb_encode_delimited(stream, RiemannEvent_fields, riemann_event);
}

// для чтения ошибки!
bool pb_decode_str(pb_istream_t *stream, const pb_field_t *field, void **arg) {
  int error_length = stream->bytes_left;
  
  XI_DEBUG_PRINT("error lenght ");
  XI_DEBUG_PRINT_VARLN(error_length);

  // while (stream->bytes_left)
  // {
  //     uint64_t value;
  //     if (!pb_decode_varint(stream, &value))
  //         return false;
  //     printf("%lld\n", value);
  // }
  return true;
}

RiemannEventMsg::RiemannEventMsg() : 
  msg_struct(RiemannMsg_init_default),
  event_struct(RiemannEvent_init_default) {
    msg_struct.events.funcs.encode = &pb_event_callback;
    msg_struct.events.arg = &event_struct;
  }

void RiemannEventMsg::setMetricF(float value) {
  event_struct.metric_f     = value;
  event_struct.has_metric_f = true;
}

void RiemannEventMsg::setMetricD(double value) {
  event_struct.metric_d     = value;
  event_struct.has_metric_d = true;
}

void RiemannEventMsg::setMetricSint64(int64_t value) {
  event_struct.metric_sint64     = value;
  event_struct.has_metric_sint64 = true;
}

void RiemannEventMsg::setService(const char* service_name) {
  event_struct.service.funcs.encode = &pb_string_callback;
  event_struct.service.arg = (char *)service_name;
}

void RiemannEventMsg::setHostname(const char* hostname) {
  event_struct.host.funcs.encode = &pb_string_callback;
  event_struct.host.arg = (char *)hostname;
}

size_t RiemannEventMsg::size() {
  size_t encoded_msg_size;
  pb_get_encoded_size(&encoded_msg_size, RiemannMsg_fields, &msg_struct);
  return encoded_msg_size;
}


Xi::Xi(WiFiClient *wifi_client)
  : _wifi_client(wifi_client),
    header_bytes{0} {}


void Xi::setServer(const char* host, const uint16_t port) { // TODO: should be possible to pass IP address
  _host = (char*)host;
  _port = (uint16_t)port;
}

bool Xi::connect() {
  if (!_wifi_client->connect(_host, _port)) {
    XI_DEBUG_PRINTLN("ERROR: connection to riemann server failed");
    return false;
  } else {
    XI_DEBUG_PRINTLN("INFO: connected to riemann server");
    return true;
  }
}

// see about header in Reiamann docs http://riemann.io/howto.html#write-a-client
pb_byte_t* Xi::lenghtHeader(size_t message_size) {

  header_bytes[0] = (message_size >> 24) & 0xFF;
  header_bytes[1] = (message_size >> 16) & 0xFF;
  header_bytes[2] = (message_size >> 8)  & 0xFF;
  header_bytes[3] =  message_size & 0xFF;

  return header_bytes;
}

bool Xi::sendEvent(RiemannEventMsg event_msg) {
  bool status;

  if( !connect())
    return false;

  pb_ostream_t output_stream;

  Stream* wifi_client_stream = _wifi_client;

  // map output_stream to wifi_client_stream
  pb_ostream_from_stream(*wifi_client_stream, output_stream);

  // writing a header to a stream
  size_t msg_size = event_msg.size();
  status = pb_write(&output_stream, lenghtHeader(msg_size), RIEMANN_HEADER_SIZE);

  if (!status) {
    XI_DEBUG_PRINT("ERROR: Writing header failed: ");
    XI_DEBUG_PRINT_VARLN(PB_GET_ERROR(&output_stream));
    return false;
  }
  
  // writing a protobuf message to a stream
  status = pb_encode(&output_stream, RiemannMsg_fields, &event_msg);

  if (!status) {
    XI_DEBUG_PRINT("ERROR: Encoding failed: ");
    XI_DEBUG_PRINT_VARLN(PB_GET_ERROR(&output_stream));
    return false;
  }

  // server_response_msg.error.funcs.decode = &pb_decode_str;
  
  unsigned long start_time = millis();
  while (_wifi_client->available() == 0) {
    if (millis() - start_time > 500) {
      Serial.println(">>> Client Timeout !");
      _wifi_client->stop();
      return false;
    }
  }

  // int bytes_av = _wifi_client->available();

  // String str = _wifi_client->readString();
  // читаем хедер, если он больше нуля читаем оставшиеся байты, потом декодим их
  if( _wifi_client->available() > RIEMANN_HEADER_SIZE ) {
    byte leght_header[RIEMANN_HEADER_SIZE] = {0};
    _wifi_client->readBytes(leght_header, RIEMANN_HEADER_SIZE);
   
    uint32_t m_size = (uint32_t)leght_header[0] << 24
                    | (uint32_t)leght_header[1] << 16
                    | (uint32_t)leght_header[2] << 8
                    | (uint32_t)leght_header[3];

    XI_DEBUG_PRINT("m_size: ");
    XI_DEBUG_PRINT_VARLN(m_size);

    if( m_size > 0 ) {
      pb_byte_t buf[64];
      RiemannMsg server_response_msg = {};
      pb_istream_t input_stream = pb_istream_from_buffer(buf, 64);
      // pb_istream_from_stream(*wifi_client_stream, input_stream);
      // _wifi_client->readBytes(buf, m_size - RIEMANN_HEADER_SIZE);

      if (!pb_decode(&input_stream, RiemannMsg_fields, &server_response_msg)) {
        XI_DEBUG_PRINT("Decode failed: ");
        XI_DEBUG_PRINT_VARLN(PB_GET_ERROR(&input_stream));
        return false;
      }

      Serial.print("Server response: ");
      Serial.println(server_response_msg.has_ok);

    }

  }

  // while (_wifi_client->available() )
  //   Serial.print(_wifi_client->read(), HEX);


  // pb_byte_t bbuf[64];

  // while (bytes_left)
  // {
  //   XI_DEBUG_PRINT("Will read bytes ");
  //   XI_DEBUG_PRINT_VARLN(bytes_left);

  //   pb_read(&input_stream, bbuf, bytes_left);

  //   XI_DEBUG_PRINT_VARLN((const char*)bbuf);
  // }
  
  // if (!pb_decode(&input_stream, Msg_fields, &server_response_msg)) {
  //   XI_DEBUG_PRINT("Decode failed: ");
  //   XI_DEBUG_PRINT_VARLN(PB_GET_ERROR(&input_stream));
  //   return false;
  // }

  // Serial.print("Server response: ");
  // Serial.println(server_response_msg.ok);

  return true;
}
