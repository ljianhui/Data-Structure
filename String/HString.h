#ifndef HSTRING_H_INCLUDED
#define HSTRING_H_INCLUDED

#include "DataStruct.h"

void InitStr(HString *pS);
//对HString的各个成员变量赋初值
//pTxt = NULL， nCapacity = 0， nLength = 0

BOOL StrAssign(HString *pS,const char *pc);
//由pc给定的字符数组赋值给pS的pTxt，生成一个内容与pc相同的串
//成功则返回1，不成功则返回0

int StrEmpty(const HString *pS);
//若*pS为空串，则返回1，否则返回0

int StrCompare(const HString *pS1, const HString *pS2);
//比较串*pS1和串*pS2，若S>T，则返回值>0，若S=T，则返回值=0，若S<T，则返回值<0

int StrLength(const HString *pS);
//返回串*pS中字符的个数，不包括空字符，空串返回0

void StrDestory(HString *pS);
//把pTxt所指向的内存释放，并把nCapacity = 0， nLength = 0

BOOL StrConcat(HString *pSObj, const HString *pSFront, const HString *pSLast);
//用*pSObj返回由串*pSFront和串*pSLast连接而成的新串
//成功则返回1，不成功则返回0；

BOOL SubString(HString *pSub, const HString *pSource, int pos, int len);
//用*pSub返回串*pSource的第pos个字符起长度为len的子串
//成功返回1，不成功则返回0

int IndexOfC(const char *pS, const char *pT, int pos);
//返回字符数组pS中第pos个字符之后第一次出现pT的位置。

int IndexOf(const HString *pS, const HString *pT);
//返回主串*pS中串*pT第一次出现的位置

BOOL StrReplace(HString *pS, const HString *pT, const HString *pV);
//用pV替换主串pS中出现的所有与pT相等的不重叠的子串
//成功返回1，不成功则返回0

void StrPrint(HString *pS);
//打印串pS


#endif // HSTRING_H_INCLUDED
