#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<string>
#include<thread>
#include<windows.h>
#include<time.h> //clock()函数
#include <functional> //函数式编程
using namespace std;

//C++11多线程 https://blog.csdn.net/weixin_42193704/article/details/113920419


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
	b.m_iX = 20;              // 修改b.m_iX的值并输出
	cout << b.m_iX << endl;
	cout << "子线程  " << &b << "  Thread_id: " << this_thread::get_id() << endl;
}


int main()
{

	A3 a3(10);
	//thread t(fun, a3);
	thread t(fun, std::ref(a3));
	t.join();
	cout << a3.m_iX << endl;           // 输出a.m_iX
	return 0;

	//-----------------------------------------------------------------------------------------------

	//explicit
	/*
	一、 operator隐式类型转换
	二、构造函数的隐式类型转换
	*/
	print_A2(0, 1); //隐式转换



	int&& rRef = square(5); //C++11 引入了右值引用的概念，以表示一个本应没有名称的临时对象。
	cout << rRef << endl;
	cout << rRef << endl;

	//-----------------------------------------------------------------------------------------------
	//第二节
	//thread myt_obj(myprint);
	A a;
	//thread myt_obj(a);
	thread myt_obj(my_lambda);
	if (myt_obj.joinable())
		myt_obj.join(); //阻塞
	//if (myt_obj.joinable())
		//myt_obj.detach();//后台运行  //主线程逐个等待不太好，引入detach
	cout << "I love China." << "" << endl;
	cout << "I love China." << "" << endl;
	cout << "I love China." << "" << endl;

	//while (!true)
	//{
	//	cout << "main thread." << endl;
	//	Sleep(2*1000);
	//}

	//-----------------------------------------------------------------------------------------------
	//第三节






	return 0;
}


