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
            for_each(m_matrix, VerifyColumnCount<FirstRowSize::value>());
        }

        ~Board()
        {
        }

        void Process()
        {
            boost::fusion::iter_fold(m_matrix, 0, ProcessRow<MatrixType, InputArrayType>(m_controller, m_inputs));

            m_controller.Process();
        }

    private:

        typedef typename boost::fusion::result_of::value_at<MatrixType,
                                                            boost::mpl::int_<0> >::type FirstRow;
        typedef typename boost::fusion::result_of::size<FirstRow>::type                 FirstRowSize;

        typedef Platform::InputElementType InputArrayType [FirstRowSize::value];

        MatrixType                m_matrix;
        InputArrayType            m_inputs;
        //Platform::InputValuesType m_inputs;
        BoardController           m_controller;
};

#endif
