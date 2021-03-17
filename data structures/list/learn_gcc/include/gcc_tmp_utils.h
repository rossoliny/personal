//
// Created by Isa on 3/15/21.
//

#ifndef TMP_UTILS_H
#define TMP_UTILS_H


#define NOEXCEPT_IF(...) noexcept(__VA_ARGS__)

#include <iterator>
#include <memory>

namespace gcc {


    template<typename Input_iterator>
    using require_input_iter =
            typename std::enable_if<
                    std::is_convertible<
                            typename std::iterator_traits<Input_iterator>::iterator_category,
                            std::input_iterator_tag
                        >::value
                >::type;

    // if iterator is noexcept_move_constructible or only_move_type then make move_iterator else iterator
    template
            <
            typename Iterator,
            typename Return_type =
            typename std::conditional<
            			!std::is_nothrow_move_constructible<Iterator>::value &&
            			std::is_copy_constructible<Iterator>::value,
            			Iterator,
            			std::move_iterator < Iterator>
                    > ::type
            >
    inline constexpr Return_type make_move_iterator_if_noexcept(Iterator i)
    {
        return _ReturnType(i);
    }

    // Overload for pointers that matches std::move_if_noexcept more closely,
    // returning a constant iterator when we don't want to move.
    template
            <
            typename Tp,
            typename Return_type =
            typename std::conditional<
                    !std::is_nothrow_move_constructible<Tp>::value && std::is_copy_constructible<Tp>::value,
                    const Tp *,
                    std::move_iterator < Tp * >
                > ::type
            >

    inline constexpr Return_type make_move_iterator_if_noexcept(Tp *i)
    {
        return _ReturnType(i);
    }

    // Optimize for stateless allocators
    template<typename Alloc, bool = std::is_empty<Alloc>::value>
    struct alloc_not_equal
    {
        static bool _so_do_it(const Alloc &, const Alloc &)
        {
            return false;
        }
    };

    // Stateful allocators
    template<typename Alloc>
    struct alloc_not_equal<Alloc, false>
    {
        static bool _so_do_it(const Alloc &one, const Alloc &two)
        {
            return one != two;
        }
    };


    // move assign allocator if possible
    template<typename Alloc>
    inline void do_alloc_on_move(Alloc& a, Alloc& b, std::true_type)
    {
        // pocma true -> move assign allocators
        a = std::move(b);
    }

    template<typename Alloc>
    inline void do_alloc_on_move(Alloc& a, Alloc& b, std::false_type)
    {
        // pocma false -> do nothing
        return;
    }

    template<typename Alloc>
    inline void alloc_on_move(Alloc& a, Alloc& b)
    {
        using pocma = typename std::allocator_traits<Alloc>::propagate_on_container_move_assignment;
        do_alloc_on_move(a, b, pocma());
    }



    // copy assign allocator if possible
    template<typename Alloc>
    inline void do_alloc_on_copy(Alloc& a, const Alloc& b, std::true_type)
    {
        a = b;
    }

    template<typename Alloc>
    inline void do_alloc_on_copy(Alloc& a, const Alloc& b, std::false_type)
    {
        return;
    }

    template<typename Alloc>
    inline void alloc_on_copy(Alloc& a, const Alloc& b)
    {
        using traits = std::allocator_traits<Alloc>;
        using pocca = typename traits::propagate_on_container_copy_assignment;

        do_alloc_on_copy(a, b, pocca());
    }


    template<typename Alloc>
    inline void do_alloc_on_swap(Alloc& a, Alloc& b, std::true_type)
    {
        using std::swap;
        swap(a, b);
    }

    template<typename Alloc>
    inline void do_alloc_on_swap(Alloc& a, Alloc& b, std::false_type)
    {
        return;
    }

    template<typename Alloc>
    inline void alloc_on_swap(Alloc& a, Alloc& b)
    {
        typedef std::allocator_traits<Alloc> traits;
        typedef typename traits::propagate_on_container_swap pocs;
        do_alloc_on_swap(a, b, pocs());
    }

    template <bool B>
    using bool_constant = std::integral_constant<bool, B>;

}

#endif //TMP_UTILS_H
