#ifndef SET_H
#define SET_H

#include <vector>
#include <functional>

///\brief: a templated Set based on std::vector. For small amounts of elements of
///        small size it is faster than other, theoretical more efficient, structures.
template <typename T>
class Set
{
    public:
        Set();
        virtual ~Set();

        ///\brief: adds an element in O(n) if not already in the set
        void AddElement(T);
        ///\brief: returns true if an element is already in the set in O(n)
        bool Contains(T);

        ///\brief: returns the element equal to the argument in O(n)
        T getElement(T);

        void setIsEqualFunction(std::function<bool(T,T)>);

    protected:
    private:
        std::function<bool(T,T)> isEqual;
        std::vector<T> m_vData;

};

#endif // SET_H
