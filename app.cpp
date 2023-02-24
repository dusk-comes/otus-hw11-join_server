#include <iostream>
#include "app.hpp"
#include "commands.hpp"
#include "reader.hpp"
#include "commands_factory.hpp"

std::string App::insert(std::string_view command)
{
    //std::cout << command << std::endl;
    return "hereweare";
}

std::string App::truncate(std::string_view command)
{
    std::cout << command << std::endl;
    return "";
}

std::string App::intersection(std::string_view command)
{
    std::cout << command << std::endl;
    return "";
}

std::string App::symmetric_diff(std::string_view command)
{
    std::cout << command << std::endl;
    return "";
}

std::string App::create_tables(std::string_view command)
{
    std::cout << command << std::endl;
    return "";
}

std::string App::execute(const char *data)
{
    auto [cmd_type, params] = reader::parse(data);
    static const Factory f;
    auto cmd = f.create(cmd_type, shared_from_this(), params);
    return cmd->execute();
}
