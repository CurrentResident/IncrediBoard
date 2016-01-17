#ifndef VERIFY_COLUMN_COUNT_H_
#define VERIFY_COLUMN_COUNT_H_

#include <boost/mpl/assert.hpp>
#include <boost/mpl/comparison.hpp>

template <int FIRST_ROW_SIZE>
struct VerifyColumnCount
{
    template <typename T>
    void operator() (const T& row) const
    {
        using namespace boost::mpl;

        BOOST_MPL_ASSERT_MSG(
            (equal_to<
                      int_<boost::fusion::result_of::size<T>::type::value>,
                      int_<FIRST_ROW_SIZE>
                     >::value
            ),
            ___BAD_NUMBER_OF_COLUMNS_DETECTED_ON_ROW__MAKE_SURE_ALL_ROWS_HAVE_SAME_NUMBER_OF_COLUMNS___,
            (void));

    }
};

#endif
