#include <string>

namespace dex {

class Base64Decoder {
    static const char k_base64_padding_char;
    static const char k_base64_char_set[];
public:
    static std::string decode(const std::string& base64_content);
private:
    static int decode_triple(const char* buffer, char* b1, char* b2, char* b3);
};

} // namespace dex
