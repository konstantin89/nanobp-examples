#include "pb_decode.h"
#include "auto_generated/ExampleMessage.pb.h"

#include <vector>
#include <fstream>
#include <string>
#include <optional>

std::optional<std::vector<uint8_t>> readBinaryFile(std::string filePath)
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


int main()
{
    auto fileContent = readBinaryFile("message.bin");

    size_t messageLength = 0;

    ExampleMessage message = ExampleMessage_init_default;

    pb_istream_t stream = pb_istream_from_buffer(
        fileContent.value().data(),
        fileContent.value().size());

    auto status = pb_decode(&stream, ExampleMessage_fields, &message);





    return 0;
}
