#pragma once

#include "benchmarks_tools.h"
#include "utils.h"

#include <bitset>

namespace bitset {

    typedef std::bitset<196> read;

    // Convert a sequence of char into binary
    void seq2bin(std::string& seq, read& bin, const uint s){

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


    // Compare two bitsets
    void compare(std::bitset<196>& b1, std::bitset<196>& b2, uint& a, uint& b){

        for (uint i=0; i<b1.size(); i+=2){

            if (b1[i] == b2[i] and b1[i+1] == b2[i+1]) {

                a++;

            } else {

                b++;
            }
        }
    }


    // Benchmark function
    void benchmark(std::ifstream& f1, std::ifstream& f2){

        const uint s=98;
        const uint nReads = countReads(f1);
        read* reads_1 = new read[nReads];
        read bin;
        std::string line;
        uint readCount = 0;

        timePoint t1 = std::chrono::high_resolution_clock::now();

        while(std::getline(f1, line)){

            if (line[0] != '>'){

                bin.reset();
                seq2bin(line, bin, s);
                reads_1[readCount] = bin;
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

                bin.reset();
                seq2bin(line, bin, s);
                reads_2[readCount] = bin;
                ++readCount;
            }
        }

        f2.close();

        t2 = std::chrono::high_resolution_clock::now();

        printTime(t1, t2, "File 2 loaded");

        t1 = std::chrono::high_resolution_clock::now();

        uint a=0, b=0, c=0;
        for (uint i = 0; i < nReads; ++i){

            compare(reads_1[i], reads_2[i], a, b);
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

        delete[] reads_1;
        delete[] reads_2;
    }

}
