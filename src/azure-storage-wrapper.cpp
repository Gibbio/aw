#include "azure-storage-blob-client.h"

#include <fstream>

static std::string error_code;
static std::string error_name;
static std::string error_description;

extern "C" const char* const get_error_code() {
    return error_code.c_str();
}

extern "C" const char* const get_error_name() {
    return error_name.c_str();
}

extern "C" const char* const get_error_description() {
    return error_description.c_str();
}

extern "C" int upload_file(
    const char* account_name,
    const char* sas_token,
    const char* container_name,
    const char* blob_name,
    const char* file_path)
{
    error_code = "N/A";
    error_name.clear();
    error_description.clear();

    std::ifstream data(file_path, std::ifstream::in);

    if (!data.good())
    {
        error_name = "FileNotFound";
        error_description = "The specified file does not exist.";
        return EXIT_FAILURE;
    }

    BlobClient client{account_name, sas_token};
    int response = EXIT_FAILURE;

    try {
        auto outcome = client.upload_stream(container_name, blob_name, data);

        if (outcome.success()) {
            response = EXIT_SUCCESS;
        } else {
            error_code = outcome.error().code;
            error_name = outcome.error().code_name;
            error_description = outcome.error().message;
        }

    } catch(std::exception& ex) {
        error_name = "Exception";
        error_description = ex.what();
    }

    return response;
}

extern "C" int upload_buffer(
    const char* account_name,
    const char* sas_token,
    const char* container_name,
    const char* blob_name,
    const char* buffer,
    unsigned long buffer_length)
{
    error_code = "N/A";
    error_name.clear();
    error_description.clear();

    BlobClient client{account_name, sas_token};
    int response = EXIT_FAILURE;

   try {
        auto outcome = client.upload_buffer(
            container_name, blob_name, buffer, buffer_length);

        if (outcome.success()) {
            response = EXIT_SUCCESS;
        } else {
            error_code = outcome.error().code;
            error_name = outcome.error().code_name;
            error_description = outcome.error().message;
        }

    } catch(std::exception& ex) {
        error_name = "Exception";
        error_description = ex.what();
    }

    return response;
}
