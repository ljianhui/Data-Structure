#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>

using namespace std;

int IndexOf(const char *text, int textSize,
            const char *match, int matchSize);
//字符串匹配，text为文本，match为模式串，返回模式串第一次出现的位置
int GetFileLength(ifstream &inputFile);
//获得文件的长度，即字节数

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        //输入的参数个数不正确，则退出程序
        cerr<<"The count of parameters is ERROR!"<<endl;
        exit(EXIT_FAILURE);
    }
    //以只读方式，打开文件fileName
    ifstream inputFile(argv[1]);
    if(!inputFile)
    {
        //打开文件失败
        cerr<<"error: unable to open input file: "
            <<argv[1]<<endl;
        exit(EXIT_FAILURE);
    }
    //获得文件的长度，即字节数，并开劈一个同样大小的数组保存文件数据
    int length = GetFileLength(inputFile);
    char *text = new char[length+1];
    //把文件的内容讲到数组中
    inputFile.read(text, length);
    inputFile.close();
    text[length] = '\0';
    //进行模式串匹配，并输出结果
    int index = IndexOf(text, length, argv[2], strlen(argv[2]));
    cout<<"The keyword: "<<argv[2]<<" , is in the location: "
        <<index<<endl;

    delete []text;
    exit(EXIT_SUCCESS);
}

int IndexOf(const char *text, int textSize,
            const char *match, int matchSize)
{
    for(int i = 0; i <= textSize - matchSize; ++i)
    {
        int j = 0;
        while(j < matchSize && match[j] == text[i+j])
            ++j;
        //所有的字符都与文本中的一致，则匹配成功
        if(j == matchSize)
            return i;
    }
    //匹配失败
    return -1;
}

int GetFileLength(ifstream &inputFile)
{
    //保存文件当前位置
    streampos pos = inputFile.tellg();
    //定位到文件尾
    inputFile.seekg(0, ios::end);
    //返回文件尾的偏移量，即文件的大小
    int length = inputFile.tellg();
    //返回到文件先前的位置
    inputFile.seekg(pos);
    return length;
}
