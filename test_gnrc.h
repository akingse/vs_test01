
//#define __declspec(method) __declspec_##method
//#define _declspec(method) __declspec_##method
// Generic


class IClass  //虚基类
{
public:
	virtual ~IClass()
	{
		//基类中的析构函数必须为虚函数，否则会出现对象释放错误
		//std::cout << "IClass destruct" << std::endl;
	}
	virtual IClass* _constructor() const = 0; //make_constructor构造
	virtual bool _is(const std::type_info& type) const = 0;
	//virtual std::type_info _as(const std::type_info& type) const = 0;
protected:
	virtual bool _copy_constructor(const IClass* src) = 0; //_deep_copy_from拷贝构造
	//virtual bool _operator_eq_copy(const IClass& src) = 0; //赋值
	//virtual bool _move_constructor(const IClass* src) = 0; //移动构造
	//virtual bool _operator_eq_rr(const IClass&& src) = 0; //移动赋值
};

template <typename T>
class Temp :public IClass //模板类
{
public:
	T m_imp;
	Temp(T src) : m_imp(src)
	{
		//1 T的拷贝构造必须在 Temp实现
		//2 Gnrc无法调用子类 操作函数，只能调用父类虚接口，以继承子类的实现
	}
	~Temp()
	{
		//std::cout << "Temp destruct" << std::endl;
	}
	inline IClass* _constructor() const override
	{
		return new Temp<T>(m_imp);
	}

protected:
	bool _copy_constructor(const IClass* src) override
	{
		if (!src->_is(typeid(T)))
			return false;
		const Temp<T>* ptr = dynamic_cast<const Temp<T>*>(src); 
		if (nullptr == ptr)
			return false;
		m_imp = ptr->m_imp;
		return true;
	}
	inline bool _is(const std::type_info& type) const override
	{
		return typeid(T) == type;
	}
	/*inline std::type_info _as(std::type_info type) const override
	{
		return type;
	}*/
};



class Gene
{
public:

	IClass* m_imp;
	template <typename T> //Gnrc 默认构造
	Gene(T src) : m_imp(new Temp<T>(src)) //Gnrc::Gnrc(T src)
	{
		//m_imp = new Temp<T>(src);
		//std::cout << "Constructor" << std::endl;
	}

	/*template <typename T>
	Gnrc(const T& src):m_imp(new Temp<T>(*(src.m_imp)))*/
	Gene(const Gene& lhs) :
		m_imp(lhs.m_imp->_constructor()) //拷贝构造
	{
		////m_imp = new IClass;
		//auto imp = (src.m_imp);
		//m_imp = (src.m_imp); // 拷贝值

		//m_imp = new Gnrc(*(src.m_imp));
		//std::cout << "Copy Constructor" << std::endl;
	}
	Gene& operator=(const Gene& lhs) noexcept //拷贝赋值
	{
		if (this != &lhs)
		{
			m_imp = lhs.m_imp->_constructor();
		}
		/*if (this == &src)
			return *this;
		delete m_imp;*/
		//std::cout << "operator=(const &)" << std::endl;
		return *this;
	}


	Gene(Gene&& rhs) noexcept : m_imp(rhs.m_imp)  //移动构造
	{
		rhs.m_imp = nullptr;
		//std::cout << "Move Constructor" << std::endl;
		//1 定义的类使用了资源并定义了移动构造函数和移动赋值运算符，
		//2 该变量即将不再使用；比如vector动态扩容
	}


	Gene& operator=(Gene&& src) noexcept //移动赋值
	{
		if (this != &src)
		{
			delete m_imp;
			m_imp = src.m_imp;
			src.m_imp = nullptr;
			//std::cout << "operator=(const &&)" << std::endl;
		}
		return *this;


		//if (this == &src)
		//	return *this;
		//delete m_imp;
		//m_imp = src.m_imp;
		//src.m_imp = nullptr;
		//std::cout << "operator=(const &&)" << std::endl;
		//return *this;
	}
	Gene* operator&() //对一般对象的取址函数
	{
		return this;
	}
	const Gene* operator&() const //对常对象的取址函数
	{
		return this;
	}

	~Gene() //Gnrc::~Gnrc()
	{
		if (m_imp)
		{
			delete m_imp;
			m_imp = nullptr;
		}
	}

	template <typename T>
	inline bool is() const
	{
		return m_imp->_is(typeid(T));
		//Temp<T>* ptr = dynamic_cast<Temp<T>*>(m_imp);
		//return ptr != nullptr;
	}

	template <typename T>
	inline T& as()
	{
		//return m_imp->_as(T);
		Temp<T>* ptr = dynamic_cast<Temp<T>*>(m_imp);
		return ptr->m_imp;
	}


	operator bool() const //重载 bool 隐式类型转换
	{
		return m_imp != nullptr;
	}

	bool operator<(const Gene& other) const
	{
		if (sizeof(*this) < sizeof(other))
			return true;
		else
			return false;
	}
	bool operator>(const Gene& other) const
	{
		if (sizeof(*this) > sizeof(other))
			return true;
		else
			return false;
	}

	bool operator==(const Gene& other) const
	{
		return false;
	}


public:
	//__declspec(dllexport) Gnrc();
	//__declspec(dllexport) virtual ~Gnrc();
	//__declspec(dllexport) Gnrc(const Gnrc& gnrc);
	//__declspec(dllexport) Gnrc(Gnrc&& gnrc);
	//__declspec(dllexport) Gnrc& operator= (const Gnrc& gnrc);
	//__declspec(dllexport) Gnrc& operator= (Gnrc&& gnrc);
	//__declspec(dllexport) operator bool() const;
	//template<typename T> inline Gnrc(const T& src);
	//template<typename T> inline T& as();
	//template<typename T> inline const T& as()const;
	//template<typename T> inline T as();
	//template<typename T> inline bool is() const;
	//template<typename T> static void enrol();
	//*Gnre::Gnre(std::type_index id, void* src, bool ref)
		
};

class Vec2
{
public:
	double x;
	double y;
};
class Vec3: public Vec2
	//struct Vec3
{
public:
	double x;
	double y;
	double z;
	double* pvalue = NULL; // 初始化为 null 的指针

	Vec3(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z)
	{
		pvalue = new double[5e2];
		//std::cout << "vec construct" << std::endl;
	}
	Vec3(const Vec3& vec) : x(vec.x), y(vec.y), z(vec.z)
	{
		std::cout << "copy construct" << std::endl;

	}
	bool operator==(Vec3 vec) //const
	{
		if (abs(vec.x - x) + abs(vec.y - y) + abs(vec.z - z) < 1e-10)
			return true;
		else
			return false;
	}


	operator bool() const
	{
		if (abs(x) + abs(y) + abs(z)<PL_A)
			return true;
		else
			return false;
	}

	~Vec3()
	{
		delete[] pvalue;
		//std::cout << "vec destruct" << std::endl;
	}
	void test()
	{

	}
	void test() const
	{
		//前面使用const 表示返回值为const
		//后面加 const表示函数不可以修改class的成员
	}

};

using GeneList = std::vector<Gene>;
using GeneDict = std::map<Gene, Gene>;


int test_gnrc_int(int n); //for google test
