#include <vector>

int Example2(std::vector<int>& vector)
{
    int zeroCount = 0;

    for (int& it : vector) {
        if (it == 0) {
            ++zeroCount;
        }
    }
    return zeroCount;
}