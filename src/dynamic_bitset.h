#pragma once

#include "utils.h"
#include "benchmarks_tools.h"

#include <boost/dynamic_bitset.hpp>


namespace dynamic_bitset {

    typedef boost::dynamic_bitset<> read;

    // Convert a sequence of char into binary
    read seq2bin(std::string& seq, const uint s){

        read bin(2*s);
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

        return bin;
    }

    // Convert a binary sequence into char
    template <typename T>
    std::string bin2seq(T& bin, const uint s){

        std::string seq(s, 'x');

        for (uint i=0; i<s; i+=2){

            switch(bin[i]){
                case 1:
                    switch(bin[i+1]){
                        case 1:
                            seq[i/2] = 'T';
                            break;
                        default:
                            seq[i/2] = 'G';
                            break;
                    }
                    break;
                default:
                    switch(bin[i+1]){
                        case 1:
                            seq[i/2] = 'C';
                            break;
                        default:
                            seq[i/2] = 'A';
                            break;
                    }
                    break;
            }
        }

        return seq;
    }

    // RevComp on a bitset
    template <typename T>
    T revComp(T& b){

        T r;
        uint s = b.size()-1;

        for (int i=s; i>=0; --i){

            r.set(s-i, !b[i]);
        }

        return r;
    }

    // Compare two bitsets
    void compare(read b1, read b2, uint& a, uint& b){

        for (uint i=0; i<b1.size(); i+=2){

            if (b1[i] == b2[i] and b1[i+1]==b2[i+1]){
                a++;
            } else {
                b++;
            }
        }
    }

    // Benchmark function
    void benchmark(std::ifstream& f1, std::ifstream& f2){

        timePoint t1 = std::chrono::high_resolution_clock::now();

        const uint nReads = countReads(f1);
        read* reads_1 = new read[nReads];
        std::string line;
        uint readCount = 0;

        while(std::getline(f1, line)){

            if (line[0] != '>'){

                reads_1[readCount] = seq2bin(line, line.size());
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

                reads_2[readCount] = seq2bin(line, line.size());
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
