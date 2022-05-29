#include "pb_encode.h"
#include "auto_generated/ExampleMessage.pb.h"

#include "common/utils.h"

#include <vector>
#include <string.h>
#include <string>


/**
* @brief: NanoPB encoder for string type.
*/
bool encode_string(pb_ostream_t* stream, const pb_field_t* field, void* const* arg);

/**
* @brief: NanoPB encoder for repeated string type.
*/
bool encode_string_vector(pb_ostream_t* stream, const pb_field_t* field, void* const* arg);

/**
* @brief: NanoPB encoder for repeated SubMessage type.
*/
bool encode_submessage_vector(pb_ostream_t* stream, const pb_field_t* field, void* const* arg);


int runEncoderExample()
{

    ExampleMessage message = ExampleMessage_init_default;

    // Fill the message content

    std::vector<std::string> str_vector = { "first", "second" };

    message.number = 3;

    message.str.arg = "str";
    message.str.funcs.encode = encode_string;

    message.str_array.arg = &str_vector;
    message.str_array.funcs.encode = encode_string_vector;

    SubMessage submessage_1 = SubMessage_init_default;
    submessage_1.sub_number = 6;
    submessage_1.sub_string.arg = "sub_str_1";
    submessage_1.sub_string.funcs.encode = encode_string;

    SubMessage submessage_2 = SubMessage_init_default;
    submessage_2.sub_number = 7;
    submessage_2.sub_string.arg = "sub_str_2";
    submessage_2.sub_string.funcs.encode = encode_string;

    std::vector<SubMessage> submessageVec = { submessage_1 , submessage_2 };

    message.sub_message_array.arg = &submessageVec;
    message.sub_message_array.funcs.encode = encode_submessage_vector;


    // Encode the message

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
        // The callback of the output stream is used to store the enoded message.
        // In this example, the encoded message is stored in buffer.
        // Other implementation example, is callback that writes the output to file.
        // If this callback is NULL, the encoding does not store the encoded message, only counts its size.
        [](pb_ostream_t* self, const pb_byte_t* buf, size_t count)
        {
            // We store the target buffer is self->state field (Its void*).
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


    // Write the encoded message to binary file

    utils::writeBinaryFile(utils::ENCODED_MESSAGE_BIN_FILE_NAME, encodedMessage);

    return 0;
}

int main()
{
    return runEncoderExample();
}



// Encoder functions

bool encode_string(pb_ostream_t* stream, const pb_field_t* field, void* const* arg)
{
    const char* str = reinterpret_cast<const char*>(*arg);

    if (!pb_encode_tag_for_field(stream, field))
        return false;

    return pb_encode_string(stream, (uint8_t*)str, strlen(str));
}

bool encode_string_vector(pb_ostream_t* stream, const pb_field_t* field, void* const* arg)
{
    std::vector<std::string>* str_vector = reinterpret_cast<std::vector<std::string>*>(*arg);

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

bool encode_submessage_vector(pb_ostream_t* stream, const pb_field_t* field, void* const* arg)
{
    std::vector<SubMessage>* submessage_vector = reinterpret_cast<std::vector<SubMessage>*>(*arg);

    for (size_t i = 0; i < submessage_vector->size(); i++)
    {

        if (!pb_encode_tag_for_field(stream, field))
        {
            return false;
        }

        if (!pb_encode_submessage(stream, SubMessage_fields, &submessage_vector->at(i)))
        {
            return false;
        }
    }

    return true;
}

