#include "pb_decode.h"
#include "auto_generated/ExampleMessage.pb.h"
#include "common/utils.h"

#include <vector>
#include <string>
#include <iostream>


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

    uint8_t buffer[1024] = { 0 };

    if (stream->bytes_left > sizeof(buffer) - 1)
        return false;

    if (!pb_read(stream, buffer, stream->bytes_left))
        return false;

    std::string tempStr = std::string((char*)buffer, sizeof(buffer));

    outStrVector->push_back(std::move(tempStr));

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

/**
* @brief: Print the content of ExampleMessage to std::out.
*/
void printDecodedMessage(ExampleMessage& message)
{
    std::cout << "ExampleMessage content" << std::endl;

    std::cout << "message.number=" << message.number << std::endl;

    auto str = reinterpret_cast<std::string*>(message.str.arg);

    std::cout << "message.str=" << str->c_str() << std::endl;

    auto str_array = reinterpret_cast<std::vector<std::string>*>(message.str_array.arg);

    for (int i = 0; i < str_array->size(); i++)
    {
        std::cout << "message.str_array[" << i << "]=" << str_array->at(i).c_str() << std::endl;
    }

    auto sub_message_array = reinterpret_cast<std::vector<SubMessage>*>(message.sub_message_array.arg);

    for (int i = 0; i < sub_message_array->size(); i++)
    {
        auto sub_number = sub_message_array->at(i).sub_number;
        auto sub_str = reinterpret_cast<std::string*>(sub_message_array->at(i).sub_string.arg);

        std::cout << "message.sub_message_array[" << i << "]=" 
            << sub_number << ", " << sub_str->c_str() << std::endl;
    }
}

int runDecoderExample()
{
    auto fileContent = utils::readBinaryFile(utils::ENCODED_MESSAGE_BIN_FILE_NAME);

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


    pb_istream_t stream = pb_istream_from_buffer(
        fileContent.value().data(),
        fileContent.value().size());

    auto status = pb_decode(&stream, ExampleMessage_fields, &message);

    printDecodedMessage(message);

    return 0;
}




int main()
{
    return runDecoderExample();
}
