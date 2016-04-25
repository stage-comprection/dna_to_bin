#pragma once

#include <string>
#include <bitset>

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


void compare(std::bitset<196>& b1, std::bitset<196>& b2, uint& a, uint& b){

    for (uint i=0; i<b1.size(); i+=2){

        if (b1[i] == b2[i] and b1[i+1]==b2[i+1]){
            a++;
        }else{
            b++;
        }
    }
}
