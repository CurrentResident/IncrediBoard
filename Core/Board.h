#ifndef BOARD_H_
#define BOARD_H_

#include <boost/fusion/algorithm.hpp>

#include "BoardController.h"
#include "Column.h"
#include "Platform.h"

template <typename MatrixType>
class Board
{
    public:

        Board()
        {
        }

        ~Board()
        {
        }

        void Process()
        {
            boost::fusion::for_each(m_matrix, ProcessColumn(m_controller, m_inputs));

            m_controller.Process();
        }

    private:

        MatrixType                m_matrix;
        Platform::InputValuesType m_inputs;
        BoardController           m_controller;
};

#endif
