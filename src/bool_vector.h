#pragma once

#include "benchmarks_tools.h"
#include "utils.h"

namespace bool_vector {

    typedef std::vector<bool> read;

    // Convert a sequence of char into binary
    read seq2bin(std::string& seq, const uint s){

        read r (2*s, false);

        for (uint i=0; i < s; ++i){

            switch(seq[i]){

                case 'T':
                    r[2*i] = true;
                    r[2*i+1] = true;
                    break;

                case 'C':
                    r[2*i] = true;
                    break;

                case 'G':
                    r[2*i+1] = true;
                    break;

                default:
                    break;
            }
        }

        return r;
    }


    // Compare two bitsets
    void compare(read& b1, read& b2, uint& a, uint& b){

        for (uint i=0; i<b1.size(); i+=2){

            if (b1[i] == b2[i] and b1[i+1] == b2[i+1]){

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
        read reads_1[nReads];
        std::string line;
        uint readCount = 0;

        while(std::getline(f1, line)){

            if (line[0] != '>'){

                reads_1[readCount] = seq2bin(line, s);;
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

                reads_2[readCount] = seq2bin(line, s);;
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
    }

}
