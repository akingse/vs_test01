#include <iostream>
using namespace std;


int counter = 1;

int fac(int n)
{
    cout << "��" << counter << "�ε��ã�" << n << " * " << "fac(" << n - 1 << ")" << endl;
    if (n == 1) {
        return 1;
    }
    else
    {
        counter++;
        return n * fac(n - 1); // �ϵ�1
    }
}

int main_recur()
{

    auto str = "thisishowishow";
    auto type = typeid(str).name();

    string str1 = "thisishowishow";
    auto type1 = typeid(str1).name();


    int n = 5;

    cout << "�����fac(" << n << ")=" << endl << fac(n) << endl;
    return 0;
}