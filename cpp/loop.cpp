#include <iostream>

void unreachable()
{
  std::cout << "Hello World" << std::endl;
}

int main()
{
  while(1);
}

