
#include <cstdlib>
#include <iostream>

using namespace std;

class A {
  public:
    A() {};
    ~A() = default;
};

void foo(A* test)
{
  printf("foo1 address: %p\n", test);
}

void foo1(A** test)
{
  printf("foo1-1 address: %p\n", *test);
  printf("foo1-2 address: %p\n", test);
}

int main()
{
  A a;
  A* ap;
  ap = &a;
  foo(&a);
  foo1(&ap);
  foo(ap);
  printf("address %p\n", &a);
  printf("address %p\n", ap);
  return 1;
}
