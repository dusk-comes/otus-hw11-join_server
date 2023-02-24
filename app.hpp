#ifndef APP_HPP
#define APP_HPP

#include <memory>
#include <string_view>

class App : std::enable_shared_from_this<App>
{
    public:
        using pointer = std::shared_ptr<App>;

        std::string insert(std::string_view);
        std::string truncate(std::string_view);
        std::string intersection(std::string_view);
        std::string symmetric_diff(std::string_view);
        std::string create_tables(std::string_view);
        std::string execute(const char*);
};

#endif /*APP_HPP*/
