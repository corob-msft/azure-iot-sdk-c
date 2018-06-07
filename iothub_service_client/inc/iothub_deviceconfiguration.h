// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

// This file is under development and it is subject to change

#ifndef IOTHUB_DEVICECONFIGURATION_H
#define IOTHUB_DEVICECONFIGURATION_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "azure_c_shared_utility/crt_abstractions.h"
#include "azure_c_shared_utility/singlylinkedlist.h"
#include <time.h>
#include "iothub_service_client_auth.h"

#include "azure_c_shared_utility/umock_c_prod.h"

#define IOTHUB_DEVICE_CONFIGURATION_RESULT_VALUES \
    IOTHUB_DEVICE_CONFIGURATION_OK,                     \
    IOTHUB_DEVICE_CONFIGURATION_INVALID_ARG,            \
    IOTHUB_DEVICE_CONFIGURATION_ERROR,                  \
    IOTHUB_DEVICE_CONFIGURATION_HTTPAPI_ERROR,          \
    IOTHUB_DEVICE_CONFIGURATION_JSON_ERROR,             \
    IOTHUB_DEVICE_CONFIGURATION_OUT_OF_MEMORY_ERROR,    \
    IOTHUB_DEVICE_CONFIGURATION_CONFIGURATION_NOT_EXIST \

DEFINE_ENUM(IOTHUB_DEVICE_CONFIGURATION_RESULT, IOTHUB_DEVICE_CONFIGURATION_RESULT_VALUES);

typedef struct IOTHUB_DEVICE_CONFIGURATION_CONTENT_TAG
{
    const char* deviceContent;
    const char* moduleContent;
} IOTHUB_DEVICE_CONFIGURATION_CONTENT;

typedef struct IOTHUB_DEVICE_CONFIGURATION_METRICS_RESULTS_TAG
{
    const long numQueries;
    const char** queryNames;
    const void* results;
} IOTHUB_DEVICE_CONFIGURATION_METRICS_RESULT;

typedef struct IOTHUB_DEVICE_CONFIGURATION_METRICS_DEFINITION_TAG
{
    const long numQueries;
    const char** queryNames;
    const char** queryStrings;
} IOTHUB_DEVICE_CONFIGURATION_METRICS_DEFINITION;

typedef struct IOTHUB_DEVICE_CONFIGURATION_LABEL_TAG
{
    const long numLabels;
    const char** labelName;
    const char** labelValue;
} IOTHUB_DEVICE_CONFIGURATION_LABELS;

typedef struct IOTHUB_DEVICE_CONFIGURATIONS_RESULTS_TAG
{
    const long numConfigurations;
    const char** configurations;
} IOTHUB_DEVICE_CONFIGURATIONS_RESULT;

#define IOTHUB_DEVICE_CONFIGURATION_SCHEMA_VERSION_1 "1.0"
#define IOTHUB_DEVICE_CONFIGURATION_CONTENT_VERSION_1 1
typedef struct IOTHUB_DEVICE_CONFIGURATION_TAG
{
    int version;
    const char* schemaVersion;                                                    //version 1+
    const char* configurationId;                                                  //version 1+
    const char* targetCondition;                                                  //version 1+
    const char* eTag;                                                             //version 1+
    int priority;                                                                 //version 1+

    IOTHUB_DEVICE_CONFIGURATION_CONTENT content;                                  //version 1+
    IOTHUB_DEVICE_CONFIGURATION_LABELS labels;                                    //version 1+

    const char* contentType;                                                      //version 1+
    const char* createdTimeUtc;
    const char* lastUpdatedTimeUtc;

    IOTHUB_DEVICE_CONFIGURATION_METRICS_RESULT metricResult;                      //version 1+
    IOTHUB_DEVICE_CONFIGURATION_METRICS_RESULT systemMetricsResult;               //version 1+

    IOTHUB_DEVICE_CONFIGURATION_METRICS_DEFINITION metricsDefinition;             //version 1+
    IOTHUB_DEVICE_CONFIGURATION_METRICS_DEFINITION systemMetricsDefinition;       //version 1+
} IOTHUB_DEVICE_CONFIGURATION;

