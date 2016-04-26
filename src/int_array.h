#pragma once

#include "utils.h"
#include "benchmarks_tools.h"
#include "hash_tables.h"

#include <utility>


namespace int_array {

    typedef std::pair<uint32_t, uint8_t*> read;

    // Convert a sequence into an array of uint8_t
    read seq2bin(std::string& seq, const uint32_t s, const uint32_t s2){

        // If sequence length is not multiple of 4, 'A's are added in the end to get a multipe of 4
        for (uint i=0; i < s2-s; ++i){

            seq += 'A';
        }

        uint8_t* bin = new uint8_t[s2/4]; // !!! Deleted in cleanup()

        for (uint i=0; i<s2; i+=4){

            bin[i/4] = seq2binTable[seq.substr(i, 4)];

        }

        return read (s, bin);
    }



    // Convert an array of int into a sequence
    std::string bin2seq(const read& r){

        std::string out;

        for (uint i=0; i<(sizeof(r.second)/sizeof(r.second[0])); ++i){

            out += bin2seqTable[r.second[i]];
        }

        return out.substr(0, r.first);
    }



    // Compare two uint8_t
    void compare(const uint8_t c1, const uint8_t c2, uint& a, uint& b){

        for(uint i=0; i<8; i+=2) {

            if(((c1&(1<<i))!=0) == ((c2&(1<<i))!=0) and ((c1&(1<<(i+1)))!=0) == ((c2&(1<<(i+1)))!=0)){

                ++a;

            } else {

                ++b;
            }
        }
    }


    // Cleanup these ugly "new" array
    void cleanup(read* r1, read* r2, uint s){

        for (uint i=0; i < s; ++i){

            delete[] r1[i].second;
            delete[] r2[i].second;
        }
    }


    // Benchmark function
    void benchmark(std::ifstream& f1, std::ifstream& f2){

        timePoint t1 = std::chrono::high_resolution_clock::now();

        const uint nReads = countReads(f1);
        const uint32_t s = getReadSize(f1);
        uint s2 = s + s%4;
        read* reads_1 = new read[nReads];
        std::string line;
        uint readCount = 0;

        while(std::getline(f1, line)){

            if (line[0] != '>'){

                reads_1[readCount] = seq2bin(line, s, s2);
                ++readCount;
            }
        }

        f1.close();

        timePoint t2 = std::chrono::high_resolution_clock::now();

        printTime(t1, t2, "File 1 loaded");

        t1 = std::chrono::high_resolution_clock::now();

        read* reads_2 = new read[nReads];
        readCount = 0;

        while(std::getline(f2, line)){

            if (line[0] != '>'){

                reads_2[readCount] = seq2bin(line, s, s2);
                ++readCount;
            }
        }

        f2.close();

        t2 = std::chrono::high_resolution_clock::now();

        printTime(t1, t2, "File 2 loaded");

        t1 = std::chrono::high_resolution_clock::now();

        uint a=0, b=0, c=0;

        for (uint i = 0; i < nReads; ++i){

            for (uint j=0; j < s2/4; j++){

                compare(reads_1[i].second[j], reads_2[i].second[j], a, b);
            }

            a -= s2-s;

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

        cleanup(reads_1, reads_2, nReads);

        delete[] reads_1;
        delete[] reads_2;
    }

}
