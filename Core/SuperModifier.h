#ifndef SUPER_MODIFIER_H_
#define SUPER_MODIFIER_H_

#include <boost/fusion/algorithm.hpp>
#include <boost/fusion/iterator.hpp>

#include "BoardState.h"
#include "Key.h"
#include "Platform.h"

template <typename ModifierKeyType, typename OtherKeysCollectionType>
class SuperModifier
{

    struct PressKeys
    {
        BoardState& state;
        bool        active;

        PressKeys(BoardState& io_state, bool i_isActive) : state(io_state), active(i_isActive) {}

        template <uint8_t T_KEY_CODE>
        void operator()(Key<T_KEY_CODE>) const
        {
            state.ChangeKeyState<T_KEY_CODE>(active);
        }

        template <uint8_t T_KEY_CODE, uint8_t T_MODIFIER>
        void operator()(KeyModifier<T_KEY_CODE, T_MODIFIER>) const
        {
            state.ChangeModifierState<T_KEY_CODE, T_MODIFIER>(active);
        }
    };

    public:

        SuperModifier() :
            m_state      (MONITORING_FOR_NO_KEYS_DOWN),
            m_releaseTime(0)
        {
        }

        void Process(BoardState& io_state)
        {
            switch(m_state)
            {
                case MONITORING_FOR_NO_KEYS_DOWN:
                    if (io_state.m_modifiers == 0 and io_state.m_keyReportArray.size() == 0)
                    {
                        m_state = MONITORING_FOR_DOWN;
                    }
                    break;

                case MONITORING_FOR_DOWN:

                    if (io_state.m_modifiers & ~ModifierKeyType::MODIFIER or
                        io_state.m_keyReportArray.size() != 0)
                    {
                        m_state = MONITORING_FOR_NO_KEYS_DOWN;
                    }
                    else
                    {
                        if (io_state.m_modifiers == ModifierKeyType::MODIFIER)
                        {
                            m_state = MONITORING_FOR_UP;
                        }
                    }

                    break;

                case MONITORING_FOR_UP:

                    if (io_state.m_modifiers & ~ModifierKeyType::MODIFIER or
                        io_state.m_keyReportArray.size() != 0)
                    {
                        m_state = MONITORING_FOR_NO_KEYS_DOWN;
                    }
                    else
                    {
                        if (io_state.m_modifiers == 0)
                        {
                            m_state = PRESSED;
                            m_releaseTime = Platform::GetMsec() + 10;

                            boost::fusion::for_each(OtherKeysCollectionType(), PressKeys(io_state, true));
                        }
                    }

                    break;

                case PRESSED:

                    if (m_releaseTime < Platform::GetMsec())
                    {
                        boost::fusion::for_each(OtherKeysCollectionType(), PressKeys(io_state, false));

                        m_state = MONITORING_FOR_NO_KEYS_DOWN;
                        m_releaseTime = 0;
                    }
                    break;

                case DISABLED:
                default:
                    break;
            }
        }

    private:

        enum StateEnum
        {
            DISABLED,
            MONITORING_FOR_NO_KEYS_DOWN,
            MONITORING_FOR_DOWN,
            MONITORING_FOR_UP,
            PRESSED,
            RELEASE
        };

        StateEnum     m_state;
        unsigned long m_releaseTime;
};

#endif
