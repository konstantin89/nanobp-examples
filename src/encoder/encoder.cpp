#include "pb_encode.h"
#include "auto_generated/ExampleMessage.pb.h"

#include "common/utils.h"

#include <vector>
#include <string.h>
#include <string>


bool encode_string(pb_ostream_t* stream, const pb_field_t* field, void* const* arg)
{
    const char* str = (const char*)(*arg);

    if (!pb_encode_tag_for_field(stream, field))
        return false;

    return pb_encode_string(stream, (uint8_t*)str, strlen(str));
}

bool encode_string_vector(pb_ostream_t* stream, const pb_field_t* field, void* const* arg)
{
    std::vector<std::string>* str_vector = (std::vector<std::string>*)(*arg);

    for (size_t i = 0; i < str_vector->size(); i++)
    {

        if (!pb_encode_tag(stream, PB_WT_STRING, field->tag)) {
            return false;
        }

        if (!pb_encode_string(stream, (uint8_t*)str_vector->at(i).c_str(), str_vector->at(i).size())) {
            return false;
        }
    }

    return true;
}


int runEncoderExample()
{

    ExampleMessage message = ExampleMessage_init_default;

    std::vector<std::string> str_vector = { "first", "second" };

    message.number = 3;

    message.str.arg = "str";
    message.str.funcs.encode = encode_string;

    message.str_array.arg = &str_vector;
    message.str_array.funcs.encode = encode_string_vector;


    std::vector<uint8_t> encodedMessage = {};

    size_t estimatedSize = 0;
    auto getEstimatedSizeSuccess = pb_get_encoded_size(&estimatedSize, ExampleMessage_fields, &message);


    if (!getEstimatedSizeSuccess)
    {
        return 1;
    }

    encodedMessage.reserve(estimatedSize);

    pb_ostream_t pbOutStream =
    {
        [](pb_ostream_t* self, const pb_byte_t* buf, size_t count)
        {
            auto buffer = (std::vector<uint8_t>*)self->state;
            buffer->insert(buffer->end(), buf, buf + count);
            return true;
        },
        &encodedMessage,
        SIZE_MAX,
        0,
        nullptr
    };

    const auto encode_successful = pb_encode(&pbOutStream, ExampleMessage_fields, &message);

    if (!encode_successful)
    {
        return 1;
    }

    writeBinaryFile("message.bin", encodedMessage);

    return 0;
}

int main()
{
    return runEncoderExample();
}
