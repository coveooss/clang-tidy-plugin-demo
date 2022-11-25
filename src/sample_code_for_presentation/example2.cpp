#include <vector>

int Example2(std::vector<int>& vector)
{
    int zeroCount = 0;

    for (std::vector<int>::iterator it = vector.begin(); it != vector.end(); ++it) {
        if (*it == 0) {
            ++zeroCount;
        }
    }
    return zeroCount;
}