#include "utils.h"



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