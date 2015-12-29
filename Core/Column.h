#ifndef COLUMN_H_
#define COLUMN_H_

#include <boost/fusion/algorithm.hpp>

#include "BoardController.h"
#include "Key.h"
#include "Platform.h"

template <typename SelectColumn, typename ColumnKeys, typename ClearColumn>
class Column
{
    public:

        void Process(BoardController&           io_controller,
                     Platform::InputValuesType& io_inputs)
        {
            // Make some easily-inlineable temporary function objects.
            SelectColumn s;
            ClearColumn  c;

            // Connect the column, wait a few microsecs, read the inputs, then disconnect the column.
            s();
            Platform::DelayMicrosecs<5>();
            Platform::ReadInputs(io_inputs);
            const unsigned long now = Platform::GetMsec();
            c();

            // With inputs in-hand, send them to the key objects in order, and update the given controller.
            boost::fusion::fold(m_keys, 0, ProcessKey(io_controller, io_inputs, now));
        }

    private:

        ColumnKeys m_keys;
};

struct ProcessColumn
{
    BoardController&           m_controller;
    Platform::InputValuesType& m_inputs;

    ProcessColumn(BoardController&           i_controller,
                  Platform::InputValuesType& i_inputs)
    :
        m_controller(i_controller),
        m_inputs    (i_inputs)
    { }

    template <typename T>
    void operator() (T& column) const
    {
        column.Process(m_controller, m_inputs);
    }
};

#endif
