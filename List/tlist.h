#ifndef _SINGLELIST_H_INCLUDED
#define _SINGLELIST_H_INCLUDED

namespace nsList
{

template<typename T>
class SingleNote
{
	public:
    	SingleNote(const T &tmp):Obj(tmp),pNext(NULL){}
    	SingleNote():pNext(NULL){}
    	T Obj;
    	SingleNote *pNext;
};

template<typename T>
class _SingleList
{
    public:
    	class Iterator
		{
			public:
				Iterator(SingleNote<T> *pT = NULL):pNote(pT){}
				Iterator& operator++();//前加
				Iterator operator++(int);//后加
				inline bool operator==(SingleNote<T> *pT);
				inline bool operator==(const Iterator &it);
				inline bool operator!=(SingleNote<T> *pT);
				inline bool operator!=(const Iterator &it);
				T* operator->()const
				{
				    return &(pNote->Obj);
				}
				T& operator*()const
				{
				    return pNote->Obj;
				}
			private:
				SingleNote<T> *pNote;
		};

		_SingleList():pHead(NULL),pLast(NULL),length(0){}
        ~_SingleList();

        SingleNote<T>* begin(){return pHead;}
        SingleNote<T>* end()
        {
            if(pLast == NULL)
                return NULL;
            return pLast->pNext;
        }
        bool IsEmpty(){return !length;}
        size_t Size(){return length;}
        void Clear();
        T& Find(const T &obj);
        T& IndexOf(size_t index);
        void Insert(const T& obj, int index = -1);
        void Remove(const T& obj);
        void Remove(int begin, int end);
        void Sort(int key = 0);
        void DelRepeat();
        void Inverse();

	private:
		void __Destory(size_t begin, size_t end);
		void __SortUp();
		void __SortDown();

