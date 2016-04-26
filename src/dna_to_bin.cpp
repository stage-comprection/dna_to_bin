#include "int_array.h"
#include "dynamic_bitset.h"
#include "bitset.h"
#include "no_binary.h"
#include "bool_vector.h"

int main(int argc, char *argv[])
{

    system("echo 1 > /proc/sys/vm/drop_caches ");

    std::ifstream f1, f2;
    f1.open("reads1.fasta");
    f2.open("reads2.fasta");

    std::cout << std::endl;
    std::cout << " --------------------------------------- " << std::endl;
    std::cout << " > Method: bitsets " << std::endl;
    std::cout << " --------------------------------------- " << std::endl;
    bitset::benchmark(f1, f2);

    f1.close();
    f2.close();

    system("echo 1 > /proc/sys/vm/drop_caches");
    f1.open("reads1.fasta");
    f2.open("reads2.fasta");

    std::cout << std::endl;
    std::cout << " --------------------------------------- " << std::endl;
    std::cout << " > Method: boost dynamic bitsets " << std::endl;
    std::cout << " --------------------------------------- " << std::endl;

    dynamic_bitset::benchmark(f1, f2);

    f1.close();
    f2.close();

    system("echo 1 > /proc/sys/vm/drop_caches");
    f1.open("reads1.fasta");
    f2.open("reads2.fasta");

    std::cout << std::endl;
    std::cout << " --------------------------------------- " << std::endl;
    std::cout << " > Method: Array of ints " << std::endl;
    std::cout << " --------------------------------------- " << std::endl;

    int_array::benchmark(f1, f2);

    f1.close();
    f2.close();

    system("echo 1 > /proc/sys/vm/drop_caches");
    f1.open("reads1.fasta");
    f2.open("reads2.fasta");

    std::cout << std::endl;
    std::cout << " --------------------------------------- " << std::endl;
    std::cout << " > Method: Bool vector " << std::endl;
    std::cout << " --------------------------------------- " << std::endl;

    bool_vector::benchmark(f1, f2);

    f1.close();
    f2.close();

    system("echo 1 > /proc/sys/vm/drop_caches");
    f1.open("reads1.fasta");
    f2.open("reads2.fasta");

    std::cout << std::endl;
    std::cout << " --------------------------------------- " << std::endl;
    std::cout << " > Method: Simple strings " << std::endl;
    std::cout << " --------------------------------------- " << std::endl;

    no_binary::benchmark(f1, f2);

    f1.close();
    f2.close();

    return 0;
}
