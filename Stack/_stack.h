#ifndef _STACK_H_INCLUDED
#define _STACK_H_INCLUDED

template<typename T>
class Stack
{
	public:
		Stack(size_t capacity = 8):
            _capacity(capacity),
            _arry(new T[_capacity]),
            _length(0),
            _top(_arry){}

		~Stack();
		inline void clearStack();

		inline bool isEmpty()const;
		inline size_t getSize()const;
		inline size_t getCapacity()const;
		void push(const T& e);
		inline T pop();
		inline const T& getTop()const;
	private:
        Stack(const Stack &s){}
        Stack& operator=(const Stack &s){return *this;}

		size_t _capacity;
		T *_arry;
		size_t _length;
		T *_top;
};

//template<typename T>
//Stact<T>::Stack(size_t capacity):
//    _capacity(capacity),
//    _arry(new T[_capacity]),
//    _length(0),
//    _top(_arry)
//{
//}

template<typename T>
Stack<T>::~Stack()
{
    delete []_arry;
}

template<typename T>
const T& Stack<T>::getTop()const
{
	if(!isEmpty())
		return *(_top - 1);
	else
		return *_top;
}

template<typename T>
void Stack<T>::push(const T &e)
{
	if(_length < _capacity)
	{
		*_top = e;
		++_top;
	}
	else
	{
		T *tmp(new T[2*_capacity]);
		T *const head(tmp);
		T *old(_arry);
		for(int i = 0; i < _length; ++i)
		{
			*tmp = *old;
			++tmp;
			++old;
		}
		_capacity *= 2;
		delete []_arry;
		_arry = head;
		*tmp = e;
		_top = ++tmp;
	}
	++_length;
}

template<typename T>
void Stack<T>::clearStack()
{
    _length = 0;
    _top = _arry;
}

template<typename T>
T Stack<T>::pop()
{
    --_length;
    return *(--_top);
}

template<typename T>
bool Stack<T>::isEmpty()const
{
    return _length == 0;
}

template<typename T>
size_t Stack<T>::getSize()const
{
    return _length;
}

template<typename T>
size_t Stack<T>::getCapacity()const
{
    return _capacity;
}

#endif // _STACK_H_INCLUDED
