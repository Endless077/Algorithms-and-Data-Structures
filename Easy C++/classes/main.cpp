
#include <iostream>

using namespace std;

// Example 1

class A {

protected:

  uint size = 0;

  char* str = nullptr;

public:

  A() = default;

  A(uint num) : size(num) {
    cout << "A new object is created" << endl;
    // size = num;
    str = new char[num]();
  }

  ~A() {
    delete[] str;
    cout << "The object is destructed" << endl;
  }

  char& operator[](const uint idx) {
    return str[idx];
    // if (idx < size)
    // {
    //   return str[idx];
    // }
    // else
    // {
    //   throw out_of_range("An unexpected access occurred!");
    // }
  }

  bool operator==(const A& obj) const noexcept {
    if (size == obj.size)
    {
      for (uint i = 0; i < size; i++)
      {
        if (str[i] != obj.str[i])
        {
          return false;
        }
      }
      return true;
    }
    return false;
  }

  friend ostream& operator<<(ostream&, const A&);

};

ostream& operator<<(ostream& outstr, const A& a) {
  for (uint i = 0; i < a.size; i++) { cout << i << ": '" << a.str[i] << "' "; }
  return outstr;
}

// // Example 2
//
// class A {
// private:
//   bool flag = false;
// // protected:
// public:
//   A() { cout << "A new base object is created" << endl; }
//   ~A() { cout << "The base object is destructed" << endl; }
// };
//
// class B: public A {
// public:
//   B() { cout << "A new derived object is created" << endl; flag = false; }
//   ~B() { cout << "The derived object is destructed" << endl; }
// };

// // Example 3

// class A {
// public:
//   A() { cout << "A new base object is created" << endl; }
//   ~A() { cout << "The base object is destructed" << endl; } // virtual
// };
//
// class B: public A {
// public:
//   B() { cout << "A new derived object is created" << endl; }
//   ~B() { cout << "The derived object is destructed" << endl; }
// };

// // Example 4
//
// class A {
// protected:
//   uint size = 0;
// public:
//   A() { cout << "A new base object is created" << endl; }
//   ~A() { cout << "The base object is destructed" << endl; } // virtual
// };
//
// class B: public A { // virtual public A
// public:
//   B() { cout << "A new derived B object is created" << endl; size = 1; }
//   ~B() { cout << "The derived B object is destructed" << endl; }
// };
//
// class C: public A { // virtual public A
// public:
//   C() { cout << "A new derived C object is created" << endl; size = 2; }
//   ~C() { cout << "The derived C object is destructed" << endl; }
// };
//
// class D: public B, C  { // public C, B
// public:
//   D() { cout << "A new derived D object is created" << endl; }
//   ~D() { cout << "The derived D object is destructed" << endl; }
//   void PrintSize() { cout << size << endl; };
//   // void PrintSize() const noexcept { cout << B::size << " " << C::size << endl; };
// };

// // Example 5
//
// class A {
// protected:
//   uint val = 0;
// public:
//
//   A() { val++; std::cout << "A " << val << std::endl; }
//
//   A(const A& a) { val = a.val; val += 2000; std::cout << "Copy A " << val << std::endl; }
//
//   ~A() { std::cout << "Delete A " << val << std::endl; }
// };
//
// class B : public A { // virtual
// public:
//
//   B() { val += 10; std::cout << "B " << val << std::endl; } // Equivalently, you can add ": A()"
//
//   B(const B& b) : A(b) { val += 20000; std::cout << "Copy B " << val << std::endl; } // Remove ": A(b)"
//
//   ~B() { std::cout << "Delete B " << val << std::endl; }
// };
//
// class C : public B { // virtual
// public:
//
//   C() { val += 100; std::cout << "C " << val << std::endl; } // Equivalently, you can add ": B()".
//
//   C(const C& c) : B(c) { val += 200000; std::cout << "Copy C " << val << std::endl; } // Remove ": B(c)"; Add ": A(c)" when A is virtual in B
//
//   ~C() { std::cout << "Delete C " << val << std::endl; }
// };


int main() {

  // Example 1

  // A* ptr = new A();

  A var1(2); // 0, {}
  A var2(2);

  cout << "var1: " << var1 << endl;
  cout << "var2: " << var2 << endl;

  cout << "var1 ?= var2: " << (var1 == var2) << endl;

  var1[0] = 'x';

  cout << "var1: " << var1 << endl;
  cout << "var2: " << var2 << endl;

  cout << "var1 ?= var2: " << (var1 == var2) << endl;

  var2[1] = 'y';

  cout << "var1: " << var1 << endl;
  cout << "var2: " << var2 << endl;

  cout << "var1 ?= var2: " << (var1 == var2) << endl;

  var1[1] = 'y';
  var2[0] = 'x';

  cout << "var1: " << var1 << endl;
  cout << "var2: " << var2 << endl;

  cout << "var1 ?= var2: " << (var1 == var2) << endl;

  // // Example 2
  //
  // B* b = new B();
  // delete b;
  // return 0;

  // // Example 3
  //
  // A *a = new B();
  // delete a;
  // return 0;

  // // Example 4
  //
  // D d;
  // d.PrintSize();

  // // Example 5
  //
  // std::cout << std::endl;
  // C x;
  // std::cout << std::endl;
  // C y(x);
  // std::cout << std::endl;

  return 0;
}
