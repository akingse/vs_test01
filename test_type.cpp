#include <stdafx.h>
using namespace std;

//std::ref������ģ�崫�ε�ʱ�������ã������޷���������������
//std::cref() ����const���õİ汾��
template<class T>
void temp_function(T arg)
{
	std::cout << "com=" << &arg << "\n";
	arg++;
}
void f(int& i) {
	for (int j = 0; j < i; j++) {
		cout << i << endl;
	}
}


int main()
{

	//��ֵ��ֵ
	int num = 1;
	int& numR1 = num; //�ǳ��������ñ���Ϊ��ֵ
	const int& numR = 1; //���������ÿ���Ϊ��ֵ
	int&& ar = 1; //��ֵ����

	int&& i = 123;
	int&& j = std::move(i);
	//int&& k = i;//���벻��������i��һ����ֵ����ֵ����ֻ��������ֵ



	int* p = new int;
	*p = 1;
	cout << *p << endl;
	cout << sizeof(*p) << endl; //4
	cout << sizeof(p) << endl; //8

	p = nullptr;
	cout << sizeof(p) << endl;
	cout << sizeof(*p) << endl;
	/*int a = 0;
	const int& b = 1;*/

	int ii = 5;
	//thread t([&]() {f(ii); });//����δʹ��ref(i);
	// thread t(f, ref(ii));
	//t.join();

	//type_info decorated undecorated-name װ����
	const std::type_info& a = typeid(int); //��ʼ��
	//typeid()������������Ϣconst std::type_info&�����������ǲ��ܸ�ֵ��
	//Ϊ�˽��������⣬C++������std::type_index�ࡣ�����������Ϊ��װ��һ��ָ��typeinfo��ָ�롣
	std::type_index b = typeid(int);
	cout << *a.name() << endl;
	cout << a.hash_code() << endl;
	cout << b.name() << endl;
	cout << b.hash_code() << endl;	//����������͵Ĺ�ϣֵ������Ψһ�ԣ�
	bool bl=a.before(a);

	auto name = typeid(int).name(); //string operator=�Զ�ת��
	auto name2= typeid(name).name(); //char const * __ptr64
	cout << typeid(int).name() << endl;
	auto name3 = ref(typeid(int));


	//int i{ 9 };
	int i(9);
	cout << "origin=" << i << endl;
	auto m1 = ref(i);
	cout << typeid(m1).name() << endl;
	++m1;
	cout << i << endl;



	int count = 10;
	int& rcount = count;
	temp_function(count);
	std::cout << count << std::endl;//10
	temp_function(rcount);
	std::cout << "main=" << &rcount << endl;
	std::cout << count << std::endl;//10
	//ʹ��std::ref������ģ�崫�ε�ʱ�������ã�thread�ķ����������õ�ʱ�򣬷����޷����ݡ�
	//ref()�����ķ���ֵ��reference_wrapper����, ������Դ���ŵ���˼����ά��һ��ָ�룬�������ز�������
	temp_function(std::ref(rcount));//������
	std::cout << count << std::endl;//11

	std::cin.get();//�ȴ�����



	cout << "----------------------------------" << endl;
	
	int n1 = 0, n2 = 0;
	++n1;
	cout << n1 << endl; //1
	n2++;
	cout << n2 << endl; //1

	n1 = 0, n2 = 0;
	cout << ++n1 << endl; //1 (i=i+1)
	cout << n2++ << endl; //0

	for (int i = 0; i < 1; ++i)
	{
		cout << i << endl;
	}
	for (int i = 0; i < 1; i++)
	{
		cout << i << endl;
	}


	//---------------------------------------------
	//��ʽ����ת��
	int m = 97;
	char c = (char)m;//��ʽ��mתΪchar����
	char c1 = char(m);
	char c2 = m; //��ʽת��
	cout << c << endl;
	cout << c1 << endl;
	cout << c2 << endl;


	return 0;
}

