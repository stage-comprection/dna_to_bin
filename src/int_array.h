#pragma once

#include "utils.h"
#include "benchmarks_tools.h"
#include "hash_tables.h"

#include <utility>


namespace int_array {
    typedef std::pair<uint32_t, uint8_t[]> read;

    read seq2bin(std::string& seq, const uint32_t s){


        uint d = s%4;
        uint s2 = s + (d>0);

        // If sequence length is not multiple of 4, 'A's are added in the end to get a multipe of 4
        for (uint i=0; i < d; ++i){

            seq += 'A';
        }

        uint8_t bin[s2/4];

        for (uint i=0; i<s2; i+=4){

            bin[i] = seq2binTable[seq.substr(i, 4)];

        }

        return read {s, bin};
    }



    //std::string bin2seq(const Read& r){

    //    std::string out;

    //    for (uint i=0; i<r.seq.size(); ++i){

    //        out += bin2seqTable[r.seq[i]];
    //    }

    //    return out.substr(0, r.size);
    //}



    void compare(const uint8_t c1, const uint8_t c2, uint& a, uint& b){

        for(uint i=0; i<8; i+=2) {

            if(((c1&(1<<i))!=0) == ((c2&(1<<i))!=0) and ((c1&(1<<(i+1)))!=0) == ((c2&(1<<(i+1)))!=0)){

                ++a;

            } else {

                ++b;
            }
        }
    }



    void benchmark(std::ifstream& f1, std::ifstream& f2){

        timePoint t1 = std::chrono::high_resolution_clock::now();

        const uint nReads = countReads(f1);
        read reads_1[nReads];
        std::string line;
        uint readCount = 0;

        while(std::getline(f1, line)){

            if (line[0] != '>'){


            }
        }

        f1.close();

        timePoint t2 = std::chrono::high_resolution_clock::now();

        printTime(t1, t2, "File 1 loaded");

        t1 = std::chrono::high_resolution_clock::now();

        read reads_2[nReads];
        readCount = 0;

        while(std::getline(f2, line)){

            if (line[0] != '>'){

                reads_2[readCount] = seq2bin(line, s);
            }
        }

        f2.close();

        t2 = std::chrono::high_resolution_clock::now();

        printTime(t1, t2, "File 2 loaded");

        t1 = std::chrono::high_resolution_clock::now();

        uint a=0, b=0, c=0;

        for (uint i = 0; i < nReads; ++i){

            for (uint j=0; j < sizeof(reads[i].second)/sizeof(reads[i].second[0]); j++){

                compare(reads_1[i].second[j], reads_2[i].second[j], a, b);
            }

            ++c;
        }

        t2 = std::chrono::high_resolution_clock::now();

        printTime(t1, t2, "Comparison ended");

        std::cout << std::endl;
        std::cout << " - Virtual memory used : " << getValue_v() << std::endl;
        std::cout << " - Physical memory used : " << getValue_p() << std::endl;

        std::cout << std::endl;
        std::cout << "Equal : " << a << std::endl;
        std::cout << "Different : " << b << std::endl;
        std::cout << "Total : " << c << std::endl << std::endl;
    }

}
