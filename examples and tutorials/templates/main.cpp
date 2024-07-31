
#include <iostream>

using namespace std;

// template <typename Data>
// class A;
//
// template <typename Data>
// ostream& operator<< (ostream& outstr, const A<Data>& a);

template <typename Data>
class A {

private:

protected:

  uint size = 0;

  Data* str = nullptr;

public:

  A() = default;

  A(uint num) : size(num) {
    cout << "A new object is created" << endl;
    str = new Data[num]();
  }

  ~A() {
    delete[] str;
    cout << "The object is destructed" << endl;
  }

  Data& operator[](const uint idx) {
    return str[idx];
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

  template <typename DataX>
  friend ostream& operator<<(ostream&, const A<DataX>&);

  // friend ostream& operator<< <>(ostream&, const A<Data>&);

};

template <typename Data>
ostream& operator<< (ostream& outstr, const A<Data>& a) {
  for (uint i = 0; i < a.size; i++) { cout << i << ": '" << a.str[i] << "' "; }
  return outstr;
}


int main() {

  A<char> var1(2);
  A<char> var2(2);

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

  cout << endl << endl;

  A<int> var3(2);
  A<int> var4(2);

  cout << "var3: " << var3 << endl;
  cout << "var4: " << var4 << endl;

  cout << "var3 ?= var4: " << (var3 == var4) << endl;

  var3[0] = 10;

  cout << "var3: " << var3 << endl;
  cout << "var4: " << var4 << endl;

  cout << "var3 ?= var4: " << (var3 == var4) << endl;

  var4[1] = 5;

  cout << "var3: " << var3 << endl;
  cout << "var4: " << var4 << endl;

  cout << "var3 ?= var4: " << (var3 == var4) << endl;

  var3[1] = 5;
  var4[0] = 10;

  cout << "var3: " << var3 << endl;
  cout << "var4: " << var4 << endl;

  cout << "var3 ?= var4: " << (var3 == var4) << endl;

  return 0;
}
