#include "utils.h"

#include <fstream>
#include <iostream>


std::optional<std::vector<uint8_t>> utils::readBinaryFile(std::string filePath)
{
    std::ifstream fileStream(filePath, std::ios::in | std::ios::binary);

    if (!fileStream.is_open())
    {
        return {};
    }

    fileStream.seekg(0, std::ios::end);
    auto fileSize = fileStream.tellg();

    if (0 == fileSize)
    {
        fileStream.close();
        return {};
    }

    fileStream.seekg(0, std::ios::beg);

    std::vector<uint8_t> fileBuffer(fileSize, 0);

    uint8_t* bufferReadPtr = &fileBuffer[0];

    fileStream.read(
        reinterpret_cast <char*>(bufferReadPtr),
        fileSize);

    fileStream.close();

    return fileBuffer;
}

bool utils::writeBinaryFile(std::string filePath, std::vector<uint8_t>& contentToWrite)
{
    std::ofstream fileStream(filePath, std::ios::out | std::ios::binary);

    if (contentToWrite.empty())
    {
        return false;
    }

    if (!fileStream.is_open())
    {
        return false;
    }

    uint8_t* bufferToWritePtr = &contentToWrite[0];

    fileStream.write(
        reinterpret_cast <char*>(bufferToWritePtr),
        contentToWrite.size());

    fileStream.close();

    return true;
}


void utils::printMessageObject(ExampleMessage& message)
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
