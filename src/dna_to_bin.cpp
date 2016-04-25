#include "binary.h"
#include <bitset>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>


int main(int argc, char *argv[])
{

    std::ifstream f;
    f.open("reads1.fasta");

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

    f.open("reads2.fasta");
    std::vector<std::bitset<2*s>> reads_2;

    while(std::getline(f, line)){

        if (line[0] == '>'){

            bin.reset();
            seq2bin(line, bin, s);
            reads_2.push_back(bin);
        }
    }

    f.close();

    uint a=0, b=0, c=0;
    for (uint i=0; i<reads_1.size(); ++i){

        for (uint j=0; j<reads_1[i].size(); j+=2){

            if (reads_1[i] == reads_2[i] and reads_1[i+1] == reads_2[i+1]){

                ++a;

            } else {

                ++b;
            }
        }

        ++c;
    }

    std::cout << std::endl;
    std::cout << "Equal : " << a << std::endl;
    std::cout << "Different : " << b << std::endl;
    std::cout << "Total : " << c << std::endl << std::endl;
}