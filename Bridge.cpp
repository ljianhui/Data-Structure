#include <iostream>

using namespace std;

class MobileSoft
{
	public:
		virtual void Run()=0;
		virtual ~MobileSoft(){}
	protected:
		MobileSoft(){}
};

class MobilePhone
{
	public:
		~MobilePhone()
		{
			delete pMS;
			pMS = NULL;
			cout<<"destory pMS"<<endl;
		}
		virtual void Run()=0;
		void SetSoft(MobileSoft *p)
		{
			pMS = p;	
		}
		
	protected:
		MobilePhone():pMS(NULL){}
		MobileSoft *pMS;
};

class Games:public MobileSoft
{
	public:
		virtual void Run()
		{
			cout<<"run the soft of Games"<<endl;
		}
};

class Chat:public MobileSoft
{
	public:
		virtual void Run()
		{
			cout<<"run the soft of Chat"<<endl;
		}
};

class HTC:public MobilePhone
{
	public:
		virtual void Run()
		{
			pMS->Run();
		}
};

class NOKIA:public MobilePhone
{
	public:
		virtual void Run()
		{
			pMS->Run();
		}
};

int main()
{
	MobilePhone *pMP(new HTC);
	pMP->SetSoft(new Games);
	pMP->Run();
	delete pMP;
	system("pause");
	pMP = new NOKIA;
	pMP->SetSoft(new Chat);
	pMP->Run();
	delete pMP;
	system("pause");
	system("pause");
	return 0;
}
