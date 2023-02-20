#include "app.hpp"
#include "commands.hpp"
#include "reader.hpp"
#include "commands_factory.hpp"

int main()
{
    std::string raw_line = "SYMMETRIC_DIFFERENCE";
    auto parsed_line = reader::parse(raw_line);
    App::pointer app;

    Factory factory;
    return 0;
}
