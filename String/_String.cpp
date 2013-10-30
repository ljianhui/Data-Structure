#include <ostream>
#include <istream>
#include <cstring>
#include "_String.h"

_String::_String()
{
    initString();
    //cout<<"_String()"<<endl;
}

_String::_String(const char *pc, size_t len)
{
    nlength = len;
    ncapacity = 2*len;

    pChar = new char[ncapacity+1];
    strncpy(pChar, pc, len);
    //cout<<"_String(const char *pc, size_t len)"<<endl;
}

_String::_String(const char *pc)
{
    nlength = strlen(pc);
    ncapacity = 2*nlength;
    pChar = new char[ncapacity + 1];
    strcpy(pChar,pc);
    //cout<<"_String(const char *pc)"<<endl;
}

_String::_String(const _String &s)
{
    ncapacity = s.GetCapacity();
    nlength = s.GetLength();
    const char *ptmp = s.GetPtr();

    pChar = new char[ncapacity + 1];
    strcpy(pChar,ptmp);
    //cout<<"_String(const _String &s)"<<endl;
}

_String& _String::operator=(const _String &s)
{
    nlength = s.GetLength();
    if(ncapacity < nlength)
    {
        delete []pChar;
        ncapacity = nlength * 2;

        pChar = new char[ncapacity + 1];
    }
    strcpy(pChar,s.GetPtr());
    //cout<<"_String::operator=(const _String &s)"<<endl;
    return *this;
}

_String& _String::operator=(const char *s)
{
    nlength = strlen(s);
    if(ncapacity < nlength)
    {
        delete []pChar;
        ncapacity = nlength * 2;

        pChar = new char[ncapacity + 1];
    }
    strcpy(pChar, s);
    return *this;
}

_String::~_String()
{
    delete []pChar;
    pChar = NULL;
}
bool _String::initString()
{
    //用于构造一个默认的字符串
    int n = 10;
    nlength = 0;
    pChar = new char[n+1];
    if(pChar == NULL)
    {
        ncapacity = 0;
        return false;
    }
    else
    {
        ncapacity = n;
        pChar[0] = '\0';
        return true;
    }
}
bool _String::resize()
{
    //重新分配字符数组，
    //从表面上看就好像是pChar指向的数组自动在其后增加了一段空间一样
    int newsize = ncapacity * 2;
    char *ptmp = new char[newsize + 1];
    if(ptmp == NULL)
        return false;

    ncapacity = newsize;
    strcpy(ptmp, pChar);
    delete []pChar;
    pChar = ptmp;
    return true;
}

void _String::clear()
{
    //清空字符串，考虑到new操作的开销，
    //如果内存占有太多，则回收其字符串内存，重新分配
    //如果字符数组不是太大，则保留内存,设置字符串为空串
    const int ADRISE_SIZE = 128;
    if(ncapacity > ADRISE_SIZE)
    {
        delete []pChar;
        initString();
    }
    else
        pChar[0] = '\0';
}
char& _String::operator[](size_t index)
{
    if(index > nlength)
        index = nlength;
    else if(index < 0)
    	index = 0;
    return *(pChar + index);
}

bool _String::operator ==(const _String &s)
{
    if(strcmp(pChar,s.GetPtr())== 0)
        return true;
    else
        return false;
}

bool _String::operator !=(const _String &s)
{
    return !(operator ==(s));
}

bool _String::operator <(const _String &s)
{
    if(strcmp(pChar,s.GetPtr()) < 0)
        return true;
    else
        return false;
}

bool _String::operator >(const _String &s)
{
    if(strcmp(pChar,s.GetPtr()) > 0)
        return true;
    else
        return false;
}
_String& _String::operator +=(const _String &s)
{
    return operator+=(s.GetPtr());
}

_String& _String::operator+=(const char *rhs)
{
    nlength += strlen(rhs);
    if(ncapacity < nlength)
    {
        //因为resize采用乘2的策略扩充内存，但是，不能保证
        //ncapacity * 2 > nlength,
        //所以在分配内存前，先设置ncapacity的值
        ncapacity = nlength;
        resize();
    }
    strcat(pChar, rhs);
    return *this;
}

bool _String::operator <=(const _String &s)
{
	if(*this < s||*this == s)
		return true;
	else
		return false;
}

bool _String::operator >=(const _String &s)
{
	if(*this > s||*this == s)
		return true;
	else
		return false;
}

ostream& operator << (ostream &os, const _String &s)
{
	os<<s.GetPtr();
	return os;
}


istream& operator >> (istream &in, _String &s)
{
	const int BUFFER_SIZE = 256;
	char buffer[BUFFER_SIZE];
	s.clear();

	do
	{
        //用于判断是否读完输入内容，因为如果还未读取的输入字符数大于buffer
        //的容量，则buffer的最后一个字符会被get函数置为'\0'
        buffer[BUFFER_SIZE - 1] = '#';
		in.get(buffer, BUFFER_SIZE);
        s += buffer;
	}while(buffer[BUFFER_SIZE - 1] == '\0');
	in.get();

	return in;
}

_String operator +(const _String &lhs, const _String &rhs)
{
    _String stemp(lhs);
    stemp += rhs;
    return stemp;
}





















