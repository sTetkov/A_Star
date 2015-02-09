#include "Set.h"

template <typename T>
Set<T>::Set()
{
    isEqual=[](T a, T b){return a==b;};
}

template <typename T>
Set<T>::~Set()
{
    //dtor
}

template <typename T>
void Set<T>::AddElement(T element)
{
    for(size_t i=0; i<m_vData.size(); i++)
        if(isEqual(element,m_vData[i]))
        {
            m_vData[i]=element;
            return;
        }
    m_vData.push_back(element);
}

template <typename T>
bool Set<T>::Contains(T element)
{
    for(size_t i=0; i<m_vData.size(); i++)
        if(isEqual(element,m_vData[i]))
            return true;
    return false;
}

template <typename T>
T Set<T>::getElement(T element)
{
    for(size_t i=0; i<m_vData.size(); i++)
        if(isEqual(element,m_vData[i]))
            return m_vData[i];
    return element;
}

template <typename T>
void Set<T>::setIsEqualFunction(std::function<bool(T,T)> isEqualFunction)
{
    isEqual=isEqualFunction;
}
