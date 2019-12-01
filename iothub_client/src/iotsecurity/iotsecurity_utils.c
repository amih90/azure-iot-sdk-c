#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "azure_c_shared_utility/strings.h"
#include "azure_c_shared_utility/xlogging.h"
#include "iotsecurity/iotsecurity_utils.h"


#define MAX_LENGTH_MACHINE_ID 512

static const char* DATETIME_FORMAT = "%FT%TZ";


STRING_HANDLE OSUtils_GetMachineId() {
    STRING_HANDLE machineId = NULL;
    FILE *fp = NULL;
    char line[MAX_LENGTH_MACHINE_ID] = { 0 };

    fp = popen("cat /etc/machine-id", "r");
    if (fp == NULL) {
        goto cleanup;
    }

    if (!ferror(fp)) {
        if (fgets(line, sizeof(line), fp) != NULL) {
            machineId = STRING_construct_n((const char*)line, strlen(line) - 1);
            if (machineId == NULL) {
                goto cleanup;
            }
        }
    }

cleanup:
    if (fp != NULL) {
        pclose(fp);
    }

    if (machineId == NULL) {
        LogInfo("WARNING: failed to find machine-id.");
    }

    return machineId;
}

bool TimeUtils_GetTimeAsString(time_t* currentTime, char* output, uint32_t* outputSize) {
    struct tm currentLocalTime;
    if (localtime_r(currentTime, &currentLocalTime) == NULL) {
        return false;
    }
    *outputSize = strftime(output, *outputSize, DATETIME_FORMAT, &currentLocalTime);
    return true;
}


bool TimeUtils_GetLocalTimeAsUTCTimeAsString(time_t* currentLocalTime, char* output, uint32_t* outputSize) {
    struct tm currentUTCTime;
    if (gmtime_r(currentLocalTime, &currentUTCTime) == NULL) {
        return false;
    }
    *outputSize = strftime(output, *outputSize, DATETIME_FORMAT, &currentUTCTime);
    return true;
}

void StringUtils_ToUpper(char* str) {
    if (str != NULL) {
        while (*str != '\0') {
            if (isalpha((int)*str) && islower((int)*str)) {
                *str = (char)toupper((int)*str);
            }
            str++;
        }
    }
}