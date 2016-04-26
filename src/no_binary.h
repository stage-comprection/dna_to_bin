#pragma once

#include "benchmarks_tools.h"
#include "utils.h"

namespace no_binary {

    // Compare two strings
    void compare(std::string& s1, std::string& s2, uint& a, uint& b){

        for (uint i=0; i < s1.size(); i+=2){

            if (s1[i] == s2[i]){

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
        std::string reads_1[nReads];
        std::string line;
        uint readCount = 0;

        while(std::getline(f1, line)){

            if (line[0] != '>'){

                reads_1[readCount] = line;
            }
        }

        f1.close();

        timePoint t2 = std::chrono::high_resolution_clock::now();

        printTime(t1, t2, "File 1 loaded");

        t1 = std::chrono::high_resolution_clock::now();

        std::string reads_2[nReads];
        readCount = 0;

        while(std::getline(f2, line)){

            if (line[0] != '>'){

                reads_2[readCount] = line;
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
