#ifndef FIXED_ARRAY_H_
#define FIXED_ARRAY_H_

#include <algorithm>
#include <cstddef>

// AVR's stlport doesn't provide std::array, so if I want a statically-allocatable fixed size array utility (with
// my convenience helper functions) I have to roll my own.

template <typename T, std::size_t N, T t_defaultValue>
class FixedArray
{
    public:

        static const std::size_t LAST_ELEMENT = N - 1;
        static const std::size_t SIZE         = N;

        typedef T*       iterator;
        typedef const T* const_iterator;

    private:

        T           m_array[N];
        std::size_t m_nextInsertIndex;

    public:

        FixedArray()
            : m_nextInsertIndex(0)
        { }

        const_iterator begin() const
        {
            return &m_array[0];
        }

        const_iterator end() const
        {
            return &m_array[0] + SIZE;
        }

        iterator begin()
        {
            return &m_array[0];
        }

        iterator end()
        {
            return &m_array[0] + SIZE;
        }

        void clear()
        {
            std::fill_n(begin(), N, t_defaultValue);
            m_nextInsertIndex = 0;
        }

        T* Get()
        {
            return m_array;
        }

        T& operator[] (const std::size_t i)
        {
            return m_array[i];
        }

        bool PushElement(const T& i_data)
        {
            if (m_nextInsertIndex < N)
            {
                m_array[m_nextInsertIndex] = i_data;
                ++m_nextInsertIndex;
                return true;
            }
            return false;
        }

        void DeleteElement(const T& i_data)
        {
            if (i_data != t_defaultValue)
            {
                T* reader;
                T* writer;

                for(reader = writer = &m_array[0]; reader <= &m_array[LAST_ELEMENT]; ++reader)
                {
                    if (*reader == i_data)
                    {
                        --m_nextInsertIndex;
                        continue;
                    }
                    if (writer != reader)
                    {
                        *writer = *reader;
                    }

                    ++writer;
                }

                while (writer <= &m_array[LAST_ELEMENT])
                {
                    *writer = t_defaultValue;
                    ++writer;
                }
            }
        }
};

#endif

