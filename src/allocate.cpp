#include "allocate.h"


void Arena::reset () { m_offset = 0; }

std::size_t Arena::capacity() const { return m_capacity; }

std::size_t Arena::remaining() const { return m_capacity - m_offset; }

std::size_t Arena::used() const { return m_offset; }

char* Arena::allocate(std::size_t size, std::size_t alignment)
{   
    char* start { m_arena.get() };
    char* end { start + m_capacity };
    char* next_free { start + m_offset };

    uintptr_t addr = reinterpret_cast<uintptr_t>(next_free);

    std::size_t padding { (alignment - (addr % alignment)) % alignment };

    char* aligned_address { next_free + padding };

    if(aligned_address + size > end)
    {
        throw std::runtime_error("SIZE TOO BIG");
    }
    m_offset = (aligned_address - start) + size;

    return aligned_address;
}

void Arena::print_debug() const
{
    std::cout << "Capacity: " << m_capacity << '\n'
             << "Used: " << used() << " bytes " << '\n'
             << "Remaining: " << remaining() << " bytes" << '\n'; 
}

