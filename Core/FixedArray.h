#ifndef FIXED_ARRAY_H_
#define FIXED_ARRAY_H_

#include <algorithm>
#include <cstddef>

// AVR's stlport doesn't provide std::array, so if I want a statically-allocatable fixed size array utility (with
// my convenience helper functions) I have to roll my own.

template <typename T, std::size_t N, T T_EMPTY_VALUE>
class FixedArray
{
    public:

        static const std::size_t LAST_ELEMENT = N - 1;
        static const std::size_t CAPACITY     = N;

        typedef T*       iterator;
        typedef const T* const_iterator;

    private:

        T           m_array[N];
        std::size_t m_nextInsertIndex;

    public:

        FixedArray()
            : m_nextInsertIndex(0)
        { 
            clear();
        }

        const_iterator begin() const
        {
            return &m_array[0];
        }

        const_iterator end() const
        {
            return &m_array[0] + CAPACITY;
        }

        iterator begin()
        {
            return &m_array[0];
        }

        iterator end()
        {
            return &m_array[0] + CAPACITY;
        }

        std::size_t size() const
        {
            return m_nextInsertIndex;
        }

        std::size_t capacity() const
        {
            return CAPACITY;
        }

        void clear()
        {
            std::fill_n(begin(), N, T_EMPTY_VALUE);
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

        FixedArray& operator=(const FixedArray& i_rhs)
        {
            std::copy(i_rhs.begin(), i_rhs.end(), begin());
            m_nextInsertIndex = i_rhs.m_nextInsertIndex;

            return *this;
        }

        bool PushElement(const T& i_data)
        {
            if (m_nextInsertIndex < N and i_data != T_EMPTY_VALUE)
            {
                m_array[m_nextInsertIndex] = i_data;
                ++m_nextInsertIndex;
                return true;
            }
            return false;
        }

        void DeleteElement(const T& i_data)
        {
            if (i_data != T_EMPTY_VALUE)
            {
                std::size_t reader;
                std::size_t writer;

                for (reader = writer = 0; reader < m_nextInsertIndex; ++ reader)
                {
                    if (m_array[reader] == i_data)
                    {
                        // The important detail about this is that reader will advance while writer stays put.
                        continue;
                    }

                    if (writer != reader)
                    {
                        m_array[writer] = m_array[reader];
                    }

                    ++writer;
                }

                m_nextInsertIndex -= (reader - writer);

                while (writer < reader)
                {
                    m_array[writer] = T_EMPTY_VALUE;
                    ++writer;
                }
            }
        }

        bool DeleteLastElement()
        {
            if (m_nextInsertIndex > 0)
            {
                --m_nextInsertIndex;
                m_array[m_nextInsertIndex] = T_EMPTY_VALUE;
                return true;
            }
            return false;
        }

};

#endif
