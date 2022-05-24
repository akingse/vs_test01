#include <iostream>
#include <list>
using namespace std;

// 内存管理，借出，归还置空
// 
// list 链表解决 double等小内存对象





template<class Object>
class ObjectPool
{

private:
	size_t m_size;
	std::list<Object*> m_pool;
	//Gene gene;

public:
	ObjectPool(size_t size) :m_size(size)
	{
		//_nSize = size;
		for (size_t n = 0; n < m_size; n++)
		{
			m_pool.push_back(new Object());
		}
	}
	virtual ~ObjectPool()
	{
		auto iter = m_pool.begin();
		//auto name = typeid(iter).name();
		while (iter != m_pool.end())
		{
			delete* iter;
			++iter;
		}
		m_size = 0;
	}

	Object* requestObject()
	{
		Object* pObj = NULL;
		if (m_size == 0)
		{
			pObj = new Object();
		}
		else
		{
			pObj = m_pool.front(); //返回第一个元素
			m_pool.pop_front(); //删除第一个元素
			--m_size;
		}
		return pObj;
	}

	void returnObject(Object* pObj)
	{
		m_pool.push_back(pObj);
		++m_size;
	}

};




class Test
{
public:
	Test() {}
	~Test() {}
	void Print()
	{
		cout << "Test" << endl;
	}
};




int main()
{
	ObjectPool<Test> obj(10);
	for (int i = 0; i < 10; i++)
	{
		Test* pA;
		pA = obj.requestObject();
		pA->Print();
		obj.returnObject(pA);
	}

	return 0;
}