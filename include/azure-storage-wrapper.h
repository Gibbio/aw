extern "C" {

const char* const get_error_code();

const char* const get_error_name();

const char* const get_error_description();

int upload_file(
    const char* account_name,
    const char* sas_token,
    const char* container_name,
    const char* blob_name,
    const char* file_path);

}

int upload_buffer(
    const char* account_name,
    const char* sas_token,
    const char* container_name,
    const char* blob_name,
    const char* buffer,
    unsigned long buffer_length);
