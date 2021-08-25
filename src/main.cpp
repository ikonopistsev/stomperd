#include "server.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    try
    {
        stomperd::startup st;
        if (st.parse(argc, argv))
        {
            stomperd::server srv(st);
            srv.run();
        }
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    catch(...)
    {   }

    return 0;
}
