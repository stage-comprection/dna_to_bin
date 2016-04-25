#pragma once

#include "bin_conversion.h"

struct Read{

    const uint32_t size;
    uint8_t* seq;
};


Read seq2bin(std::string& seq, const uint32_t s){

    uint d = s%4;
    uint s2 = s + (d>0);

    // If sequence length is not multiple of 4, 'A's are added in the end to get a multipe of 4
    for (uint i=0; i < d; ++i){

        seq += 'A';
    }

    uint8_t bin[s2];

    for (uint i=0; i<s2; i+=4){

        bin[i] = seq2binTable[seq.substr(i, i+3)];
    }


    return Read {s, bin};
}



std::string bin2seq(const Read& r){

    std::string out;

    uint s = sizeof(r.seq) / sizeof(r.seq[0]);

    for (uint i=0; i<s; ++i){

        out += bin2seqTable[r.seq[i]];
    }

    return out.substr(0, r.size);
}



void compare(const uint8_t c1, const uint8_t c2, uint& a, uint& b){

    for(uint i=0; i<8; i+=2) {

        if(((c1&(1<<i))!=0) == ((c2&(1<<i))!=0) and ((c1&(1<<(i+1)))!=0) == ((c2&(1<<(i+1)))!=0)){

            ++a;

        } else {

            ++b;
        }
    }
}
