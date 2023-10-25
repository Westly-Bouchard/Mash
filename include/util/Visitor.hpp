/**
 * @file Visitor.hpp
 * @author Westly Bouchard (westly_bouchard@mines.edu)
 * @brief Utility file for visitor pattern implementation
 * @version 0.1
 * @date 2023-10-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef VISITOR_HPP
#define VISITOR_HPP

// Template declaration
template <typename... Types>
class Visitor;

// Specialization for one type
template <typename T>
class Visitor<T> {
    public:
        virtual void visit(T& visitable) = 0;
};

template <typename T, typename... Types>
class Visitor<T, Types...> : public Visitor<Types...> {
    public:
        // Promote function from base class
        using Visitor<Types...>::visit;

        virtual void visit(T& visitable) = 0;
};

#endif
