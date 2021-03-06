#include "pb_decode.h"
#include "auto_generated/ExampleMessage.pb.h"
#include "common/utils.h"

#include <vector>
#include <string>

/**
* @brief: NanoPB encoder for repeated string type.
*/
bool decode_string(pb_istream_t *stream, const pb_field_t *field, void **arg);

/**
* @brief: NanoPB encoder for repeated string type.
*/
bool decode_string_vector(pb_istream_t *stream, const pb_field_t *field, void **arg);

/**
* @brief: NanoPB encoder for repeated string type.
*/
bool decode_submessage_vector(pb_istream_t *stream, const pb_field_t *field, void **arg);


int runDecoderExample()
{
    // Read encoded message

    auto fileContent = utils::readBinaryFile(utils::ENCODED_MESSAGE_BIN_FILE_NAME);


    // Fill the data needed for decoding

    size_t messageLength = 0;

    std::string decodedStr = {};
    std::vector<std::string> decodedStrArray = {};
    std::vector<SubMessage> decodedSubmessageArray = {};

    ExampleMessage message = ExampleMessage_init_default;

    message.str.funcs.decode = decode_string;
    message.str.arg = &decodedStr;

    message.str_array.funcs.decode = decode_string_vector;
    message.str_array.arg = &decodedStrArray;

    message.sub_message_array.arg = &decodedSubmessageArray;
    message.sub_message_array.funcs.decode = decode_submessage_vector;


    // Decode the message

    pb_istream_t stream = pb_istream_from_buffer(
        fileContent.value().data(),
        fileContent.value().size());

    auto status = pb_decode(&stream, ExampleMessage_fields, &message);


    // Print the decoded message

    utils::printMessageObject(message);

    return 0;
}

int main()
{
    return runDecoderExample();
}


// Decoder functions

bool decode_string(pb_istream_t *stream, const pb_field_t *field, void **arg)
{
    std::string* outStr = reinterpret_cast<std::string*>(*arg);

    std::vector<uint8_t> buffer = std::vector<uint8_t>(stream->bytes_left + 1, 0);

    if (stream->bytes_left > buffer.size() - 1)
        return false;

    if (!pb_read(stream, buffer.data(), stream->bytes_left))
        return false;

    *outStr = std::string(reinterpret_cast<char*>(buffer.data()), buffer.size());

    return true;
}

bool decode_string_vector(pb_istream_t *stream, const pb_field_t *field, void **arg)
{
    std::vector<std::string>* outStrVector = reinterpret_cast<std::vector<std::string>*>(*arg);

    std::vector<uint8_t> buffer = std::vector<uint8_t>(stream->bytes_left + 1, 0);

    if (stream->bytes_left > buffer.size() - 1)
        return false;

    if (!pb_read(stream, buffer.data(), stream->bytes_left))
        return false;

    std::string strinElement = std::string(
        reinterpret_cast<char*>(buffer.data()),
        buffer.size());

    outStrVector->push_back(std::move(strinElement));

    return true;
}

bool decode_submessage_vector(pb_istream_t *stream, const pb_field_t *field, void **arg)
{
    std::vector<SubMessage>* outSubmessageVector = reinterpret_cast<std::vector<SubMessage>*>(*arg);

    std::string* subStrPtr = new std::string();


    SubMessage submessage = SubMessage_init_default;
    submessage.sub_string.arg = subStrPtr;
    submessage.sub_string.funcs.decode = decode_string;

    if (!pb_decode(stream, SubMessage_fields, &submessage))
        return false;

    outSubmessageVector->push_back(submessage);

    return true;
}


