#ifndef FILEREADER_HPP
#define FILEREADER_HPP
#include "FileReader.hpp"

#include "LinkedList.hpp"
#include <string>

class FileReader
{
public:
    static LinkedList readFromFile(const std::string &filename);
};

#endif
