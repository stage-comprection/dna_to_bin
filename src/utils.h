#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

// Splits a std::string into a std::vector of std::strings according to a specified delimiter
std::vector<std::string> split(std::string str, const std::string delimiter){

    std::vector<std::string> output;
    size_t pos;

    while ((pos = str.find(delimiter)) != std::string::npos){

        output.push_back(str.substr(0, pos));
        str.erase(0, pos + delimiter.length());
    }

    output.push_back(str.substr(0, pos));

    return output;
}




// Sets back a file line index to 0 (getline will start from the beginning of the file again)
void resetFileIndex(std::ifstream& file){

    file.clear();
    file.seekg (0, std::ios::beg);
}




// Counts reads in a fasta file
const uint countReads(std::ifstream& file){

    uint count = 0;
    std::string line;

    while(std::getline(file, line)){

        if (line[0] == '>') ++count;
    }

    resetFileIndex(file);

    return count;
}


uint32_t getReadSize(std::ifstream& f){

    bool found = false;
    uint32_t s = 0;
    std::string line;

    while (std::getline(f, line) and !found){

        if (line[0] != '>'){

            s = line.size();
            if (s > 0) found = true;
        }
    }

    resetFileIndex(f);

    return s;
}
