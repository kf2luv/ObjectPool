#include "ObjPool.hh"
#include <vector>
using std::cout;
using std::endl;

class TestType {
   public:
    TestType() : a(1), b(2), c(3) {}

    TestType(int x, int y, int z) : a(x), b(y), c(z) {}

   public:
    int a;
    int b;
    int c;
};

struct TreeNode
{
	int _val;
	TreeNode* _left;
	TreeNode* _right;

	TreeNode()
		:_val(0)
		, _left(nullptr)
		, _right(nullptr)
	{}
};

void TestObjectPool()
{
	// 申请释放的轮次
	const size_t Rounds = 5;

	// 每轮申请释放多少次
	const size_t N = 1000000;

	std::vector<TreeNode*> v1;
	v1.reserve(N);

	size_t begin1 = clock();
	for (size_t j = 0; j < Rounds; ++j)
	{
		for (int i = 0; i < N; ++i)
		{
			v1.push_back(new TreeNode);
		}
		for (int i = 0; i < N; ++i)
		{
			delete v1[i];
		}
		v1.clear();
	}

	size_t end1 = clock();

	std::vector<TreeNode*> v2;
	v2.reserve(N);

	ObjectPool<TreeNode> TNPool;
	size_t begin2 = clock();
	for (size_t j = 0; j < Rounds; ++j)
	{
		for (int i = 0; i < N; ++i)
		{
			v2.push_back(TNPool.New());
		}
		for (int i = 0; i < N; ++i)
		{
			TNPool.Delete(v2[i]);
		}
		v2.clear();
	}
	size_t end2 = clock();

	cout << "new cost time:" << end1 - begin1 << endl;
	cout << "object pool cost time:" << end2 - begin2 << endl;
}

int main() {
    // ObjectPool<TestType> objPool;

    // TestType* tt = objPool.New();
    // std::cout << "a:" << tt->a << std::endl;
    // std::cout << "b:" << tt->b << std::endl;
    // std::cout << "c:" << tt->c << std::endl;

    // TestType* tt1 = objPool.New(11, 22, 33);
    // std::cout << "a:" << tt1->a << std::endl;
    // std::cout << "b:" << tt1->b << std::endl;
    // std::cout << "c:" << tt1->c << std::endl;

    // TestType* tt1 = objPool.New();
    // TestType* tt2 = objPool.New();
    // TestType* tt3 = objPool.New();//扩容

    // objPool.Delete(tt);
    // TestType* tt4 = objPool.New();

    TestObjectPool();

    return 0;
}