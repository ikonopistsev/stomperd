#include "output.hpp"
#include "types.hpp"

namespace stomperd {

// объявляем глобально
e4pp::util::output u;

std::string to_string(const sock_addr_arg& addr_arg)
{
    char text_buf[INET6_ADDRSTRLEN];
    
    auto family = addr_arg->sa_family;
    const auto addr_ptr = (family == AF_INET) ? 
        static_cast<const void*>(addr_arg.sin_addr()) :
        static_cast<const void*>(addr_arg.sin6_addr());

    auto rc = e4pp::detail::check_pointer("evutil_inet_ntop",
        evutil_inet_ntop(family, addr_ptr, text_buf, sizeof(text_buf)));

    // check addr is short ipv6
    std::string out;
    out.reserve(INET6_ADDRSTRLEN);
    if (rc[0] != ':') {
        out = rc;
    } else {
        out += '[';
        out += rc;
        out += ']';
    }
    return out;
}

} // namespace stomperd