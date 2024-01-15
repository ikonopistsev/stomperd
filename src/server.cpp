#include "server.hpp"
#include "startup.hpp"
#include "e4pp/config.hpp"
#include "e4pp/ev.hpp"
#include "output.hpp"
#include "types.hpp"
#include <functional>

#ifndef _WIN32
#include <signal.h>
#endif // _WIN32

using namespace stomperd;
using namespace std::literals;

// void server::listen(const btpro::ipv4::addr& addr)
// {
//     j.trace([&]{
//         return std::string("listen ") + addr.to_string() +
//             ':' + std::to_string(addr.port());
//     });

//     acceptor_.listen(queue_,
//         LEV_OPT_REUSEABLE_PORT|LEV_OPT_DEFERRED_ACCEPT, addr);
// }

// void server::stop_server()
// {
//     running_ = false;
//     j.cout() << "stop server"sv << std::endl;
//     acceptor_.close();
// }

server::server(startup& startup)
    : queue_{e4pp::config{e4pp::ev_feature_01|e4pp::ev_feature_et
        |e4pp::ev_feature_early_close}}
{   }

void server::on_accept(evutil_socket_t fd, sockaddr* sa, int len)
{
    cout() << "accept connection from " 
        << to_string({sa, static_cast<socklen_t>(len)}) << std::endl;
    evutil_closesocket(fd);
}

void server::run()
{
    trace([]{
        return "run queue"sv;
    });

#ifndef WIN32
    auto f = [&](auto, auto){
        u.trace([]{
            return "loop break"sv;
        });
        running_ = false;
        queue_.loop_break();
    };
    e4pp::ev_stack sint;
    sint.create(queue_, SIGINT, e4pp::ev_signal|e4pp::ev_persist, f);
    sint.add();
    e4pp::ev_stack sterm;
    sterm.create(queue_, SIGTERM, e4pp::ev_signal|e4pp::ev_persist, f);
    sterm.add();
#endif // _WIN32

    try
    {
        sockaddr_storage sa{};
        auto slen = int{sizeof(sa)};
        evutil_parse_sockaddr_port("[::1]:61616",
            reinterpret_cast<sockaddr*>(&sa), &slen);

        auto accept_fn = [&](auto fd, auto sa, auto len) {            
            cout() << "accept connection from " 
                << to_string({sa, static_cast<socklen_t>(len)}) << std::endl;
            evutil_closesocket(fd);
        };

        listener_.listen(queue_, 
            reinterpret_cast<const sockaddr*>(&sa), static_cast<socklen_t>(slen), 
            accept_fn, 2048, e4pp::lev_default|e4pp::lev_reuseable_port);

        while (running_)
            queue_.dispatch();

        listener_.close();
    }
    catch(const std::exception& e)
    {
        cerr() << e.what() << std::endl;
    }

    trace([]{
        return "stop queue"sv;
    });
}

void server::disable()
{
    queue_.once([&](){
        listener_.disable();
    });
}


void server::stop()
{
    running_ = false;
    trace([]{
        return "stop server"sv;
    });
}
