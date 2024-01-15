#pragma once

#include "e4pp/util.hpp"

namespace stomperd {

extern e4pp::util::output u;

inline std::ostream& cerr() noexcept
{
    return u.cerr();
}

inline std::ostream& cout() noexcept
{
    return u.cout();
}

template<class F>
void do_trace(F fn) noexcept
{
    u.do_trace(std::move(fn));
}

template<class F>
void trace(F fn) noexcept
{
    u.trace(std::move(fn));
}

struct sock_addr_arg;

std::string to_string(const sock_addr_arg& val);

} // namespace stomperd