#ifndef _STRING_H_INCLUDED
#define _STRING_H_INCLUDED

using std::ostream;
using std::istream;

class _String
{
    public:
        _String();
        _String(const _String& s);
        _String(const char *pc, size_t len);
        _String(const char *pc);

        _String& operator=(const _String &s);
        _String& operator=(const char *s);
        ~_String();

        char& operator[](const size_t index);
        bool operator ==(const _String &s);
        bool operator !=(const _String &s);
        bool operator <(const _String &s);
        bool operator >(const _String &s);
        bool operator <=(const _String &s);
        bool operator >=(const _String &s);
        _String& operator+=(const _String &rhs);
        _String& operator+=(const char *rhs);
        void clear();
        size_t GetLength()const {return nlength;}
        size_t GetCapacity()const {return ncapacity;}
        char* GetPtr()const {return pChar;}

    private:
        bool resize(int newsize);
        bool initString();
        bool assign(const char *data, int data_size);
        bool addAssign(const char *data, int data_size);
        size_t ncapacity;
        size_t nlength;
        char *pChar;
};

_String operator+(const _String &lhs, const _String &rhs);
ostream& operator <<(ostream &os, const _String &s);
istream& operator >>(istream &in, _String &s);

#endif // _STRING_H_INCLUDED
