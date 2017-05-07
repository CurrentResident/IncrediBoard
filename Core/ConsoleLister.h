#ifndef CONSOLE_LISTER_H_
#define CONSOLE_LISTER_H_

#include "Console.h"

struct ConsoleLister
{
    Console&    cons;

    ConsoleLister(Console& io_cons) :
        cons(io_cons)
    { }

    struct ListCommands
    {
        const ConsoleLister& lister;    // Or reference to the console itself..?

        ListCommands(const ConsoleLister& i_lister) :
            lister(i_lister)
        { }

        template <typename SpecificCommand>
        void operator()(SpecificCommand& command) const
        {
            BOOST_MPL_ASSERT(
                (std::is_base_of<Console::BaseCommand,
                                          SpecificCommand>));

            lister.cons.PushOutput(command.name);
            lister.cons.PushOutput('\n');
        }
    };

    template <typename Component>
    void List(Component& comp, std::false_type) const
    {
    }

    template <typename Component>
    void List(Component& comp, std::true_type) const
    {
        typename Component::Commands commands;
        boost::fusion::for_each(commands, ListCommands(*this));
    }

    template <typename Component>
    void operator()(Component& comp) const
    {
        List(comp,
             typename std::is_base_of<WithCommands, Component>());
    }
};

#endif
