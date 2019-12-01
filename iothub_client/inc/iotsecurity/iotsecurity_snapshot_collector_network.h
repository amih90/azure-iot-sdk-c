// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef IOTSECURITY_COLLECTOR_NETWORK_H
#define IOTSECURITY_COLLECTOR_NETWORK_H

#include "parson.h"
#include "iotsecurity_collector.h"

#ifdef __cplusplus
extern "C"
{
#else
#endif

// FIXME check how enums should be declared after MU_DEFINE_ENUM* is deprecated
// typedef enum IOTSECURITY_COLLECTOR_NETWORK_NETID_TAG {
//     NETID_TCP = 0,
//     NETID_UDP = 1,
//     NETID_RAW = 2,
//     NETID_U_DGR = 3,
//     NETID_U_STR = 4,
//     NETID_P_RAW = 5,
//     NETID_P_DGR = 6,
//     NETID_U_STR = 7,
// } IOTSECURITY_COLLECTOR_NETWORK_NETID;

#define NETID_RESULT_VALUES    \
    NETID_TCP,              \
    NETID_UDP,              \
    NETID_RAW,              \
    NETID_U_DGR,            \
    NETID_U_STR,            \
    NETID_P_RAW,            \
    NETID_P_DGR,            \
    NETID_NL

    MU_DEFINE_ENUM(NETID_RESULT, NETID_RESULT_VALUES)


MOCKABLE_FUNCTION(, IOTSECURITY_COLLECTOR_RESULT, SnapshotCollectorNetwork_Collect, JSON_Object, *root);

#ifdef __cplusplus
}
#endif

#endif /* IOTSECURITY_COLLECTOR_NETWORK_H */
