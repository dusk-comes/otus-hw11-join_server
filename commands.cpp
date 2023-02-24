#include <sstream>
#include <iterator>
#include <algorithm>
#include "commands.hpp"

command_base::command_base(const App::pointer &app) :
    m_app(app)
{
}

command_base::command_base(const App::pointer &app, parameters &params) :
    m_app(app),
    m_params(std::move(params))
{
}

std::string command_base::execute(std::string_view)
{
    return "";
}

InsertCmd::InsertCmd(const App::pointer &app) :
        command_base(app)
{
}

InsertCmd::InsertCmd(const App::pointer &app, parameters &text) :
    command_base(app, text)
{
}

TruncateCmd::TruncateCmd(const App::pointer &app, parameters &text) :
    command_base(app, text)
{
}

TruncateCmd::TruncateCmd(const App::pointer &app) :
    command_base(app)
{
}

IntersectionCmd::IntersectionCmd(const App::pointer &app) :
    command_base(app)
{
}

IntersectionCmd::IntersectionCmd(const App::pointer &app, parameters &text) :
    command_base(app, text)
{
}

SymmetricDiffCmd::SymmetricDiffCmd(const App::pointer &app, parameters &text) :
    command_base(app, text)
{
}

SymmetricDiffCmd::SymmetricDiffCmd(const App::pointer &app) :
    command_base(app)
{
}

UnknownCmd::UnknownCmd(const App::pointer &app, parameters &text) :
    command_base(app, text)
{
}

UnknownCmd::UnknownCmd(const App::pointer &app) :
    command_base(app)
{
}

CreateTableCmd::CreateTableCmd(const App::pointer &app) :
    command_base(app)
{
}

CreateTableCmd::CreateTableCmd(const App::pointer &app, parameters &text) :
    command_base(app, text)
{
}

std::string InsertCmd::execute(std::string_view)
{
    auto begin = command_base::m_params.cbegin();
    auto end = command_base::m_params.cend();
    auto it = begin;

    auto table_name = *it++;

    std::ostringstream oss;
    oss << "INSERT INTO TABLE" << " " + table_name
        << " (id, name)"
        << " VALUES (";

    std::move(it, end - 1, std::ostream_iterator<std::string>(oss, ", "));
    std::move(end - 1, end, std::ostream_iterator<std::string>(oss, ""));
    oss << ");";

    return command_base::m_app->insert(oss.str());
}

std::string TruncateCmd::execute(std::string_view)
{
    auto begin = command_base::m_params.cbegin();
    auto end = command_base::m_params.cend();
    auto it = begin;

    auto table_name = *it++;

    std::ostringstream oss;
    oss << "DELETE FROM " << table_name << ";";

    return command_base::m_app->truncate(oss.str());
}

std::string IntersectionCmd::execute(std::string_view)
{
    std::ostringstream oss;
    oss << "SELECT A.id, A.name, B.name FROM A"
        << " INNER JOIN B on A.id = B.id;";

    return command_base::m_app->intersection(oss.str());
}

std::string SymmetricDiffCmd::execute(std::string_view)
{
    std::ostringstream oss;
    oss << "SELECT * FROM A"
        << " FULL OUTER JOIN B ON A.id = B.id"
        << " WHERE A.id ISNULL OR B.id ISNULL;";

    return command_base::m_app->symmetric_diff(oss.str());
}

std::string CreateTableCmd::execute(std::string_view table)
{
    std::ostringstream oss;
    oss << "CREATE TABLE " << table << " (id integer primary key, name text);";

    return command_base::m_app->create_tables(oss.str());
}

std::string UnknownCmd::execute(std::string_view)
{
    return "";
}

namespace
{
    const std::map<std::string, cmd::type> mapper({
            {"INSERT", cmd::type::INSERT},
            {"CREATE", cmd::type::CREATE},
            {"TRUNCATE", cmd::type::TRUNCATE},
            {"INTERSECTION", cmd::type::INTERSECTION},
            {"SYMMETRIC_DIFFERENCE", cmd::type::SYMMETRIC_DIFFERENCE}
            });
}

cmd::type cmd::stringToType(const std::string &token)
{
    if(auto it = mapper.find(token); it != mapper.end())
        return it->second;
    else
        return type::UNKNOWN;
}
