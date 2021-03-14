//
// Created by Isa on 3/15/21.
//

#ifndef TMP_UTILS_H
#define TMP_UTILS_H

#include <iterator>

namespace gcc {


    template<typename Input_iterator>
    using require_input_iter =
            typename std::enable_if<
                    std::is_convertible<
                            typename std::iterator_traits<Input_iterator>::iterator_category,
                            std::input_iterator_tag
                        >::value
                >::type;

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

}

#endif //TMP_UTILS_H
