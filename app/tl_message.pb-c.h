/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: tl_message.proto */

#ifndef PROTOBUF_C_tl_5fmessage_2eproto__INCLUDED
#define PROTOBUF_C_tl_5fmessage_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1000000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1003001 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif


typedef struct _TflightPackage__BaseMsg TflightPackage__BaseMsg;
typedef struct _TflightPackage__TFmessage TflightPackage__TFmessage;
typedef struct _TflightPackage__TflightPB TflightPackage__TflightPB;
typedef struct _TflightPackage__TSPCtrlInfo TflightPackage__TSPCtrlInfo;
typedef struct _TflightPackage__DSTCtrlInfo TflightPackage__DSTCtrlInfo;
typedef struct _TflightPackage__TFLightCtrlInfo TflightPackage__TFLightCtrlInfo;
typedef struct _TflightPackage__ServCtrlInfo TflightPackage__ServCtrlInfo;


/* --- enums --- */

typedef enum _TflightPackage__MsgType {
  TFLIGHT_PACKAGE__MSG_TYPE__tflightPBType = 0,
  TFLIGHT_PACKAGE__MSG_TYPE__TSPCtrlInfoType = 1,
  TFLIGHT_PACKAGE__MSG_TYPE__DSTCtrlInfoType = 2,
  TFLIGHT_PACKAGE__MSG_TYPE__TFLightCtrlInfoType = 3,
  TFLIGHT_PACKAGE__MSG_TYPE__ServCtrlInfoType = 4
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(TFLIGHT_PACKAGE__MSG_TYPE)
} TflightPackage__MsgType;

/* --- messages --- */

struct  _TflightPackage__BaseMsg
{
  ProtobufCMessage base;
  TflightPackage__MsgType msg_type;
};
#define TFLIGHT_PACKAGE__BASE_MSG__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&tflight_package__base_msg__descriptor) \
    , TFLIGHT_PACKAGE__MSG_TYPE__tflightPBType }


struct  _TflightPackage__TFmessage
{
  ProtobufCMessage base;
  uint32_t stage;
  uint32_t state;
  uint32_t time;
  uint32_t nextstate;
  uint32_t nexttime;
  uint32_t r_period;
  uint32_t g_period;
  uint32_t y_period;
};
#define TFLIGHT_PACKAGE__TFMESSAGE__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&tflight_package__tfmessage__descriptor) \
    , 0, 0, 0, 0, 0, 0, 0, 0 }


struct  _TflightPackage__TflightPB
{
  ProtobufCMessage base;
  TflightPackage__MsgType msg_type;
  size_t n_tf;
  TflightPackage__TFmessage **tf;
};
#define TFLIGHT_PACKAGE__TFLIGHT_PB__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&tflight_package__tflight_pb__descriptor) \
    , TFLIGHT_PACKAGE__MSG_TYPE__tflightPBType, 0,NULL }


struct  _TflightPackage__TSPCtrlInfo
{
  ProtobufCMessage base;
  TflightPackage__MsgType msg_type;
  protobuf_c_boolean vehicle_priority_enable;
  uint32_t priority_rule;
  uint32_t curr_vehicle_phase;
  protobuf_c_boolean has_green_extend_time;
  uint32_t green_extend_time;
  protobuf_c_boolean vehicle_passed_flag;
};
#define TFLIGHT_PACKAGE__TSPCTRL_INFO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&tflight_package__tspctrl_info__descriptor) \
    , TFLIGHT_PACKAGE__MSG_TYPE__tflightPBType, 0, 0, 0, 0, 0, 0 }


struct  _TflightPackage__DSTCtrlInfo
{
  ProtobufCMessage base;
  TflightPackage__MsgType msg_type;
  uint32_t dst_status;
  size_t n_green_time_init;
  uint32_t *green_time_init;
  protobuf_c_boolean has_curr_green_time;
  uint32_t curr_green_time;
};
#define TFLIGHT_PACKAGE__DSTCTRL_INFO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&tflight_package__dstctrl_info__descriptor) \
    , TFLIGHT_PACKAGE__MSG_TYPE__tflightPBType, 0, 0,NULL, 0, 0 }


