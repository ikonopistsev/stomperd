#include "server.hpp"
#include "output.hpp"

#include "e4pp/thread.hpp"

#include <iostream>
#include <memory>
#include <mutex>
#include <list>

namespace {

#ifdef _WIN32

struct wsa
{
    wsa(unsigned char h, unsigned char l)
    {
        WSADATA w;
        auto err = ::WSAStartup(MAKEWORD(h, l), &w);
        if (0 != err)
            throw std::runtime_error("::WSAStartup");
    }

    ~wsa() noexcept
    {
        ::WSACleanup();
    }
};

#endif // _WIN32    
    
} // namespace

namespace stomperd {

void configure_output(startup& st) 
{
    using e4pp::util::detail::std_output;
    using e4pp::util::detail::std_timestamp_output;

    u.verbose = true;
    u.errptr = &std::cerr;
    
    u.stream = [output = std_output()] 
        (std::ostream& os) -> auto& {
            static std::mutex mutex{};
            std::lock_guard<std::mutex> l{mutex};
            return output(os);
        };        
}

} // namespace

int main(int argc, char* argv[])
{
    try
    {
#ifdef _WIN32
        wsa w{2, 2};
#endif // _WIN32        
        e4pp::use_threads();

        stomperd::startup st;
        if (st.parse(argc, argv))
        {
            stomperd::configure_output(st);
            stomperd::cout() << "SERVER STARTED" << std::endl;

            stomperd::server srv(st);
            srv.run();
        }

        return 0;
    }
    catch(const std::exception& e)
    {
        stomperd::cerr() << e.what() << std::endl;
    }
    catch(...)
    {   }

    return 1;
}
