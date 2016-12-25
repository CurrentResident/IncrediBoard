#ifndef PLATFORM_GENERIC_H_
#define PLATFORM_GENERIC_H_

#include <boost/mpl/assert.hpp>
#include <boost/mpl/comparison.hpp>
#include <boost/mpl/int.hpp>

#include <stdint.h>

namespace Platform
{
    void Init();
    unsigned long GetMsec();

    void JumpToBootloader();

    // =================================================================
    // The following templates need to be specialized for your platform!
    //
    template<typename InputElementType, int N>
    void ReadInputs(InputElementType (& o_inputs)[N])
    {
        using namespace boost::mpl;

        BOOST_MPL_ASSERT_MSG ((equal_to<int_<N>, int_<-1> >::value ),
                              YOU_MUST_SPECIALIZE_ReadInputs_FOR_ARRAY_SIZE__SEE_N_PARAMETER,
                              (void));
    }

    template<int c>
    void SetRow ()
    {
        using namespace boost::mpl;

        BOOST_MPL_ASSERT_MSG ((equal_to<int_<c>, int_<-1> >::value ),
                              YOU_MUST_SPECIALIZE_SetRow_FOR_THIS_ROW__SEE_c_PARAMETER,
                              (void));
    };

    template<int c>
    void ClearRow ()
    {
        using namespace boost::mpl;

        BOOST_MPL_ASSERT_MSG ((equal_to<int_<c>, int_<-1> >::value ),
                              YOU_MUST_SPECIALIZE_ClearRow_FOR_THIS_ROW__SEE_c_PARAMETER,
                              (void));
    };
}

#define INSIDE_PLATFORM_H_
#include "PlatformSpecific.h"
#undef INSIDE_PLATFORM_H_

#endif
