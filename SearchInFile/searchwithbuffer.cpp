#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>

using namespace std;

/******
由于文件可能太大，采用一次把文件的所有内容读进内存不太可能，所以把文件
的内容分批次地读入缓冲区，然后查找出相对应的关键字首次出现所在的位置
******/
int IndexOf(const char *text, int textSize,
            const char *match, int matchSize,
            int &lastMatch);
//字符串匹配，text为文本，match为模式串，返回模式串第一次出现的位置
int IndexInFile(const char *fileName, const char *keyWord);
//找出文件fileName中关键字首次出现的位置
void WriteEndToBegin(char *text, int textSize, int writeCount);
//把字符数组中最后writeCount个字符写到最前面

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        //输入的参数个数不正确，则退出程序
        cerr<<"The count of parameters is ERROR!"<<endl;
        exit(EXIT_FAILURE);
    }
    int index = IndexInFile(argv[1], argv[2]);
    cout<<"The keyword: "<<argv[2]<<" , is in the location: "
        <<index<<endl;
    exit(EXIT_SUCCESS);
}
int IndexInFile(const char *fileName, const char *keyWord)
{
    //以只读方式，打开文件fileName
    ifstream inputFile(fileName);
    if(!inputFile)
    {
        //打开文件失败
        cerr<<"error: unable to open input file: "
            <<fileName<<endl;
        return -1;
    }
    int keySize = strlen(keyWord);//关键字的长度
    int index = 0;  //记录关键字首次出现的位置
    int lastMatch = 0;//记录最后一次匹配的位置
    const int bufferSize = 5;
    char buffer[bufferSize + 1];
    while(!inputFile.eof())
    {
        //把最后一次比较配置的字符复制到最前面
        WriteEndToBegin(buffer, bufferSize, lastMatch);
        //读入数据到缓冲区中lastMatch后的位置中
        inputFile.read(buffer + lastMatch,
                       bufferSize - lastMatch);
        buffer[bufferSize] = '\0';
        cout<<buffer<<endl;
        int thisIndex = IndexOf(buffer, bufferSize,
                                keyWord, keySize, lastMatch);
        cout<<lastMatch;
        if(thisIndex != -1)
        {
            //若查找成功，则下标值为之前查找过的字符数加上此次查找的字符数
            index += thisIndex;
            return index;
        }
        else
        {
            //若查找不成功，则加上新放入到缓冲区的字符数
            index += (bufferSize - lastMatch);
        }
    }
    return -1;
}
int IndexOf(const char *text, int textSize,
            const char *match, int matchSize,
            int &lastMatch)
{
    for(int i = 0; i < textSize; ++i)
    {
        lastMatch = 0;
        while(lastMatch < matchSize && match[lastMatch] == text[i+lastMatch])
            ++lastMatch;
        //所有的字符都与文本中的一致，则匹配成功
        if(lastMatch == matchSize)
            return i;
        //所有的字符都匹配，但是模式串还没匹配完，主串已经到了尽头
        if(i + lastMatch == textSize)
            break;
    }
    //匹配失败
    return -1;
}

void WriteEndToBegin(char *text, int textSize, int writeCount)
{
    //把字符数组中最后writeCount个字符写到最前面
    for(int i = 0; i < writeCount; ++i)
    {
        text[i] = text[textSize - writeCount + i];
    }
}

