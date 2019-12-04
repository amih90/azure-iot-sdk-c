#include "azure_iot_security_sdk/client_core.h"
#include "iotsecurity_client.h"

typedef CLIENT_CORE_HANDLE IOTSECURITY_CLIENT_HANDLE;


IOTSECURITY_CLIENT_HANDLE IoTSecurityClient_Init(IOTSECURITY_CLIENT_CREATE_MESSAGE_CALLBACK create_message_callback, IOTSECURITY_CLIENT_SEND_EVENT_CALLBACK send_message_callback) {
    return ClientCore_Init(create_message_callback, send_message_callback);
}

IOTSECURITY_CLIENT_RESULT IoTSecurityClient_Collect(IOTSECURITY_CLIENT_HANDLE, iotsecurity_client_handle) {
    IOTSECURITY_CLIENT_RESULT result = IOTSECURITY_CLIENT_RESULT_OK;
    CLIENT_CORE_RESULT client_core_result = CLIENT_CORE_RESULT_OK;

    client_core_result = iotsecurity_client_handle->collect();
    if (client_core_result != IOTSECURITY_CLIENT_RESULT_OK) {
        result = IOTSECURITY_CLIENT_RESULT_EXCEPTION;
    }

    return result;
}

IOTHUB_CLIENT_RESULT IoTSecurityClient_SendEventAsync() {

}

IOTSECURITY_CLIENT_RESULT IoTSecurityClient_Deinit() {

}

