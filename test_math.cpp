#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>
#include <complex>

#define _USE_MATH_DEFINES
#include<math.h>
using namespace std;
int main1()
{
    std::cout << "Hello World!\n";
    //for (int i = 0; i <= 5; i++)
    //for (int i = 0; i <= 5; ++i) //Ч��һ����++iЧ�ʸ�
    //    std::cout << i << endl;

    double a = 2;
    std::cout << a << endl;

    //a = a ^ 2;
    a = pow(a, 2);
    std::cout << a << endl;
    std::cout << M_PI << endl;
    std::cout << cos(M_PI / 2) << endl;

    vector<int> vecA;
    for (int i = 0; i < 10; i++)
        vecA.push_back(i);
    std::cout << vecA[vecA.size() - 1] << endl;
    auto it = vecA.end();
    std::cout << vecA.front() << endl;
    std::cout << vecA.back() << endl;
    //auto it = vecA.rbegin();

    complex<double> acp(2, 1);
    complex<double> ac2 = 2.0 + 3i;
    std::cout << "complex" << acp << endl;
    std::cout << "complex" << ac2 << endl;
    std::cout << " " << acp.real() << endl;
    std::cout << " " << acp.imag() << endl;

    vector<double> aList;
    aList.push_back(1);
    //aList.push_back(ac2);

    vector<complex<double>> compList;
    compList.push_back(acp);

    /*double operator^( double& a, double& b)
    {

    }*/
    return 0;
}


using namespace std;
//https://www.cnblogs.com/xiaoxi666/p/6421228.html

#define N 5

//����˷�
double* multiply(double A[N * N], double B[N * N])
{
    double* C = new double[N * N]{};
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int k = 0; k < N; k++)
            {
                C[i * N + j] += A[i * N + k] * B[k * N + j];
                if (abs(C[i * N + j]) < 1e-10)
                {
                    C[i * N + j] = 0;
                }
            }
        }
    }
    return C;
}

//LUP�ֽ�  LU Factorization
void LUP_Descomposition(double A[N * N], double L[N * N], double U[N * N], int P[N])
{
    int row = 0;
    for (int i = 0; i < N; i++)
    {
        P[i] = i;
    }
    for (int i = 0; i < N - 1; i++)
    {
        double p = 0.0;
        for (int j = i; j < N; j++)
        {
            if (abs(A[j * N + i]) > p)
            {
                p = abs(A[j * N + i]);
                row = j;
            }
        }
        if (0 == p)
        {
            cout << "singular matrixm,there is no inverse matrix!" << endl; //�������죬�޷�������
            return;
        }

        //����P[i]��P[row]
        int tmp = P[i];
        P[i] = P[row];
        P[row] = tmp;

        double tmp2 = 0.0;
        for (int j = 0; j < N; j++)
        {
            //����A[i][j]�� A[row][j]
            tmp2 = A[i * N + j];
            A[i * N + j] = A[row * N + j];
            A[row * N + j] = tmp2;
        }

        //����ͬLU�ֽ�
        double u = A[i * N + i], l = 0.0;
        for (int j = i + 1; j < N; j++)
        {
            l = A[j * N + i] / u;
            A[j * N + i] = l;
            for (int k = i + 1; k < N; k++)
            {
                A[j * N + k] = A[j * N + k] - A[i * N + k] * l;
            }
        }

    }

    //����L��U
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            if (i != j)
            {
                L[i * N + j] = A[i * N + j];
            }
            else
            {
                L[i * N + j] = 1;
            }
        }
        for (int k = i; k < N; k++)
        {
            U[i * N + k] = A[i * N + k];
        }
    }

}

//LUP��ⷽ��
double* LUP_Solve(double L[N * N], double U[N * N], int P[N], double b[N])
{
    double* x = new double[N]();
    double* y = new double[N]();

    //�����滻
    for (int i = 0; i < N; i++)
    {
        y[i] = b[P[i]];
        for (int j = 0; j < i; j++)
        {
            y[i] = y[i] - L[i * N + j] * y[j];
        }
    }
    //�����滻
    for (int i = N - 1; i >= 0; i--)
    {
        x[i] = y[i];
        for (int j = N - 1; j > i; j--)
        {
            x[i] = x[i] - U[i * N + j] * x[j];
        }
        x[i] /= U[i * N + i];
    }
    return x;
}

