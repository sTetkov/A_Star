#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <vector>
#include <functional>

///\brief: Templated priority queue class based on std::vector
///
/// Priority queue with constant access to the highest priority element and
/// linear insertion time. While there are better structures on a therorethical
/// level, std::vector is often the fastest choiche for small elements adn low
/// element count (low element count in this case being up to 10K elements).
template <typename T, typename K>
class PriorityQueue
{
    public:
        PriorityQueue();
        virtual ~PriorityQueue();

        ///\brief: Adds an element to the priority queue, given the lement and the key
        ///
        /// Adds an element of type T using a key of type K. Insertion has a linear cost
        /// of O(n) with n being the number of already stored elements.
        void AddElement(T,K);

        ///\brief: Returns the element with highest priority, deleting it from the queue
        T Pop();

        ///\brief: returns the element with highest priority
        T Peek();

        ///\brief: returns true if the Priority queue contains already an element T
        bool contains(T);

        ///\brief: returns true if the priority queueu is emtpy
        bool isEmpty();

        ///\brief: Adds an element with its key if the queue doesn't already contain it,
        ///        otherwise it updates the key for the element.
        void AddOrUpdateElement(T,K);

        ///\brief: Sets the function for a<b if needed
        void setIsLessFunction(std::function<bool(K,K)>);

        ///\brief: sets the function for a==b if needed
        void setIsEqualFunction(std::function<bool(T,T)>);

        ///\brief: sets the condition for updating an element if needed
        void setIsToUpdateFunction(std::function<bool(T,T)>);

    protected:
    private:
        std::function<bool(K,K)> isLess;
        std::function<bool(T,T)> isEqual;
        std::function<bool(T,T)> isToUpdate;

        std::vector<T> m_vData;
        std::vector<K> m_vKeys;

        void swap(size_t,size_t);
        size_t findMinIndex();
        size_t findElement(T);
};

#endif // PRIORITYQUEUE_H
