#ifndef MATRIX_COMPONENT_H_
#define MATRIX_COMPONENT_H_

#include <boost/fusion/algorithm.hpp>
#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/mpl/int.hpp>

#include "BoardState.h"
#include "Platform.h"
#include "Row.h"
#include "VerifyColumnCount.h"

template <typename MatrixType>
class MatrixComponent
{
    public:

        MatrixComponent()
        {
            for_each(m_matrix, VerifyColumnCount<FirstRowSize::value>());
        }

        void Process(BoardState& io_state)
        {
            boost::fusion::iter_fold(m_matrix, 0, ProcessRow<MatrixType, InputArrayType>(io_state, m_inputs));
        }

    private:

        typedef typename boost::fusion::result_of::value_at<MatrixType,
                                                            boost::mpl::int_<0> >::type FirstRow;
        typedef typename boost::fusion::result_of::size<FirstRow>::type                 FirstRowSize;

        typedef Platform::InputElementType InputArrayType [FirstRowSize::value];

        InputArrayType            m_inputs;

        MatrixType m_matrix;
};

#endif
