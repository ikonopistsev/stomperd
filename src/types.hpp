#pragma once

#include "e4pp/e4pp.hpp"

namespace stomperd {

// структура используется для передачи
struct sock_addr_arg
{
    sockaddr* p;
    ev_socklen_t sz;

    const sockaddr* operator->() const noexcept
    {
        assert(p);
        return p;
    }

    const in_addr* sin_addr() const noexcept
    {
        assert(p);
        return &reinterpret_cast<sockaddr_in*>(p)->sin_addr;
    }

    const in6_addr* sin6_addr() const noexcept
    {
        assert(p);
        return &reinterpret_cast<sockaddr_in6*>(p)->sin6_addr;
    }
};

} // namespace stomperd