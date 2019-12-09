// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef USE_SECURITY_MODULE
//trying to compile iotsecurity_client.c while the symbol USE_SECURITY_MODULE is not defined
#else

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
#include "umock_c/umock_c_prod.h"

typedef enum IOTSECURITY_CLIENT_RESULT_TAG {
    IOTSECURITY_CLIENT_RESULT_OK = 0,
    IOTSECURITY_CLIENT_RESULT_EXCEPTION = 1,
    IOTSECURITY_CLIENT_RESULT_MEMORY_EXCEPTION = 2,
    IOTSECURITY_CLIENT_RESULT_NOT_SUPPORTED_EXCEPTION = 3
} IOTSECURITY_CLIENT_RESULT;

typedef struct IOTSECURITY_CLIENT_HANDLE_TAG* IOTSECURITY_CLIENT_HANDLE;

MOCKABLE_FUNCTION(, IOTSECURITY_CLIENT_HANDLE, IoTSecurityClient_Init, IOTHUB_DEVICE_CLIENT_HANDLE, iothub_client_handle);

MOCKABLE_FUNCTION(, IOTSECURITY_CLIENT_RESULT, IoTSecurityClient_Collect, IOTSECURITY_CLIENT_HANDLE, iotsecurity_client_handle);

MOCKABLE_FUNCTION(, IOTHUB_CLIENT_RESULT, IoTSecurityClient_SendEventAsync, IOTSECURITY_CLIENT_HANDLE, iotsecurity_client_handle);

MOCKABLE_FUNCTION(, IOTSECURITY_CLIENT_RESULT, IoTSecurityClient_Deinit, IOTSECURITY_CLIENT_HANDLE, iotsecurity_client_handle);

#ifdef __cplusplus
}
#endif

#endif /* IOTSECURITY_CLIENT_H */

#endif /* USE_SECURITY_MODULE */