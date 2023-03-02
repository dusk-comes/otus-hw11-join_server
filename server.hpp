#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/system/error_code.hpp>

#include "app.hpp"
#include "connection.hpp"
#include "commands_factory.hpp"

using boost::asio::ip::tcp;

class server
{
    public:
        server(boost::asio::io_context&, short);
        void deploy(App::pointer);

    private:
        tcp::acceptor m_acceptor;
        connection_pool m_pool;
        App::pointer m_app;

        void do_accept();
        void handle_accept(connection::pointer, const boost::system::error_code&);
};
