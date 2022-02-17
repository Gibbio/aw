# Azure Storage C wrapper

Basic C wrapper around the [Azure Storage C++ Client Library (Lite)](https://github.com/Azure/azure-storage-cpplite). Its purpose is to let Python scripts running inside MK5 gateways to upload files into an Azure Blob Storage.

## API

See [azure-storage-wrapper.h](./include/azure-storage-wrapper.h).

## Usage

See [azure-storage-client.py](./tools/examples/azure-storage-client.py).

## How to build for PC

CMake and the `build-essential` packages are required. The following libraries are required too:

    sudo apt install libcurl4-openssl-dev libssl-dev uuid-dev

Then `cd` into the project directory and issue the following commands:

    mkdir -p build/x86
    cd build/x86
    cmake ../.. -DCMAKE_BUILD_TYPE=Release
    make

## How to build for ARM

Activate ARM toolchain:

    . /opt/poky/2.6.4/environment-setup-armv7at2hf-neon-poky-linux-gnueabi

Then `cd` into the project directory and issue the following commands:

    mkdir -p build/arm
    cd build/arm
    cmake ../.. -DCMAKE_BUILD_TYPE=Release
    make

## TODO

* install
* version/build date API

## Notes

In order to build the `azure-storage-wrapper.so` shared library the _Azure Storage C++ Client Library (Lite)_ dependency must be compiled with the `-fPIC` flag enabled; moreover, the `/src/blob/blob_client_wrapper.cpp` file does not compile for ARM (see for example [Type-limits warnings when building for ARM32](https://github.com/Azure/azure-storage-cpplite/issues/72)). For these reasons a [custom patch](./deps/patches/azure-storage-lite-fPIC.patch) is applied to the main `CMakeLists.txt` file.
