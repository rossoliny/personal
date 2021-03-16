//
// Created by Isa on 3/13/21.
//

#ifndef ALIGNED_BUFFER_H
#define ALIGNED_BUFFER_H

#include <type_traits>

namespace gcc
{
    template<typename Tp>
    struct aligned_membuf
    {

        struct Tp2
        {
            Tp m_t;
        };

        alignas(alignof(Tp2::m_t)) unsigned char m_storage[sizeof(Tp)];

        aligned_membuf() = default;

        // Can be used to avoid value-initialization zeroing _M_storage.
        aligned_membuf(std::nullptr_t)
        {
            // do not zero out storage
        }

        void* m_addr() noexcept
        {
            return static_cast<void*>(&m_storage);
        }

        const void* m_addr() const noexcept
        {
            return static_cast<const void*>(&m_storage);
        }

        Tp* m_ptr() noexcept
        {
            return static_cast<Tp *>(m_addr());
        }

        const Tp* m_ptr() const noexcept
        {
            return static_cast<const Tp*>(m_addr());
        }
    };

}


#endif //ALIGNED_BUFFER_H
