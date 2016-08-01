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
  #include "riemann.pb.h"
}

#include "nanopb/pb_arduino_encode.h"

bool pb_string_callback(pb_ostream_t *stream, const pb_field_t *field, void * const *arg);

bool pb_event_callback(pb_ostream_t *stream, const pb_field_t *field, void * const *arg);

class RiemannEventMsg {
  private:
  Msg   msg_struct;
  Event event_struct;

  public:
  /*! * default Constructor */
  RiemannEventMsg();

  void setMetricF(float value);

  void setMetricD(double value);

  void setMetricSint64(int64_t value);

  void setService(const char* service_name);

  void setHostname(const char* hostname);

  size_t size(void);
};

class Xi {
    
private:
  WiFiClient *_wifi_client;
  char*    _host;
  uint16_t _port;
  pb_byte_t header_bytes[RIEMANN_HEADER_SIZE];

public:
  /*! * default Constructor */
  Xi(WiFiClient *wifi_client);

  void setServer(const char* host, const uint16_t port); // TODO: should be possible to pass IP address

  bool connect();
  
  // see about header in Reiamann docs http://riemann.io/howto.html#write-a-client
  pb_byte_t* lenghtHeader(size_t message_size);

  bool sendEvent(RiemannEventMsg event_msg);
};

#endif
