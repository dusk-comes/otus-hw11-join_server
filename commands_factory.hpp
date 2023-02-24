#pragma once

#include <boost/container/flat_map.hpp>
#include <boost/functional/factory.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>

#include "commands.hpp"

class Factory
{
    using command_pointer = ICommand::pointer;

    using factory = boost::function<command_pointer(
            const App::pointer&,
            command_base::parameters&)>;

    public:
        Factory();
        ~Factory() = default;

        command_pointer create(cmd::type, const App::pointer&, command_base::parameters&) const;

    private:
        boost::container::flat_map<cmd::type, factory> factories;

        factory create_handler(cmd::type) const;
};
