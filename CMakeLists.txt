cmake_minimum_required(VERSION 3.8)
project(azurestoragewrapper)

set(CMAKE_CXX_STANDARD 17)

set(APP_VERSION "1.0.0")
string(TIMESTAMP APP_BUILD_TIMESTAMP "%Y-%m-%dT%H:%M:%S" UTC)

# Retrieve git commit hash
execute_process(
        COMMAND git rev-parse HEAD
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE APP_COMMIT_HASH
        OUTPUT_STRIP_TRAILING_WHITESPACE)

configure_file(config.h.in config.h)

# Dependencies
include(ExternalProject)
include(cmake/azure-storage-lite.cmake)

# Library
add_library(azure-storage-wrapper MODULE
        src/azure-storage-blob-client.h
        src/azure-storage-wrapper.cpp)

target_include_directories(azure-storage-wrapper
        PRIVATE ${AZURE_STORAGE_LITE_INCLUDE_DIRS})

add_dependencies(azure-storage-wrapper
        azurestoragelite)

target_link_libraries(azure-storage-wrapper
        ${AZURE_STORAGE_LITE_STATIC_LIB}
        curl
        crypto
        pthread
        ssl
        uuid)

# Executable
add_executable(azure-storage-uploader
        src/base64-decoder.h
        src/base64-decoder.cpp
        src/azure-storage-blob-client.h
        src/azure-storage-uploader.cpp)

target_include_directories(azure-storage-uploader
        PRIVATE ${AZURE_STORAGE_LITE_INCLUDE_DIRS})

add_dependencies(azure-storage-uploader
        azurestoragelite)

target_link_libraries(azure-storage-uploader
        ${AZURE_STORAGE_LITE_STATIC_LIB}
        curl
        crypto
        pthread
        ssl
        uuid)

# DEBUG/NDEBUG defines
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG")

# Optimize release binary sizes
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -ffunction-sections -fdata-sections -s")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -ffunction-sections -fdata-sections -s")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -Wl,--gc-sections")
