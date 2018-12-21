class A {
  A() : a{false} {}

private:
  bool a;
}

class B : public A {
  B() : A(), b{false} {}

private:
  bool b;
}

class C : public A {
  C() : A(), c{false} {};

private:
  bool c;
}

int main() {
  B tb = new B();
  tb.a = true;

  C return 0;
}
