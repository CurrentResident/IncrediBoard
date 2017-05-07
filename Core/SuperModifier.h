#ifndef SUPER_MODIFIER_H_
#define SUPER_MODIFIER_H_

#include <boost/fusion/algorithm.hpp>

#include "BoardState.h"
#include "Platform.h"

template <typename ModifierKeyType, typename OtherKeysCollectionType>
class SuperModifier
{
    public:

        SuperModifier() :
            m_state      (MONITORING_FOR_DOWN),
            m_releaseTime(0)
        {
        }

        void Process(BoardState& io_state)
        {
            switch(m_state)
            {
                case MONITORING_FOR_DOWN:

                    if (io_state.m_modifiers & ModifierKeyType::MODIFIER and
                        io_state.m_keyReportArray.size() == 0)
                    {
                        m_state = MONITORING_FOR_UP;
                    }

                    break;

                case MONITORING_FOR_UP:

                    if (io_state.m_keyReportArray.size() != 0)
                    {
                        m_state = NO_GO_WAIT_FOR_MOD_RELEASE;
                    }
                    else
                    {
                        if ((io_state.m_modifiers & ModifierKeyType::MODIFIER) == 0)
                        {
                            m_state = PRESSED;
                            m_releaseTime = Platform::GetMsec() + 10;

                            //TODO: Press the button.
                        }
                    }

                    break;

                case NO_GO_WAIT_FOR_MOD_RELEASE:

                    if (io_state.m_keyReportArray.size() == 0 and
                       (io_state.m_modifiers & ModifierKeyType::MODIFIER) == 0)
                    {
                        m_state = MONITORING_FOR_DOWN;
                    }

                    break;

                case PRESSED:

                    if (m_releaseTime < Platform::GetMsec())
                    {
                        //TODO: Release the buttons.

                        m_state = MONITORING_FOR_DOWN;
                        m_releaseTime = 0;
                    }
                    break;

                case DISABLED:
                    if (m_releaseTime != 0)
                    {
                        //TODO: Release the buttons.
                        m_releaseTime = 0;
                    }

                default:
                    break;
            }
        }

    private:

        enum StateEnum
        {
            DISABLED,
            MONITORING_FOR_DOWN,
            MONITORING_FOR_UP,
            NO_GO_WAIT_FOR_MOD_RELEASE,
            PRESSED
        };

        StateEnum     m_state;
        unsigned long m_releaseTime;
};

#endif
