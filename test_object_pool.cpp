#include<stdafx.h> 

#include<stdlib.h> //stantard library
#include<iostream>
#include<mutex> //thread lock
#include<assert.h>
using namespace std;

//�����ģʽ��Object Pool Pattern��
// ����ز�������

//void 


//------------------------------------------------------------------------------
// header





template<class T, size_t nPoolSize>
class PPCObjectPool
{
private:
	class NodeHeader 
	{
	public:
		int nID;//�ڴ����
		int nRef; //���ô���
		NodeHeader* pNext; // ��һ��λ��
		bool bPool; //�Ƿ����ڴ����

	private:
		//Ԥ��
		char c1;
		char c2;
	};

	NodeHeader* _pHeader;
	//������ڴ滺������ַ
	char* _pBuffer;
	std::mutex _mutex;

public:

	PPCObjectPool()
	{
		_pBuffer = nullptr;
	}
	~PPCObjectPool()
	{
		if (!_pBuffer)
			delete[] _pBuffer;
	}

public:
	//��ʼ�������
	void initPool()
	{
		assert(nullptr == _pBuffer);
		if (nullptr != _pBuffer)
			return;

		//�������صĴ�С
		//string type = typeid(T).name();
		//int siz = sizeof(T);
		//int sizn = sizeof(NodeHeader); //24

		size_t realSize = sizeof(T) + sizeof(NodeHeader);
		size_t n = nPoolSize * realSize;
		_pBuffer = new char[n];
		//��ʼ�������
		_pHeader = (NodeHeader*)_pBuffer;
		_pHeader->bPool = true;
		_pHeader->nID = 1;
		_pHeader->nRef = 0;
		_pHeader->pNext = nullptr;
		NodeHeader* pTemp1 = _pHeader;
		for (size_t n = 2; n < nPoolSize; n++)
		{
			NodeHeader* pTemp2 = (NodeHeader*)(_pBuffer + (n * realSize));
			pTemp2->bPool = true;
			pTemp2->nID = n;
			pTemp2->nRef = 0;
			pTemp2->pNext = nullptr;
			pTemp1->pNext = pTemp2;
			pTemp1 = pTemp2;
		}
	}
	//�������
	void* newObjectMemory(size_t Size) 
	{
		if (nullptr == _pBuffer)
		{
			initPool();
		}
		std::lock_guard<std::mutex> lg(_mutex);

		NodeHeader* pReturn = nullptr;
		if (nullptr == _pHeader) 
		{
			pReturn = (NodeHeader*)new char(sizeof(T) + sizeof(NodeHeader));
			pReturn->bPool = false;
			pReturn->nID = -1;
			pReturn->nRef = 1;
			pReturn->pNext = nullptr;
		}
		else 
		{
			pReturn = _pHeader;
			_pHeader = _pHeader->pNext;
			//����
			assert(0 == pReturn->nRef);
			pReturn->nRef = 1;
		}
		//���ص��ڴ�ռ�Ҳû��NodeHeader�İ�ͷ
		return ((char*)pReturn + sizeof(NodeHeader));
	}
	//�ͷŶ���
	void deleteObjectMemory(void* pMem)
	{
		//��������ֵû��NodeHeader�İ�ͷ
		//���Դ�������ָ����Ҫ�����ƶ�sizeof��NodeHeader�����ֽ�
		NodeHeader* pBlock = (NodeHeader*)((char*)pMem - sizeof(NodeHeader));
		assert(1 == pBlock->nRef);
		if (pBlock->bPool)
		{
			std::lock_guard<std::mutex> lg(_mutex);
			if (--pBlock->nRef != 0)
				return;
			pBlock->pNext = _pHeader;
			_pHeader = pBlock;
		}
		else
		{
			if (--pBlock->nRef != 0)
				return;
			delete[] pBlock;
		}

	}
};


template <class T, size_t nPoolSize>
class PPCObjectPoolTemp
{
private:
	//typedef PPCObjectPool<T, nPoolSize> classTypePool;
	static PPCObjectPool<T, nPoolSize>& objectPool()
	{
		static PPCObjectPool<T, nPoolSize> sPool;//��̬��
		return sPool;
	}

public:
	void* operator new(size_t size)
	{
		return objectPool().newObjectMemory(size);
	}

