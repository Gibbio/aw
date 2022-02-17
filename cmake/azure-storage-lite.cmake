ExternalProject_Add(azurestoragelite
        PREFIX azure-storage-cpplite
        URL file://${CMAKE_SOURCE_DIR}/deps/azure-storage-cpplite-master.zip
        URL_HASH SHA256=7b222812eb6a562f23518b10ddf2b1f94e5b81b943922ab5a0bb420e3887b90f
        CMAKE_ARGS
        UPDATE_COMMAND ""
        PATCH_COMMAND patch < ${CMAKE_SOURCE_DIR}/deps/patches/azure-storage-lite-fPIC.patch
        INSTALL_COMMAND ""
        LOG_DOWNLOAD ON)

set(AZURE_STORAGE_LITE_INCLUDE_DIRS
        ${AZURE_STORAGE_LITE_INCLUDE_DIRS}
        ${CMAKE_CURRENT_BINARY_DIR}/azure-storage-cpplite/src/azurestoragelite/include)

set(AZURE_STORAGE_LITE_STATIC_LIB
        ${AZURE_STORAGE_LITE_STATIC_LIB}
        ${CMAKE_CURRENT_BINARY_DIR}/azure-storage-cpplite/src/azurestoragelite-build/libazure-storage-lite.a)
