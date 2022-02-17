#include "azure-storage-blob-client.h"
#include "base64-decoder.h"

std::string read_stdin() {
    std::cin >> std::noskipws;
    std::istream_iterator<char> begin(std::cin);
    std::istream_iterator<char> end;
    return std::string(begin, end);
}

int main(int argc, char* argv[]) {

    if (argc != 5) {
        std::cerr
            << "Usage: azure-storage-uploader account-name sas-token container-name blob-name\n"
            << "Upload the base64-encoded data received from STDIN into the specified blob.\n";
        return EXIT_FAILURE;
    }

    const char* account_name   = argv[1];
    const char* sas_token      = argv[2];
    const char* container_name = argv[3];
    const char* blob_name      = argv[4];

    BlobClient client{account_name, sas_token};
    int response = EXIT_FAILURE;

    try {
        const std::string encoded_blob = read_stdin();
        const std::string raw_data = dex::Base64Decoder::decode(encoded_blob);
        auto outcome = client.upload_buffer(
            container_name, blob_name, raw_data.data(), raw_data.size());

        if (outcome.success()) {
            response = EXIT_SUCCESS;
        } else {
            std::cerr
                << "error "
                << outcome.error().code
                << " - "
                << outcome.error().code_name
                << ": "
                << outcome.error().message
                << ".";
        }

    } catch(std::exception& ex) {
        std::cerr << "unexpected error: " << ex.what() << ".";
    } catch(...) {
        std::cerr << "unexpected unknown error.";
    }

    return response;
}
