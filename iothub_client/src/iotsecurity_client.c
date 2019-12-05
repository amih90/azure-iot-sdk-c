#include "client_core.h"
#include "message.h"
#include "iotsecurity_client.h"
#include "iothub_device_client.h"
#include "iothub_message.h"

struct IOTSECURITY_CLIENT_HANDLE_TAG {
    CLIENT_CORE_HANDLE client_core_handle;
    IOTHUB_DEVICE_CLIENT_HANDLE device_client_handle;
};


IOTSECURITY_CLIENT_HANDLE IoTSecurityClient_Init(IOTHUB_DEVICE_CLIENT_HANDLE iothub_client_handle) {
    IOTSECURITY_CLIENT_HANDLE result = malloc(sizeof(IOTSECURITY_CLIENT_HANDLE));
    result->device_client_handle = iothub_client_handle;
    result->client_core_handle = ClientCore_Init(IoTSecurityClient_SendMessageCallback);
    return result;
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
    IoTHubDeviceClient_SendEventAsync(iotsecurity_client_handle->device_client_handle, message_handle, IoTSecurityClient_EventConfirmationCallback, NULL);

}

IOTSECURITY_CLIENT_RESULT IoTSecurityClient_Deinit() {

}

CLIENT_CORE_RESULT IoTSecurityClient_SendMessageCallback(const char* message) {
}

void IoTSecurityClient_EventConfirmationCallback(IOTHUB_CLIENT_CONFIRMATION_RESULT result, void* context) {
    CLIENT_CORE_RESULT result = CLIENT_CORE_RESULT_OK;
    ClientCore_MessageConfirmationCallback(result, context);
}
