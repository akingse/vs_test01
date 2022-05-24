#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Box
{
public:

    double getVolume(void)
    {
        return length * breadth * height;
    }
    void setLength(double len)
    {
        length = len;
    }

    void setBreadth(double bre) //��
    {
        breadth = bre;
    }

    void setHeight(double hei)
    {
        height = hei;
    }
    // ���� + ����������ڰ����� Box �������
    Box operator+(const Box& b)
    {
        Box box;
        box.length = this->length + b.length;
        box.breadth = this->breadth + b.breadth;
        box.height = this->height + b.height;
        return box;
    }
    Box operator*(const int& b)
    {
        Box box;
        box.length = this->length * b;
        box.breadth = this->breadth * b;
        box.height = this->height * b;
        return box;
    }
    //friend Box operator*(const int& b, Box box); //�����˽������Ҫ����Ԫ�޶�

//private:
public:

    double length;      // ����
    double breadth;     // ���
    double height;      // �߶�

    
};

Box operator*(const int& b, Box box)
{
    box.length = box.length * b;
    box.breadth = box.breadth * b;
    box.height = box.height * b;
    return box;
}

// �����������
int main_o()
{



    Box Box1;                // ���� Box1������Ϊ Box
    Box Box2;                // ���� Box2������Ϊ Box
    Box Box3;                // ���� Box3������Ϊ Box
    double volume = 0.0;     // ������洢�ڸñ�����

    // Box1 ����
    Box1.setLength(1.0);
    Box1.setBreadth(1.0);
    Box1.setHeight(1.0);

    // Box2 ����
    Box2.setLength(2.0);
    Box2.setBreadth(2.0);
    Box2.setHeight(2.0);

    // Box1 �����
    volume = Box1.getVolume();
    cout << "Volume of Box1 : " << volume << endl;

    // Box2 �����
    volume = Box2.getVolume();
    cout << "Volume of Box2 : " << volume << endl;

    // ������������ӣ��õ� Box3
    //Box3 = Box1 + Box2;

    //// Box3 �����
    //volume = Box3.getVolume();
    //cout << "Volume of Box3 : " << volume << endl;
    Box3 = 3*Box2 ;
    //Box3 = Box2*2;
    volume = Box3.getVolume();
    cout << "Volume of Box3 : " << volume << endl;

    vector<int> v1 = { 1,2 };
    //int a, b = vec[0],vec[1];
    // vectorƴ��
    std::vector<int> v3={3, 4};
    v3.insert(v3.end(), v1.begin(), v1.end());
    int a = 1;
    cout << v3.back() << endl;
    cout << *v3.begin() << endl;
    cout << &a << endl;
    
    //����
    sort(v3.begin(), v3.end());//��С����
    reverse(v3.begin(), v3.end());//�Ӵ�С 

    return 0;
}