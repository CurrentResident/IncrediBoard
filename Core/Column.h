#ifndef COLUMN_H_
#define COLUMN_H_

#include <boost/fusion/algorithm.hpp>

#include "Key.h"
#include "Platform.h"

template <typename SelectColumn, typename ColumnKeys, typename ClearColumn>
class Column
{
    public:

        void Process(Platform::InputValuesType& io_inputs)
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

            // With inputs in-hand, send them to the key objects in order.
            boost::fusion::fold(m_keys, 0, ProcessKey(io_inputs, now));
        }

    private:

        ColumnKeys   m_keys;
};

struct ProcessColumn
{
    Platform::InputValuesType& m_inputs;

    ProcessColumn(Platform::InputValuesType& i_inputs):m_inputs(i_inputs) {}

    template <typename T>
    void operator() (T& column) const
    {
        column.Process(m_inputs);
    }
};

#endif
