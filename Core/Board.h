#ifndef BOARD_H_
#define BOARD_H_

#include <boost/fusion/algorithm.hpp>
#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/comparison.hpp>
#include <boost/mpl/int.hpp>

#include "BoardController.h"
//#include "Column.h"
#include "Platform.h"
#include "Row.h"

template <typename MatrixType>
class Board
{
    public:

        Board()
        {
            using namespace boost::fusion;
            using namespace boost::mpl;

            typedef typename result_of::value_at<MatrixType, int_<0> >::type FirstRow;
            typedef typename result_of::size<typename FirstRow::Keys>::type  FirstRowSize;

            for_each(m_matrix,
                    VerifyColumnCount
                    <
                        FirstRowSize::value
                    >());
        }

        ~Board()
        {
        }

        void Process()
        {
            boost::fusion::for_each(m_matrix, ProcessRow(m_controller, m_inputs));

            m_controller.Process();
        }

    private:

        MatrixType                m_matrix;
        Platform::InputValuesType m_inputs;
        BoardController           m_controller;

        template <int FIRST_ROW_SIZE>
        struct VerifyColumnCount
        {
            template <typename T>
            void operator() (const T& row) const
            {
                using namespace boost::mpl;

                BOOST_MPL_ASSERT_MSG((equal_to
                                      <
                                        int_<boost::fusion::result_of::size<typename T::Keys>::type::value>,
                                        int_<FIRST_ROW_SIZE>
                                      >::value
                                     ),
                                     BAD_NUMBER_OF_COLUMNS_DETECTED_ON_ROW,
                                     (void));

            }
        };
};

#endif
