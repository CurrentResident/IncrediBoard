#ifndef ROW_H_
#define ROW_H_

#include <boost/fusion/algorithm.hpp>

#include "BoardController.h"
#include "Key.h"
#include "Platform.h"

template <typename MatrixType, typename InputArrayType>
struct ProcessRow
{
    BoardController&    m_controller;
    InputArrayType&     m_inputs;

    ProcessRow(BoardController&     i_controller,
                  InputArrayType&   i_inputs)
    :
        m_controller(i_controller),
        m_inputs    (i_inputs)
    { }

    typedef int result_type;

    typedef typename boost::fusion::result_of::begin<MatrixType>::type BeginIteratorType;

    template <typename T>
    int operator() (const int i, T& rowIter) const
    {
        using namespace boost::fusion;

        typedef typename result_of::distance<BeginIteratorType, T>::type RowPositionType;

        Platform::SetRow   <RowPositionType::value>();
        Platform::DelayMicrosecs<5>();
        Platform::ReadInputs(m_inputs);
        const unsigned long now = Platform::GetMsec();
        Platform::ClearRow <RowPositionType::value>();

        fold (deref (rowIter),
              0,
              ProcessKey<InputArrayType>(m_controller,
                                         m_inputs,
                                         now));

        return 0;
    }
};

#endif
