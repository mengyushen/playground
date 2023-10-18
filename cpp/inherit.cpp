#include <string>
#include <iostream>


class Fruit {
  private:
    std::string name_;
    std::string color_;
  public:
    Fruit(const std::string& n, const std::string& c): name_{n}, color_{c} {
      doSomething();
    }

    const std::string getName() const { return name_; }
    const std::string getColor() const { return color_; }

    virtual void doSomething() {
      std::cout << "do something\n";
    }
};

class Apple : public Fruit {
  private:
    double fiber_;
  public:
    Apple(const std::string& n, const std::string& c, double f)
      : Fruit(n, c), fiber_{f} {}

    double getFiber() const { return fiber_; }

    virtual void doSomething() const {
      std::cout << "Apple do something\n";
    }
};

class Banana : public Fruit {
  public:
    Banana(const std::string& n, const std::string& c)
      : Fruit(n, c) {}
};

std::ostream& operator<<(std::ostream &out, const Fruit &b)
{
  out << "Fruit(" << b.getName() << ", " << b.getColor() << ")";
  return out;
}

std::ostream& operator<<(std::ostream &out, const Apple &a)
{
  out << "Apple(" << a.getName() << ", " << a.getColor() << ", " << a.getFiber() << ")";
  return out;
}

std::ostream& operator<<(std::ostream &out, const Banana &a)
{
  out << "Banana(" << a.getName() << ", " << a.getColor() << ")";
  return out;
}

// Apple(Red delicious, red, 4.2)
// Banana(Cavendish, yellow)

int main()
{
  const Apple a{ "Red delicious", "red", 4.2 };
  a.doSomething();
  std::cout << a << '\n';

  const Banana b{ "Cavendish", "yellow" };
  std::cout << b << '\n';

  return 0;
}
