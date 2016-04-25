#pragma once

#include <vector>
#include <string>

// Convert a sequence of char into binary
std::vector<bool> seq2bin(const std::string& seq, const uint s){

    std::vector<bool> bin;
    bin.resize(2*s);

    for (uint i=0; i < s; ++i){

        switch(seq[i]){

            case 'T':
                bin[2*i] = true;
                bin[2*i+1] = true;
                break;

            case 'C':
                bin[2*i] = true;
                break;

            case 'G':
                bin[2*i+1] = true;
                break;

            default:
                break;
        }
    }

    return bin;
}
