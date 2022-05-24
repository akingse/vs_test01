//#include <string>
//#include <iostream>
//#include <memory>
//#include <vector>

#include <stdafx.h>
#include "test_gnrc.h"
using namespace std;


	//class ClassInt :public IClass
	//{
	//public:
	//	int m_imp;
	//	ClassInt(int src) :
	//		m_imp(src)
	//	{
	//	}
	//};
	//class ClassDouble :public IClass
	//{
	//public:
	//	double m_imp;
	//	ClassDouble(double src) :
	//		m_imp(src)
	//	{
	//	}
	//};
	//Gene(double src)
	//{
	//	m_imp = new ClassDouble(src);
	//}
	//bool is(int)
	//{
	//	ClassInt* ptr = dynamic_cast<ClassInt*>(m_imp);
	//	return ptr != nullptr;
	//}
	//bool is(double)
	//{
	//	ClassDouble* ptr = dynamic_cast<ClassDouble*>(m_imp);
	//	return ptr != nullptr;
	//}
	//int& as(int)
	//{
	//	ClassInt* ptr = dynamic_cast<ClassInt*>(m_imp);
	//	return ptr->m_imp;
	//}
	//double& as(double)
	//{
	//	ClassDouble* ptr = dynamic_cast<ClassDouble*>(m_imp);
	//	return ptr->m_imp;
	//}
//template<typename T> 
//inline Gene(const T& src)
//
//template<typename T>
//



/*
单元测试
int double longlong
class struct vector map
构造和析构
继承类

*/

int test_gnrc_int(int n)
{
	Gene gnrcint(n);
	if (gnrcint.is<int>())
	{
		return gnrcint.as<int>();
	}
	return -1;
}

void test1()
{
	const int& a = 0; //非常量引用的初始值必须为左值
//左值是指表达式结束后依然存在的持久对象，右值是指表达式结束时就不再存在的临时对象。
//一个区分左值与右值的便捷方法是：看能不能对表达式取地址（能不能再次赋值），如果能，则为左值，否则为右值。
	int b = 0;
	++b = 1;
	//b++ = 1; //右值
	Vec3 v;
	const Vec3 v1;
	v.test();
	v1.test() ;
}

/*static */ Gene getA()
{
	Gene a(11);
	return a; //不能简化为Gene(11)
}


