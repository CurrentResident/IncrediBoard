#ifndef BOARD_H_
#define BOARD_H_

#include "BoardState.h"

template <typename ComponentCollectionType>
class Board
{
    public:

        void Process()
        {
            boost::fusion::for_each(m_components, Dispatch(m_state));
        }

    private:

        struct Dispatch
        {
            BoardState& m_dispatchState;

            Dispatch(BoardState& i_state) :
                m_dispatchState(i_state)
            { }

            template <typename ComponentType>
            void operator()(ComponentType& component) const
            {
                component.Process(m_dispatchState);
            }
        };

        ComponentCollectionType m_components;
        BoardState m_state;
};

#endif