#define IOTHUB_DEVICE_CONFIGURATION_CREATE_VERSION_1 1
typedef struct IOTHUB_DEVICE_CONFIGURATION_CREATE_TAG
{
    int version;
    const char* configurationId;                                    //version 1+
    const char* targetCondition;                                    //version 1+
    int priority;                                                   //version 1+

    IOTHUB_DEVICE_CONFIGURATION_CONTENT content;                    //version 1+
    IOTHUB_DEVICE_CONFIGURATION_LABELS labels;                      //version 1+
    IOTHUB_DEVICE_CONFIGURATION_METRICS_DEFINITION metrics;         //version 1+
} IOTHUB_DEVICE_CONFIGURATION_CREATE;

#define IOTHUB_DEVICE_CONFIGURATION_UPDATE_VERSION_1 1
typedef struct IOTHUB_DEVICE_CONFIGURATION_UPDATE_TAG
{
    int version;
    const char* configurationId;                                    //version 1+
    const char* targetCondition;                                    //version 1+
    int priority;                                                   //version 1+

    IOTHUB_DEVICE_CONFIGURATION_LABELS labels;                      //version 1+
    IOTHUB_DEVICE_CONFIGURATION_METRICS_DEFINITION metrics;         //version 1+
} IOTHUB_DEVICE_CONFIGURATION_UPDATE;

/** @brief Handle to hide struct and use it in consequent APIs
*/
typedef struct IOTHUB_SERVICE_CLIENT_DEVICE_CONFIGURATION_TAG* IOTHUB_SERVICE_CLIENT_DEVICE_CONFIGURATION_HANDLE;


/** @brief  Creates a IoT Hub Service Client DeviceConfiguration handle for use it in consequent APIs.
*
* @param    serviceClientHandle    Service client handle.
*
* @return   A non-NULL @c IOTHUB_SERVICE_CLIENT_DEVICE_CONFIGURATION_HANDLE value that is used when
*           invoking other functions for IoT Hub DeviceConfiguration and @c NULL on failure.
*/
MOCKABLE_FUNCTION(, IOTHUB_SERVICE_CLIENT_DEVICE_CONFIGURATION_HANDLE, IoTHubDeviceConfiguration_Create, IOTHUB_SERVICE_CLIENT_AUTH_HANDLE, serviceClientHandle);

/** @brief  Disposes of resources allocated by the IoT Hub IoTHubDeviceConfiguration_Create.
*
* @param    serviceClientDeviceConfigurationHandle    The handle created by a call to the create function.
*/
MOCKABLE_FUNCTION(, void, IoTHubDeviceConfiguration_Destroy, IOTHUB_SERVICE_CLIENT_DEVICE_CONFIGURATION_HANDLE, serviceClientDeviceConfigurationHandle);

/** @brief  Retrieves the Configuration info for multiple configurations from IoT Hub.
*
* @param    serviceClientDeviceConfigurationHandle    The handle created by a call to the create function.
* @param    maxConfigurationsCount                    Maximum number of configurations requested
* @param    configurations                            Output parameter, if it is not NULL will contain the requested configurations
*
* @return   IOTHUB_DEVICE_CONFIGURATION_RESULT upon success or an error code upon failure.
*/
MOCKABLE_FUNCTION(, IOTHUB_DEVICE_CONFIGURATION_RESULT, IoTHubDeviceConfiguration_GetConfigurations, IOTHUB_SERVICE_CLIENT_DEVICE_CONFIGURATION_HANDLE, serviceClientDeviceConfigurationHandle, const int, maxConfigurationsCount, SINGLYLINKEDLIST_HANDLE, configurationsList);

