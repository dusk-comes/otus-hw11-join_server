#include "app.hpp"
#include "commands.hpp"
#include "reader.hpp"
#include "commands_factory.hpp"

int main()
{
    std::string raw_line = "INSERT BINGO-BONGO foo bar";
    auto parsed_line = reader::parse(raw_line);
    App::pointer app;

    Factory factory;
    auto cmd = factory.create(parsed_line.first, app, parsed_line.second);
    cmd->execute();
    return 0;
}