/*****************����ԭ��ת��BEGIN********************/

/* ��� */
int getNext(int i, int m, int n)
{
    return (i % n) * m + i / n;
}

/* ǰ�� */
int getPre(int i, int m, int n)
{
    return (i % m) * n + i / m;
}

/* �������±�iΪ���Ļ� */
void movedata(double* mtx, int i, int m, int n)
{
    double temp = mtx[i]; // �ݴ�
    int cur = i;    // ��ǰ�±�
    int pre = getPre(cur, m, n);
    while (pre != i)
    {
        mtx[cur] = mtx[pre];
        cur = pre;
        pre = getPre(cur, m, n);
    }
    mtx[cur] = temp;
}

/* ת�ã���ѭ���������л� */
void transpose(double* mtx, int m, int n)
{
    for (int i = 0; i < m * n; ++i)
    {
        int next = getNext(i, m, n);
        while (next > i) // �����ں��С��i˵���ظ�,�Ͳ�������ȥ�ˣ�ֻ�в��ظ�ʱ����whileѭ����
            next = getNext(next, m, n);
        if (next == i)  // ����ǰ��
            movedata(mtx, i, m, n);
    }
}
/*****************����ԭ��ת��END********************/

//LUP����(��ÿ��b����ĸ���x������װ)
double* LUP_solve_inverse(double A[N * N])
{
    //��������A�ĸ�����ע�ⲻ��ֱ����A���㣬��ΪLUP�ֽ��㷨�ѽ���ı�
    double* A_mirror = new double[N * N]();
    double* inv_A = new double[N * N]();//���յ�����󣨻���Ҫת�ã�
    double* inv_A_each = new double[N]();//������ĸ���
    //double *B    =new double[N*N]();
    double* b = new double[N]();//b��ΪB����о������

    for (int i = 0; i < N; i++)
    {
        double* L = new double[N * N]();
        double* U = new double[N * N]();
        int* P = new int[N]();

        //���쵥λ���ÿһ��
        for (int i = 0; i < N; i++)
        {
            b[i] = 0;
        }
        b[i] = 1;

        //ÿ�ζ���Ҫ���½�A����һ��
        for (int i = 0; i < N * N; i++)
        {
            A_mirror[i] = A[i];
        }

        LUP_Descomposition(A_mirror, L, U, P);

        inv_A_each = LUP_Solve(L, U, P, b);
        memcpy(inv_A + i * N, inv_A_each, N * sizeof(double));//������ƴ������
    }
    transpose(inv_A, N, N);//�������ڸ���ÿ��b�����x���д洢�������ת��

    return inv_A;
}

int main4()
{
    double* A = new double[N * N]();

    srand((unsigned)time(0));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            A[i * N + j] = rand() % 100 * 0.01;
        }
    }


    double* E_test = new double[N * N]();
    double* invOfA = new double[N * N]();
    invOfA = LUP_solve_inverse(A);

    E_test = multiply(A, invOfA);    //��֤��ȷ��

    cout << "����A:" << endl;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << A[i * N + j] << " ";
        }
        cout << endl;
    }

    cout << "inv_A:" << endl;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << invOfA[i * N + j] << " ";
        }
        cout << endl;
    }

    cout << "E_test:" << endl;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << E_test[i * N + j] << " ";
        }
        cout << endl;
    }

    return 0;
}


int funtion(int a, int b)
{
    if (a == 1)
        return 1;
    else if (a == 2)
    {
        if (b == 1)
            return -1;
    }

    else
        return 3;
    return 0;
}

int math_sign(float x)
{
    if (abs(x) < 1e-10)
        return 0;
    //return (x > 0) ? 1 : -1;
    return (x > 0) ? (1) : (-1);
}

int main2()
{
    int p = 5, b = 2;
    int c = funtion(5, b);
    //cout << c << endl;
    std::cout << pow(-27.0, 1.0 / 3) << endl;

    //&ȡֵ��ֵ
    vector<int> numList = { 1,2,3 };
    for (auto& iter : numList) //&
    {
        iter = 2 * iter;
    }
    //cout << numList[0] << endl;
    cout << math_sign(-10) << endl;

    return 0;
}



