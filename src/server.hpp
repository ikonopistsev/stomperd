#pragma once

#include "btpro/queue.hpp"
#include "btpro/tcp/acceptorfn.hpp"
#include "startup.hpp"

namespace stomperd {

class server
{
    btpro::queue queue_;
    btpro::tcp::acceptorfn<server> acceptor4_{ *this, &server::accept };

    void accept(btpro::socket sock, btpro::ip::addr addr);

    void create();

public:
    server(const startup& startup);

    void run();
};

} // namespace stomperd
