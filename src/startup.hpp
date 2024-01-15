#pragma once

#include <filesystem>
#include <string>
#include <vector>

namespace stomperd {

using fs_path = std::filesystem::path;

struct startup
{
    fs_path config{};
    std::size_t verbose{};
    std::string listen{};
    int port{};
    bool timestamps{};

    bool parse(int argc, char *argv[]);
};

} // namespace stomperd
