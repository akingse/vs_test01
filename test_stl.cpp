#include <iostream>
#include <algorithm> 
#include <vector>
#include <string>
#include <cassert>
using namespace std;



vector<int> alist()
{
	//return { 1,2,3 };
	vector<int> a(6,0);
	return a;
	//return vector<int> a(6, 0);//not alllow
}

int test_fun(int a)
{

	assert(a ==10);
	return 0;

}
void print_number(int* myInt) {
	assert(myInt != NULL);  //如果myInt!=NULL,程序继续执行，反之程序打印报错信息，程序终止运行
	//assert(myInt!=NULL && 1==0) //检查多个条件
	cout << *myInt << endl;
}


int main()
{
	test_fun(10);
	vector<int> mlist = alist();
	cout << mlist.at(0) << endl;


	/*float a = 1.3;
	float b = 1.5;

	auto ar = round(a);
	auto br = round(b);*/

	vector<int> a(6, 0);
	a = { 0,1,2,3 };

	vector<int> b = { 1,2,3 };
	vector<int> c = { 4,5,6 };
	a = b;
	a = c;

	//两种访问(越界)
	//cout << b[3] << endl;
	cout << b.at(3) << endl;


	int sm = 1 < 2 ? 1 : 2;

	for (int i = 0; i < 10; i++)
	{
		sm++;
	}
	int n = 2;

	if (n == 2)
		cout << "success" << endl;
	if (!(n == 1))
		cout << "success" << endl;

	return 0;
}


