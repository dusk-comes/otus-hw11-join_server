#include "app.hpp"
#include "commands.hpp"
#include "reader.hpp"
#include "commands_factory.hpp"
#include "server.hpp"
#include <exception>
#include <iostream>
#include <boost/system/error_code.hpp>

App::pointer app = std::make_shared<App>();

int main()
{
    /*
    const char *raw_line = "INSERT BINGO-BONGO foo bar";
    auto parsed_line = reader::parse(raw_line);

    Factory factory;
    auto cmd = factory.create(parsed_line.first, app, parsed_line.second);
    cmd->execute();
    */


    try
    {
        boost::asio::io_context io_context;
        server srv(io_context, 9999);
        io_context.run();
    }
    catch (const boost::system::error_code &er)
    {
        std::cout << er.message() << std::endl;
    }
    catch (const std::exception &ex)
    {
        std::cout << ex.what() << std::endl;
    }
    return 0;
}
