#include "ObjPool.hh"

class TestType{
public:
    int a;
    int b;
    int c;
};

int main(){
    ObjectPool<TestType> objPool;

    TestType* tt = objPool.New();
    tt->a = 1;
    tt->b = 2;
    tt->c = 3;

    TestType* tt1 = objPool.New();
    TestType* tt2 = objPool.New();
    TestType* tt3 = objPool.New();//扩容

    objPool.Delete(tt);
    TestType* tt4 = objPool.New();

    return 0;
}