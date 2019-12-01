// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef IOTSECURITY_CLIENT_H
#define IOTSECURITY_CLIENT_H

#ifdef __cplusplus
extern "C"
{
#else
#endif

#include "iothub_device_client.h"
#include "iothub_message.h"
#include "parson.h"


typedef enum IOTSECURITY_CLIENT_RESULT_TAG {
    IOTSECURITY_CLIENT_RESULT_OK = 0,
    IOTSECURITY_CLIENT_RESULT_EXCEPTION = 1,
    IOTSECURITY_CLIENT_RESULT_MEMORY_EXCEPTION = 2,
    IOTSECURITY_CLIENT_RESULT_NOT_SUPPORTED_EXCEPTION = 3
} IOTSECURITY_CLIENT_RESULT;


MOCKABLE_FUNCTION(, IOTSECURITY_CLIENT_RESULT, IoTSecurityClient_Collect, IOTHUB_MESSAGE_HANDLE*, message_handle);

MOCKABLE_FUNCTION(, IOTHUB_CLIENT_RESULT, IoTSecurityClient_SendEventAsync, IOTHUB_DEVICE_CLIENT_HANDLE, iotHubClientHandle, IOTHUB_MESSAGE_HANDLE, eventMessageHandle, IOTHUB_CLIENT_EVENT_CONFIRMATION_CALLBACK, eventConfirmationCallback, void*, userContextCallback);


#ifdef __cplusplus
}
#endif

#endif /* IOTSECURITY_CLIENT_H */
