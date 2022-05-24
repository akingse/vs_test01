#include <iostream>
#include <fstream>
#include <string>
#include <chrono>   
#include <map>
#include <iostream>
#include <string>
#include <memory>
#include <vector>


/*
#��;
1. �����Ժ�ȷ��
2. �����ظ�����
3. Ϊ��/�ӿ��ṩ����λ����
4. �������������ģ��ɱ䳤ģ�� ...
5. ģ��ʵ����������
#ʹ�ü���
6. �ػ���ƫ�ػ�
7. �����Ƶ�
8. auto
*/

/*
1. new ��û�� delete
2. ������
3. ����ָ���໥����
4. �ṹ���Ĭ�������������⣬��������������
*/


//-------------------------------------------------------------------------
const std::string& get_personal_information(const std::string& name);

//һ���򵥵Ļ����demo
int main_cache()
{
    // ��ʱ
    auto start = std::chrono::system_clock::now();
    for (size_t i = 0; i < 30000; i++)
    {
        std::string winfor = get_personal_information("������");
        std::string zinfor = get_personal_information("�ź�");
    }
    auto end = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "������"
        << double(duration.count()) * std::chrono::microseconds::period::num / std::chrono::microseconds::period::den
        << "��" << std::endl;
    return 0;
}


// ���������ļ����ڴ�
std::string load_file(std::string file) {
    std::ifstream infile(file, std::ios::binary); // �����Ʒ�ʽ
    if (!infile.is_open())
        throw std::string("�ļ� ") + std::string(file) + std::string(" ������");
    // ��ȡ�ļ�����
    infile.seekg(0, std::ios::end);
    size_t length = infile.tellg();
    infile.seekg(0, std::ios::beg);
    std::string buffer;
    buffer.resize(length);
    infile.read((char*)buffer.data(), length);
    infile.close();
    return buffer;
}


const std::string& get_personal_information(const std::string& name)
{
    static std::map<std::string, std::string> cache;
    auto iter = cache.find(name);
    if (iter == cache.end())
        cache[name] = load_file(std::string("C:\\Users\\youqi\\source\\repos\\Data\\Data\\") + name + ".txt");
    return cache[name];
}
// ����
// ����

/*
#��;
1. �����Ժ�ȷ��
2. �����ظ�����
3. Ϊ��/�ӿ��ṩ����λ����
4. �������������ģ��ɱ䳤ģ�� ...
5. ģ��ʵ����������
#ʹ�ü���
6. �ػ���ƫ�ػ�
7. �����Ƶ�
8. auto
*/

/*
1. new ��û�� delete
2. ������
3. ����ָ���໥����
4. �ṹ���Ĭ�������������⣬��������������
*/


/*
ģ�� # ������
�ڴ�й© # ������
���ǳ�� # ������
����
���л�����?
Gnrc������
����ֵ�����õ�����
lambda
hashmap

�����
    ע�����
    �־û������������
    BPDataKey�������
�ź�

*/
