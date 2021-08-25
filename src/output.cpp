#include "output.hpp"

#include "btdef/date.hpp"

namespace stomperd {

std::ostream& output::log_time(std::ostream& output)
{
    return output << btdef::date::log_time_text() << ' ';
}

void output::set(std::size_t verbose)
{
    verbose_ = verbose;
}

} // namespace stomperd

stomperd::output j;
