#ifndef _QUEUE_H_INCLUDED
#define _QUEUE_H_INCLUDED

//实现循环队列

template<typename T>
class Queue
{
    public:
        Queue(size_t _capacity = 1);
        ~Queue();

        inline void clearQueue();
        inline bool isEmpty()const;
        inline size_t getLength()const;
        inline const T& getHead()const;
        inline void enqueue(const T &e);
        T depueue();

    private:
        Queue(const Queue &queue){}
        Queue& operator=(const Queue &Queue){return *this;}

        void _newMenory();
        void _insert(const T &e);

        size_t capacity;
        size_t length;
        T *pBase;
        T *pHead;
        T *pLast;
};

template<typename T>
Queue<T>::Queue(size_t _capacity):
    capacity(_capacity),
    length(0),
    pBase(new T[_capacity]),
    pHead(pBase),
    pLast(pBase)
{
}

template<typename T>
Queue<T>::~Queue()
{
    delete []pBase;
}

template<typename T>
void Queue<T>::clearQueue()
{
    pHead = pBase;
    pLast = pBase;
    length = 0;
}

template<typename T>
bool Queue<T>::isEmpty()const
{
    return !length;
}

template<typename T>
size_t Queue<T>::getLength()const
{
    return length;
}

template<typename T>
const T& Queue<T>::getHead()const
{
    return *pHead;
}

template<typename T>
void Queue<T>::_newMenory()
{
    T *ptmpNew(new T[2*capacity]);
    T *ptmpNewCopy(ptmpNew);
    T *ptmpheadCopy(pHead);
    T *ptmplimit(pBase + capacity -1);

    for(size_t i = 0; i < capacity; ++i)
    {
        *ptmpNewCopy = *ptmpheadCopy;
        if(ptmpheadCopy == ptmplimit)
        {
            ptmpheadCopy = pBase;
            continue;
        }
        ++ptmpNewCopy;
        ++ptmpheadCopy;
    }
    delete []pBase;
    pBase = ptmpNew;
    pHead = pBase;
    pLast = pBase + capacity;
    capacity *= 2;
}

template<typename T>
void Queue<T>::_insert(const T &e)
{
    if(pLast != (pBase + capacity))
    {
        *pLast = e;
        ++pLast;
    }
    else
    {
        *pBase = e;
        pLast = pBase + 1;
    }
}

template<typename T>
void Queue<T>::enqueue(const T &e)
{
    ++length;

    if(length > capacity)
        _newMenory();

    _insert(e);
}

template<typename T>
T Queue<T>::depueue()
{
    if(length > 0)
    {
        --length;
        if(pHead == pBase + capacity -1)
        {
            T tmp(*pHead);
            pHead = pBase;
            return tmp;
        }
        return *(pHead++);
    }
    return *pBase;
}


#endif // _QUEUE_H_INCLUDED
