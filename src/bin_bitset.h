#pragma once

#include <string>

// Convert a sequence of char into binary
template <typename T>
void seq2bin(std::string& seq, T& bin, const uint s){

    for (uint i=0; i < s; ++i){

        switch(seq[i]){

            case 'T':
                bin.flip(2*i);
                bin.flip(2*i+1);
                break;

            case 'C':
                bin.flip(2*i);
                break;

            case 'G':
                bin.flip(2*i+1);
                break;

            default:
                break;
        }
    }
}
