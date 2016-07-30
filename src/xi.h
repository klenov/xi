/*
        xi - Riemann esp8266 Client
        github.com/klenov/xi
*/

#ifndef XI_RIEMANN_CLIENT
#define XI_RIEMANN_CLIENT

#define RIEMANN_HEADER_SIZE 4

#include <ESP8266WiFi.h>

#define XI_DEBUG_LEVEL 1
#include "utils/debug.h"

extern "C"{
  #include "nanopb/pb_encode.h" // TODO: add decode to read server response
  #include "nanopb/pb_arduino_encode.h"
  #include "riemann.pb.h"
}

bool pb_string_callback(pb_ostream_t *stream, const pb_field_t *field, void * const *arg) {
  char *str = (char*) *arg;

  if (!pb_encode_tag_for_field(stream, field))
    return false;

  return pb_encode_string(stream, (uint8_t*)str, strlen(str));
}

bool pb_event_callback(pb_ostream_t *stream, const pb_field_t *field, void * const *arg) {
  Event *riemann_event = (Event*) *arg;

  if (!pb_encode_tag_for_field(stream, field))
    return false;

  return pb_encode_delimited(stream, Event_fields, riemann_event);
}

class RiemannEventMsg {
  private:
  Msg   msg_struct;
  Event event_struct;

  public:
  /*! * default Constructor */
  RiemannEventMsg() : 
  msg_struct(Msg_init_default),
  event_struct(Event_init_default) {
    msg_struct.events.funcs.encode = &pb_event_callback;
    msg_struct.events.arg = &event_struct;
  }

  void setMetric(float value) { // TODO: add other types
    event_struct.metric_f     = value;
    event_struct.has_metric_f = true;
  }

  void setService(char* service_name) {
    event_struct.service.funcs.encode = &pb_string_callback;
    event_struct.service.arg = service_name;
  }

  void setHostname(char* hostname) {
    event_struct.host.funcs.encode = &pb_string_callback;
    event_struct.host.arg = hostname;
  }

  size_t size() {
    size_t encoded_msg_size;
    pb_get_encoded_size(&encoded_msg_size, Msg_fields, &msg_struct);
    return encoded_msg_size;
  }


};

class Xi {
    
private:
  WiFiClient *_wifi_client;
  char*    _host;
  uint16_t _port;
  pb_byte_t header_bytes[RIEMANN_HEADER_SIZE];

public:
  /*! * default Constructor */
  Xi(WiFiClient *wifi_client)
    : _wifi_client(wifi_client),
      header_bytes{0} {}

  void setServer(const char* host, const uint16_t port) { // TODO: should be possible to pass IP address
    _host = (char*)host;
    _port = (uint16_t)port;
  }

  bool connect() {
    if (!_wifi_client->connect(_host, _port)) {
      XI_DEBUG_PRINTLN("ERROR: connection to riemann server failed");
      return false;
    } else {
      XI_DEBUG_PRINTLN("INFO: connected to riemann server");
      return true;
    }
  }
  
  // see about header in Reiamann docs http://riemann.io/howto.html#write-a-client
  pb_byte_t* lenghtHeader(size_t message_size) {

    header_bytes[0] = (message_size >> 24) & 0xFF;
    header_bytes[1] = (message_size >> 16) & 0xFF;
    header_bytes[2] = (message_size >> 8)  & 0xFF;
    header_bytes[3] =  message_size & 0xFF;

    return header_bytes;
  }

  bool sendEvent(RiemannEventMsg event_msg) {
    bool status;

    if( !connect())
      return false;

    pb_ostream_t output_stream;
    // bool status;     

    Stream* wifi_client_stream = _wifi_client;

    // map output_stream to wifi_client_stream
    pb_ostream_from_stream(*wifi_client_stream, output_stream);

    // writing a header to a stream
    size_t msg_size = event_msg.size();
    status = pb_write(&output_stream, lenghtHeader(msg_size), RIEMANN_HEADER_SIZE);

    if (!status) {
      XI_DEBUG_PRINT("ERROR: Writing header failed: ");
      XI_DEBUG_PRINT_VARLN(PB_GET_ERROR(&output_stream));
      return status;
    }
    
    // writing a protobuf message to a stream
    status = pb_encode(&output_stream, Msg_fields, &event_msg);

    if (!status) {
      XI_DEBUG_PRINT("ERROR: Encoding failed: ");
      XI_DEBUG_PRINT_VARLN(PB_GET_ERROR(&output_stream));
      return status;
    }

    return true;
  }


};

#endif
