#ifndef BOARD_H_
#define BOARD_H_

#include <boost/fusion/include/for_each.hpp>
#include <type_traits>

#include "BoardState.h"
#include "Decorators.h"

template <typename ComponentCollectionType>
class Board
{
    public:

        void Process()
        {
            boost::fusion::for_each(m_components, Dispatch(m_state, m_components));
        }

    private:

        struct Dispatch
        {
            BoardState&              boardState;
            ComponentCollectionType& boardComponents;

            Dispatch(BoardState&              i_state,
                     ComponentCollectionType& i_components) :
                boardState      (i_state),
                boardComponents (i_components)
            { }

            template <typename ComponentType>
            void Call(ComponentType& component, std::false_type) const
            {
                component.Process(boardState);
            }

            template <typename ComponentType>
            void Call(ComponentType& component, std::true_type) const
            {
                component.Process(boardState, boardComponents);
            }

            template <typename ComponentType>
            void operator()(ComponentType& component) const
            {
                Call(component, std::is_base_of<NeedsAllComponents, ComponentType>());
            }
        };

        ComponentCollectionType m_components;
        BoardState              m_state;
};

#endif
