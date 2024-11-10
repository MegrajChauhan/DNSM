#include "utils.hpp"

DNSM::Randomizer::Randomizer()
{
    std::random_device rd;
    mt_engine = std::mt19937(rd());
}

int DNSM::Randomizer::generate_int(int min, int max)
{
    std::uniform_int_distribution<int> dist(min, max);
    return dist(mt_engine);
}

double DNSM::Randomizer::generate_double(double min, double max)
{
    std::uniform_real_distribution<double> dist(min, max);
    return dist(mt_engine);
}

bool DNSM::Randomizer::generate_bool()
{
    std::bernoulli_distribution dist(0.5);
    return dist(mt_engine);
}

float DNSM::Randomizer::generate_float_01()
{
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    return dist(mt_engine);
}

char DNSM::Randomizer::generate_char()
{
    std::uniform_int_distribution<int> dist(0, 61);
    const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    return charset[dist(mt_engine)];
}