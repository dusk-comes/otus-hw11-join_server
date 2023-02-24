#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/system/error_code.hpp>

#include <memory>
#include <vector>
#include <array>

#include "app.hpp"

extern App::pointer app;

using boost::asio::ip::tcp;

class connection : std::enable_shared_from_this<connection>
{
    public:
        using pointer = std::unique_ptr<connection>;
        connection(boost::asio::io_context&);
        tcp::socket &socket();

        void start();

        void read();
        //void handle_read(const boost::system::error_code&);

    private:
        tcp::socket m_socket;
        static const std::size_t m_bufsize = 1024;
        std::array<char, m_bufsize> m_buf;

        void write();
};

class connection_pool
{
    private:
        struct connection_block
        {
            connection::pointer cnct;
            bool busy;
        };

        boost::asio::io_context &m_io_context;
        std::vector<connection_block> m_pool;

        void add_block();

    public:
       connection_pool() = delete;
       connection_pool(boost::asio::io_context&, short);
       ~connection_pool() = default;

       connection *get();
       void put(connection*);
};
