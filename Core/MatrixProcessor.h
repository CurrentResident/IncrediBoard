#ifndef MATRIX_PROCESSOR_H_
#define MATRIX_PROCESSOR_H_

#include <boost/fusion/algorithm.hpp>
#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/mpl/int.hpp>

#include "Platform.h"
#include "Row.h"
#include "VerifyColumnCount.h"

template <typename MatrixType>
class MatrixProcessor
{
    public:

        MatrixProcessor()
        {
            for_each(m_matrix, VerifyColumnCount<FirstRowSize::value>());
        }

        void Process()
        {
            boost::fusion::iter_fold(m_matrix, 0, ProcessRow<MatrixType, InputArrayType>(m_controller, m_inputs));
        }

    private:

        typedef typename boost::fusion::result_of::value_at<MatrixType,
                                                            boost::mpl::int_<0> >::type FirstRow;
        typedef typename boost::fusion::result_of::size<FirstRow>::type                 FirstRowSize;

        typedef Platform::InputElementType InputArrayType [FirstRowSize::value];

        InputArrayType            m_inputs;

        MatrixType m_matrix;
}

#endif
