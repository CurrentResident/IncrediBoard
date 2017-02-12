#ifndef CONSOLE_DISPATCHER_H_
#define CONSOLE_DISPATCHER_H_

#include <cstring>

#include "Console.h"

struct ConsoleDispatcher
{
    Console&    cons;
    const char* cmdName;

    ConsoleDispatcher(Console& io_cons, const char* i_cmdName) :
        cons(io_cons),
        cmdName(i_cmdName)
    { }

    typedef bool result_type;

    template <typename Component>
    struct ComponentLocalDispatch
    {
        typedef bool result_type;

        Component& comp;
        const ConsoleDispatcher& disp;

        ComponentLocalDispatch(Component& i_comp, const ConsoleDispatcher& i_disp) :
            comp(i_comp),
            disp(i_disp)
        { }

        template <typename SpecificCommand>
        bool operator()(bool alreadyFound, SpecificCommand& command) const
        {
            BOOST_MPL_ASSERT(
                (std::is_base_of<Console::BaseCommand,
                                          SpecificCommand>));

            if (not alreadyFound and std::strcmp(command.name, disp.cmdName) == 0)
            {
                command(disp.cons, comp);
                return true;
            }
            return alreadyFound;
        }

        template <typename SpecificCommand>
        void operator()(SpecificCommand& command) const
        {
            BOOST_MPL_ASSERT(
                (std::is_base_of<Console::BaseCommand,
                                          SpecificCommand>));

            disp.cons.PushOutput(command.name);
            disp.cons.PushOutput('\n');
        }
    };

    template <typename Component>
    bool Call(Component& comp, std::false_type) const
    {
        return false;
    }

    template <typename Component>
    void List(Component& comp, std::false_type) const
    {
    }

    template <typename Component>
    bool Call(Component& comp, std::true_type) const
    {
        // I had been searching for a way to move the command instances into the component, but then
        // it occurred to me that doing it this way prevents us from having to dedicate memory 100% duty
        // to storing the command objects.  As component and command count increase, this will overall
        // be much better for space efficiency, for the tradeoff of pretty simple constructor logic when
        // searching for the right command to run.
        //
        typename Component::Commands commands;
        return boost::fusion::fold(commands, false, ComponentLocalDispatch<Component>(comp, *this));
    }

    template <typename Component>
    void List(Component& comp, std::true_type) const
    {
        typename Component::Commands commands;
        boost::fusion::for_each(commands, ComponentLocalDispatch<Component>(comp, *this));
    }
    // When folded, the dispatcher calls the command.
    template <typename Component>
    bool operator()(bool alreadyFound, Component& comp) const
    {
        return alreadyFound or
                Call(comp,
                     typename std::is_base_of<WithCommands, Component>());
    }

    // When for_each'd, the dispatcher lists commands.  Seems hacky...
    template <typename Component>
    void operator()(Component& comp) const
    {
        List(comp,
             typename std::is_base_of<WithCommands, Component>());
    }
};

#endif
