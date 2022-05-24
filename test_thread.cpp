#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<string>
#include<thread>
#include<windows.h>
#include<time.h> //clock()����
#include <functional> //����ʽ���
using namespace std;

//C++11���߳� https://blog.csdn.net/weixin_42193704/article/details/113920419


void myprint(/*int i*/)
{

	cout << "\a" << endl;
	cout << "child thread begin." << endl;
	cout << "child thread end." << endl;
	Sleep(1000);
	cout << "\a" << endl;


	//while (!true)
	//{
	//	cout << "child thread." << endl;
	//	Sleep(1 * 1000);
	//}
}

class A
{
public:
	void operator()()
	{
		cout << "child thread begin." << endl;
		cout << "child thread end." << endl;
	}
};

auto my_lambda = [] {
	cout << "child thread begin." << endl;
	cout << "child thread end." << endl;
};


//
class A2
{
public:
	int m_i;

	A2(int a) :m_i(a) { cout << "This is Construct" << endl; }
	A2(const A2& a) :m_i(a.m_i) { cout << "This is Copy Construct" << endl; }
	~A2() { cout << "This is Destruct" << endl; }

};

void print_A2(int i, const A2& a)
{
	cout << a.m_i << endl;
}

int square(int x)
{
	return x * x;
}

class A3
{
public:
	mutable int m_iX;
	A3(int x) : m_iX(x) {
		cout << "constru  " << this << "   Thread_id: " << this_thread::get_id() << endl;
	}
	A3(const A3& a) {
		m_iX = a.m_iX;
		cout << "copycon  " << this << "  Thread_id: " << this_thread::get_id() << endl;
	}
	~A3() {
		cout << "destru  " << this << "  Thread_id: " << this_thread::get_id() << endl;
	}
};

void fun(const A3& b) {
	b.m_iX = 20;              // �޸�b.m_iX��ֵ�����
	cout << b.m_iX << endl;
	cout << "���߳�  " << &b << "  Thread_id: " << this_thread::get_id() << endl;
}


int main()
{

	A3 a3(10);
	//thread t(fun, a3);
	thread t(fun, std::ref(a3));
	t.join();
	cout << a3.m_iX << endl;           // ���a.m_iX
	return 0;

	//-----------------------------------------------------------------------------------------------

	//explicit
	/*
	һ�� operator��ʽ����ת��
	�������캯������ʽ����ת��
	*/
	print_A2(0, 1); //��ʽת��



	int&& rRef = square(5); //C++11 ��������ֵ���õĸ���Ա�ʾһ����Ӧû�����Ƶ���ʱ����
	cout << rRef << endl;
	cout << rRef << endl;

	//-----------------------------------------------------------------------------------------------
	//�ڶ���
	//thread myt_obj(myprint);
	A a;
	//thread myt_obj(a);
	thread myt_obj(my_lambda);
	if (myt_obj.joinable())
		myt_obj.join(); //����
	//if (myt_obj.joinable())
		//myt_obj.detach();//��̨����  //���߳�����ȴ���̫�ã�����detach
	cout << "I love China." << "" << endl;
	cout << "I love China." << "" << endl;
	cout << "I love China." << "" << endl;

	//while (!true)
	//{
	//	cout << "main thread." << endl;
	//	Sleep(2*1000);
	//}

	//-----------------------------------------------------------------------------------------------
	//������






	return 0;
}


