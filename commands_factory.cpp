#include "commands_factory.hpp"
#include "commands.hpp"

Factory::Factory()
{
    factories[cmd::type::INSERT] = boost::bind(boost::factory<InsertCmd::pointer>(), _1, _2);
    factories[cmd::type::CREATE] = boost::bind(boost::factory<InsertCmd::pointer>(), _1);
    factories[cmd::type::TRUNCATE] = boost::bind(boost::factory<TruncateCmd::pointer>(), _1, _2);
    factories[cmd::type::UNKNOWN] = boost::bind(boost::factory<UnknownCmd::pointer>(), _1, _2);
    factories[cmd::type::INTERSECTION] = boost::bind(boost::factory<IntersectionCmd::pointer>(), _1, _2);
    factories[cmd::type::SYMMETRIC_DIFFERENCE] = boost::bind(boost::factory<SymmetricDiffCmd::pointer>(), _1, _2);
}

auto Factory::create(cmd::type type) -> factory
{
    auto it = factories.find(type);
    if (it != factories.end())
        return it->second;
    else
        return factories[cmd::type::UNKNOWN];
}
