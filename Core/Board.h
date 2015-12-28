#ifndef BOARD_H_
#define BOARD_H_

#include <boost/fusion/algorithm.hpp>

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
            boost::fusion::for_each(m_matrix, ProcessColumn(m_inputs));
        }

    private:

        MatrixType                m_matrix;
        Platform::InputValuesType m_inputs;
};

#endif
