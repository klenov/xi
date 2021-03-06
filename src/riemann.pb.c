/* Automatically generated nanopb constant definitions */
/* Generated by nanopb-0.3.6 at Sat Oct  1 22:01:56 2016. */

#include "riemann.pb.h"

/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif



const pb_field_t RiemannState_fields[9] = {
    PB_FIELD(  1, INT64   , OPTIONAL, STATIC  , FIRST, RiemannState, time, time, 0),
    PB_FIELD(  2, STRING  , OPTIONAL, CALLBACK, OTHER, RiemannState, state, time, 0),
    PB_FIELD(  3, STRING  , OPTIONAL, CALLBACK, OTHER, RiemannState, service, state, 0),
    PB_FIELD(  4, STRING  , OPTIONAL, CALLBACK, OTHER, RiemannState, host, service, 0),
    PB_FIELD(  5, STRING  , OPTIONAL, CALLBACK, OTHER, RiemannState, description, host, 0),
    PB_FIELD(  6, BOOL    , OPTIONAL, STATIC  , OTHER, RiemannState, once, description, 0),
    PB_FIELD(  7, STRING  , REPEATED, CALLBACK, OTHER, RiemannState, tags, once, 0),
    PB_FIELD(  8, FLOAT   , OPTIONAL, STATIC  , OTHER, RiemannState, ttl, tags, 0),
    PB_LAST_FIELD
};

const pb_field_t RiemannEvent_fields[12] = {
    PB_FIELD(  1, INT64   , OPTIONAL, STATIC  , FIRST, RiemannEvent, time, time, 0),
    PB_FIELD(  2, STRING  , OPTIONAL, CALLBACK, OTHER, RiemannEvent, state, time, 0),
    PB_FIELD(  3, STRING  , OPTIONAL, CALLBACK, OTHER, RiemannEvent, service, state, 0),
    PB_FIELD(  4, STRING  , OPTIONAL, CALLBACK, OTHER, RiemannEvent, host, service, 0),
    PB_FIELD(  5, STRING  , OPTIONAL, CALLBACK, OTHER, RiemannEvent, description, host, 0),
    PB_FIELD(  7, STRING  , REPEATED, CALLBACK, OTHER, RiemannEvent, tags, description, 0),
    PB_FIELD(  8, FLOAT   , OPTIONAL, STATIC  , OTHER, RiemannEvent, ttl, tags, 0),
    PB_FIELD(  9, MESSAGE , REPEATED, CALLBACK, OTHER, RiemannEvent, attributes, ttl, &RiemannAttribute_fields),
    PB_FIELD( 13, SINT64  , OPTIONAL, STATIC  , OTHER, RiemannEvent, metric_sint64, attributes, 0),
    PB_FIELD( 14, DOUBLE  , OPTIONAL, STATIC  , OTHER, RiemannEvent, metric_d, metric_sint64, 0),
    PB_FIELD( 15, FLOAT   , OPTIONAL, STATIC  , OTHER, RiemannEvent, metric_f, metric_d, 0),
    PB_LAST_FIELD
};

const pb_field_t RiemannQuery_fields[2] = {
    PB_FIELD(  1, STRING  , OPTIONAL, CALLBACK, FIRST, RiemannQuery, string, string, 0),
    PB_LAST_FIELD
};

const pb_field_t RiemannMsg_fields[6] = {
    PB_FIELD(  2, BOOL    , OPTIONAL, STATIC  , FIRST, RiemannMsg, ok, ok, 0),
    PB_FIELD(  3, STRING  , OPTIONAL, CALLBACK, OTHER, RiemannMsg, error, ok, 0),
    PB_FIELD(  4, MESSAGE , REPEATED, CALLBACK, OTHER, RiemannMsg, states, error, &RiemannState_fields),
    PB_FIELD(  5, MESSAGE , OPTIONAL, STATIC  , OTHER, RiemannMsg, query, states, &RiemannQuery_fields),
    PB_FIELD(  6, MESSAGE , REPEATED, CALLBACK, OTHER, RiemannMsg, events, query, &RiemannEvent_fields),
    PB_LAST_FIELD
};

const pb_field_t RiemannAttribute_fields[3] = {
    PB_FIELD(  1, STRING  , REQUIRED, CALLBACK, FIRST, RiemannAttribute, key, key, 0),
    PB_FIELD(  2, STRING  , OPTIONAL, CALLBACK, OTHER, RiemannAttribute, value, key, 0),
    PB_LAST_FIELD
};


/* Check that field information fits in pb_field_t */
#if !defined(PB_FIELD_32BIT)
/* If you get an error here, it means that you need to define PB_FIELD_32BIT
 * compile-time option. You can do that in pb.h or on compiler command line.
 * 
 * The reason you need to do this is that some of your messages contain tag
 * numbers or field sizes that are larger than what can fit in 8 or 16 bit
 * field descriptors.
 */
PB_STATIC_ASSERT((pb_membersize(RiemannEvent, attributes) < 65536 && pb_membersize(RiemannMsg, states) < 65536 && pb_membersize(RiemannMsg, query) < 65536 && pb_membersize(RiemannMsg, events) < 65536), YOU_MUST_DEFINE_PB_FIELD_32BIT_FOR_MESSAGES_RiemannState_RiemannEvent_RiemannQuery_RiemannMsg_RiemannAttribute)
#endif

#if !defined(PB_FIELD_16BIT) && !defined(PB_FIELD_32BIT)
/* If you get an error here, it means that you need to define PB_FIELD_16BIT
 * compile-time option. You can do that in pb.h or on compiler command line.
 * 
 * The reason you need to do this is that some of your messages contain tag
 * numbers or field sizes that are larger than what can fit in the default
 * 8 bit descriptors.
 */
PB_STATIC_ASSERT((pb_membersize(RiemannEvent, attributes) < 256 && pb_membersize(RiemannMsg, states) < 256 && pb_membersize(RiemannMsg, query) < 256 && pb_membersize(RiemannMsg, events) < 256), YOU_MUST_DEFINE_PB_FIELD_16BIT_FOR_MESSAGES_RiemannState_RiemannEvent_RiemannQuery_RiemannMsg_RiemannAttribute)
#endif


/* On some platforms (such as AVR), double is really float.
 * These are not directly supported by nanopb, but see example_avr_double.
 * To get rid of this error, remove any double fields from your .proto.
 */
PB_STATIC_ASSERT(sizeof(double) == 8, DOUBLE_MUST_BE_8_BYTES)

/* @@protoc_insertion_point(eof) */
