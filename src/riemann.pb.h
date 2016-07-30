/* Automatically generated nanopb header */
/* Generated by nanopb-0.3.6 at Wed Jul 27 21:42:12 2016. */

#ifndef PB_RIEMANN_PB_H_INCLUDED
#define PB_RIEMANN_PB_H_INCLUDED
#include "nanopb/pb.h"

/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Struct definitions */
typedef struct _Attribute {
    pb_callback_t key;
    pb_callback_t value;
/* @@protoc_insertion_point(struct:Attribute) */
} Attribute;

typedef struct _Query {
    pb_callback_t string;
/* @@protoc_insertion_point(struct:Query) */
} Query;

typedef struct _Event {
    bool has_time;
    int64_t time;
    pb_callback_t state;
    pb_callback_t service;
    pb_callback_t host;
    pb_callback_t description;
    pb_callback_t tags;
    bool has_ttl;
    float ttl;
    pb_callback_t attributes;
    bool has_metric_sint64;
    int64_t metric_sint64;
    bool has_metric_d;
    double metric_d;
    bool has_metric_f;
    float metric_f;
/* @@protoc_insertion_point(struct:Event) */
} Event;

typedef struct _Msg {
    bool has_ok;
    bool ok;
    pb_callback_t error;
    pb_callback_t states;
    bool has_query;
    Query query;
    pb_callback_t events;
/* @@protoc_insertion_point(struct:Msg) */
} Msg;

typedef struct _State {
    bool has_time;
    int64_t time;
    pb_callback_t state;
    pb_callback_t service;
    pb_callback_t host;
    pb_callback_t description;
    bool has_once;
    bool once;
    pb_callback_t tags;
    bool has_ttl;
    float ttl;
/* @@protoc_insertion_point(struct:State) */
} State;

/* Default values for struct fields */

/* Initializer values for message structs */
#define State_init_default                       {false, 0, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, false, 0, {{NULL}, NULL}, false, 0}
#define Event_init_default                       {false, 0, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, false, 0, {{NULL}, NULL}, false, 0, false, 0, false, 0}
#define Query_init_default                       {{{NULL}, NULL}}
#define Msg_init_default                         {false, 0, {{NULL}, NULL}, {{NULL}, NULL}, false, Query_init_default, {{NULL}, NULL}}
#define Attribute_init_default                   {{{NULL}, NULL}, {{NULL}, NULL}}
#define State_init_zero                          {false, 0, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, false, 0, {{NULL}, NULL}, false, 0}
#define Event_init_zero                          {false, 0, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, false, 0, {{NULL}, NULL}, false, 0, false, 0, false, 0}
#define Query_init_zero                          {{{NULL}, NULL}}
#define Msg_init_zero                            {false, 0, {{NULL}, NULL}, {{NULL}, NULL}, false, Query_init_zero, {{NULL}, NULL}}
#define Attribute_init_zero                      {{{NULL}, NULL}, {{NULL}, NULL}}

/* Field tags (for use in manual encoding/decoding) */
#define Attribute_key_tag                        1
#define Attribute_value_tag                      2
#define Query_string_tag                         1
#define Event_time_tag                           1
#define Event_state_tag                          2
#define Event_service_tag                        3
#define Event_host_tag                           4
#define Event_description_tag                    5
#define Event_tags_tag                           7
#define Event_ttl_tag                            8
#define Event_attributes_tag                     9
#define Event_metric_sint64_tag                  13
#define Event_metric_d_tag                       14
#define Event_metric_f_tag                       15
#define Msg_ok_tag                               2
#define Msg_error_tag                            3
#define Msg_states_tag                           4
#define Msg_query_tag                            5
#define Msg_events_tag                           6
#define State_time_tag                           1
#define State_state_tag                          2
#define State_service_tag                        3
#define State_host_tag                           4
#define State_description_tag                    5
#define State_once_tag                           6
#define State_tags_tag                           7
#define State_ttl_tag                            8

/* Struct field encoding specification for nanopb */
extern const pb_field_t State_fields[9];
extern const pb_field_t Event_fields[12];
extern const pb_field_t Query_fields[2];
extern const pb_field_t Msg_fields[6];
extern const pb_field_t Attribute_fields[3];

/* Maximum encoded size of messages (where known) */
/* State_size depends on runtime parameters */
/* Event_size depends on runtime parameters */
/* Query_size depends on runtime parameters */
/* Msg_size depends on runtime parameters */
/* Attribute_size depends on runtime parameters */

/* Message IDs (where set with "msgid" option) */
#ifdef PB_MSGID

#define RIEMANN_MESSAGES \


#endif

#ifdef __cplusplus
} /* extern "C" */
#endif
/* @@protoc_insertion_point(eof) */

#endif
