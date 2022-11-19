#define RANDOM_MAX_VALUE 100
#define ITERATIONS 10
#include "sortSystem.h"

#include <vector>

int main()
{
    SortSystem sortSystem;
    std::vector<SortSystem::Type> Types = {
        SortSystem::Type::POSITIVE,
        SortSystem::Type::REVERSE,
        SortSystem::Type::RANDOM};

    std::vector<int> sortSize = {100, 1000, 3000, 6000, 10000};

    for (auto size : sortSize)
    {
        std::cout << "n = " << size << std::endl;

        for (auto type : Types)
        {
            sortSystem.init(size, type);
            sortSystem.run();
        }
    }

    return 0;
}