#pragma once

#include <memory>
#include <string_view>

class App
{
    public:
        using pointer = std::shared_ptr<App>;

        void insert(std::string_view);
        void truncate(std::string_view);
        void intersection(std::string_view);
        void symmetric_diff(std::string_view);
        void create_tables(std::string_view);
};
