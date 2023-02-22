#pragma once

#include <cstdint>
#include <map>
#include <memory>
#include <vector>
#include <string>
#include "app.hpp"

struct ICommand
{
    using pointer = std::unique_ptr<ICommand>;
    virtual void execute(std::string_view option = "") = 0;
};

class command_base : public ICommand
{
    public:
        using pointer = std::unique_ptr<command_base>;
        using parameters = std::vector<std::string>;

        command_base() = delete;
        explicit command_base(const App::pointer&);
        command_base(const App::pointer&, parameters&);
        virtual ~command_base() = default;

        virtual void execute(std::string_view);

    protected:
        const App::pointer m_app;
        parameters m_params;
};

class InsertCmd : public command_base
{
    public:
        using pointer = std::unique_ptr<InsertCmd>;

        InsertCmd(const App::pointer&);
        InsertCmd(const App::pointer&, parameters&);

        void execute(std::string_view) override;
};

class TruncateCmd : public command_base
{
    public:
        using pointer = std::unique_ptr<TruncateCmd>;

        TruncateCmd(const App::pointer&);
        TruncateCmd(const App::pointer&, parameters&);

        void execute(std::string_view) override;
};

class IntersectionCmd : public command_base
{
    public:
        using pointer = std::unique_ptr<IntersectionCmd>;

        IntersectionCmd(const App::pointer&);
        IntersectionCmd(const App::pointer&, parameters&);

        void execute(std::string_view) override;
};

class SymmetricDiffCmd : public command_base
{
    public:
        using pointer = std::unique_ptr<SymmetricDiffCmd>;

        SymmetricDiffCmd(const App::pointer&);
        SymmetricDiffCmd(const App::pointer&, parameters&);

        void execute(std::string_view) override;
};

class UnknownCmd : public command_base
{
    public:
        using pointer = std::unique_ptr<UnknownCmd>;

        UnknownCmd(const App::pointer&);
        UnknownCmd(const App::pointer&, parameters&);

        void execute(std::string_view) override;
};

class CreateTableCmd : public command_base
{
    public:
        using pointer = std::unique_ptr<CreateTableCmd>;

        CreateTableCmd(const App::pointer&);
        CreateTableCmd(const App::pointer&, parameters&);

        void execute(std::string_view) override;
};

namespace cmd
{
    enum class type : std::uint8_t
    {
        INSERT, TRUNCATE, INTERSECTION, SYMMETRIC_DIFFERENCE, UNKNOWN, CREATE
    };

    type stringToType(const std::string&);
}
