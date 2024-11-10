#ifndef _UTILS_
#define _UTILS_

#include <random>
#include <vector>

namespace DNSM
{
    class Randomizer
    {
    private:
        std::mt19937 mt_engine;

    public:
        Randomizer();

        int generate_int(int min, int max);
        double generate_double(double min, double max);
        bool generate_bool();
        float generate_float_01();

        char generate_char();
    };
};

#endif