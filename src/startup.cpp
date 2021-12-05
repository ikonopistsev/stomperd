#include "startup.hpp"

#include "boost/program_options.hpp"
#include <string_view>
#include <iostream>

using namespace stomperd;

namespace po = boost::program_options;
using namespace std::literals;

bool startup::parse(int argc, char *argv[])
{
    po::options_description desc("stomperd options");
    desc.add_options()
        ("help,h", "show help message")
        ("listen,l", po::value<std::string>(&listen_)->default_value("0.0.0.0"),
            "listening address")
        ("port,p", po::value<int>(&port_)->default_value(61613),
            "listening port")
        ("config,c", po::value<path_type>(), "config path")
        ("pid,f", po::value<path_type>(), "pid path")
        ("journal,j", po::value<path_type>(), "journal path")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help"))
    {
        std::cout << desc << std::endl;
        return false;
    }

//    if (vm.count("config"))
//        config_ = vm["config"].as<path_type>();
//    else
//        throw std::runtime_error("no config");

    return true;
}
