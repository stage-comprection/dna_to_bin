#include "int_array.h"
#include "dynamic_bitset.h"
#include "bitset.h"

int main(int argc, char *argv[])
{

    std::ifstream f1, f2;
    f1.open("reads1.fasta");
    f2.open("reads2.fasta");

    bitset::benchmark(f1, f2);

    dynamic_bitset::benchmark(f1, f2);

    int_array::benchmark(f1, f2);

    return 0;
}
