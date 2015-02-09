#include "PriorityQueue.h"

///\brief: Constructor for the priority queue. Initializes the comparison functions
template <typename T, typename K>
PriorityQueue<T,K>::PriorityQueue()
{
    isLess=[](K a, K b){return a<b;};
    isEqual=[](T a, T b){return a==b;};
    isToUpdate=[](T a, T b){return false;};
}

template <typename T, typename K>
PriorityQueue<T,K>::~PriorityQueue()
{
    //dtor
}

///\brief: Adds element to the queue in O(n)
template <typename T, typename K>
void PriorityQueue<T,K>::AddElement(T element, K key)
{
    m_vData.push_back(element);
    m_vKeys.push_back(key);
    size_t minIdx=findMinIndex();
    if(m_vData.size()!=1 && minIdx!=(m_vData.size()-1))
        swap(minIdx,m_vData.size()-1);
}

///\brief: Adds an element or updates it if already present and the new key is better than the old one.
template <typename T, typename K>
void PriorityQueue<T,K>::AddOrUpdateElement(T element, K key)
{
    size_t idx=findElement(element);
    if(idx==m_vData.size())
    {
        AddElement(element,key);
        return;
    }
    if(!isToUpdate(element,m_vData[idx]))
        return;

    m_vData[idx]=element;
    m_vKeys[idx]=key;

    size_t minIdx=findMinIndex();
    if(m_vData.size()!=1 && minIdx!=(m_vData.size()-1))
        swap(minIdx,m_vData.size()-1);
}

///\brief: returns the element with highest priority and deletes it from the queue
template <typename T, typename K>
T PriorityQueue<T,K>::Pop()
{
    T res=m_vData.back();
    m_vData.pop_back();
    m_vKeys.pop_back();
    return res;
}

///\brief: returns the element with the highest priority
template <typename T, typename K>
T PriorityQueue<T,K>::Peek()
{
    return m_vData.back();
}

template <typename T, typename K>
bool PriorityQueue<T,K>::contains(T element)
{
    for(size_t i=0;i<m_vData.size();i++)
        if(isEqual(m_vData[i],element))
            return true;
    return false;
}

template <typename T, typename K>
bool PriorityQueue<T,K>::isEmpty()
{
    return m_vData.size()==0;
}

template <typename T, typename K>
void PriorityQueue<T,K>::setIsLessFunction(std::function<bool(K,K)> isLessFunction)
{
    isLess=isLessFunction;
}

template <typename T, typename K>
void PriorityQueue<T,K>::setIsEqualFunction(std::function<bool(T,T)> isEqualFunction)
{
    isEqual=isEqualFunction;
}

template <typename T, typename K>
void PriorityQueue<T,K>::setIsToUpdateFunction(std::function<bool(T,T)> isToUpdateFunction)
{
    isToUpdate=isToUpdateFunction;
}

template <typename T, typename K>
void PriorityQueue<T,K>::swap(size_t idxA, size_t idxB)
{
    T auxD=m_vData[idxA];
    K auxK=m_vKeys[idxA];

    m_vData[idxA]=m_vData[idxB];
    m_vKeys[idxA]=m_vKeys[idxB];

    m_vData[idxB]=auxD;
    m_vKeys[idxB]=auxK;
}

template <typename T, typename K>
size_t PriorityQueue<T,K>::findMinIndex()
{
    size_t idx=0;
    for(size_t i=0; i<m_vKeys.size(); i++)
        if(isLess(m_vKeys[i],m_vKeys[idx]))
            idx=i;
    return idx;
}

template <typename T, typename K>
size_t PriorityQueue<T,K>::findElement(T element)
{
    for(size_t i=0; i<m_vData.size(); i++)
        if(isEqual(element,m_vData[i]))
            return i;
    return m_vKeys.size();
}
