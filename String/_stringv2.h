#ifndef _STRINGV2_H_INCLUDED
#define _STRINGV2_H_INCLUDED

/***
String类的部分实现，采用的内存管理策略是：隐式共享，写时复制
实现方法：与智能指针的实现类似
***/
class String
{
    public:
        String();
        String(const String& s);
        String(const char *pc, size_t len);
        String(const char *pc);
        ~String();

        String& operator=(const String &s);
        String& operator=(const char *s);

        String& operator+=(const String &rhs);
        String& operator+=(const char *rhs);

        void clear();
        size_t getLength()const {return _length;}
        const char* cstr()const {return _cstr;}

    private://function
        void _initString(const char *cstr, size_t len);
        void _decUsed();
        char* _renewAndCat(const char *cstr, size_t len);
        void _addString(const char *cstr, size_t len);
        void _addAssignOpt(const char *cstr, size_t len);

    private://data
        char *_cstr;
        size_t *_used;
        size_t _length;
        size_t _capacity;
};

String operator+(const String &lhs, const String &rhs);
std::ostream& operator <<(std::ostream &os, const String &s);
std::istream& operator >>(std::istream &in, String &s);

#endif // _STRINGV2_H_INCLUDED
