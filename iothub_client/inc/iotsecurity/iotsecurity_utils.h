// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef IOTSECURITY_UTILS_H
#define IOTSECURITY_UTILS_H

#ifdef __cplusplus
extern "C"
{
#else
#endif

/**
 * @brief Get machine-id
 *
 * The /etc/machine-id file contains the unique machine ID of the local
 * system that is set during installation. The machine ID is a single
 * newline-terminated, hexadecimal, 32-character, lowercase ID. When
 * decoded from hexadecimal, this corresponds to a 16-byte/128-bit
 * value.

 * The machine ID is usually generated from a random source during
 * system installation and stays constant for all subsequent boots.
 * Optionally, for stateless systems, it is generated during runtime at
 * early boot if it is found to be empty.
 *
 * @return STRING_HANDLE containing machine-id
 */

MOCKABLE_FUNCTION(, STRING_HANDLE, OSUtils_GetMachineId);


/**
 * @brief Converts the given time to string.
 *
 * @param   currentTime     The current time to convert.
 * @param   output          Out param. pre-allocated buffer that will contain the formated time.
 * @param   outputSize      In out param. When function is called it should be the size of the output buffer.
 *                          On return this should be the size of the formated time.
 *
 * @return true on success. false otherwise.
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
 * @return true on success. false otherwise.
 */
MOCKABLE_FUNCTION(, bool, TimeUtils_GetLocalTimeAsUTCTimeAsString, time_t*, currentLocalTime, char*, output, uint32_t*, outputSize);

MOCKABLE_FUNCTION(, void, StringUtils_ToUpper, char*, str);

#ifdef __cplusplus
}
#endif

#endif /* IOTSECURITY_UTILS_H */