int main() // maingnrc
{




	//测试基本函数
	//Gene num0(0);
	//Gene gnrc_c0(num0); //拷贝构造 
	//Gene gnrc_c1 = num0; //拷贝构造 
	//num0 = gnrc_c1; //拷贝赋值

	//Gene geta = getA(); //移动构造
	//Gene gnrc_m = move(geta); //移动构造 
	//Gene gnrc_m2(2);
	//Gene gnrc_m1(std::move(gnrc_m2));//移动构造
	//Gene gnrc_m3(3);
	//Gene &&gnrc_m4= move(gnrc_m3); //右值赋值
	//Gene gnrc_m5(gnrc_m4);//直接赋值无效，还是拷贝构造


	//gnrc_m2 = getA();//移动赋值
	//gnrc_m2 = move(gnrc_m); //移动赋值

	GeneList list;
	vector<Vec3> vecs;
	vector<int> vecint;
	//Vec3* v = new Vec3[10];
	//Gene num0 = Gene(0);
	//Gene gnrcn(num0);



	auto siz = sizeof(list); //vector 统一32byte
	auto siz0 = sizeof(int); //4
	auto siz1 = sizeof(vecs); //32
	auto siz2 = sizeof(vecint); //32
	auto siz3 = sizeof(Gene(0)); //8
	auto siz4 = sizeof(map<int,int>); //24
	auto siz5 = sizeof(Gene); //8
	auto siz6 = sizeof(Vec3); //32

	for (int i = 0; i < 10; i++)
	{
		Vec3 v(i, i, i);
		//vecs.push_back(v);
		vecs.push_back(move(v)); //右值引用成功
	}

	//if (1) // true
	for (int i = 0; i < 1e6; i++) //1e1
	{
		//size_t a=list.capacity();
		Gene num0(0); // num0(nullptr);// = Gene(); //int(1)
		Gene num1(1); // num1(nullptr);// = Gene();
		Gene num2(2); // num2(nullptr);// = Gene();
		//Gene gnrc0(num0);
		//Gene gnrc1(num1);
		//Gene gnrc2(num2);
		list.push_back(num0);
		list.push_back(num1);
		list.push_back(num2);

		vecint.push_back(0);
		vecint.push_back(1);
		vecint.push_back(2);

		//a = list.capacity();
		/*list.push_back(std::move(num0));
		list.push_back(std::move(num1));
		list.push_back(std::move(num2));*/

		//Vec3 v0 = Vec3(0, 0, 0);
		//Vec3 v1 = Vec3(1, 1, 1);
		//Vec3 v2 = Vec3(2, 2, 2);
		//vecs.push_back(v0);
		//vecs.push_back(v1);
		//vecs.push_back(v2);
	}


	//list.push_back(num);
	////list.push_back(Gene(1));
	//Gene num1 = Gene(1);
	//list.push_back(num1);
	//return 0;
	//vecs.clear();


	//for (int i = 0; i < 1e4; i++)
	//{
	//	Gene gnrcint(int(0)); //测试独立Gene对象
	//	Gene gnrcint1(int(1));

	//	Gene num = Gene(0);
	//	//list.push_back(num);  //测试vector<Gene>对象
	//	//list.push_back(gnrcint1);
	//	//list.push_back(Gene(0));
	//	//list.push_back(Gene(1));

	//	//GeneList aint = { int(1),double(2),string("3"), Vec3() };
	//	GeneList aint = { int(0), int(1) };// , double(2), string("3"), Vec3()
	//}


	//-------------------------------------------------
	//类型支持验证
	//map<string,int> mp={ {"A",1} }; 验证支持map
	////mp["A"] = 1;
	//Gene gmap(mp);
	//auto gmapas = gmap.as<map<string, int>>();

	Gene gnrcint(int(4884));
	if (gnrcint.is<double>()) //可判断
	{
		std::cout << "" << endl;
	}

	if (gnrcint.is<int>())
	{
		auto res2 = gnrcint.as<int>();
		int a=1;
	}
	Gene gnrcdouble(double(1.23));
	//auto res3 = gnrcdouble.is<double>();
	if (gnrcdouble.is<double>())
	{
		auto res3 = gnrcdouble.as<double>();
		cout << res3 << endl;
	}
	Gene gnrcstring(std::string("sss"));
	if (gnrcstring.is<string>())
	{
		auto res4 = gnrcstring.as<string>();
		int a = 1;
	}

	char chas[] = "chars";
	char* chas2 = chas;
	//const char* chas = "chars";
	cout << chas << endl;
	Gene gnrcchar(chas);
	if (gnrcchar.is<char*>())
	{
		auto res4 = gnrcchar.as<char*>();
		cout << res4 << endl;
		int a = 1;
	}

	int n = 1;
	int& nref = n;

	Gene gnrcref(nref);


	Vec3 a = Vec3(1, 2, 3);
	Vec3 b;
	Gene gnrc(a);
	if (gnrc.is<Vec3>())
	{
		b = gnrc.as<Vec3>();
		int a = 0;
	}
	bool jud = (a == b); //重载 ==
	auto dd = (double)a;
	auto bb = bool(a);
	auto ddd = double(a);

	long long l = 112;
	Gene gnrc2(l);
	if (gnrc2.is<long long>())
	{
		auto b = gnrc2.as<long long>();
		string name = typeid(b).name();
		type_index namei = typeid(b);
		int a = 0;

	}





	return 0;
}