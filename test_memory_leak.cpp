#include <iostream>
#include "my_template.h"
#include<vector>
#include<type_traits>
#include <memory>
using namespace std;
/*
### �ڴ�й©�����

1��new without delete

2������ָ���໥����

3��������

4���ṹ��


*/

class C
{
public:

    double* val_ָ��;
    std::shared_ptr<std::vector<double>> vla_����ָ��;
    C()
    {
        val_ָ�� = new double(1.3);
        std::cout << "C()" << std::endl;
    }
    C(const C& src)//:
        //vla_����ָ��(new std::vector<double>(*src.vla_����ָ��));
    {
        const std::vector<double>& vc = *src.vla_����ָ��;
        std::vector<double>* vp = new std::vector<double>(vc);
        //vla_����ָ��.reset(vp);
        std::cout << "C(const C&)" << std::endl;
    }
    ~C()
    {
        std::cout << "~C()" << std::endl;
    }
};
int main_ml()
{
    //���ü���
//���ü����Ǽ������������е�һ���ڴ����������ָ����Դ�������Ƕ����ڴ����̿ռ�ȵȣ��ı����ô��������������������ô�����Ϊ��ʱ�ͽ����ͷŵĹ��̡�
    shared_ptr<C> pterA(new C);


    C ���ʺ��� = C();
    //C ���ʺ��ϼ� = ���ʺ���; // �
    C& ���вƼ� = ���ʺ���; // ǳ��
    C* ���вƼҵĿ�ݵ�ַ = &���вƼ�; // ǳ��
    C* ���ʺ��ҵĿ�ݵ�ַ = &���ʺ���; // ǳ��
    return 0;
}




int& func()
{
	int a = 1;
	return a;
}



//������
class Manage
{
public:
    static Manage& get_instance();
    //static s_instance();
};

//������,ֻ��һ��ʵ������

//Manage* Manage::s_instance = nullptr;



//�ṹ��
struct C_struct
{
    double vd; //����©
    string ch = "cha"; //string�ɱ䳤

    ~C_struct()
    {

    }
};
//delete��Ҫָ������

//����Ҫ��


int main_me()
{
	/*while (true)
	{
		C c;
		
	}*/
	int& ra = func(); //������ջ��Ұָ��
	ra = 2;

	char* pchar = new char;
	delete pchar; //�����������ͷ��ڴ棬�������ÿգ�
	pchar = nullptr;

	//�ǳ��
	//��ֵ��ֵ
	int a = 123;
	int b = a;//�
	int& c = a;//ǳ��
	int* p = &a;//ǳ��
    //Manager::get_instance().m_id2name[i++] = "name";


	return 0;
}



