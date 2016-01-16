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
            boost::fusion::for_each(m_matrix, VerifyColumnCount<5>());
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

        //typedef 

/*
        typedef boost::mpl::fold<MatrixType,
                                 boost::fusion::size<boost::fusion::at_c<MatrixType, 0> >,
*/
        MatrixType                m_matrix;
        Platform::InputValuesType m_inputs;
        BoardController           m_controller;

        template <int FIRST_ROW_SIZE>
        struct VerifyColumnCount
        {
            template <typename T>
            void operator() (const T& row) const
            {
                //BOOST_STATIC_ASSERT (boost::fusion::result_of::size<typename T::Keys>::type::value > FIRST_ROW_SIZE);
                //using namespace boost::fusion;
/*
                BOOST_MPL_ASSERT_MSG(boost::fusion::result_of::size<typename T::Keys>::type::value == FIRST_ROW_SIZE,
                                     Bad_number_of_columns_detected_on_row,
                                     (typename T::Keys));
*/
                //BOOST_MPL_ASSERT((boost::result_of::size<typename T::Keys>::type::value == FIRST_ROW_SIZE));
                //BOOST_MPL_ASSERT((boost::mpl::is_same<boost::fusion::result_of::size<T>::type::value, FIRST_ROW_SIZE>));
/*                BOOST_MPL_ASSERT((boost::mpl::equal_to
                                 <
                                    boost::mpl::int_<boost::fusion::result_of::size<typename T::Keys>::type::value>,
                                    boost::mpl::int_<FIRST_ROW_SIZE>
                                  >));
*/
                using namespace boost::mpl;

//                BOOST_MPL_ASSERT(( equal_to<int_<4>, int_<FIRST_ROW_SIZE> > ));

                BOOST_MPL_ASSERT_MSG( //GOOD:  (boost::mpl::equal_to<int_<5>, int_<FIRST_ROW_SIZE> >::value) ,
                                     (equal_to
                                      <
                                        int_<boost::fusion::result_of::size<typename T::Keys>::type::value>,
                                        int_<FIRST_ROW_SIZE>
                                      >::value
                                     ),
                                     BAD_NUMBER_OF_COLUMNS_DETECTED_ON_ROW,
                                     (void));

                //BOOST_MPL_ASSERT_RELATION(boost::fusion::result_of::size<typename T::Keys>::type::value, ==, FIRST_ROW_SIZE);
            }
        };
/*
        boost::fusion::result_of::for_each
        <
            MatrixType,
            //VerifyColumnCount<boost::result_of::size<boost::fusion::at_c<MatrixType, 0> >::value >::type m_throwaway;
            VerifyColumnCount<3>
        >::type m_throwaway;
*/
};

#endif
