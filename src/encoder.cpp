#include "nanopb/pb_encode.h"
#include "auto_generated/ExampleMessage.pb.h"

#include <vector>
#include <string.h>

bool encode_string(pb_ostream_t* stream, const pb_field_t* field, void* const* arg)
{
    const char* str = (const char*)(*arg);

    if (!pb_encode_tag_for_field(stream, field))
        return false;

    return pb_encode_string(stream, (uint8_t*)str, strlen(str));
}

int main()
{

    ExampleMessage message = ExampleMessage_init_default;

    message.number = 3;

    message.str.arg = "str";
    message.str.funcs.encode = encode_string;


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

    return 0;
}