/** @brief  Retrieves the Configuration info for specified configurationId from IoT Hub.
*
* @param    serviceClientDeviceConfigurationHandle    The handle created by a call to the create function.
* @param    configurationId                         The configuration name (id) to retrieve Configuration info for.
* @param    configuration                           Output parameter, if it is not NULL will contain the requested configuration info structure
*
* @return   IOTHUB_DEVICE_CONFIGURATION_RESULT upon success or an error code upon failure.
*/
MOCKABLE_FUNCTION(, IOTHUB_DEVICE_CONFIGURATION_RESULT, IoTHubDeviceConfiguration_GetConfiguration, IOTHUB_SERVICE_CLIENT_DEVICE_CONFIGURATION_HANDLE, serviceClientDeviceConfigurationHandle, const char*, configurationId, IOTHUB_DEVICE_CONFIGURATION*, configuration);

/** @brief  Adds the Configuration info to IoT Hub.
*
* @param    serviceClientDeviceConfigurationHandle    The handle created by a call to the create function.
* @param    configurationCreate     IOTHUB_DEVICE_CONFIGURATION_CREATE structure containing
*                                   the new configuration Id and other optional parameters
* @param    configuration           Output parameter, if it is not NULL will contain the created configuration info structure
*
* @return   IOTHUB_DEVICE_CONFIGURATION_RESULT upon success or an error code upon failure.
*/
MOCKABLE_FUNCTION(, IOTHUB_DEVICE_CONFIGURATION_RESULT, IoTHubDeviceConfiguration_AddConfiguration, IOTHUB_SERVICE_CLIENT_DEVICE_CONFIGURATION_HANDLE, serviceClientDeviceConfigurationHandle, const IOTHUB_DEVICE_CONFIGURATION_CREATE*, configurationCreate, IOTHUB_DEVICE_CONFIGURATION*, configuration);

/** @brief  Updates (partial update) the given Configuration in IoT Hub.
*
* @param    serviceClientDeviceConfigurationHandle    The handle created by a call to the create function.
* @param    configurationUpdate     IOTHUB_DEVICE_CONFIGURATION_CREATE structure containing
*                                   the new configuration info. Note that Configuration content cannot be updated.
* @param    configuration           Output parameter, if it is not NULL will contain the updated configuration info structure
*
* @return   IOTHUB_DEVICE_CONFIGURATION_RESULT upon success or an error code upon failure.
*/
MOCKABLE_FUNCTION(, IOTHUB_DEVICE_CONFIGURATION_RESULT, IoTHubDeviceConfiguration_UpdateConfiguration, IOTHUB_SERVICE_CLIENT_DEVICE_CONFIGURATION_HANDLE, serviceClientDeviceConfigurationHandle, const IOTHUB_DEVICE_CONFIGURATION_UPDATE*, configurationUpdate, IOTHUB_DEVICE_CONFIGURATION*, configuration);

/** @brief  Deletes the given Configuration from IoT Hub.
*
* @param    serviceClientDeviceConfigurationHandle    The handle created by a call to the create function.
* @param    configurationId         The configuration name (id) to delete Configuration info for.
*
* @return   IOTHUB_DEVICE_CONFIGURATION_RESULT upon success or an error code upon failure.
*/
MOCKABLE_FUNCTION(, IOTHUB_DEVICE_CONFIGURATION_RESULT, IoTHubDeviceConfiguration_DeleteConfiguration, IOTHUB_SERVICE_CLIENT_DEVICE_CONFIGURATION_HANDLE, serviceClientDeviceConfigurationHandle, const char*, configurationId);

/**
* @brief    Free members of the IOTHUB_DEVICE_CONFIGURATION structure (NOT the structure itself)
*
* @param    configuration      The structure to have its members freed.
*/
extern void IoTHubDeviceConfiguration_FreeConfigurationMembers(IOTHUB_DEVICE_CONFIGURATION* configuration);

#ifdef __cplusplus
}
#endif

#endif // IOTHUB_DEVICECONFIGURATION_H
