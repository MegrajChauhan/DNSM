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

    template <typename T>
    class pointer
    {
        T *orig;

    public:
        explicit pointer(T *ptr = nullptr) : orig(ptr) {}

        ~pointer() DNSM::pointer<T>::~pointer()
        {
            delete orig;
        }

        pointer(const pointer &) = delete;

        pointer &operator=(const pointer &) = delete;

        pointer(pointer &&other) noexcept : orig(other.orig)
        {
            other.orig = nullptr;
        }

        pointer &operator=(pointer &&other) noexcept
        {
            if (this != &other)
            {
                delete orig;
                orig = other.orig;
                other.orig = nullptr;
            }
            return *this;
        }

        T *get() const
        {
            return orig;
        }

        T &operator*() const
        {
            return *orig;
        }

        T *operator->() const
        {
            return orig;
        }

        T *release()
        {
            T *temp = orig;
            orig = nullptr;
            return temp;
        }

        void reset(T *ptr = nullptr)
        {
            if (orig != ptr)
            {
                delete orig;
                orig = ptr;
            }
        }
    };
};

#endif