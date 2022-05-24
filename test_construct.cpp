#include<iostream>
#include<vector>


class B
{
public:
    int m_imp;
    B(int b=-1) :m_imp(b)
    { 
        std::cout << "B Constructor" << std::endl; 
    }
    B(const B& b) 
    { 
        std::cout << "B copy Constructor" << std::endl; 
    }
};

class A
{
private:
    B* m_b;
public:
    A(int a=0) : 
        m_b(new B(a)) //Ĭ�Ϲ���
    { 
        std::cout << "A Constructor" << std::endl; 
    }
    A(const A& src) 
        //m_b(new B(*(src.m_b))) //��������
    {
        m_b = new B;
        //m_b = src.m_b; // ��ָ��
        *m_b = *src.m_b; // ����ֵ
        /*
        �������������ÿ������캯����
��1��һ��������ֵ���ݵķ�ʽ���뺯����
��2��һ��������ֵ���ݵķ�ʽ�Ӻ�������
��3��һ��������Ҫͨ������һ��������г�ʼ����
        */
        std::cout << "A Copy Constructor" << std::endl;
    }

    //std::move���������Էǳ��򵥵ķ�ʽ����ֵת��Ϊ��ֵ���á�
    //ͨ��std::move�����Ա��ⲻ��Ҫ�Ŀ���������std::move��Ϊ���ܶ�����
    A(A&& src) : 
        m_b(src.m_b) //�ƶ�����
    {
        src.m_b = nullptr;
        std::cout << "A Move Constructor" << std::endl;
    }
    
    A& operator=(A&& src) noexcept //�ƶ���ֵ
    {
        if (this == &src)
            return *this;

        delete m_b;
        m_b = src.m_b;
        src.m_b = nullptr;
        std::cout << "operator=(const A&& src)" << std::endl;
        return *this;
    }
    A& operator=(const A& src) noexcept //��ֵ
    {
        if (this == &src)
            return *this;

        delete m_b;
        m_b = new B(*(src.m_b));
        std::cout << "operator=(const A& src)" << std::endl;
        return *this;
    }

    ~A() 
    { 
        if (m_b);
            delete m_b; 
    }

};

static A getA()
{
    A a(1);
    //std::cout << "=======================" << std::endl;
    return a;
}

int main_c()
{
    //int si = sizeof(int);
    //si = sizeof(long);
    //si = sizeof(long long);
    //A a;
    //a= getA();
    //std::vector<A> list; //�ڴ��Ƿ�й©
    //for (int i = 0; i < 1e1; i++)
    //{
    //    A a0(0);
    //    A a1(1);
    //    list.push_back(a0);
    //    list.push_back(a1);
    //}
    //int siz = sizeof(list);

    //getA();
    A a = getA();//�ƶ�����
    std::cout << "================================================" << std::endl;
    A a1(a);//�������죬������Ϊ���


    std::cout << "================================================" << std::endl;
    A a2(std::move(a1));//�ƶ�����

    std::cout << "================================================" << std::endl;
    a2 = getA();//�ƶ���ֵ

    return 0;

    std::cout << "================================================" << std::endl;
    a2 = a1;//������ֵ
    return 0;

}