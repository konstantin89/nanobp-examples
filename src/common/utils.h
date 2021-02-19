#pragma once

#include <optional>
#include <vector>
#include <fstream>
#include <string>

std::optional<std::vector<uint8_t>> readBinaryFile(std::string filePath);

bool writeBinaryFile(std::string filePath, std::vector<uint8_t>& contentToWrite);
