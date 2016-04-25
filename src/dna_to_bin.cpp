#include "binary.h"

#include <bitset>
#include <fstream>
#include <vector>
#include <iostream>
#include <chrono>
#include "sys/types.h"
#include "sys/sysinfo.h"
#include "string.h"


int parseLine(char* line){
        int i = strlen(line);
        while (*line < '0' || *line > '9') line++;
        line[i-3] = '\0';
        i = atoi(line);
        return i;
}


int getValue_v(){ //Note: this value is in KB!
    FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];


    while (fgets(line, 128, file) != NULL){
        if (strncmp(line, "VmSize:", 7) == 0){
            result = parseLine(line);
            break;
        }
    }
    fclose(file);
    return result;
}


int getValue_p(){ //Note: this value is in KB!
    FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];


    while (fgets(line, 128, file) != NULL){
        if (strncmp(line, "VmRSS:", 6) == 0){
            result = parseLine(line);
            break;
        }
    }
    fclose(file);
    return result;
}


int main(int argc, char *argv[])
{

    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    std::ifstream f;
    f.open("reads1.fasta");

    std::vector<Read> reads_1;

    std::string line;
    while(std::getline(f, line)){

        if (line[0] != '>'){

            reads_1.push_back(seq2bin(line, line.size()));
        }
    }

    f.close();

    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    std::cout << " - File 1 loaded (" << duration << " µs)" << std::endl;

    t1 = std::chrono::high_resolution_clock::now();

    f.open("reads2.fasta");

    std::vector<Read> reads_2;

    while(std::getline(f, line)){

        if (line[0] != '>'){

            reads_2.push_back(seq2bin(line, line.size()));
        }
    }

    f.close();

    t2 = std::chrono::high_resolution_clock::now();

    duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    std::cout << " - File 2 loaded (" << duration << " µs)" << std::endl;

    std::cout << " - Virtual memory used : " << getValue_v() << std::endl;
    std::cout << " - Physical memory used : " << getValue_p() << std::endl;

    t1 = std::chrono::high_resolution_clock::now();

    uint a=0, b=0, c=0;
    for (uint i=0; i<reads_1.size(); ++i){

        for (uint j=0; j<reads_1[i].seq.size(); j+=2){

            compare(reads_1[i].seq[j], reads_2[i].seq[j], a, b);

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

    return 0;
}
