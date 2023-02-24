#include <sstream>
#include "reader.hpp"

std::pair<cmd::type, command_base::parameters> reader::parse(const char* data)
{
    std::istringstream iss(data);
    std::string token;
    iss >> token;

    command_base::parameters params;
    params.reserve(5);

    std::string param;
    while (iss >> param)
            params.push_back(param);

    return {cmd::stringToType(token), params};
}
