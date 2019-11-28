// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef UTILS_H
#define UTILS_H

#ifdef __cplusplus
extern "C"
{
#else
#endif

MOCKABLE_FUNCTION(, STRING_HANDLE, OSUtils_GetMachineId);


/**
 * @brief Converts the given time to string.
 *
 * @param   currentTime     The current time to convert.
 * @param   output          Out param. pre-allocated buffer that will contain the formated time.
 * @param   outputSize      In out param. When function is called it should be the size of the output buffer.
 *                          On return this should be the size of the formated time.
 *
 * @retrn true on success. false otherwise.
 */
MOCKABLE_FUNCTION(, bool, TimeUtils_GetTimeAsString, time_t*, currentTime, char*, output, uint32_t*, outputSize);

/**
 * @brief Converts the given local time to a UTC time and returns the string representation of the UTC time.
 *
 * @param   currentLocalTime     The current time to convert.
 * @param   output               Out param. pre-allocated buffer that will contain the formated time.
 * @param   outputSize           In out param. When function is called it should be the size of the output buffer.
 *                               On return this should be the size of the formated time.
 *
 * @retrn true on success. false otherwise.
 */
MOCKABLE_FUNCTION(, bool, TimeUtils_GetLocalTimeAsUTCTimeAsString, time_t*, currentLocalTime, char*, output, uint32_t*, outputSize);


#ifdef __cplusplus
}
#endif

#endif /* UTILS_H */