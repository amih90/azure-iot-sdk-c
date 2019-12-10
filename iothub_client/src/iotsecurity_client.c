#ifndef USE_SECURITY_MODULE
//trying to compile iotsecurity_client.c while the symbol USE_SECURITY_MODULE is not defined
#else

#include "azure_c_shared_utility/xlogging.h"
#include "azure_iot_security_sdk/client_core.h"
#include "azure_iot_security_sdk/message.h"
#include "iothub_device_client.h"
#include "iothub_message.h"
#include "iotsecurity_client.h"

struct IOTSECURITY_CLIENT_HANDLE_TAG {
    CLIENT_CORE_HANDLE client_core_handle;
    IOTHUB_DEVICE_CLIENT_HANDLE device_client_handle;
};

void IoTSecurityClient_EventConfirmationCallback(IOTHUB_CLIENT_CONFIRMATION_RESULT result, void* context);


IOTSECURITY_CLIENT_HANDLE IoTSecurityClient_Init(IOTHUB_DEVICE_CLIENT_HANDLE iothub_client_handle) {
    IOTSECURITY_CLIENT_HANDLE iotsecurity_client_handle = malloc(sizeof(IOTSECURITY_CLIENT_HANDLE));
    if (iotsecurity_client_handle == NULL) {
        LogError("Failed creating IoT Security Client");
        return iotsecurity_client_handle;
    }

    iotsecurity_client_handle->client_core_handle = ClientCore_Init();
    if (iotsecurity_client_handle->client_core_handle == NULL) {
        LogError("Failed creating IoT Security Client Core");

        IoTSecurityClient_Deinit(iotsecurity_client_handle);
        free(iotsecurity_client_handle);
    }
    iotsecurity_client_handle->device_client_handle = iothub_client_handle;

    return NULL;
}

IOTSECURITY_CLIENT_RESULT IoTSecurityClient_Collect(IOTSECURITY_CLIENT_HANDLE iotsecurity_client_handle) {
    IOTSECURITY_CLIENT_RESULT result = IOTSECURITY_CLIENT_RESULT_OK;
    CLIENT_CORE_RESULT client_core_result = CLIENT_CORE_RESULT_OK;

    client_core_result = ClientCore_Collect(iotsecurity_client_handle->client_core_handle);
    if (client_core_result != IOTSECURITY_CLIENT_RESULT_OK) {
        result = IOTSECURITY_CLIENT_RESULT_EXCEPTION;
    }

    return result;
}

IOTHUB_CLIENT_RESULT IoTSecurityClient_SendEventAsync(IOTSECURITY_CLIENT_HANDLE iotsecurity_client_handle) {
    MESSAGE message = ClientCore_GetMessage(iotsecurity_client_handle->client_core_handle);
    char* string;
    MESSAGE_RESULT result = Message_GetAsString(&string, message);
    IOTHUB_MESSAGE_HANDLE message_handle = IoTHubMessage_CreateFromString(string);
    IoTHubMessage_SetAsSecurityMessage(message_handle);
    // IOTHUB_CLIENT_RESULT iothub_client_result = IoTHubDeviceClient_SendEventAsync(iotsecurity_client_handle->device_client_handle, message_handle, IoTSecurityClient_EventConfirmationCallback, NULL);
}

void IoTSecurityClient_EventConfirmationCallback(IOTHUB_CLIENT_CONFIRMATION_RESULT result, void* context) {
    CLIENT_CORE_RESULT client_core_result = CLIENT_CORE_RESULT_OK;

    // FIXME map CLIENT_CORE_RESULT<-IOTHUB_CLIENT_CONFIRMATION_RESULT

    ClientCore_MessageConfirmationCallback(client_core_result, context);
}


IOTSECURITY_CLIENT_RESULT IoTSecurityClient_Deinit(IOTSECURITY_CLIENT_HANDLE iotsecurity_client_handle) {
    IOTSECURITY_CLIENT_RESULT client_result = IOTSECURITY_CLIENT_RESULT_OK;

    if (iotsecurity_client_handle != NULL) {
        if (iotsecurity_client_handle->client_core_handle != NULL) {
            free(iotsecurity_client_handle->client_core_handle);
            iotsecurity_client_handle->client_core_handle = NULL;
        }

        free(iotsecurity_client_handle);
        iotsecurity_client_handle = NULL;
    }

    return client_result;
}

#endif /* USE_SECURITY_MODULE */
