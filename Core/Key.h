#ifndef KEY_H_
#define KEY_H_

#include <boost/static_assert.hpp>
#include <stdint.h>

#include "BoardState.h"
#include "Platform.h"

template<unsigned long T_DEBOUNCE_PERIOD>
class DebouncedButton
{
    BOOST_STATIC_ASSERT (T_DEBOUNCE_PERIOD > 0);

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

        bool Process(const uint8_t currentState, const unsigned long now)
        {
            bool result = false;

            // Because time is represented as an unsigned long with millisecond units, time will eventually
            // overflow at 49.71-ish days.  This algorithm deals with it okay (but not perfect) by just bailing
            // out of the debounce if it extends thru the overflown duration.

            if (currentState != m_readState)
            {
                m_readState = currentState;
                m_debounceTime = now + T_DEBOUNCE_PERIOD;
            }

            if (m_debounceTime < now)
            {
                if (m_debouncedState != m_readState)
                {
                    m_debouncedState = m_readState;
                    result = true;
                }
            }

            return result;
        }
};

class BaseKey : public DebouncedButton<5>   // 5 msec per cherry spec.
{
};

template <uint8_t T_KEY_CODE>
class Key : public BaseKey
{
};

template <uint8_t T_KEY_CODE, uint8_t T_KEY_MODIFIER>
class KeyModifier : public BaseKey
{
};

class KeyFn : public BaseKey
{
};

// Specialization for 'None' key does nothing.
template <> class Key<0>
{
    public:

        uint8_t GetState() const
        {
            return 0;
        }

        bool Process(const uint8_t currentState, const unsigned long now)
        {
            return false;
        }
};

// Functor that updates key objects.
//
// This functor is designed to be called by boost's fusion::fold, which operates on a fusion sequence of Key
// instances.  It is designed for maximum inline-ability, thus the use of const references for the input
// states.  GCC is pretty dang smart about inlining the whole thing and optimizing away these "temporary"
// members, which is very much desired for embedded targets where we have far more flash storage for code
// than RAM for data.
template <typename InputArrayType>
struct ProcessKey
{
    BoardState&             m_state;
    const InputArrayType&   m_inputs;
    const unsigned long&    m_now;

    ProcessKey (BoardState&        io_state,
                const InputArrayType&   i_inputs,
                const unsigned long&    i_now) :
        m_state (io_state),
        m_inputs(i_inputs),
        m_now   (i_now)
    {}

    typedef uint8_t result_type;    // result_type must be defined if we intend to pass ProcessKey to fusion::fold.

    // Here's what the functor does when handed an ordinary Key.
    //
    template <uint8_t T_KEY_CODE>
    uint8_t operator() (const uint8_t colIndex, Key<T_KEY_CODE>& key) const
    {
        if (key.Process(m_inputs[colIndex], m_now))
        {
            m_state.ChangeKeyState<T_KEY_CODE>(key.GetState());
        }
        return colIndex + 1;
    }

    // Here's what the functor does when handed a KeyModifier.
    //
    template <uint8_t T_KEY_CODE, uint8_t T_KEY_MODIFIER>
    uint8_t operator() (const uint8_t colIndex, KeyModifier<T_KEY_CODE, T_KEY_MODIFIER>& key) const
    {
        if(key.Process(m_inputs[colIndex], m_now))
        {
            m_state.ChangeModifierState<T_KEY_CODE, T_KEY_MODIFIER>(key.GetState());
        }
        return colIndex + 1;
    }

    // Here's what to do when processing an update to the Func key.
    uint8_t operator() (const uint8_t colIndex, KeyFn& key) const
    {
        if(key.Process(m_inputs[colIndex], m_now))
        {
            m_state.SetFunctionKey(key.GetState());
        }

        return colIndex + 1;
    }
};


#endif
