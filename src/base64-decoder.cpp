#include "base64-decoder.h"

#include <stdexcept>
#include <string.h>

namespace dex {

const char Base64Decoder::k_base64_char_set[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdef"
    "ghijklmnopqrstuvwxyz0123456789+/";

const char Base64Decoder::k_base64_padding_char = '=';

std::string Base64Decoder::decode(const std::string& base64_content)
{
    std::string raw_content;
    const int size = base64_content.size();

    if ((size % 4) != 0)
        throw std::runtime_error(
            "wrong base64 encoded data"
            " (not a 4x byte long sequence)");

    if (!size)
        return raw_content;

    int byte_count = size / 4 * 3;

    // Take care of padding characters.
    const char last_char = *base64_content.rbegin();
    const char second_last_char = *(base64_content.rbegin() + 1);

    if (last_char == k_base64_padding_char)
        byte_count -= (second_last_char == k_base64_padding_char) ? 2 : 1;

    // Decode the binary content.
    const char* const buffer = base64_content.c_str();
    int i = 0;
    char dummy = 0;

    raw_content.resize(byte_count);
    char* block = &raw_content[0];

    while (i < base64_content.size()) {
        if ((i < size - 4) || buffer[i + 3] != k_base64_padding_char)
            decode_triple(buffer + i, block, block + 1, block + 2);
        else if (buffer[i + 2] == k_base64_padding_char)
            decode_triple(buffer + i, block, &dummy, &dummy);
        else
            decode_triple(buffer + i, block, block + 1, &dummy);
        i += 4;
        block += 3;
    }

    return raw_content;
}

int Base64Decoder::decode_triple(
    const char* buffer, char* b1, char* b2, char* b3)
{
    const char* const p1 = strchr(k_base64_char_set, buffer[0]);
    const char* const p2 = strchr(k_base64_char_set, buffer[1]);
    const char* const p3 = strchr(k_base64_char_set, buffer[2]);
    const char* const p4 = strchr(k_base64_char_set, buffer[3]);

    if ((p1 == NULL)
        || (p2 == NULL)
        || ((p3 == NULL) && (buffer[2] != k_base64_padding_char))
        || ((p4 == NULL) && (buffer[3] != k_base64_padding_char)))
        throw std::runtime_error("not a valid base64 sequence)");

    const char d1 = static_cast<char>(p1 - k_base64_char_set);
    const char d2 = static_cast<char>(p2 - k_base64_char_set);
    const char d3 = static_cast<char>(p3 ? p3 - k_base64_char_set : 0);
    const char d4 = static_cast<char>(p4 ? p4 - k_base64_char_set : 0);

    *(b1) =  (d1 << 2)         | ((d2 & 0x30) >> 4);
    *(b2) = ((d2 & 0x0f) << 4) | ((d3 & 0x3c) >> 2);
    *(b3) = ((d3 & 0x03) << 6) |  (d4 & 0x3f);

    return 3;
}

} // namespace dex
