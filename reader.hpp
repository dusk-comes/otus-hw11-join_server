#pragma once

#include <utility>
#include "commands.hpp"

struct reader
{
    static std::pair<cmd::type, command_base::parameters> parse(std::string);
};
