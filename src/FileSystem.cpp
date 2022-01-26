#include <fstream>
#include "FileSystem.h"

bool FileSystem::fileExists(fs::path &pathToFile) {
    if (pathToFile.empty() || !pathToFile.has_filename()) return false;
    return fs::exists(pathToFile);
}

bool FileSystem::checkFileExtension(fs::path &pathToFile, std::string extension) {
    if (pathToFile.empty() || !pathToFile.has_extension()) return false;
    return pathToFile.extension() == extension;
}

cv::Mat FileSystem::loadImage(std::string &stringPath) {
    return cv::imread(stringPath, cv::ImreadModes::IMREAD_COLOR);
}

cv::Mat FileSystem::loadImage(fs::path &pathToFile) {
    std::string stringPath(pathToFile);
    return loadImage(stringPath);
}

FileSystem::Lines FileSystem::readLines(fs::path &pathToFile) {
    if (!fileExists(pathToFile))
        throw FileDoesNotExist(pathToFile);

    Lines fileData;
    std::ifstream in(pathToFile.c_str());
    std::string line;
    while (std::getline(in, line)) {
        if (!line.empty()) {
            fileData.push_back(line);
        }
    }
    return fileData;
}
