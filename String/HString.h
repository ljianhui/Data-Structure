#ifndef HSTRING_H_INCLUDED
#define HSTRING_H_INCLUDED

#include "DataStruct.h"

void InitStr(HString *pS);
//��HString�ĸ�����Ա��������ֵ
//pTxt = NULL�� nCapacity = 0�� nLength = 0

BOOL StrAssign(HString *pS,const char *pc);
//��pc�������ַ����鸳ֵ��pS��pTxt������һ��������pc��ͬ�Ĵ�
//�ɹ��򷵻�1�����ɹ��򷵻�0

int StrEmpty(const HString *pS);
//��*pSΪ�մ����򷵻�1�����򷵻�0

int StrCompare(const HString *pS1, const HString *pS2);
//�Ƚϴ�*pS1�ʹ�*pS2����S>T���򷵻�ֵ>0����S=T���򷵻�ֵ=0����S<T���򷵻�ֵ<0

int StrLength(const HString *pS);
//���ش�*pS���ַ��ĸ��������������ַ����մ�����0

void StrDestory(HString *pS);
//��pTxt��ָ����ڴ��ͷţ�����nCapacity = 0�� nLength = 0

BOOL StrConcat(HString *pSObj, const HString *pSFront, const HString *pSLast);
//��*pSObj�����ɴ�*pSFront�ʹ�*pSLast���Ӷ��ɵ��´�
//�ɹ��򷵻�1�����ɹ��򷵻�0��

BOOL SubString(HString *pSub, const HString *pSource, int pos, int len);
//��*pSub���ش�*pSource�ĵ�pos���ַ��𳤶�Ϊlen���Ӵ�
//�ɹ�����1�����ɹ��򷵻�0

int IndexOfC(const char *pS, const char *pT, int pos);
//�����ַ�����pS�е�pos���ַ�֮���һ�γ���pT��λ�á�

int IndexOf(const HString *pS, const HString *pT);
//��������*pS�д�*pT��һ�γ��ֵ�λ��

BOOL StrReplace(HString *pS, const HString *pT, const HString *pV);
//��pV�滻����pS�г��ֵ�������pT��ȵĲ��ص����Ӵ�
//�ɹ�����1�����ɹ��򷵻�0

void StrPrint(HString *pS);
//��ӡ��pS


#endif // HSTRING_H_INCLUDED
