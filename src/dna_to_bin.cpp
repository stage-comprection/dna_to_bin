#include "binary.h"
#include "bool_vector.h"
#include <bitset>
#include <fstream>
#include <iostream>
#include <chrono>


int main(int argc, char *argv[])
{

    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    std::ifstream f;
    f.open("reads1.fasta");

    std::cout<<std::endl;

    std::string line;

    const uint s = 98;
    std::bitset<2*s> bin;
    std::vector<std::bitset<2*s>> reads_1;

    while(std::getline(f, line)){

        if (line[0] != '>'){

            bin.reset();
            seq2bin(line, bin, s);
            reads_1.push_back(bin);
        }
    }

    f.close();

    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    std::cout << " - File 1 loaded (" << duration << " µs)" << std::endl;

    t1 = std::chrono::high_resolution_clock::now();

    f.open("reads2.fasta");
    std::vector<std::bitset<2*s>> reads_2;

    while(std::getline(f, line)){

        if (line[0] != '>'){

            bin.reset();
            seq2bin(line, bin, s);
            reads_2.push_back(bin);
        }
    }

    f.close();

    t2 = std::chrono::high_resolution_clock::now();

    duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    std::cout << " - File 2 loaded (" << duration << " µs)" << std::endl;

    t1 = std::chrono::high_resolution_clock::now();

    uint a=0, b=0, c=0;
    for (uint i=0; i<reads_1.size(); ++i){

        for (uint j=0; j<reads_1[i].size(); j+=2){

            if (reads_1[i][j] == reads_2[i][j] and reads_1[i][j+1] == reads_2[i][j+1]){

                ++a;

            } else {

                ++b;
            }
        }

        ++c;
    }

    t2 = std::chrono::high_resolution_clock::now();

    duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    std::cout << " - Comparison ended (" << duration << " µs)" << std::endl;

    std::cout << std::endl;
    std::cout << "Equal : " << a << std::endl;
    std::cout << "Different : " << b << std::endl;
    std::cout << "Total : " << c << std::endl << std::endl;
}
