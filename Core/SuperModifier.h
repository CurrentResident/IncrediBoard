#ifndef SUPER_MODIFIER_H_
#define SUPER_MODIFIER_H_

#include <boost/fusion/algorithm.hpp>
#include <boost/fusion/iterator.hpp>

#include "BoardState.h"
#include "Key.h"
#include "Platform.h"

#if 0
//template <typename CollectionType>
/*
template <typename CollectionType>
struct PressKeysB
{
    typedef typename boost::fusion::result_of::begin<CollectionType>::type BeginType;
    typedef typename boost::fusion::result_of::end<CollectionType>::type EndType;

    template <uint8_t T_KEY_CODE>
    void Press(Key<T_KEY_CODE>)
    {

    }

    template <typename I>
    void operator() () const
    {
        operator()<typename boost::fusion::result_of::next<I>::type>();
    }

    template <typename I>
    void operator() () const
    {
        operator()<typename boost::fusion::result_of::next<I>::type>();
    }
};
*/

template <typename CollectionType, typename Iterator>
struct PressKeysA
{

    /*
    template <typename KeyType>
    void Press(BoardState& io_state) const
    {
    }
    */

    template <uint8_t T_KEY_CODE>
    void Press(BoardState& io_state, Key<T_KEY_CODE>) const
    {
        io_state.ChangeKeyState<T_KEY_CODE>(1);
    }

    void operator() (BoardState& io_state) const
    {
        Press(io_state, typename boost::fusion::result_of::value_of<Iterator>::type());

        //PressKeysA<CollectionType, typename boost::fusion::result_of::deref<Iterator>::type> b;
        //b(io_state);

        PressKeysA<CollectionType, typename boost::fusion::result_of::next<Iterator>::type> a;
        a(io_state);
    }
};

/*
template <typename CollectionType, uint8_t T_KEY_CODE>
struct PressKeysA<CollectionType, Key<T_KEY_CODE> >
{
    void operator() (BoardState& io_state) const
    {
    }
};
*/
template <typename CollectionType>
struct PressKeysA<CollectionType, typename boost::fusion::result_of::end<CollectionType>::type>
{
    void operator() (BoardState& io_state) const
    {
    }
};

template <typename CollectionType>
struct PressKeys
{
    void operator() (BoardState& io_state) const
    {
        PressKeysA<CollectionType, typename boost::fusion::result_of::begin<CollectionType>::type> a;
        a(io_state);
    }
};
#endif

struct PressKeys
{
    BoardState& state;
    PressKeys(BoardState& io_state) : state(io_state) {}

    template <uint8_t T_KEY_CODE>
    void operator()(Key<T_KEY_CODE>) const
    {
        state.ChangeKeyState<T_KEY_CODE>(1);
    }
};
/*
namespace Press
{
    template <typename CollectionType, typename Iterator>
    void One()
        {
            One<CollectionType, typename boost::fusion::result_of::next<Iterator>::type>();
        }
                //boost::fusion::result_of::begin
    template <typename CollectionType>
    void One<typename boost::fusion::result_of::end<CollectionType>::type>()
        {
            //One<CollectionType, typename boost::fusion::result_of::next<Iterator>::type>();
        }

    template <typename CollectionType>
    void All()
        {
            One<CollectionType, typename boost::fusion::result_of::begin<CollectionType>::type>();
        }
};

template <typename CollectionType>
static void Press<CollectionType>::One<typename boost::fusion::result_of::end<CollectionType>::type>()
    {
    }

*/
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

                            //Press::All<OtherKeysCollectionType>();
                            //TODO: Press the button.
                            //PressKeys<OtherKeysCollectionType> a;
                            boost::fusion::for_each(OtherKeysCollectionType(), PressKeys(io_state));
                            //a(io_state);
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
            PRESSED,
            RELEASE
        };

        StateEnum     m_state;
        unsigned long m_releaseTime;
};

#endif
