/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: tl_message.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "tl_message.pb-c.h"
void   tflight_package__base_msg__init
                     (TflightPackage__BaseMsg         *message)
{
  static const TflightPackage__BaseMsg init_value = TFLIGHT_PACKAGE__BASE_MSG__INIT;
  *message = init_value;
}
size_t tflight_package__base_msg__get_packed_size
                     (const TflightPackage__BaseMsg *message)
{
  assert(message->base.descriptor == &tflight_package__base_msg__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t tflight_package__base_msg__pack
                     (const TflightPackage__BaseMsg *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &tflight_package__base_msg__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t tflight_package__base_msg__pack_to_buffer
                     (const TflightPackage__BaseMsg *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &tflight_package__base_msg__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
TflightPackage__BaseMsg *
       tflight_package__base_msg__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (TflightPackage__BaseMsg *)
     protobuf_c_message_unpack (&tflight_package__base_msg__descriptor,
                                allocator, len, data);
}
void   tflight_package__base_msg__free_unpacked
                     (TflightPackage__BaseMsg *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &tflight_package__base_msg__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   tflight_package__tfmessage__init
                     (TflightPackage__TFmessage         *message)
{
  static const TflightPackage__TFmessage init_value = TFLIGHT_PACKAGE__TFMESSAGE__INIT;
  *message = init_value;
}
size_t tflight_package__tfmessage__get_packed_size
                     (const TflightPackage__TFmessage *message)
{
  assert(message->base.descriptor == &tflight_package__tfmessage__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t tflight_package__tfmessage__pack
                     (const TflightPackage__TFmessage *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &tflight_package__tfmessage__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t tflight_package__tfmessage__pack_to_buffer
                     (const TflightPackage__TFmessage *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &tflight_package__tfmessage__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
TflightPackage__TFmessage *
       tflight_package__tfmessage__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (TflightPackage__TFmessage *)
     protobuf_c_message_unpack (&tflight_package__tfmessage__descriptor,
                                allocator, len, data);
}
void   tflight_package__tfmessage__free_unpacked
                     (TflightPackage__TFmessage *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &tflight_package__tfmessage__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   tflight_package__tflight_pb__init
                     (TflightPackage__TflightPB         *message)
{
  static const TflightPackage__TflightPB init_value = TFLIGHT_PACKAGE__TFLIGHT_PB__INIT;
  *message = init_value;
}
size_t tflight_package__tflight_pb__get_packed_size
                     (const TflightPackage__TflightPB *message)
{
  assert(message->base.descriptor == &tflight_package__tflight_pb__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t tflight_package__tflight_pb__pack
                     (const TflightPackage__TflightPB *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &tflight_package__tflight_pb__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t tflight_package__tflight_pb__pack_to_buffer
                     (const TflightPackage__TflightPB *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &tflight_package__tflight_pb__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
TflightPackage__TflightPB *
       tflight_package__tflight_pb__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (TflightPackage__TflightPB *)
     protobuf_c_message_unpack (&tflight_package__tflight_pb__descriptor,
                                allocator, len, data);
}
void   tflight_package__tflight_pb__free_unpacked
                     (TflightPackage__TflightPB *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &tflight_package__tflight_pb__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   tflight_package__cxssctrl_info__init
                     (TflightPackage__CXSSCtrlInfo         *message)
{
  static const TflightPackage__CXSSCtrlInfo init_value = TFLIGHT_PACKAGE__CXSSCTRL_INFO__INIT;
  *message = init_value;
}
size_t tflight_package__cxssctrl_info__get_packed_size
                     (const TflightPackage__CXSSCtrlInfo *message)
{
  assert(message->base.descriptor == &tflight_package__cxssctrl_info__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t tflight_package__cxssctrl_info__pack
                     (const TflightPackage__CXSSCtrlInfo *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &tflight_package__cxssctrl_info__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t tflight_package__cxssctrl_info__pack_to_buffer
                     (const TflightPackage__CXSSCtrlInfo *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &tflight_package__cxssctrl_info__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
TflightPackage__CXSSCtrlInfo *
       tflight_package__cxssctrl_info__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (TflightPackage__CXSSCtrlInfo *)
     protobuf_c_message_unpack (&tflight_package__cxssctrl_info__descriptor,
                                allocator, len, data);
}
void   tflight_package__cxssctrl_info__free_unpacked
                     (TflightPackage__CXSSCtrlInfo *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &tflight_package__cxssctrl_info__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   tflight_package__tflight_ctrl_info__init
                     (TflightPackage__TFLightCtrlInfo         *message)
{
  static const TflightPackage__TFLightCtrlInfo init_value = TFLIGHT_PACKAGE__TFLIGHT_CTRL_INFO__INIT;
  *message = init_value;
}
size_t tflight_package__tflight_ctrl_info__get_packed_size
                     (const TflightPackage__TFLightCtrlInfo *message)
{
  assert(message->base.descriptor == &tflight_package__tflight_ctrl_info__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t tflight_package__tflight_ctrl_info__pack
                     (const TflightPackage__TFLightCtrlInfo *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &tflight_package__tflight_ctrl_info__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t tflight_package__tflight_ctrl_info__pack_to_buffer
                     (const TflightPackage__TFLightCtrlInfo *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &tflight_package__tflight_ctrl_info__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
TflightPackage__TFLightCtrlInfo *
       tflight_package__tflight_ctrl_info__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (TflightPackage__TFLightCtrlInfo *)
     protobuf_c_message_unpack (&tflight_package__tflight_ctrl_info__descriptor,
                                allocator, len, data);
}
void   tflight_package__tflight_ctrl_info__free_unpacked
                     (TflightPackage__TFLightCtrlInfo *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &tflight_package__tflight_ctrl_info__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   tflight_package__serv_ctrl_info__init
                     (TflightPackage__ServCtrlInfo         *message)
{
  static const TflightPackage__ServCtrlInfo init_value = TFLIGHT_PACKAGE__SERV_CTRL_INFO__INIT;
  *message = init_value;
}
size_t tflight_package__serv_ctrl_info__get_packed_size
                     (const TflightPackage__ServCtrlInfo *message)
{
  assert(message->base.descriptor == &tflight_package__serv_ctrl_info__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t tflight_package__serv_ctrl_info__pack
                     (const TflightPackage__ServCtrlInfo *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &tflight_package__serv_ctrl_info__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t tflight_package__serv_ctrl_info__pack_to_buffer
                     (const TflightPackage__ServCtrlInfo *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &tflight_package__serv_ctrl_info__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
TflightPackage__ServCtrlInfo *
       tflight_package__serv_ctrl_info__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (TflightPackage__ServCtrlInfo *)
     protobuf_c_message_unpack (&tflight_package__serv_ctrl_info__descriptor,
                                allocator, len, data);
}
void   tflight_package__serv_ctrl_info__free_unpacked
                     (TflightPackage__ServCtrlInfo *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &tflight_package__serv_ctrl_info__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor tflight_package__base_msg__field_descriptors[1] =
{
  {
    "msg_type",
    1,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_ENUM,
    0,   /* quantifier_offset */
    offsetof(TflightPackage__BaseMsg, msg_type),
    &tflight_package__msg_type__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned tflight_package__base_msg__field_indices_by_name[] = {
  0,   /* field[0] = msg_type */
};
static const ProtobufCIntRange tflight_package__base_msg__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 1 }
};
const ProtobufCMessageDescriptor tflight_package__base_msg__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "tflightPackage.BaseMsg",
  "BaseMsg",
  "TflightPackage__BaseMsg",
  "tflightPackage",
  sizeof(TflightPackage__BaseMsg),
  1,
  tflight_package__base_msg__field_descriptors,
  tflight_package__base_msg__field_indices_by_name,
  1,  tflight_package__base_msg__number_ranges,
  (ProtobufCMessageInit) tflight_package__base_msg__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor tflight_package__tfmessage__field_descriptors[8] =
{
  {
    "stage",
    1,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(TflightPackage__TFmessage, stage),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "state",
    2,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(TflightPackage__TFmessage, state),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "time",
    3,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(TflightPackage__TFmessage, time),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "nextstate",
    4,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(TflightPackage__TFmessage, nextstate),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "nexttime",
    5,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(TflightPackage__TFmessage, nexttime),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "r_period",
    6,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(TflightPackage__TFmessage, r_period),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "g_period",
    7,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(TflightPackage__TFmessage, g_period),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "y_period",
    8,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(TflightPackage__TFmessage, y_period),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned tflight_package__tfmessage__field_indices_by_name[] = {
  6,   /* field[6] = g_period */
  3,   /* field[3] = nextstate */
  4,   /* field[4] = nexttime */
  5,   /* field[5] = r_period */
  0,   /* field[0] = stage */
  1,   /* field[1] = state */
  2,   /* field[2] = time */
  7,   /* field[7] = y_period */
};
static const ProtobufCIntRange tflight_package__tfmessage__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 8 }
};
const ProtobufCMessageDescriptor tflight_package__tfmessage__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "tflightPackage.TFmessage",
  "TFmessage",
  "TflightPackage__TFmessage",
  "tflightPackage",
  sizeof(TflightPackage__TFmessage),
  8,
  tflight_package__tfmessage__field_descriptors,
  tflight_package__tfmessage__field_indices_by_name,
  1,  tflight_package__tfmessage__number_ranges,
  (ProtobufCMessageInit) tflight_package__tfmessage__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor tflight_package__tflight_pb__field_descriptors[2] =
{
  {
    "msg_type",
    1,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_ENUM,
    0,   /* quantifier_offset */
    offsetof(TflightPackage__TflightPB, msg_type),
    &tflight_package__msg_type__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "TF",
    2,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_MESSAGE,
    offsetof(TflightPackage__TflightPB, n_tf),
    offsetof(TflightPackage__TflightPB, tf),
    &tflight_package__tfmessage__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned tflight_package__tflight_pb__field_indices_by_name[] = {
  1,   /* field[1] = TF */
  0,   /* field[0] = msg_type */
};
static const ProtobufCIntRange tflight_package__tflight_pb__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 2 }
};
const ProtobufCMessageDescriptor tflight_package__tflight_pb__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "tflightPackage.tflightPB",
  "TflightPB",
  "TflightPackage__TflightPB",
  "tflightPackage",
  sizeof(TflightPackage__TflightPB),
  2,
  tflight_package__tflight_pb__field_descriptors,
  tflight_package__tflight_pb__field_indices_by_name,
  1,  tflight_package__tflight_pb__number_ranges,
  (ProtobufCMessageInit) tflight_package__tflight_pb__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor tflight_package__cxssctrl_info__field_descriptors[9] =
{
  {
    "msg_type",
    1,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_ENUM,
    0,   /* quantifier_offset */
    offsetof(TflightPackage__CXSSCtrlInfo, msg_type),
    &tflight_package__msg_type__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "vehicle_priority_enable",
    2,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_BOOL,
    0,   /* quantifier_offset */
    offsetof(TflightPackage__CXSSCtrlInfo, vehicle_priority_enable),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "priority_rule",
    3,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(TflightPackage__CXSSCtrlInfo, priority_rule),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "curr_vehicle_phase",
    4,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(TflightPackage__CXSSCtrlInfo, curr_vehicle_phase),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "green_extend_time",
    5,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_UINT32,
    offsetof(TflightPackage__CXSSCtrlInfo, has_green_extend_time),
    offsetof(TflightPackage__CXSSCtrlInfo, green_extend_time),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "vehicle_passed_flag",
    6,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_BOOL,
    0,   /* quantifier_offset */
    offsetof(TflightPackage__CXSSCtrlInfo, vehicle_passed_flag),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "dst_status",
    7,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(TflightPackage__CXSSCtrlInfo, dst_status),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "next_green_time",
    8,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(TflightPackage__CXSSCtrlInfo, next_green_time),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "curr_green_time",
    9,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_UINT32,
    offsetof(TflightPackage__CXSSCtrlInfo, has_curr_green_time),
    offsetof(TflightPackage__CXSSCtrlInfo, curr_green_time),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned tflight_package__cxssctrl_info__field_indices_by_name[] = {
  8,   /* field[8] = curr_green_time */
  3,   /* field[3] = curr_vehicle_phase */
  6,   /* field[6] = dst_status */
  4,   /* field[4] = green_extend_time */
  0,   /* field[0] = msg_type */
  7,   /* field[7] = next_green_time */
  2,   /* field[2] = priority_rule */
  5,   /* field[5] = vehicle_passed_flag */
  1,   /* field[1] = vehicle_priority_enable */
};
static const ProtobufCIntRange tflight_package__cxssctrl_info__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 9 }
};
const ProtobufCMessageDescriptor tflight_package__cxssctrl_info__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "tflightPackage.CXSSCtrlInfo",
  "CXSSCtrlInfo",
  "TflightPackage__CXSSCtrlInfo",
  "tflightPackage",
  sizeof(TflightPackage__CXSSCtrlInfo),
  9,
  tflight_package__cxssctrl_info__field_descriptors,
  tflight_package__cxssctrl_info__field_indices_by_name,
  1,  tflight_package__cxssctrl_info__number_ranges,
  (ProtobufCMessageInit) tflight_package__cxssctrl_info__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor tflight_package__tflight_ctrl_info__field_descriptors[5] =
{
  {
    "msg_type",
    1,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_ENUM,
    0,   /* quantifier_offset */
    offsetof(TflightPackage__TFLightCtrlInfo, msg_type),
    &tflight_package__msg_type__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "curr_light_phase",
    2,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(TflightPackage__TFLightCtrlInfo, curr_light_phase),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "curr_light_state",
    3,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(TflightPackage__TFLightCtrlInfo, curr_light_state),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "curr_run_time",
    4,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(TflightPackage__TFLightCtrlInfo, curr_run_time),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "priority_ctrl_ongoing",
    5,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_BOOL,
    0,   /* quantifier_offset */
    offsetof(TflightPackage__TFLightCtrlInfo, priority_ctrl_ongoing),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned tflight_package__tflight_ctrl_info__field_indices_by_name[] = {
  1,   /* field[1] = curr_light_phase */
  2,   /* field[2] = curr_light_state */
  3,   /* field[3] = curr_run_time */
  0,   /* field[0] = msg_type */
  4,   /* field[4] = priority_ctrl_ongoing */
};
static const ProtobufCIntRange tflight_package__tflight_ctrl_info__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 5 }
};
const ProtobufCMessageDescriptor tflight_package__tflight_ctrl_info__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "tflightPackage.TFLightCtrlInfo",
  "TFLightCtrlInfo",
  "TflightPackage__TFLightCtrlInfo",
  "tflightPackage",
  sizeof(TflightPackage__TFLightCtrlInfo),
  5,
  tflight_package__tflight_ctrl_info__field_descriptors,
  tflight_package__tflight_ctrl_info__field_indices_by_name,
  1,  tflight_package__tflight_ctrl_info__number_ranges,
  (ProtobufCMessageInit) tflight_package__tflight_ctrl_info__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor tflight_package__serv_ctrl_info__field_descriptors[6] =
{
  {
    "msg_type",
    1,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_ENUM,
    0,   /* quantifier_offset */
    offsetof(TflightPackage__ServCtrlInfo, msg_type),
    &tflight_package__msg_type__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "mode",
    2,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(TflightPackage__ServCtrlInfo, mode),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "priority_rule",
    3,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(TflightPackage__ServCtrlInfo, priority_rule),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "curr_vehicle_phase",
    4,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(TflightPackage__ServCtrlInfo, curr_vehicle_phase),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "green_extend_time",
    5,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_UINT32,
    offsetof(TflightPackage__ServCtrlInfo, has_green_extend_time),
    offsetof(TflightPackage__ServCtrlInfo, green_extend_time),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "restore_phase",
    6,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_UINT32,
    offsetof(TflightPackage__ServCtrlInfo, has_restore_phase),
    offsetof(TflightPackage__ServCtrlInfo, restore_phase),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned tflight_package__serv_ctrl_info__field_indices_by_name[] = {
  3,   /* field[3] = curr_vehicle_phase */
  4,   /* field[4] = green_extend_time */
  1,   /* field[1] = mode */
  0,   /* field[0] = msg_type */
  2,   /* field[2] = priority_rule */
  5,   /* field[5] = restore_phase */
};
static const ProtobufCIntRange tflight_package__serv_ctrl_info__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 6 }
};
const ProtobufCMessageDescriptor tflight_package__serv_ctrl_info__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "tflightPackage.ServCtrlInfo",
  "ServCtrlInfo",
  "TflightPackage__ServCtrlInfo",
  "tflightPackage",
  sizeof(TflightPackage__ServCtrlInfo),
  6,
  tflight_package__serv_ctrl_info__field_descriptors,
  tflight_package__serv_ctrl_info__field_indices_by_name,
  1,  tflight_package__serv_ctrl_info__number_ranges,
  (ProtobufCMessageInit) tflight_package__serv_ctrl_info__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCEnumValue tflight_package__msg_type__enum_values_by_number[4] =
{
  { "tflightPBType", "TFLIGHT_PACKAGE__MSG_TYPE__tflightPBType", 0 },
  { "CXSSCtrlInfoType", "TFLIGHT_PACKAGE__MSG_TYPE__CXSSCtrlInfoType", 1 },
  { "TFLightCtrlInfoType", "TFLIGHT_PACKAGE__MSG_TYPE__TFLightCtrlInfoType", 2 },
  { "ServCtrlInfoType", "TFLIGHT_PACKAGE__MSG_TYPE__ServCtrlInfoType", 3 },
};
static const ProtobufCIntRange tflight_package__msg_type__value_ranges[] = {
{0, 0},{0, 4}
};
static const ProtobufCEnumValueIndex tflight_package__msg_type__enum_values_by_name[4] =
{
  { "CXSSCtrlInfoType", 1 },
  { "ServCtrlInfoType", 3 },
  { "TFLightCtrlInfoType", 2 },
  { "tflightPBType", 0 },
};
const ProtobufCEnumDescriptor tflight_package__msg_type__descriptor =
{
  PROTOBUF_C__ENUM_DESCRIPTOR_MAGIC,
  "tflightPackage.MsgType",
  "MsgType",
  "TflightPackage__MsgType",
  "tflightPackage",
  4,
  tflight_package__msg_type__enum_values_by_number,
  4,
  tflight_package__msg_type__enum_values_by_name,
  1,
  tflight_package__msg_type__value_ranges,
  NULL,NULL,NULL,NULL   /* reserved[1234] */
};
