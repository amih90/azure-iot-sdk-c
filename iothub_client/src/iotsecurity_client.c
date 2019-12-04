#include "azure_c_shared_utility/lock.h"
#include "azure_c_shared_utility/threadapi.h"
#include "azure_iot_security_sdk/collector.h"
#include "azure_iot_security_sdk/message_schema_consts.h"
#include "azure_iot_security_sdk/collector_network.h"
#include "azure_iot_security_sdk/utils.h"
#include "iothub_client_core_common.h"
#include "iothub_client_core.h"
#include "iothub_message.h"
#include "iotsecurity_client.h"
#include "parson.h"

const char* MESSAGE_SCHEMA_VERSION = "1.0";
const char* AGENT_VERSION = "0.0.5";



static STRING_HANDLE MACHINE_ID = NULL;

// TODO cleanup
static size_t g_message_count_send_confirmations = 0;

/** TODO P1 implementation **/
// typedef struct IOTSECURITY_CLIENT_INSTANCE_TAG
// {
//     /** POC shouldn't include threads **/
//     // THREAD_HANDLE ThreadHandle;
//     // LOCK_HANDLE LockHandle;

// } IoTSecurityClient;


static void IoTSecurityClient_SendConfirmCallback(IOTHUB_CLIENT_CONFIRMATION_RESULT result, void* userContextCallback);


IOTSECURITY_CLIENT_RESULT IoTSecurityClient_AddMessageMetadata_V1_0(JSON_Object *root_object) {
    IOTSECURITY_CLIENT_RESULT client_result = IOTSECURITY_CLIENT_RESULT_OK;
    JSON_Status json_status = JSONSuccess;

    json_status |= json_object_set_string(root_object, AGENT_VERSION_KEY, AGENT_VERSION);

    MACHINE_ID = OSUtils_GetMachineId(); // TODO lazy
    if (MACHINE_ID != NULL) {
        json_status = json_object_set_string(root_object, AGENT_ID_KEY, STRING_c_str(MACHINE_ID));
        if (json_status != JSONSuccess) {
            goto cleanup;
        }
    }
    json_status |= json_object_set_string(root_object, MESSAGE_SCHEMA_VERSION_KEY, MESSAGE_SCHEMA_VERSION);

cleanup:
    if (json_status != JSONSuccess) {
        client_result = IOTSECURITY_CLIENT_RESULT_EXCEPTION;
    }

    if (client_result != IOTSECURITY_CLIENT_RESULT_OK) {
        // TODO free
    }

    return client_result;
}

IOTSECURITY_CLIENT_RESULT IoTSecurityClient_CreateMessageSchema(JSON_Value **root_value) {
    IOTSECURITY_CLIENT_RESULT client_result = IOTSECURITY_CLIENT_RESULT_OK;
    JSON_Status json_status = JSONSuccess;

    JSON_Object* root_object;

    *root_value = json_value_init_object();
    root_object = json_value_get_object(*root_value);

    client_result = IoTSecurityClient_AddMessageMetadata_V1_0(root_object);
    if (client_result != IOTSECURITY_CLIENT_RESULT_OK) {
        goto cleanup;
    }

    JSON_Value *events_value = json_value_init_array();
    JSON_Array *events_object = json_value_get_array(events_value);

    json_status = json_object_set_value(root_object, EVENTS_KEY, events_value);
    if (json_status != JSONSuccess) {
        goto cleanup;
    }

cleanup:
    if (json_status != JSONSuccess) {
        client_result = IOTSECURITY_CLIENT_RESULT_EXCEPTION;
    }

    if (client_result != IOTSECURITY_CLIENT_RESULT_OK) {
        // TODO free
    }

    return client_result;
}


IOTSECURITY_CLIENT_RESULT IoTSecurityClient_Collect(IOTHUB_MESSAGE_HANDLE* message_handle) {
    IOTSECURITY_CLIENT_RESULT client_result = IOTSECURITY_CLIENT_RESULT_OK;
    JSON_Status json_status = JSONSuccess;

    JSON_Value *root_value;
    client_result = IoTSecurityClient_CreateMessageSchema(&root_value);
    if (client_result != IOTSECURITY_CLIENT_RESULT_OK) {
        goto cleanup;
    }

    JSON_Object* root_object = json_value_get_object(root_value);
    JSON_Array *events_array = json_object_get_array(root_object, EVENTS_KEY);

    // iterate over registred collectors
    IOTSECURITY_COLLECTOR_RESULT collector_result = COLLECTOR_RESULT_OK;

    JSON_Value* event_value = json_value_init_object();
    JSON_Object* event_object = json_value_get_object(event_value);

    collector_result = CollectorNetwork_Collect(event_object);
    if (collector_result != COLLECTOR_RESULT_OK) {
        (void)printf("failed to collect network events\n");
    } else {
        json_status |= json_array_append_value(events_array, event_value);
    }


    char *serialized_string = NULL;
    serialized_string = json_serialize_to_string_pretty(root_value);
    (void)printf("\r\nCreated Message: %s\r\n", serialized_string);

    *message_handle = IoTHubMessage_CreateFromString(serialized_string);

cleanup:
    json_free_serialized_string(serialized_string);
    json_value_free(root_value);

    if (json_status != JSONSuccess) {
        client_result = IOTSECURITY_CLIENT_RESULT_EXCEPTION;
    }

    if (client_result != IOTSECURITY_CLIENT_RESULT_OK) {
        // TODO free
    }

    return client_result;
}


IOTHUB_CLIENT_RESULT IoTSecurityClient_SendEventAsync(IOTHUB_DEVICE_CLIENT_HANDLE iotHubClientHandle, IOTHUB_MESSAGE_HANDLE eventMessageHandle, IOTHUB_CLIENT_EVENT_CONFIRMATION_CALLBACK eventConfirmationCallback, void* userContextCallback) {
    (void)IoTHubMessage_SetAsSecurityMessage(eventMessageHandle);
    (void)IoTHubMessage_SetContentTypeSystemProperty(eventMessageHandle, "application%2fjson");
    (void)IoTHubMessage_SetContentEncodingSystemProperty(eventMessageHandle, "utf-8");

    if (eventConfirmationCallback == NULL) {
        eventConfirmationCallback = IoTSecurityClient_SendConfirmCallback;
    }

    return IoTHubClientCore_SendEventAsync(iotHubClientHandle, eventMessageHandle, eventConfirmationCallback, NULL);
}


static void IoTSecurityClient_SendConfirmCallback(IOTHUB_CLIENT_CONFIRMATION_RESULT result, void* userContextCallback)
{
    (void)userContextCallback;
    (void)printf("IoTSecurity message confirmation callback received for message %lu with result %s\r\n", (unsigned long)g_message_count_send_confirmations, MU_ENUM_TO_STRING(IOTHUB_CLIENT_CONFIRMATION_RESULT, result));
}