struct  _TflightPackage__TFLightCtrlInfo
{
  ProtobufCMessage base;
  TflightPackage__MsgType msg_type;
  uint32_t curr_light_phase;
  uint32_t curr_light_state;
  uint32_t curr_run_time;
  protobuf_c_boolean priority_ctrl_ongoing;
};
#define TFLIGHT_PACKAGE__TFLIGHT_CTRL_INFO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&tflight_package__tflight_ctrl_info__descriptor) \
    , TFLIGHT_PACKAGE__MSG_TYPE__tflightPBType, 0, 0, 0, 0 }


struct  _TflightPackage__ServCtrlInfo
{
  ProtobufCMessage base;
  TflightPackage__MsgType msg_type;
  /*
   *normal, TSP, DST
   */
  uint32_t mode;
  /*
   *control mode
   */
  uint32_t priority_rule;
  /*
   *current phase
   */
  uint32_t curr_vehicle_phase;
  /*
   *green delay
   */
  protobuf_c_boolean has_green_extend_time;
  uint32_t green_extend_time;
  /*
   *restore phase
   */
  protobuf_c_boolean has_restore_phase;
  uint32_t restore_phase;
};
#define TFLIGHT_PACKAGE__SERV_CTRL_INFO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&tflight_package__serv_ctrl_info__descriptor) \
    , TFLIGHT_PACKAGE__MSG_TYPE__tflightPBType, 0, 0, 0, 0, 0, 0, 0 }


/* TflightPackage__BaseMsg methods */
void   tflight_package__base_msg__init
                     (TflightPackage__BaseMsg         *message);
size_t tflight_package__base_msg__get_packed_size
                     (const TflightPackage__BaseMsg   *message);
size_t tflight_package__base_msg__pack
                     (const TflightPackage__BaseMsg   *message,
                      uint8_t             *out);
size_t tflight_package__base_msg__pack_to_buffer
                     (const TflightPackage__BaseMsg   *message,
                      ProtobufCBuffer     *buffer);
TflightPackage__BaseMsg *
       tflight_package__base_msg__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   tflight_package__base_msg__free_unpacked
                     (TflightPackage__BaseMsg *message,
                      ProtobufCAllocator *allocator);
/* TflightPackage__TFmessage methods */
void   tflight_package__tfmessage__init
                     (TflightPackage__TFmessage         *message);
size_t tflight_package__tfmessage__get_packed_size
                     (const TflightPackage__TFmessage   *message);
size_t tflight_package__tfmessage__pack
                     (const TflightPackage__TFmessage   *message,
                      uint8_t             *out);
size_t tflight_package__tfmessage__pack_to_buffer
                     (const TflightPackage__TFmessage   *message,
                      ProtobufCBuffer     *buffer);
TflightPackage__TFmessage *
       tflight_package__tfmessage__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   tflight_package__tfmessage__free_unpacked
                     (TflightPackage__TFmessage *message,
                      ProtobufCAllocator *allocator);
/* TflightPackage__TflightPB methods */
void   tflight_package__tflight_pb__init
                     (TflightPackage__TflightPB         *message);
size_t tflight_package__tflight_pb__get_packed_size
                     (const TflightPackage__TflightPB   *message);
size_t tflight_package__tflight_pb__pack
                     (const TflightPackage__TflightPB   *message,
                      uint8_t             *out);
size_t tflight_package__tflight_pb__pack_to_buffer
                     (const TflightPackage__TflightPB   *message,
                      ProtobufCBuffer     *buffer);
TflightPackage__TflightPB *
       tflight_package__tflight_pb__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   tflight_package__tflight_pb__free_unpacked
                     (TflightPackage__TflightPB *message,
                      ProtobufCAllocator *allocator);
/* TflightPackage__TSPCtrlInfo methods */
void   tflight_package__tspctrl_info__init
                     (TflightPackage__TSPCtrlInfo         *message);
size_t tflight_package__tspctrl_info__get_packed_size
                     (const TflightPackage__TSPCtrlInfo   *message);
size_t tflight_package__tspctrl_info__pack
                     (const TflightPackage__TSPCtrlInfo   *message,
                      uint8_t             *out);
size_t tflight_package__tspctrl_info__pack_to_buffer
                     (const TflightPackage__TSPCtrlInfo   *message,
                      ProtobufCBuffer     *buffer);
TflightPackage__TSPCtrlInfo *
       tflight_package__tspctrl_info__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   tflight_package__tspctrl_info__free_unpacked
                     (TflightPackage__TSPCtrlInfo *message,
                      ProtobufCAllocator *allocator);
