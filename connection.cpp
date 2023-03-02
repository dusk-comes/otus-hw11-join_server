#include <boost/system/error_code.hpp>

#include <algorithm>

#include "connection.hpp"

connection::connection(boost::asio::io_context &io_context) :
    m_socket(io_context)
{
}

tcp::socket &connection::socket()
{
    return m_socket;
}

void connection::start()
{
    read();
}

void connection::read()
{
    auto self(shared_from_this());
    m_socket.async_read_some(boost::asio::buffer(m_buf, m_bufsize),
            [this,self](const boost::system::error_code &er, std::size_t length)
            {
                if (er.value() == boost::system::errc::success)
                {
                    auto result = app->execute(m_buf.data());
                    std::move(result.begin(), result.end(), m_buf.begin());
                    write(result.size());
                }
            });
}

void connection::write(std::size_t length)
{
    auto self(shared_from_this());

    boost::asio::async_write(m_socket, boost::asio::buffer(m_buf, length),
            [this,self](boost::system::error_code ec, std::size_t m_buffsize) {
            m_socket.release();
            });
}

connection_pool::connection_pool(boost::asio::io_context &io_context, short size) :
    m_io_context(io_context)
{
    while (size-- > 0)
    {
        add_block();
    }
}

connection::pointer connection_pool::get()
{
    for (auto &block : m_pool)
    {
        if (block.busy) continue;
        block.busy = true;
        return block.cnct;
    }

    add_block(); 
    return m_pool.back().cnct;
}

void connection_pool::put(connection::pointer cnct)
{
    for (auto &block : m_pool)
    {
        if (block.cnct == cnct)
        {
            block.busy = false;
            break;
        }
    }
}

void connection_pool::add_block()
{
    auto block = connection_block{
        connection::pointer{new connection(m_io_context)},
        false};

    m_pool.emplace_back(std::move(block));
}
