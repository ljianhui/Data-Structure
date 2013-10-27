#include <stdlib.h>
#include <stdio.h>
#include "HString.h"

/*****************************************************************/
BOOL ReNew(HString *pS, int nStrLen)
{
    char *ptmp = NULL;
    int i = 0;
    if(!(ptmp = (char*)malloc((nStrLen+1)*sizeof(char))))
    {
        return 0;
    }
    for(i = 0; i < pS->nLength; ++i)
    {
        ptmp[i] = pS->pTxt[i];
    }
    ptmp[i] = '\0';
    free(pS->pTxt);
    pS->pTxt = ptmp;
    pS->nCapacity = nStrLen;
    return 1;
}
/*****************************************************************/
void InitStr(HString *pS)
{
    pS->pTxt = NULL;
    pS->nLength = 0;
    pS->nCapacity = 0;
}
/*****************************************************************/
BOOL StrAssign(HString *pS, const char *pc)
{
    int n = 0, i = 0;
    char *ptmp = pc;
    for(n = 0; *ptmp != '\0'; ++ptmp,++n);

    if(pS->nCapacity < n || !(pS->pTxt))
    {
        if(!ReNew(pS, n))
        {
            printf("Out Of Menory\n");
            return 0;
        }
    }
    for(i = 0; i < n; ++i)
    {
        pS->pTxt[i] = pc[i];
    }
    pS->pTxt[i] = '\0';
    pS->nLength = n;

    return 1;
}
/*****************************************************************/
int StrEmpty(const HString *pS)
{
    if(!pS)
        return 0;
    return pS->nLength;
}
/*****************************************************************/
int StrCompare(const HString *pS1, const HString *pS2)
{
    if(!pS1 || !pS2)
        return 0;
    int i = 0;
    for(; i < pS1->nLength && i < pS2->nLength; ++i)
    {
        if(pS1->pTxt[i] != pS2->pTxt[i])
            return pS1->pTxt[i] - pS2->pTxt[i];
    }
    return pS1->nLength - pS2->nLength;
}
/*****************************************************************/
int StrLength(const HString *pS)
{
    if(!pS)
        return -1;
    return pS->nLength;
}
/*****************************************************************/
BOOL StrConcat(HString *pSObj, const HString *pSFront, const HString *pSLast)
{
    if(!pSObj || !pSFront || !pSLast)
        return 0;
    char *pobj = NULL;
    char *psrc = NULL;
    int i = 0;
    if(pSObj->nCapacity < (pSFront->nLength+pSLast->nLength))
    {
        if(!ReNew(pSObj, pSFront->nLength+pSLast->nLength))
        {
            printf("Out Of Menory!\n");
            return 0;
        }
    }

    for(i = 0, pobj = pSObj->pTxt, psrc = pSFront->pTxt;
        i < pSFront->nLength; ++i, ++pobj, ++psrc)
    {
        *pobj = *psrc;
    }
    for(i = 0, psrc = pSLast->pTxt; i < pSLast->nLength;
        ++i,++pobj, ++psrc)
    {
        *pobj = *psrc;
    }
    *pobj = '\0';
    pSObj->nLength = pSFront->nLength + pSLast->nLength;
    return 1;
}
/*****************************************************************/
BOOL SubString(HString *pSub, const HString *pSource, int pos, int len)
{
    if(!pSub || !pSource)
        return 0;
    int i = 0;
    char *ptmp = pSource->pTxt+pos;

    if(pos < 0 || pos > pSource->nLength-1 ||
       len < 0 || len > pSource->nLength - pos)
    {
        return 0;
    }
    if(pSub->nLength < len)
    {
        if(!ReNew(pSub, len))
        {
            printf("Out Of Menory!\n");
            return 0;
        }
    }
    for(i = 0; i < len; ++i, ++ptmp)
    {
        pSub->pTxt[i] = *ptmp;
    }
    pSub->pTxt[i] = '\0';
    pSub->nLength = len;
    return 1;
}
/*****************************************************************/
int IndexOfC(const char *pS, const char *pT, int pos)
{
    if(!pS || !pT || pT[0] == '\0')
        return -1;
    int iS = 0;
    int iT = 0;
    int flag = 0;
    for(iS = pos; pS[iS] != '\0'; ++iS)
    {
        flag = 1;
        for(iT = 0; pT[iT] != '\0'; ++iT)
        {
			if(pS[iS+iT] == '\0' || pT[iT] != pS[iS+iT])
            {
                flag = 0;
                break;
            }
        }
        if(flag)
            return iS;
    }
    return -1;
}
/*****************************************************************/
int IndexOf(const HString *pS, const HString *pT)
{
    if(!pS || !pT)
        return -1;
    return IndexOfC(pS->pTxt, pT->pTxt, 0);
}
/*****************************************************************/
BOOL StrReplace(HString *pS, const HString *pT, const HString *pV)
{
    if(!pS || !pT || !pV)
        return 0;
    if(!pS->nLength || !pT->nLength)
        return 0;

    int nT = pT->nLength;
    int nV = pV->nLength;
    int iS = 0, iV = 0, i = 0, pos = 0;
    int d = 0;

    while((iS = IndexOfC(pS->pTxt, pT->pTxt, pos)) != -1)
    {
        if(nT < nV)
        {
            d = nV - nT;
            while((pS->nCapacity - pS->nLength) < d)
                if(!ReNew(pS, pS->nCapacity*2))
                    return 0;

            for(i = pS->nLength; i >= iS+nT; --i)
            {
                pS->pTxt[i+d] = pS->pTxt[i];
            }
            for(i = iS,iV = 0; iV < nV; ++iV, ++i)
            {
                pS->pTxt[i] = pV->pTxt[iV];
            }
            pS->nLength += d;
        }
        else if(nT > nV)
        {
            d = nT - nV;
            for(i = iS+nV; i <= pS->nLength; ++i)
            {
                pS->pTxt[i] = pS->pTxt[i+d];
            }
            for(i = iS,iV = 0; iV < nV; ++iV, ++i)
            {
                pS->pTxt[i] = pV->pTxt[iV];
            }
            pS->nLength -= d;
        }
        else
        {
            for(i = iS,iV = 0; iV < nV; ++iV, ++i)
            {
                pS->pTxt[i] = pV->pTxt[iV];
            }
        }
        pos = iS + nV;
    }

    return 1;
}
/*****************************************************************/
void StrDestory(HString *pS)
{
    if(!pS)
        return;
    free(pS->pTxt);
    pS->pTxt = NULL;
    pS->nLength = 0;
    pS->nCapacity = 0;
}
/*****************************************************************/
void StrPrint(HString *pS)
{
    if(!pS)
    {
        printf("''\n");
    }
    else
    {
        printf("'%s'\n", pS->pTxt);
    }
}
