//���̱߳��

#include <iostream>
#include <algorithm> 
#include <vector>
#include <string>
using namespace std;

int g_Value = 0;
class CLambda
{
protected:
	int m_Value;
public:
	void Test1(int InValue)
	{
		int Value = 0;
		auto a1 = [](int x) {/*���ܷ���ȫ���ⲿ����*/};
		auto a2 = [Value](int x) {/*ֵ���ݾֲ�����Value*/};
		auto a3 = [this](int x) {/*ֵ����thisָ��*/};
		auto a4 = [&Value](int x) {/*���ô��ݾֲ�����Value*/};
		auto a5 = [=](int x) {/*ֵ�������пɷ��ʵ��ⲿ����*/};
		auto a6 = [&](int x) {/*���ô������пɷ��ʵ��ⲿ����*/};
		auto a7 = [=, &Value](int x) {/*���ô��ݾֲ�����Value��ֵ�������������ɷ��ʵ��ⲿ����*/};
		auto a8 = [&, Value](int x) {/*ֵ���ݾֲ�����Value�����ô������������ɷ��ʵ��ⲿ����*/};
	}
};
/*
[]��Ĭ�ϲ������κα�����
[=]��Ĭ����ֵ�������б�����
[&]��Ĭ�������ò������б�����
[x]������ֵ����x����������������
[&x]���������ò���x����������������
[=, &x]��Ĭ����ֵ�������б���������x�����⣬ͨ�����ò���
[&, x]��Ĭ�������ò������б���������x�����⣬ͨ��ֵ����
[this]��ͨ�����ò���ǰ������ʵ�Ǹ���ָ�룩��
[*this]��ͨ����ֵ��ʽ����ǰ����
*/

void myfunction(int i) {  // function:
	std::cout << ' ' << i;
}

struct myclass {           // function object type:  one paramter
	void operator() (int i) 
	{ std::cout << ' ' << i; }
} myobject;

struct myclass_twoParam {           // function object type:  two or more paramter
	void operator() (int i, int ii) 
	{ std::cout << ' ' << i << " " << ii; }
} myobject_TwoParam;



int main() {
	std::vector<int> myvector = {10,20,30};

	std::cout << "myvector contains:";
	for_each(myvector.begin(), myvector.end(), myfunction);  //�� for_each ����һ������
	std::cout << '\n';

	// or:
	std::cout << "myvector contains:";
	for_each(myvector.begin(), myvector.end(), myobject);   //�� for_each ����һ����������33   std::cout << '\n'; 34 35   // or: 36   std::cout << "myvector contains:";//�� for_each ����һ��lamdba37   for_each (myvector.begin(), myvector.end(), [&](int i){myobject_TwoParam(i, 100);}); //���ɵ��ö�����ߺ����Ĳ���������������ʱ�� ���Ը� for_each����һ��lamdba��ʱ�ɵ��ö����������ʱ�ɵ��ö���ԭ�ɵ��ö������һ�Ρ� 38   std::cout << '\n'; 3940   return 0; 
	std::cout << '\n';
	// or: 
	std::cout << "myvector contains:";//�� for_each ����һ��lamdba
	for_each(myvector.begin(), myvector.end(), [&](int i) {myobject_TwoParam(i, 100); }); //���ɵ��ö�����ߺ����Ĳ���������������ʱ�� ���Ը� for_each����һ��lamdba��ʱ�ɵ��ö����������ʱ�ɵ��ö���ԭ�ɵ��ö������һ�Ρ� 
	std::cout << '\n';
	
	/*
	std::for_each
	��һ��������ʾһ������Ŀ�ʼ�������ǵ�������Ҳ�����������ĳ��λ�ã�
	�ڶ���������ʾһ������Ľ����������ǵ�������Ҳ�����������ĳ��λ�ã�
	������������ʾһ���ɵ��ö��󣬿����Ǻ����������Ǻ�������Ҳ������lamdba��
	std::for_each ���ص��������������ߵ�������������ֵ���á�
	*/

	std::vector<int> some_list = { 1,2,3 };
	int total = 0;
	int total_2 = 0;
	/*for (int i = 0; i < 5; ++i)
		some_list.push_back(i);*/
	/*std::for_each(begin(some_list), end(some_list), [&total](int x)
		{
			total += x;
		});*/
	std::for_each(some_list.begin(), some_list.end(), [&total_2](int x)
		{
			total_2 += x;
		});
	//[capture] (parameters) specifiers->return_type{ body }
	//capture ������ⲿ�����б�ͨ�����ŷָ����ɽ��д�ֵ����������ò���lambda���ʽ����Щ������ⲿ�����ṹ��һ���հ���Closure�����ⲿ����Ϊ�հ��ĳ�Ա����
	cout << total << endl;
	cout << total_2 << endl;
	int a = 2;
	auto f = [&total](int a) ->int {total += 1; cout << "lambda=" << total << endl; return total; };
	f(1);
	cout << typeid(f).name() << endl;
	//if (a <= 1) { a != 2; };
	long long num = 2;
	cout << num << endl;
	cout << int(num) << endl;
	
	


	return 0;
}