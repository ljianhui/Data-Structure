#ifndef SHAREPTR1_H_INCLUDED
#define SHAREPTR1_H_INCLUDED

#include <stdexcept>


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
        void _decUsed();
        inline void _nullTest()const;
        inline bool _isSame(const SharePtr &sptr)const;
        inline bool _isSame(const T *tptr)const;

    private://data
        T *_ptr;
        size_t *_used;
};

template <typename T>
SharePtr<T>::SharePtr(T *tptr):
    _ptr(tptr),
    _used(new size_t(1))
{
}

template <typename T>
SharePtr<T>::SharePtr(const SharePtr &sptr):
    _ptr(sptr._ptr),
    _used(sptr._used)
{
    ++*_used;
}

template <typename T>
SharePtr<T>& SharePtr<T>::operator=(const SharePtr &sptr)
{
    ++*_used;
    _decUsed();
    _ptr = sptr._ptr;
    return *this;
}

template <typename T>
SharePtr<T>& SharePtr<T>::operator=(T *tptr)
{
    _decUsed();
    _ptr = tptr;
    _used = new size_t(1);
    return *this;
}

template <typename T>
SharePtr<T>::~SharePtr()
{
    _decUsed();
}

template <typename T>
T& SharePtr<T>::operator*()const
{
    _nullTest();
    return *_ptr;
}

template <typename T>
T* SharePtr<T>::operator->()const
{
    _nullTest();
    return _ptr;
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
    return _ptr;
}

template <typename T>
void SharePtr<T>::_decUsed()
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
void SharePtr<T>::_nullTest()const
{
    if(_ptr == NULL)
        throw std::runtime_error("Use the memory address 0x0");
}

template <typename T>
bool SharePtr<T>::_isSame(const SharePtr &sptr)const
{
    return _isSame(sptr._ptr);
}

template <typename T>
bool SharePtr<T>::_isSame(const T *tptr)const
{
    if(_ptr == tptr)
        return true;
    return false;
}

#endif // SHAREPTR1_H_INCLUDED
