#include "startup.hpp"

#include "boost/program_options.hpp"
#include <string_view>
#include <iostream>
#include <vector>

using namespace stomperd;

namespace po = boost::program_options;
using namespace std::literals;

bool startup::parse(int argc, char *argv[])
{
    po::options_description desc("stomperd options");
    desc.add_options()
        ("help,h", "show help message")
        ("listen,l", po::value<std::string>(&listen)->default_value("0.0.0.0"),
            "listening address")
        ("port,p", po::value<int>(&port)->default_value(61613),
            "listening port")
        ("config,c", po::value<fs_path>(), "config path")
        ("pid,f", po::value<fs_path>(), "pid path")
        ("verbose,v", po::value<std::size_t>(&verbose)->default_value(0),
            "verbose output")
        ("timestamps,t", po::bool_switch(&timestamps)->default_value(false), "use timestamps")
        ("journal,j", po::value<fs_path>(), "journal path")
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