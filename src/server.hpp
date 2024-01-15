#pragma once

#include "e4pp/queue.hpp"
#include "e4pp/listener.hpp"
#include "types.hpp"
#include "output.hpp"
#include "startup.hpp"
#include <list>


namespace stomperd {

class server
{
    bool running_{true};

    e4pp::queue queue_{};
    e4pp::listener listener_{};

    e4pp::acceptor_fn<server> accept_{&server::on_accept, *this};
    void on_accept(evutil_socket_t fd, sockaddr* sockaddr, int socklen);

public:
    server(startup& startup);

    void run();

    template<class Fn>
    void disable(e4pp::queue& other, Fn fn)
    {
        queue_.once(other, [&](){
            listener_.disable();
            fn();
        });
    }

    void disable();

    void stop();

};

} // namespace stomperd