        SingleNote<T> *pHead;
        SingleNote<T> *pLast;
        size_t length;
};

template<typename T>
void _SingleList<T>::__Destory(size_t begin, size_t end)
{
    if(pHead == NULL)
    	return;

	SingleNote<T> *ptmpNext(pHead->pNext);
    SingleNote<T> *ptmpFront(pHead);
    SingleNote<T> *pBegin(NULL);   //删除的第一个节点的前驱,当begin>1时，才有效

    if(begin != 0)
    {
        for(size_t i = 0; i < begin-1 ; ++i)  //找到要删除的第一个节点的前驱
        {
            ptmpFront = ptmpNext;
            ptmpNext = ptmpNext->pNext;
        }
        pBegin = ptmpFront;
        ptmpFront = ptmpNext;
        ptmpNext = ptmpNext->pNext;
    }
    delete ptmpFront;

    for(size_t i = begin; i < end-1; ++i)   //开始删除
    {
        ptmpFront = ptmpNext;
        ptmpNext = ptmpNext->pNext;
        delete ptmpFront;
    }

    if(begin != 0)
        pBegin->pNext = ptmpNext;
    if(begin == 0)  //判断头结点是否被删除
    {
        pHead = ptmpNext;
        if(pHead == NULL)
            pLast = NULL;
    }
    else if(end == length)   //判断尾结点是否被删除
    {
        pBegin->pNext = NULL;
        pLast = pBegin;
    }
    length -= end - begin;
}

template<typename T>
_SingleList<T>::~_SingleList()
{
    __Destory(0,length);
}

template<typename T>
void _SingleList<T>::Clear()
{
    __Destory(0,length);
}

template<typename T>
T& _SingleList<T>::Find(const T &obj)
{
	SingleNote<T> *ptmp(pHead);
    for(size_t i = 0; i<length; ++i)
    {
        if(ptmp->Obj == obj)
            return ptmp->Obj;
        ptmp = ptmp->pNext;
    }
    return pHead->Obj;
}

template<typename T>
T& _SingleList<T>::IndexOf(size_t index)
{
	if(length <= index)
        index = length - 1;

    SingleNote<T> *ptmp(pHead);
    for(size_t i = 0; i < index; ++i)
    {
        ptmp = ptmp->pNext;
    }
    return ptmp->Obj;
}

template<typename T>
void _SingleList<T>::Insert(const T &obj,int index)
{
	SingleNote<T> *pObj(new SingleNote<T>(obj));

	if(pHead != NULL)
	{	//判断链表是否为空
		SingleNote<T> *ptmp1(pHead);
		SingleNote<T> *ptmp2(NULL);

		switch(index)
		{
			case -1:	//添加在尾结点
				pLast->pNext = pObj;
				pLast = pObj;
				break;
			case 0:		//添加在头结点
				pObj->pNext = pHead;
				pHead = pObj;
				break;
			default:	//添加在中间结点，加在index的前面，从0开始
				if(index >= length)	//若下标出界，则默认为加在最后
				{
					pLast->pNext = pObj;
                    pLast = pObj;
                    break;
				}
				for(int i = 0; i<index-1; ++i)
				{
					ptmp1 = ptmp1->pNext;	//找到index前一个结点
				}
				ptmp2 = ptmp1->pNext;		//找到index对应结点
				ptmp1->pNext = pObj;
				pObj->pNext = ptmp2;
				break;
		}
	}
	else
	{
		pHead = pObj;
		pLast = pObj;
	}
	++length;
}

template<typename T>
void _SingleList<T>::Remove(int begin, int end) //删除第begin至end-1个元素,从0开始
{
	if(pHead == NULL)	//若链表是一个空表，则返回
    	return;

    if(begin > end)
    {
        int tmp = begin;
        begin = end;
        end = tmp;
    }
    if(end < 1 ||begin == end || (begin >length-1 && begin>0))
        return;     //不合法的输入，则返回，注意无符号数与有符号数的比较
    if(begin < 0)
        begin = 0;
    if(end > length)
        end = length;

    __Destory(begin,end);
}
template<typename T>
void _SingleList<T>::Remove(const T& obj)
{
	if(pHead == NULL)
        return;
	SingleNote<T> *pObj(pHead);

	if(pObj->Obj == obj)	//若删除的结点是头结点
	{
		pHead = pObj->pNext;
		delete pObj;
        --length;
        if(length == 0)
            pLast = NULL;
		return;
	}
	else if(pLast->Obj == obj)  //若删除的结点是尾结点
    {
        for(size_t i = 0; i<length-2;++i )
        {
            pObj = pObj->pNext;
        }
        delete pLast;
        pLast = pObj;
        pLast->pNext = NULL;
        --length;
        return;
    }
	//若删除的结点不是头尾结点
	SingleNote<T> *ptmp1(pHead);
	SingleNote<T> *ptmp2(NULL);
	pObj = pObj->pNext;

	for(size_t i=1; i < length-1; ++i)
	{
		if(pObj->Obj == obj)
		{
			ptmp2 = pObj->pNext;
			delete pObj;
			ptmp1->pNext = ptmp2;
			--length;
		}
		ptmp1 = pObj;
		pObj = pObj->pNext;
	}
}

template<typename T>
void _SingleList<T>::Sort(int key)	//默认key==0,从小到大排序，若key！=0,从大到小排序
{
	if(!key)
	{
        __SortUp();
	}
	else
    {
        __SortDown();
    }


}
template<typename T>
void _SingleList<T>::__SortUp()
{
    if(pHead == NULL || pHead->pNext == NULL)   //若链表只有1个结点或链表为空，则无需排序
        return;

    //先处理头结点
    SingleNote<T> *pM(pHead);       //指向最小或最大结点
	SingleNote<T> *pMf(pHead);		//最大或最小的结点的前驱结点
	SingleNote<T> *ptmp(pHead);
    for(size_t i=0; i<length-1; ++i)
    {
        if(pMf->Obj > ptmp->pNext->Obj)
        {
            pMf = ptmp;
        }
        ptmp = ptmp->pNext;
    }
    if(pMf != pHead)
    {
        pM = pMf->pNext;
        pMf->pNext = pM->pNext;
        pM->pNext = pHead;
        pHead = pM;
    }
    //处理后续结点
    SingleNote<T> *pMn; //指向pM的后驱
    for(size_t i=1; i<length-1; ++i)
    {
        pMf = pM;
        ptmp = pM->pNext;
        bool flag(false);
        for(size_t j=1; j<length-i; ++j)
        {
            if(pMf->pNext->Obj > ptmp->pNext->Obj)
            {
                 pMf = ptmp;
                 flag = true;
            }

            ptmp = ptmp->pNext;
        }
        if(flag)
        {
            pMn = pM->pNext;
            pM->pNext = pMf->pNext;
            pM = pMf->pNext;
            pMf->pNext = pM->pNext;
            pM->pNext = pMn;
        }
        else
        {
            pM = pM->pNext;
        }
    }

    pLast = pM->pNext;
}
template<typename T>
void _SingleList<T>::__SortDown()
{
    if(pHead == NULL || pHead->pNext == NULL)   //若链表只有1个结点或链表为空，则无需排序
        return;

    //先处理头结点
    SingleNote<T> *pM(pHead);       //指向最小或最大结点
	SingleNote<T> *pMf(pHead);		//最大或最小的结点的前驱结点
	SingleNote<T> *ptmp(pHead);
    for(size_t i=0; i<length-1; ++i)
    {
        if(pMf->Obj < ptmp->pNext->Obj)
        {
            pMf = ptmp;
        }
        ptmp = ptmp->pNext;
    }
    if(pMf != pHead)
    {
        pM = pMf->pNext;
        pMf->pNext = pM->pNext;
        pM->pNext = pHead;
        pHead = pM;
    }
    //处理后续结点
    SingleNote<T> *pMn; //指向pM的后驱
    for(size_t i=1; i<length-1; ++i)
    {
        pMf = pM;
        ptmp = pM->pNext;
        bool flag(false);
        for(size_t j=1; j<length-i; ++j)
        {
            if(pMf->pNext->Obj < ptmp->pNext->Obj)
            {
                 pMf = ptmp;
                 flag = true;
            }

            ptmp = ptmp->pNext;
        }
        if(flag)
        {
            pMn = pM->pNext;
            pM->pNext = pMf->pNext;
            pM = pMf->pNext;
            pMf->pNext = pM->pNext;
            pM->pNext = pMn;
        }
        else
        {
            pM = pM->pNext;
        }
    }

    pLast = pM->pNext;
}

template<typename T>
void _SingleList<T>::DelRepeat()
{
    if(length == 0 || length == 1)
        return;

    SingleNote<T> *ptmp(pHead);
    SingleNote<T> *pObj(pHead);
    SingleNote<T> *pDel(NULL);

    for(;pObj->pNext != NULL; pObj = pObj->pNext)
    {
        ptmp = pObj;
        while(ptmp->pNext != NULL)
        {
            if(ptmp->pNext->Obj == pObj->Obj)
            {
                pDel = ptmp->pNext;
                ptmp->pNext = pDel->pNext;
                delete pDel;
                --length;
            }
            else
            {
                ptmp = ptmp->pNext;
            }
        }
    }
    pLast = pObj;
}

template<typename T>
void _SingleList<T>::Inverse()
{
    if(length < 2)  //若只有一个节点或链表为空，则返回
        return;

    SingleNote<T> *ptmp1(pHead);
    SingleNote<T> *ptmp2(ptmp1->pNext);
    SingleNote<T> *ptmp3(ptmp2->pNext);

    //设置头尾结点，并实现第一次交换指向
    pHead->pNext = NULL;
    pHead = pLast;
    pLast = ptmp1;
    ptmp2->pNext = ptmp1;

    while(ptmp3)
    {
        ptmp1 = ptmp2;
        ptmp2 = ptmp3;
        ptmp3 = ptmp3->pNext;
        ptmp2->pNext = ptmp1;
    }
}

template<typename T>
typename _SingleList<T>::Iterator& _SingleList<T>::Iterator::operator++()//前加
{
    pNote = pNote->pNext;
    return *this;
}
template<typename T>
typename _SingleList<T>::Iterator _SingleList<T>::Iterator::operator++(int)//后加
{
	Iterator tmp(*this);
    pNote = pNote->pNext;
    return tmp;
}
template<typename T>
bool _SingleList<T>::Iterator::operator==(SingleNote<T> *pT)
{
	bool flag(pNote == pT);
	return flag;
}
template<typename T>
bool _SingleList<T>::Iterator::operator==(const Iterator &it)
{
	bool flag(it.pNote == pNote);
	return flag;
}
template<typename T>
bool _SingleList<T>::Iterator::operator!=(SingleNote<T> *pT)
{
	return (!(*this == pT));
}
template<typename T>
bool _SingleList<T>::Iterator::operator!=(const Iterator &it)
{
	return (!(*this==it));
}

}
using nsList::_SingleList;
#endif // _SINGLELIST_H_INCLUDED
