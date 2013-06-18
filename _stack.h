#ifndef _STACK_H_INCLUDED
#define _STACK_H_INCLUDED
//#include <iostream>

template<typename T>
class _stack
{
	public:
		_stack(size_t _capacity = 1):capacity(_capacity),pArry(new T[_capacity]),length(0),pTop(pArry){}
		~_stack(){delete []pArry;}
		void ClearStack()
		{
            length = 0;
            pTop = pArry;
        }

		bool IsEmpty()const {return length == 0;}
		size_t GetSize()const {return length;}
		void Push(T& e);
		T Pop()
		{
		    --length;
            return *(--pTop);
		}
		T& GetTop()const;
		void vist()const;
	private:
		size_t capacity;
		T *pArry;
		size_t length;
		T *pTop;
};

template<typename T>
T& _stack<T>::GetTop()const
{
	if(!IsEmpty())
		return *(pTop - 1);
	else
		return *pTop;
}

template<typename T>
void _stack<T>::Push(T &e)
{
	++length;
	if(length < capacity)
	{
		*pTop = e;
		++pTop;
	}
	else
	{
		T *ptmp(new T[2*capacity]);
		T *const phead(ptmp);
		T *pT(pArry);
		for(int i = 0; i < length; ++i)
		{
			*ptmp = *pT;
			++ptmp;
			++pT;
		}
		capacity *= 2;
		delete []pArry;
		*(++ptmp) = e;
		pTop = ++ptmp;
		pArry = phead;
	}
}
template<typename T>
void _stack<T>::vist()const
{
	T *ptmp(pTop);
	while(ptmp != pArry)
	{
		std::cout<<*(--ptmp)<<" ";
	}
}

#endif // _STACK_H_INCLUDED