/* TflightPackage__DSTCtrlInfo methods */
void   tflight_package__dstctrl_info__init
                     (TflightPackage__DSTCtrlInfo         *message);
size_t tflight_package__dstctrl_info__get_packed_size
                     (const TflightPackage__DSTCtrlInfo   *message);
size_t tflight_package__dstctrl_info__pack
                     (const TflightPackage__DSTCtrlInfo   *message,
                      uint8_t             *out);
size_t tflight_package__dstctrl_info__pack_to_buffer
                     (const TflightPackage__DSTCtrlInfo   *message,
                      ProtobufCBuffer     *buffer);
TflightPackage__DSTCtrlInfo *
       tflight_package__dstctrl_info__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   tflight_package__dstctrl_info__free_unpacked
                     (TflightPackage__DSTCtrlInfo *message,
                      ProtobufCAllocator *allocator);
/* TflightPackage__TFLightCtrlInfo methods */
void   tflight_package__tflight_ctrl_info__init
                     (TflightPackage__TFLightCtrlInfo         *message);
size_t tflight_package__tflight_ctrl_info__get_packed_size
                     (const TflightPackage__TFLightCtrlInfo   *message);
size_t tflight_package__tflight_ctrl_info__pack
                     (const TflightPackage__TFLightCtrlInfo   *message,
                      uint8_t             *out);
size_t tflight_package__tflight_ctrl_info__pack_to_buffer
                     (const TflightPackage__TFLightCtrlInfo   *message,
                      ProtobufCBuffer     *buffer);
TflightPackage__TFLightCtrlInfo *
       tflight_package__tflight_ctrl_info__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   tflight_package__tflight_ctrl_info__free_unpacked
                     (TflightPackage__TFLightCtrlInfo *message,
                      ProtobufCAllocator *allocator);
/* TflightPackage__ServCtrlInfo methods */
void   tflight_package__serv_ctrl_info__init
                     (TflightPackage__ServCtrlInfo         *message);
size_t tflight_package__serv_ctrl_info__get_packed_size
                     (const TflightPackage__ServCtrlInfo   *message);
size_t tflight_package__serv_ctrl_info__pack
                     (const TflightPackage__ServCtrlInfo   *message,
                      uint8_t             *out);
size_t tflight_package__serv_ctrl_info__pack_to_buffer
                     (const TflightPackage__ServCtrlInfo   *message,
                      ProtobufCBuffer     *buffer);
TflightPackage__ServCtrlInfo *
       tflight_package__serv_ctrl_info__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   tflight_package__serv_ctrl_info__free_unpacked
                     (TflightPackage__ServCtrlInfo *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*TflightPackage__BaseMsg_Closure)
                 (const TflightPackage__BaseMsg *message,
                  void *closure_data);
typedef void (*TflightPackage__TFmessage_Closure)
                 (const TflightPackage__TFmessage *message,
                  void *closure_data);
typedef void (*TflightPackage__TflightPB_Closure)
                 (const TflightPackage__TflightPB *message,
                  void *closure_data);
typedef void (*TflightPackage__TSPCtrlInfo_Closure)
                 (const TflightPackage__TSPCtrlInfo *message,
                  void *closure_data);
typedef void (*TflightPackage__DSTCtrlInfo_Closure)
                 (const TflightPackage__DSTCtrlInfo *message,
                  void *closure_data);
typedef void (*TflightPackage__TFLightCtrlInfo_Closure)
                 (const TflightPackage__TFLightCtrlInfo *message,
                  void *closure_data);
typedef void (*TflightPackage__ServCtrlInfo_Closure)
                 (const TflightPackage__ServCtrlInfo *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCEnumDescriptor    tflight_package__msg_type__descriptor;
extern const ProtobufCMessageDescriptor tflight_package__base_msg__descriptor;
extern const ProtobufCMessageDescriptor tflight_package__tfmessage__descriptor;
extern const ProtobufCMessageDescriptor tflight_package__tflight_pb__descriptor;
extern const ProtobufCMessageDescriptor tflight_package__tspctrl_info__descriptor;
extern const ProtobufCMessageDescriptor tflight_package__dstctrl_info__descriptor;
extern const ProtobufCMessageDescriptor tflight_package__tflight_ctrl_info__descriptor;
extern const ProtobufCMessageDescriptor tflight_package__serv_ctrl_info__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_tl_5fmessage_2eproto__INCLUDED */
