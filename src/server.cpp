#include "server.hpp"
#include "output.hpp"
#include "startup.hpp"

#include "btpro/config.hpp"
#include "btpro/evcore.hpp"

#ifndef _WIN32
#include <signal.h>
#endif // _WIN32

using namespace stomperd;
using namespace std::literals;

void server::accept(btpro::socket sock, btpro::ip::addr addr)
{
    j.cout() << "accept "sv << btpro::sock_addr(addr).to_text() << std::endl;

    queue_.once(std::chrono::seconds(2), [sock](auto...) mutable {
        j.cout() << "close "sv << sock.fd() << std::endl;
        sock.close();
    });
}

void server::create()
{
    btpro::config conf;
#ifndef _WIN32
    conf.require_features(EV_FEATURE_O1);
#endif //
    queue_.create(conf);
}

server::server(const startup& startup)
{
    create();

//    btpro::sock_addr addr(btpro::ipv4::any(61613));
//    addr.assign(argv[1]);

//    acceptor4_.listen(queue_,
//        LEV_OPT_REUSEABLE_PORT|LEV_OPT_DEFERRED_ACCEPT, addr);
}

void server::run()
{
#ifndef WIN32
    auto f = [&](auto...) {
        j.cout() << "stop"sv << std::endl;
        queue_.loop_break();
        return 0;
    };

    btpro::evs i;
    i.create(queue_, SIGINT, EV_SIGNAL|EV_PERSIST, f);
    i.add();

    btpro::evs t;
    t.create(queue_, SIGTERM, EV_SIGNAL|EV_PERSIST, f);
    t.add();
#endif // _WIN32

    queue_.dispatch();
}
