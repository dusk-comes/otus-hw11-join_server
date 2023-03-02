#include <boost/asio/placeholders.hpp>
#include <boost/bind.hpp>
#include <iostream>

#include "server.hpp"

server::server(boost::asio::io_context &io_context, short port) :
    m_acceptor(io_context, tcp::endpoint(tcp::v4(), port)),
    m_pool(io_context, 1),
    m_app{nullptr}
{
    do_accept();
}

void server::do_accept()
{
    auto cnct = m_pool.get();
    m_acceptor.async_accept(cnct->socket(), boost::bind(
                &server::handle_accept,
                this,
                cnct,
                boost::asio::placeholders::error));
}

void server::deploy(App::pointer app)
{
    m_app = app;
}

void server::handle_accept(connection::pointer cnct, const boost::system::error_code &error)
{
    if (error.value() == boost::system::errc::success)
        cnct->start(std::bind(&connection_pool::put, m_pool, std::placeholders::_1));
    else
        std::cerr << "error: " << error.message() << std::endl;

    do_accept();
}
