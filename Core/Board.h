#ifndef BOARD_H_
#define BOARD_H_

#include <boost/fusion/algorithm.hpp>
#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/mpl/int.hpp>

#include "BoardController.h"
#include "Platform.h"
#include "Row.h"
#include "VerifyColumnCount.h"

template <typename MatrixType>
class Board
{
    public:

        Board()
        {
            using namespace boost::fusion;
            using namespace boost::mpl;

            typedef typename result_of::value_at<MatrixType, int_<0> >::type FirstRow;
            typedef typename result_of::size<FirstRow>::type                 FirstRowSize;

            for_each(m_matrix, VerifyColumnCount<FirstRowSize::value>());
        }

        ~Board()
        {
        }

        void Process()
        {
            using namespace boost::fusion;

            boost::fusion::iter_fold(m_matrix, 0, ProcessRow<MatrixType>(m_controller, m_inputs));

            m_controller.Process();
        }

    private:

        MatrixType                m_matrix;
        Platform::InputValuesType m_inputs;
        BoardController           m_controller;
};

#endif
