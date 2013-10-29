#include <ostream>
#include <istream>
#include <cstring>
#include "_String.h"

_String::_String():
    ncapacity(10),
    nlength(0),
    pChar(new char[ncapacity+1])
{
    *pChar = '\0';
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

bool _String::resize()
{
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
    nlength += s.GetLength();
    if(ncapacity < nlength)
    {
        ncapacity = nlength;
        resize();
    }
    strcat(pChar,s.GetPtr());
}

_String& _String::operator+=(const char *rhs)
{
    nlength += strlen(rhs);
    if(ncapacity < nlength)
    {
        ncapacity = nlength;
        resize();
    }
    strcat(pChar, rhs);
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
	char buffer[256];
	do
	{
        in.get(buffer, 256);
        s += buffer;
	}while(in);
	return in;
}

_String operator +(const _String &lhs, const _String &rhs)
{
    _String stemp(lhs);
    stemp += rhs;
    return stemp;
}






















