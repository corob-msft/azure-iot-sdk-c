#Copyright (c) Microsoft. All rights reserved.
#Licensed under the MIT license. See LICENSE file in the project root for full license information.

#this is CMakeLists.txt for iothub_client_sample_amqp_websockets_shared

compileAsC99()

if(NOT ${use_amqp})
    message(FATAL_ERROR "iothub_client_sample_amqp_websockets_shared being generated without uamqp support")
endif()

set(iothub_client_sample_amqp_websockets_shared_c_files
    iothub_client_sample_amqp_websockets_shared.c
)

set(iothub_client_sample_amqp_websockets_shared_h_files
    iothub_client_sample_amqp_websockets_shared.h
)

IF(WIN32)
    #windows needs this define
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_definitions(-DGB_MEASURE_MEMORY_FOR_THIS -DGB_DEBUG_ALLOC)
ENDIF(WIN32)

#Conditionally use the SDK trusted certs in the samples
if(${use_sample_trusted_cert})
    add_definitions(-DSET_TRUSTED_CERT_IN_SAMPLES)
    include_directories(${PROJECT_SOURCE_DIR}/certs)
    set(iothub_client_sample_amqp_websockets_shared_c_files ${iothub_client_sample_amqp_websockets_shared_c_files} ${PROJECT_SOURCE_DIR}/certs/certs.c)
endif()

include_directories(.)

add_executable(iothub_client_sample_amqp_websockets_shared ${iothub_client_sample_amqp_websockets_shared_c_files} ${iothub_client_sample_amqp_websockets_shared_h_files})

target_link_libraries(iothub_client_sample_amqp_websockets_shared
        iothub_client
        iothub_client_amqp_ws_transport)

linkSharedUtil(iothub_client_sample_amqp_websockets_shared)
linkUAMQP(iothub_client_sample_amqp_websockets_shared)
