#pragma once

#include <optional>
#include <vector>
#include <fstream>
#include <string>

namespace utils
{
    const char ENCODED_MESSAGE_BIN_FILE_NAME[] = "message.bin";

    std::optional<std::vector<uint8_t>> readBinaryFile(std::string filePath);

    bool writeBinaryFile(std::string filePath, std::vector<uint8_t>& contentToWrite);
}


