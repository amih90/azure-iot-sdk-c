// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef IOTSECURITY_COLLECTOR_H
#define IOTSECURITY_COLLECTOR_H

#ifdef __cplusplus
extern "C"
{
#else
#endif

typedef enum IOTSECURITY_COLLECTOR_RESULT_TAG {
    COLLECTOR_OK = 0,
    COLLECTOR_EXCEPTION = 1,
    COLLECTOR_PARSE_EXCEPTION = 2,
    COLLECTOR_MEMORY_EXCEPTION = 3,
    COLLECTOR_NOT_SUPPORTED_EXCEPTION = 4
} IOTSECURITY_COLLECTOR_RESULT;

#ifdef __cplusplus
}
#endif

#endif /* IOTSECURITY_COLLECTOR_H */
