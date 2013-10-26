#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>

using namespace std;

int IndexOf(const char *text, int textSize,
            const char *match, int matchSize);
//�ַ���ƥ�䣬textΪ�ı���matchΪģʽ��������ģʽ����һ�γ��ֵ�λ��
int GetFileLength(ifstream &inputFile);
//����ļ��ĳ��ȣ����ֽ���

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        //����Ĳ�����������ȷ�����˳�����
        cerr<<"The count of parameters is ERROR!"<<endl;
        exit(EXIT_FAILURE);
    }
    //��ֻ����ʽ�����ļ�fileName
    ifstream inputFile(argv[1]);
    if(!inputFile)
    {
        //���ļ�ʧ��
        cerr<<"error: unable to open input file: "
            <<argv[1]<<endl;
        exit(EXIT_FAILURE);
    }
    //����ļ��ĳ��ȣ����ֽ�����������һ��ͬ����С�����鱣���ļ�����
    int length = GetFileLength(inputFile);
    char *text = new char[length+1];
    //���ļ������ݽ���������
    inputFile.read(text, length);
    inputFile.close();
    text[length] = '\0';
    //����ģʽ��ƥ�䣬��������
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
        //���е��ַ������ı��е�һ�£���ƥ��ɹ�
        if(j == matchSize)
            return i;
    }
    //ƥ��ʧ��
    return -1;
}

int GetFileLength(ifstream &inputFile)
{
    //�����ļ���ǰλ��
    streampos pos = inputFile.tellg();
    //��λ���ļ�β
    inputFile.seekg(0, ios::end);
    //�����ļ�β��ƫ���������ļ��Ĵ�С
    int length = inputFile.tellg();
    //���ص��ļ���ǰ��λ��
    inputFile.seekg(pos);
    return length;
}
