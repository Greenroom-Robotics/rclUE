// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from ue_msgs:srv/SetInt32.idl
// generated code does not contain a copyright notice

#ifndef UE_MSGS__SRV__DETAIL__SET_INT32__FUNCTIONS_H_
#define UE_MSGS__SRV__DETAIL__SET_INT32__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "ue_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "ue_msgs/srv/detail/set_int32__struct.h"

/// Initialize srv/SetInt32 message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * ue_msgs__srv__SetInt32_Request
 * )) before or use
 * ue_msgs__srv__SetInt32_Request__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_ue_msgs
bool
ue_msgs__srv__SetInt32_Request__init(ue_msgs__srv__SetInt32_Request * msg);

/// Finalize srv/SetInt32 message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ue_msgs
void
ue_msgs__srv__SetInt32_Request__fini(ue_msgs__srv__SetInt32_Request * msg);

/// Create srv/SetInt32 message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * ue_msgs__srv__SetInt32_Request__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_ue_msgs
ue_msgs__srv__SetInt32_Request *
ue_msgs__srv__SetInt32_Request__create();

/// Destroy srv/SetInt32 message.
/**
 * It calls
 * ue_msgs__srv__SetInt32_Request__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ue_msgs
void
ue_msgs__srv__SetInt32_Request__destroy(ue_msgs__srv__SetInt32_Request * msg);


/// Initialize array of srv/SetInt32 messages.
/**
 * It allocates the memory for the number of elements and calls
 * ue_msgs__srv__SetInt32_Request__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_ue_msgs
bool
ue_msgs__srv__SetInt32_Request__Sequence__init(ue_msgs__srv__SetInt32_Request__Sequence * array, size_t size);

/// Finalize array of srv/SetInt32 messages.
/**
 * It calls
 * ue_msgs__srv__SetInt32_Request__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ue_msgs
void
ue_msgs__srv__SetInt32_Request__Sequence__fini(ue_msgs__srv__SetInt32_Request__Sequence * array);

/// Create array of srv/SetInt32 messages.
/**
 * It allocates the memory for the array and calls
 * ue_msgs__srv__SetInt32_Request__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_ue_msgs
ue_msgs__srv__SetInt32_Request__Sequence *
ue_msgs__srv__SetInt32_Request__Sequence__create(size_t size);

/// Destroy array of srv/SetInt32 messages.
/**
 * It calls
 * ue_msgs__srv__SetInt32_Request__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ue_msgs
void
ue_msgs__srv__SetInt32_Request__Sequence__destroy(ue_msgs__srv__SetInt32_Request__Sequence * array);

/// Initialize srv/SetInt32 message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * ue_msgs__srv__SetInt32_Response
 * )) before or use
 * ue_msgs__srv__SetInt32_Response__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_ue_msgs
bool
ue_msgs__srv__SetInt32_Response__init(ue_msgs__srv__SetInt32_Response * msg);

/// Finalize srv/SetInt32 message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ue_msgs
void
ue_msgs__srv__SetInt32_Response__fini(ue_msgs__srv__SetInt32_Response * msg);

/// Create srv/SetInt32 message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * ue_msgs__srv__SetInt32_Response__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_ue_msgs
ue_msgs__srv__SetInt32_Response *
ue_msgs__srv__SetInt32_Response__create();

/// Destroy srv/SetInt32 message.
/**
 * It calls
 * ue_msgs__srv__SetInt32_Response__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ue_msgs
void
ue_msgs__srv__SetInt32_Response__destroy(ue_msgs__srv__SetInt32_Response * msg);


/// Initialize array of srv/SetInt32 messages.
/**
 * It allocates the memory for the number of elements and calls
 * ue_msgs__srv__SetInt32_Response__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_ue_msgs
bool
ue_msgs__srv__SetInt32_Response__Sequence__init(ue_msgs__srv__SetInt32_Response__Sequence * array, size_t size);

/// Finalize array of srv/SetInt32 messages.
/**
 * It calls
 * ue_msgs__srv__SetInt32_Response__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ue_msgs
void
ue_msgs__srv__SetInt32_Response__Sequence__fini(ue_msgs__srv__SetInt32_Response__Sequence * array);

/// Create array of srv/SetInt32 messages.
/**
 * It allocates the memory for the array and calls
 * ue_msgs__srv__SetInt32_Response__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_ue_msgs
ue_msgs__srv__SetInt32_Response__Sequence *
ue_msgs__srv__SetInt32_Response__Sequence__create(size_t size);

/// Destroy array of srv/SetInt32 messages.
/**
 * It calls
 * ue_msgs__srv__SetInt32_Response__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ue_msgs
void
ue_msgs__srv__SetInt32_Response__Sequence__destroy(ue_msgs__srv__SetInt32_Response__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // UE_MSGS__SRV__DETAIL__SET_INT32__FUNCTIONS_H_
