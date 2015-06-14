#include "utils.h"
#include <random>
#include <numeric>

namespace utils
{

void prepareIndices(std::vector<int>& indices, int max, int numLast, int numOther)
{
    if(numLast != -1)
    {
        if (numLast > max)
            numLast = max;
        if (numLast + numOther > max)
            numOther = max - numLast;
    }

    auto totalSize = (numLast == -1) ? max : numLast + numOther;
    indices.resize(totalSize);

    if(numLast == -1)
    {
        std::iota(indices.begin(), indices.end(), 0);
    }
    else
    {
        std::iota(indices.begin(), indices.begin() + numLast, max - numLast);

        std::vector<int> temp(max - numLast);
        std::iota(temp.begin(), temp.end(), 0);
        std::random_shuffle(temp.begin(), temp.end());
        std::copy_n(temp.begin(), numOther, indices.begin() + numLast);
    }

    std::random_shuffle(indices.begin(), indices.end());
}

}
