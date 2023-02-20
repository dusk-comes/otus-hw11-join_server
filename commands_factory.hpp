#include <boost/container/flat_map.hpp>
#include <boost/functional/factory.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>

#include "commands.hpp"

class Factory
{
    using factory = boost::function<command_base::pointer(
            const App::pointer&,
            command_base::parameters&)>;

    public:
        Factory();
        ~Factory() = default;

        factory create(cmd::type);

    private:
        boost::container::flat_map<cmd::type, factory> factories;
};
