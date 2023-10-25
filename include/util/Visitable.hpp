/**
 * @file Visitable.hpp
 * @author Westly Bouchard (westly_bouchard@mines.edu)
 * @brief Utility file for visitable objects
 * @version 0.1
 * @date 2023-10-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef VISITABLE_HPP
#define VISITABLE_HPP

#include "Visitor.hpp"

template <typename... Types>
class Visitable {
    public:
        virtual void accept(Visitor<Types...>& visitor) = 0;
};

template <typename Derived, typename... Types>
class VisitableImpl : public Visitable<Types...> {
    public:
        virtual void accept(Visitor<Types...>& visitor) {
            visitor.visit(static_cast<Derived&>(*this));
        }

        virtual ~VisitableImpl() = default;
};

#endif