	void operator delete(void* p)
	{
		objectPool().deleteObjectMemory(p);
	}

	
	template<typename ...Args> // ģ�庯��,���������ɴ���
	static T* createObject(Args ... args)
	{
		T* obj = new T(args...);
		return obj;
	}

	static void deleteObject(T* obj)
	{
		delete obj;
	}



};


//main ��������
//class A��B�������أ����û��������A����Bʱ������ֱ�Ӵӳ������룬��������������ʱ����Ҫֱ�����ڴ����롣
//�����е��ڴ�����ʱ��Ҳ�������ڴ����롣����Ҫ˼�����ڴ�����ƣ�


class A :public PPCObjectPoolTemp <A, 10> 
{
private:
	int Anum; 
public:
	A() 
	{
		Anum = 0;
		printf("A created\n");
	}
	~A() 
	{
		printf("A deleted\n");
	}
};


class B :public PPCObjectPoolTemp<B, 10> 
{
public:
	int num;
	//double dou=1;
	int num2;
public:
	B(int Num) 
	{
		num = Num;
		printf("B created\n");
	}

	~B() 
	{
		printf("B deleted\n");
	}
};


int main_pool() 
{
	int a = 123;
	char c = a; //the ascii of 123
	A* a2 = A::createObject();
	A::deleteObject(a2);

	B* bb = new B(2);
	delete bb;

	B* b2 = B::createObject(2);
	B::deleteObject(b2);

	return 0;

	//public class Client 
	//{
	//	public static void main(String[] args) 
	//	{ 
	//		ObjectPool pool = new ObjectPool(10, 50);        
	//		IPooledObject object = pool.borrowObject();        
	//		object.operation();        
	//		pool.returnObject(object);        
	//		System.out.println(); 
	//	}    
	//	//�������    
	//	interface IPooledObject 
	//	{        void operation();    }    
	//	//�������    
	//	static class ConcretePoolObject implements IPooledObject 
	//	{        
	//		public void operation() 
	//		{            
	//			System.out.println("doing");        
	//		}    
	//	}    
	//	//�����    
	//	static class ObjectPool 
	//	{        private int step = 10;                      
	//	//�����󲻹��õ�ʱ��ÿ�����ݵ�����        
	//	private int minCount;        
	//	private int maxCount;        
	//	private Vector<IPooledObject> returneds;     
	//	//����δ����Ķ���        
	//	private Vector<IPooledObject> borroweds;     
	//	//�����ѱ�����Ķ���        
	//	//��ʼ�������        
	//	public ObjectPool(int minCount,int maxCount)
	//	{            
	//		borroweds = new Vector<IPooledObject>();            
	//		returneds = new Vector<IPooledObject>();            
	//		this.minCount = minCount;           
	//		this.maxCount = maxCount;            
	//		refresh(this.minCount);        
	//	}        
	//	//��Ϊ�ڲ�״̬�߱������ԣ�������Ϊ����ļ�        
	//	public IPooledObject borrowObject() {            
	//		IPooledObject next = null;            
	//		if(returneds.size() > 0)
	//		{                
	//			Iterator<IPooledObject> i = returneds.iterator();                
	//			while (i.hasNext())
	//			{                    
	//				next = i.next();                    
	//				returneds.remove(next);                    
	//				borroweds.add(next);                    
	//				return next;                
	//			}            
	//		}
	//		else
	//		{                
	//			//�����ʣ��ɴ����Ķ�����                
	//			int count = (maxCount - minCount);                
	//			//ʣ��ɴ������������ڵ��ι̶������Ķ����� //���ٳ�ʼ��һ���̶������Ķ���                  
	//			refresh(count > step ? step : count);            
	//		}            
	//		return next;        }        
	//	//����Ҫʹ�õĶ���黹�ظ�����        
	//	public void returnObject(IPooledObject pooledObject)
	//	{            returneds.add(pooledObject);            
	//		if(borroweds.contains(pooledObject))
	//		{                
	//			borroweds.remove(pooledObject);            
	//		}
	//	}        
	//	private void refresh(int count)
	//	{            
	//		for (int i = 0; i < count; i++) 
	//		{                
	//				returneds.add(new ConcretePoolObject());            
	//		}        
	//	}    
	//	
	//}

}
