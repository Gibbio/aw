#include <storage_credential.h>
#include <storage_account.h>
#include <blob/blob_client.h>

using namespace azure::storage_lite;

class BlobClient {
    std::shared_ptr<storage_credential> credential_;
    std::shared_ptr<storage_account> account_;
    std::shared_ptr<blob_client> blob_client_;
    std::vector<std::pair<std::string, std::string>> metadata_;
public:
    BlobClient(
        const char* account_name,
        const char* sas_token)
        : credential_{
            std::make_shared<shared_access_signature_credential>(
                sas_token)}
        , account_{
        std::make_shared<storage_account>(
            account_name,
            credential_,
            true)} // use_https
        , blob_client_{
            std::make_shared<blob_client>(
                account_,
                1)} // max_concurrency
    {
    }

    storage_outcome<void> upload_stream(
        const char* container_name,
        const char* blob_name,
        std::istream &stream)
    {
        return blob_client_->upload_block_blob_from_stream(
            container_name, blob_name, stream, metadata_).get();
    }

    storage_outcome<void> upload_buffer(
        const char* container_name,
        const char* blob_name,
        const char* buffer,
        unsigned long buffer_size)
    {
        return blob_client_->upload_block_blob_from_buffer(
            container_name, blob_name, buffer, metadata_, buffer_size).get();
    }
};
