#ifndef MY_ALLOCATE_H
#define MY_ALLOCATE_H

#include <iostream>
#include <memory>

class Arena
{
    private:
        std::unique_ptr<char[]> m_arena { };
        std::size_t  m_offset { };
        std::size_t m_capacity { };

    public:
        Arena(std::size_t capacity)
        : m_arena { std::make_unique<char[]> (capacity) }, m_capacity { capacity }
        { }

        char* allocate(std::size_t size, std::size_t alignment);
        void reset ();
        std::size_t capacity() const;
        std::size_t remaining() const;
        std::size_t used() const;
        void print_debug() const;

        //rule of FIVE

        //copy construcor
        Arena(const Arena&) = delete;
        //copy assignment
        Arena& operator=(const Arena&) = delete;
        //move constrocor
        Arena (Arena&&) = delete;
        //move assignment
        Arena& operator=(Arena&&) = delete;
        //destructor
        ~Arena() = default;
};

#endif //MY_ALLOCATE_H