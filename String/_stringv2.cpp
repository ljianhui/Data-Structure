#include <ostream>
#include <istream>
#include <string.h>
#include "_stringv2.h"

using std::ostream;
using std::istream;

String::String():
    _cstr(NULL),
    _used(new size_t(1)),
    _length(0),
    _capacity(0)
{
}

String::String(const String &s):
    _cstr(s._cstr),
    _used(s._used),
    _length(s._length),
    _capacity(s._capacity)
{
    ++*_used;
}

String::String(const char *cstr)
{
    size_t len = strlen(cstr);
    _initString(cstr, len);
}

String::String(const char *cstr, size_t len)
{
    size_t str_len = strlen(cstr);
    if(len <= str_len)
    {
        _initString(cstr, len);
    }
}

String::~String()
{
    _decUsed();
}

String& String::operator=(const String &s)
{
    ++*(s._used);
    _decUsed();
    _cstr = s._cstr;
    _length = s._length;
    _capacity = s._capacity;
    return *this;
}

String& String::operator=(const char *cstr)
{
    if(cstr != NULL)
    {
        _decUsed();
        size_t len = strlen(cstr);
        _initString(cstr, len);
    }
    return *this;
}

String& String::operator+=(const String &s)
{
    _addAssignOpt(s._cstr, s._length);
    return *this;
}

String& String::operator+=(const char *cstr)
{
    if(cstr != NULL)
        _addAssignOpt(cstr, strlen(cstr));
    return *this;
}

void String::clear()
{
    _decUsed();
    _cstr = NULL;
    _used = new size_t(1);
    _length = 0;
    _capacity = 0;
}

void String::_initString(const char *cstr, size_t len)
{
    if(cstr == NULL)
        return;

    _cstr = new char[len + 1];
    memcpy(_cstr, cstr, len);
    _cstr[len] = 0;
    _used = new size_t(1);
    _length = len;
    _capacity = len;
}

void String::_decUsed()
{
    --*_used;
    if(_used == 0)
    {
        if(_cstr != NULL)
        {
            delete[] _cstr;
            _cstr = NULL;
            _length = 0;
            _capacity = 0;
        }
        delete _used;
        _used = NULL;
    }
}

char* String::_renewAndCat(const char *cstr, size_t len)
{
    size_t new_len = len + _length;
    size_t capacity = new_len;
    capacity += (capacity >> 1);

    char *ptr = new char[capacity+1];
    if(_cstr != NULL)
        memcpy(ptr, _cstr, _length);
    ptr[_length] = 0;

    _length = new_len;
    _capacity = capacity;
    strncat(ptr, cstr, len);
    return ptr;
}

void String::_addString(const char *cstr, size_t len)
{
    //本函数，只有在引用计数为1时，才可用
    if(*_used != 1)
        return;

    if(len + _length > _capacity)
    {
        char *ptr = _renewAndCat(cstr, len);
        delete[] _cstr;
        _cstr = ptr;
    }
    else
    {
        strncat(_cstr, cstr, len);
        _length += len;
    }
}

void String::_addAssignOpt(const char *cstr, size_t len)
{
    if(*_used == 1)
        _addString(cstr, len);
    else
    {
        _decUsed();
        _cstr = _renewAndCat(cstr, len);
        _used = new size_t(1);
    }
}

String operator +(const String &lhs, const String &rhs)
{
    String stemp(lhs);
    stemp += rhs;
    return stemp;
}

ostream& operator << (ostream &os, const String &s)
{
	os<<s.cstr();
	return os;
}

istream& operator >> (istream &in, String &s)
{
	const int BUFFER_SIZE = 6;
	char buffer[BUFFER_SIZE];
	char *end = buffer + BUFFER_SIZE -1;
	s.clear();

	do
	{
        //用于判断是否读完输入内容，因为如果还未读取的输入字符数大于buffer
        //的容量，则buffer的最后一个字符会被get函数置为'\0'
        *end = '#';
		in.get(buffer, BUFFER_SIZE);
        s += buffer;
	}while(*end == '\0');
	in.get();

	return in;
}
