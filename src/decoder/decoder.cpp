#include "pb_decode.h"
#include "auto_generated/ExampleMessage.pb.h"
#include "common/utils.h"

#include <vector>
#include <string>


bool decode_string(pb_istream_t *stream, const pb_field_t *field, void **arg)
{
    uint8_t buffer[1024] = { 0 };
    std::string* outStr = (std::string*)*arg;

    if (stream->bytes_left > sizeof(buffer) - 1)
        return false;

    if (!pb_read(stream, buffer, stream->bytes_left))
        return false;

    std::string s = std::string((char*)buffer, sizeof(buffer));

    *outStr = s;

    return true;
}

bool decode_string_vector(pb_istream_t *stream, const pb_field_t *field, void **arg)
{
    std::vector<std::string>* outStrVector = (std::vector<std::string>*)*arg;

    uint8_t buffer[1024] = { 0 };

    if (stream->bytes_left > sizeof(buffer) - 1)
        return false;

    if (!pb_read(stream, buffer, stream->bytes_left))
        return false;

    std::string tempStr = std::string((char*)buffer, sizeof(buffer));

    outStrVector->push_back(std::move(tempStr));

    return true;
}

int runDecoderExample()
{
    auto fileContent = readBinaryFile("message.bin");

    size_t messageLength = 0;

    std::string decodedStr = {};
    std::vector<std::string> decodedStrArray = {};

    ExampleMessage message = ExampleMessage_init_default;

    message.str.funcs.decode = decode_string;
    message.str.arg = &decodedStr;

    message.str_array.funcs.decode = decode_string_vector;
    message.str_array.arg = &decodedStrArray;

    pb_istream_t stream = pb_istream_from_buffer(
        fileContent.value().data(),
        fileContent.value().size());

    auto status = pb_decode(&stream, ExampleMessage_fields, &message);

    return 0;
}

int main()
{
    return runDecoderExample();
}
