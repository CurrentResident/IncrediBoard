#ifndef KEY_H_
#define KEY_H_

#include <boost/static_assert.hpp>
#include <stdint.h>

#include "Platform.h"

template<unsigned long t_debouncePeriod, uint8_t t_keyValue>
class DebouncedButton
{
    BOOST_STATIC_ASSERT(t_debouncePeriod > 0);

    private:

        uint8_t m_debouncedState;
        uint8_t m_readState;

        unsigned long m_debounceTime;

    public:
        DebouncedButton() :
            m_debouncedState(0),
            m_readState     (0),
            m_debounceTime  (0)
        {}

        uint8_t GetState() const
        {
            return m_debouncedState;
        }

        uint8_t GetData() const
        {
            return t_keyValue;
        }

        void Process(const uint8_t currentState, const unsigned long now)
        {
            // Because time is represented as an unsigned long with millisecond units, time will eventually
            // overflow at 49.71-ish days.  This algorithm deals with it okay (but not perfect) by just bailing
            // out of the debounce if it extends thru the overflown duration.

            if (currentState != m_readState)
            {
                m_readState = currentState;
                m_debounceTime = now + t_debouncePeriod;
            }

            if (m_debounceTime < now)
            {
                if (m_debouncedState != m_readState)
                {
                    m_debouncedState = m_readState;
                }
            }
        }
};

template <uint8_t t_keyValue>
class Key : public DebouncedButton<5, t_keyValue>   // 5 msec per cherry spec.
{
};

// Specialization for 'None' key does nothing.
template <> class Key<0> { public: void Process(const uint8_t currentState, const unsigned long now) {} };

// Functor that updates key objects.
//
// This functor is designed to be called by boost's fusion::fold, which operates on a fusion sequence of Key
// instances.  It is designed for maximum inline-ability, thus the use of const references for the input
// states.  GCC is pretty dang smart about inlining the whole thing and optimizing away these "temporary"
// members, which is very much desired for embedded targets where we have far more flash storage for code
// than RAM for data.
struct ProcessKey
{
    const Platform::InputValuesType& m_inputs;
    const unsigned long&             m_now;

    ProcessKey (const Platform::InputValuesType& i_inputs,
                const unsigned long&             i_now) :
        m_inputs(i_inputs),
        m_now   (i_now)
    {}

    typedef uint8_t result_type;    // result_type must be defined if we intend to pass ProcessKey to fusion::fold.

    template <typename T>
    uint8_t operator() (const uint8_t rowIndex, T& key) const
    {
        key.Process(m_inputs.row[rowIndex], m_now);
        return rowIndex + 1;
    }
};


#endif
