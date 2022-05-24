#include <iostream>
#include <ctime>    //���ڲ���������ݵ�����
using namespace std;
#define N 3    //���Ծ���ά������

//����һ��չ������|A|
double getDetA(double mat[N][N], int n)
{
    if (n == 1)
    {
        return mat[0][0];
    }
    double ans = 0;
    double temp[N][N] = { 0.0 };
    int i, j, k;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n - 1; j++)
        {
            for (k = 0; k < n - 1; k++)
            {
                temp[j][k] = mat[j + 1][(k >= i) ? k + 1 : k];
            }
        }
        double t = getDetA(temp, n - 1);
        if (i % 2 == 0)
        {
            ans += mat[0][i] * t;
        }
        else
        {
            ans -= mat[0][i] * t;
        }
    }
    return ans;
}

//����ÿһ��ÿһ�е�ÿ��Ԫ������Ӧ������ʽ�����A*
void  getAStart(double mat[N][N], int n, double ans[N][N])
{
    if (n == 1)
    {
        ans[0][0] = 1;
        return;
    }
    int i, j, k, t;
    double temp[N][N];
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            for (k = 0; k < n - 1; k++)
            {
                for (t = 0; t < n - 1; t++)
                {
                    temp[k][t] = mat[k >= i ? k + 1 : k][t >= j ? t + 1 : t];
                }
            }
            ans[j][i] = getDetA(temp, n - 1);  //�˴�˳�������ת��
            if ((i + j) % 2 == 1)//����
            {
                ans[j][i] = -ans[j][i];
            }
        }
    }
}

//�õ���������src������󱣴浽des�С�
bool GetMatrixInverse(double src[N][N], int n, double des[N][N])
{
    double flag = getDetA(src, n);
    double t[N][N];
    if (0 == flag)
    {
        cout << "det_A==0,there isno inverse matrix!" << endl;
        return false;//���������������ʽΪ0�������½���
    }
    else
    {
        getAStart(src, n, t);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                des[i][j] = t[i][j] / flag;
            }
        }
    }
    return true;
}

int main3()
{
    bool flag;//��־λ���������ʽΪ0�����������
    int row = N;
    int col = N;
    double matrix_before[N][N]{};//{1,2,3,4,5,6,7,8,9};

    //������ݣ����滻
    srand((unsigned)time(0));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matrix_before[i][j] = rand() % 100 * 0.01;
        }
    }

    cout << "ԭ����" << endl;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            //cout << matrix_before[i][j] <<" ";
            cout << *(*(matrix_before + i) + j) << " ";
        }
        cout << endl;
    }


    double matrix_after[N][N]{};
    flag = GetMatrixInverse(matrix_before, N, matrix_after);
    if (false == flag)
        return 0;


    cout << "�����" << endl;

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cout << matrix_after[i][j] << " ";
            //cout << *(*(matrix_after+i)+j)<<" ";
        }
        cout << endl;
    }

    GetMatrixInverse(matrix_after, N, matrix_before);

    cout << "�����ԭ����" << endl;//Ϊ����֤����ľ���
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            //cout << matrix_before[i][j] <<" ";
            cout << *(*(matrix_before + i) + j) << " ";
        }
        cout << endl;
    }


    return 0;
}