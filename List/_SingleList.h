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
				Iterator& operator++();//ǰ��
				Iterator operator++(int);//���
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
    SingleNote<T> *pBegin(NULL);   //ɾ���ĵ�һ���ڵ��ǰ��,��begin>1ʱ������Ч

    if(begin != 0)
    {
        for(size_t i = 0; i < begin-1 ; ++i)  //�ҵ�Ҫɾ���ĵ�һ���ڵ��ǰ��
        {
            ptmpFront = ptmpNext;
            ptmpNext = ptmpNext->pNext;
        }
        pBegin = ptmpFront;
        ptmpFront = ptmpNext;
        ptmpNext = ptmpNext->pNext;
    }
    delete ptmpFront;

    for(size_t i = begin; i < end-1; ++i)   //��ʼɾ��
    {
        ptmpFront = ptmpNext;
        ptmpNext = ptmpNext->pNext;
        delete ptmpFront;
    }

    if(begin != 0)
        pBegin->pNext = ptmpNext;
    if(begin == 0)  //�ж�ͷ����Ƿ�ɾ��
    {
        pHead = ptmpNext;
        if(pHead == NULL)
            pLast = NULL;
    }
    else if(end == length)   //�ж�β����Ƿ�ɾ��
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
	{	//�ж������Ƿ�Ϊ��
		SingleNote<T> *ptmp1(pHead);
		SingleNote<T> *ptmp2(NULL);

		switch(index)
		{
			case -1:	//�����β���
				pLast->pNext = pObj;
				pLast = pObj;
				break;
			case 0:		//�����ͷ���
				pObj->pNext = pHead;
				pHead = pObj;
				break;
			default:	//������м��㣬����index��ǰ�棬��0��ʼ
				if(index >= length)	//���±���磬��Ĭ��Ϊ�������
				{
					pLast->pNext = pObj;
                    pLast = pObj;
                    break;
				}
				for(int i = 0; i<index-1; ++i)
				{
					ptmp1 = ptmp1->pNext;	//�ҵ�indexǰһ�����
				}
				ptmp2 = ptmp1->pNext;		//�ҵ�index��Ӧ���
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
void _SingleList<T>::Remove(int begin, int end) //ɾ����begin��end-1��Ԫ��,��0��ʼ
{
	if(pHead == NULL)	//��������һ���ձ��򷵻�
    	return;

    if(begin > end)
    {
        int tmp = begin;
        begin = end;
        end = tmp;
    }
    if(end < 1 ||begin == end || (begin >length-1 && begin>0))
        return;     //���Ϸ������룬�򷵻أ�ע���޷��������з������ıȽ�
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

	if(pObj->Obj == obj)	//��ɾ���Ľ����ͷ���
	{
		pHead = pObj->pNext;
		delete pObj;
        --length;
        if(length == 0)
            pLast = NULL;
		return;
	}
	else if(pLast->Obj == obj)  //��ɾ���Ľ����β���
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
	//��ɾ���Ľ�㲻��ͷβ���
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
void _SingleList<T>::Sort(int key)	//Ĭ��key==0,��С����������key��=0,�Ӵ�С����
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
    if(pHead == NULL || pHead->pNext == NULL)   //������ֻ��1����������Ϊ�գ�����������
        return;

    //�ȴ���ͷ���
    SingleNote<T> *pM(pHead);       //ָ����С�������
	SingleNote<T> *pMf(pHead);		//������С�Ľ���ǰ�����
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
    //����������
    SingleNote<T> *pMn; //ָ��pM�ĺ���
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
    if(pHead == NULL || pHead->pNext == NULL)   //������ֻ��1����������Ϊ�գ�����������
        return;

    //�ȴ���ͷ���
    SingleNote<T> *pM(pHead);       //ָ����С�������
	SingleNote<T> *pMf(pHead);		//������С�Ľ���ǰ�����
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
    //����������
    SingleNote<T> *pMn; //ָ��pM�ĺ���
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
    if(length < 2)  //��ֻ��һ���ڵ������Ϊ�գ��򷵻�
        return;

    SingleNote<T> *ptmp1(pHead);
    SingleNote<T> *ptmp2(ptmp1->pNext);
    SingleNote<T> *ptmp3(ptmp2->pNext);

    //����ͷβ��㣬��ʵ�ֵ�һ�ν���ָ��
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
typename _SingleList<T>::Iterator& _SingleList<T>::Iterator::operator++()//ǰ��
{
    pNote = pNote->pNext;
    return *this;
}
template<typename T>
typename _SingleList<T>::Iterator _SingleList<T>::Iterator::operator++(int)//���
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
