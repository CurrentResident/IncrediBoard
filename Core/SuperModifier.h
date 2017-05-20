#ifndef SUPER_MODIFIER_H_
#define SUPER_MODIFIER_H_

#include <boost/fusion/algorithm.hpp>
#include <boost/fusion/iterator.hpp>

#include "BoardState.h"
#include "Key.h"
#include "Platform.h"

namespace SuperModifier
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


    enum StateEnum
    {
        DISABLED,
        MONITORING_FOR_NO_KEYS_DOWN,
        MONITORING_FOR_DOWN,
        MONITORING_FOR_UP,
        PRESSED,
        RELEASE
    };


    template <typename ModifierKeyType, typename OtherKeysCollectionType>
    struct Keys
    {
        Keys():
            releaseTime (0),
            state       (MONITORING_FOR_NO_KEYS_DOWN)
        {}

        unsigned long releaseTime;

        StateEnum                       state;
        typedef OtherKeysCollectionType OtherKeys;
    };

    struct UpdateState
    {
        UpdateState(BoardState& io_boardState) : boardState(io_boardState) {}

        BoardState& boardState;

        template <typename ModifierKeyType, typename OtherKeysCollectionType>
        void operator() (Keys<ModifierKeyType, OtherKeysCollectionType>& superMod) const
        {
            switch(superMod.state)
            {
                case MONITORING_FOR_NO_KEYS_DOWN:
                    if (boardState.m_modifiers == 0 and boardState.m_keyReportArray.size() == 0)
                    {
                        superMod.state = MONITORING_FOR_DOWN;
                    }
                    break;

                case MONITORING_FOR_DOWN:

                    if (boardState.m_modifiers & ~ModifierKeyType::MODIFIER or
                        boardState.m_keyReportArray.size() != 0)
                    {
                        superMod.state = MONITORING_FOR_NO_KEYS_DOWN;
                    }
                    else
                    {
                        if (boardState.m_modifiers == ModifierKeyType::MODIFIER)
                        {
                            superMod.state = MONITORING_FOR_UP;
                        }
                    }

                    break;

                case MONITORING_FOR_UP:

                    if (boardState.m_modifiers & ~ModifierKeyType::MODIFIER or
                        boardState.m_keyReportArray.size() != 0)
                    {
                        superMod.state = MONITORING_FOR_NO_KEYS_DOWN;
                    }
                    else
                    {
                        if (boardState.m_modifiers == 0)
                        {
                            superMod.state = PRESSED;
                            superMod.releaseTime = Platform::GetMsec() + 10;

                            boost::fusion::for_each(OtherKeysCollectionType(), PressKeys(boardState, true));
                        }
                    }

                    break;

                case PRESSED:

                    if (superMod.releaseTime < Platform::GetMsec())
                    {
                        boost::fusion::for_each(OtherKeysCollectionType(), PressKeys(boardState, false));

                        superMod.state = MONITORING_FOR_NO_KEYS_DOWN;
                        superMod.releaseTime = 0;
                    }
                    break;

                case DISABLED:
                default:
                    break;
            }
        }
    };
};

template <typename SuperModKeysCollection>
class SuperModifierComponent
{
    public:
        void Process(BoardState& io_state)
        {
            boost::fusion::for_each(this->m_superModKeys, SuperModifier::UpdateState(io_state));
        }

    private:

        SuperModKeysCollection m_superModKeys;
};

#endif
