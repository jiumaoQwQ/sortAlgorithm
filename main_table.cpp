#define RANDOM_MAX_VALUE 100
#define ITERATIONS 10
#include "sortSystem_table.h"

#include <vector>
#include <fstream>
#include <string>

SortSystem sortSystem;
std::vector<SortSystem::Type> Types = {
    SortSystem::Type::POSITIVE,
    SortSystem::Type::REVERSE,
    SortSystem::Type::RANDOM};

std::vector<int> sortSize = {100, 1000, 3000, 6000, 10000};

std::vector<std::string> res;
std::ofstream output;

void save()
{
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            output << res[i * 4 + j];
        }
        output << std::endl;
    }
    output << std::endl;
}

int main()
{
    output.open("./table.md", std::ios::out);

    output << " - Format: timeExpense timesOfComprision timesOfMoves \n \n \
 - Unit of time : microseconds \n \n";
    res.reserve(4 * 7);
    res = {"| |", "POSITIVE|", "REVERSE|", "RANDOM|",
           "|-|", "-|", "-|", "-|",
           "|insertionSort|", "", "", "",
           "|selectionSort|", "", "", "",
           "|mergeSort|", "", "", "",
           "|heapSort|", "", "", "",
           "|quickSort|", "", "", ""};

    for (auto size : sortSize)
    {
        output << "n = " << size << std::endl;

        for (auto type : Types)
        {
            sortSystem.init(size, type, &res);
            sortSystem.run();
        }
        save();
    }
    return 0;
}