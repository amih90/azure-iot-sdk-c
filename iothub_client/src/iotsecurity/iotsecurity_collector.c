#include <stdint.h>
#include "parson.h"
#include "azure_c_shared_utility/gb_time.h"
#include "azure_c_shared_utility/strings.h"
#include "azure_c_shared_utility/uniqueid.h"
#include "iotsecurity/iotsecurity_collector.h"
#include "iotsecurity/iotsecurity_message_schema_consts.h"
#include "iotsecurity/iotsecurity_utils.h"

#define RECORD_TIME_PROPERTY_MAX_LENGTH 25
#define EVENT_ID_SIZE 37

// FIXME refactor time implementation
#define MAX_TIME_AS_STRING_LENGTH 25


IOTSECURITY_COLLECTOR_RESULT Collector_AddMetadata(JSON_Object *root) {
    IOTSECURITY_COLLECTOR_RESULT collector_result = COLLECTOR_RESULT_OK;
    JSON_Status json_status = JSONSuccess;

    json_status = json_object_set_string(root, EVENT_PAYLOAD_SCHEMA_VERSION_KEY, LISTENING_PORTS_PAYLOAD_SCHEMA_VERSION);
    if (json_status != JSONSuccess) {
        goto cleanup;
    }

    json_status = json_object_set_string(root, EVENT_NAME_KEY, LISTENING_PORTS_NAME);
    if (json_status != JSONSuccess) {
        goto cleanup;
    }

    json_status = json_object_set_string(root, EVENT_CATEGORY_KEY, EVENT_PERIODIC_CATEGORY);
    if (json_status != JSONSuccess) {
        goto cleanup;
    }

    json_status = json_object_set_string(root, EVENT_TYPE_KEY, EVENT_TYPE_SECURITY_VALUE);
    if (json_status != JSONSuccess) {
        goto cleanup;
    }

    char eventId[EVENT_ID_SIZE] = "";
    UNIQUEID_RESULT uuidResult = UniqueId_Generate(eventId, sizeof(eventId));
    if (uuidResult != UNIQUEID_OK) {
        collector_result = COLLECTOR_RESULT_EXCEPTION;
        goto cleanup;
    }
    json_status = json_object_set_string(root, EVENT_ID_KEY, eventId);
    if (json_status != JSONSuccess) {
        goto cleanup;
    }

    // FIXME refactor time implementation
    time_t eventLocalTime;
    time(&eventLocalTime);
    char timeStr[RECORD_TIME_PROPERTY_MAX_LENGTH];
    uint32_t timeStrLength = RECORD_TIME_PROPERTY_MAX_LENGTH;
    memset(timeStr, 0, timeStrLength);
    if (!TimeUtils_GetTimeAsString(&eventLocalTime, timeStr, &timeStrLength)) {
        return COLLECTOR_RESULT_EXCEPTION;
    }

    json_status = json_object_set_string(root, EVENT_LOCAL_TIMESTAMP_KEY, timeStr);
    if (json_status != JSONSuccess) {
        goto cleanup;
    }

    timeStrLength = MAX_TIME_AS_STRING_LENGTH;
    memset(timeStr, 0, timeStrLength);
    if (!TimeUtils_GetLocalTimeAsUTCTimeAsString(&eventLocalTime, timeStr, &timeStrLength)) {
        return COLLECTOR_RESULT_EXCEPTION;
    }
    json_status = json_object_set_string(root, EVENT_UTC_TIMESTAMP_KEY, timeStr);
    if (json_status != JSONSuccess) {
        goto cleanup;
    }

    JSON_Value *payload_value = json_value_init_array();
    JSON_Array *payload_object = json_value_get_array(payload_value);

    json_status = json_object_set_value(root, PAYLOAD_KEY, payload_value);
    if (json_status != JSONSuccess) {
        goto cleanup;
    }

cleanup:
    if (json_status != JSONSuccess) {
        collector_result = COLLECTOR_RESULT_EXCEPTION;
    }

    if (collector_result != COLLECTOR_RESULT_OK) {
        // TODO free
    }

    return collector_result;
}