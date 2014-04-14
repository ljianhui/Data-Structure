#ifndef SHAREPTR2_H_INCLUDED
#define SHAREPTR2_H_INCLUDED

#include <stdexcept>

template<typename T>
class SharePtr;
template<typename T>
class ObjectCount;

template <typename T>
class ObjectCount
{
    friend class SharePtr<T>;

    public:
        ~ObjectCount();
        void decUsed();
        void addUsed();

    private://function
        ObjectCount(T *tptr = NULL);

    private://data
        T *_ptr;
        size_t *_used;
};

template <typename T>
class SharePtr
{
    public:
        SharePtr(T *tptr = NULL);
        SharePtr(const SharePtr &sptr);
        SharePtr& operator=(const SharePtr &sptr);
        SharePtr& operator=(T *tptr);
        ~SharePtr();

        T& operator*()const;
        T* operator->()const;

        bool operator==(const SharePtr &sptr)const;
        bool operator!=(const SharePtr &sptr)const;

        bool operator==(const T *tptr)const;
        bool operator!=(const T *tptr)const;

        const T* getPtr()const;


    private://function
        inline void _nullTest()const;
        inline bool _isSame(const SharePtr &sptr)const;
        inline bool _isSame(const T *tptr)const;

    private://data
        ObjectCount<T> *_objptr;
};

template <typename T>
ObjectCount<T>::ObjectCount(T *tptr):
    _ptr(tptr),
    _used(new size_t(1))
{
}

template <typename T>
void ObjectCount<T>::decUsed()
{
    --*_used;
    if(*_used == 0)
    {
        if(_ptr != NULL)
        {
            delete _ptr;
            _ptr = NULL;
        }
        delete _used;
        _used = NULL;
    }
}

template <typename T>
void ObjectCount<T>::addUsed()
{
    ++*_used;
}

template <typename T>
ObjectCount<T>::~ObjectCount()
{
    decUsed();
}

template <typename T>
SharePtr<T>::SharePtr(T *tptr)
    :_objptr(new ObjectCount<T>(tptr))
{
}

template <typename T>
SharePtr<T>::SharePtr(const SharePtr &sptr):
    _objptr(sptr._objptr)
{
    _objptr->addUsed();
}

template <typename T>
SharePtr<T>& SharePtr<T>::operator=(const SharePtr &sptr)
{
    sptr._objptr->addUsed();
    _objptr->decUsed();
    _objptr = sptr._objptr;
    return *this;
}

template <typename T>
SharePtr<T>& SharePtr<T>::operator=(T *tptr)
{
    _objptr->decUsed();
    _objptr = new ObjectCount<T>(tptr);
    return *this;
}

template <typename T>
SharePtr<T>::~SharePtr()
{
    _objptr->decUsed();
}

template <typename T>
T& SharePtr<T>::operator*()const
{
    _nullTest();
    return *(_objptr->_ptr);
}

template <typename T>
T* SharePtr<T>::operator->()const
{
    _nullTest();
    return _objptr->_ptr;
}

template <typename T>
bool SharePtr<T>::operator==(const SharePtr &sptr)const
{
    return _isSame(sptr);
}

template <typename T>
bool SharePtr<T>::operator!=(const SharePtr &sptr)const
{
    return _isSame(sptr);
}

template <typename T>
bool SharePtr<T>::operator==(const T *tptr)const
{
    return _isSame(tptr);
}

template <typename T>
bool SharePtr<T>::operator!=(const T *tptr)const
{
    return _isSame(tptr);
}

template <typename T>
const T* SharePtr<T>::getPtr()const
{
    return _objptr->_ptr;
}

template <typename T>
void SharePtr<T>::_nullTest()const
{
    if(_objptr->_ptr == NULL)
        throw std::runtime_error("Use the memory address 0x0");
}

template <typename T>
bool SharePtr<T>::_isSame(const SharePtr &sptr)const
{
    if(_objptr == sptr._objptr)
        return true;
    return false;
}

template <typename T>
bool SharePtr<T>::_isSame(const T *tptr)const
{
    if(_objptr->_ptr == tptr)
        return true;
    return false;
}

#endif // SHAREPTR2_H_INCLUDED
