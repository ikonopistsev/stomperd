#pragma once

#include <filesystem>
#include <string>

namespace stomperd {

class startup
{
public:
    using path_type = std::filesystem::path;

private:
    path_type config_{};
    std::string listen_{};
    int port_{};

public:
    startup() = default;

    bool parse(int argc, char *argv[]);
};

} // namespace stomperd
