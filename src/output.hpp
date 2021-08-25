#pragma once

#include <iostream>

namespace stomperd {

class output
{
    std::size_t verbose_ = { 0u };
    std::ostream& log_time(std::ostream& output);

public:
    output() = default;

    void set(std::size_t verbose);

    std::ostream& cerr()
    {
        return log_time(std::cerr);
    }

    std::ostream& cout()
    {
        return log_time(std::cout);
    }

    template<class F>
    std::ostream& cout(F fn)
    {
        if (verbose_)
            return cout() << fn();

        return std::cout;
    }
};

} // namespace stomperd

extern stomperd::output j;
