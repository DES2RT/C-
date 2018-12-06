// GB simple code to demonstrate:
//   1. copy constructor         (deep copy)
//   2. assignment operator      (deep copy)
//   3. move constructor         (no deep copy, move the pointers)
//   4. move assignment operator (no deep copy, move the pointers)
//   5. destructor

#include <iostream>
#include <string>
using namespace std;

int main1(int argc, char**argv)
{
  class X {
    size_t  size;
    double* data;
  public:
    ~X()                            // destructor
    { 
      print("dtor"); 
      if(data) delete [] data; 
    }
  
    X() : size(0), data(nullptr)
    { 
      print("ctor"); 
    }
  
    X(size_t s) : size(s), data(new double[s])
    {
      print("ctor"); 
    }
  
    void print() const { cout << "size = " << size << ", " << size * sizeof(*data) * 1e-9 << " GB" << " \n"; }
  
    void print(const char* txt) const { cout << txt << " "; print(); }
  
    X(X& rhs)                       // OOP244 copy ctor
    {
      data = nullptr; // must do this or operator= might segfault deleting garbage
      *this = rhs;    // use assignment op to do the copy
    }
  
    X& operator=(const X& rhs)      // OOP244 assigment operator
    {
      if(this != &rhs) {
        print("deleting ");
        if(data) delete [] data;
        size = rhs.size;
        data = new double[size];
        print("deep copy of ");
        for(int i = 0; i < size; i++)   // deep copy
          data[i] = rhs.data[i];
      }
      return *this;
    }
  
  
    X(X&& rhs)                      // OOP345 move constructor
    {
      data = rhs.data;              // move pointers
      size = rhs.size;
      rhs.data = nullptr;           // zombie
      rhs.size = 0;
    }
  
    X&& operator=(X&& rhs)          // OOP345 move assignment operator
    {
      if(this != &rhs) {
        if(data) delete [] data;
        data = rhs.data;            // move pointers
        size = rhs.size;
        rhs.data = nullptr;         // zombie
        rhs.size = 0;
      }
      return std::move(*this);
    }
   
  };

  X x(1 * 125 * 1000000);

  X y(2 * 125 * 1000000);

  x = x;
  cout << "x=y\n";
  x = y;

  cout << "X z(x)\n";
  X z(x);

  cout << "X a(std::move(x))\n";
  X a( std::move(x) );
  a.print("a ");
  x.print("x ");

  cout << "x = std::move(a);\n";
  x = std::move(a);
  x.print("x ");
  a.print("a ");
  return 0;
}

int main2(int argc, char**argv)
{
  class XHistory {
    size_t  size;
    double* data;
    string  history;
  public:
    ~XHistory()                            // destructor
    { 
      cout << "dtor: " << history << "\n"; 
      if(data) delete [] data; 
    }
  
    XHistory(string n) : size(0), data(nullptr), history(n) 
    { 
      cout <<  n << " ctor\n"; 
    }
  
    XHistory(size_t s,string n) : size(s), data(new double[s]), history(n) 
    {
    }
  
    void print() { cout << "size = " << size <<  "  " <<  history << "\n"; }
  
    XHistory(XHistory& rhs)                       // OOP244 copy ctor
    {
      data = nullptr; // must do this or operator= might segfault deleting garbage
      *this = rhs;    // use assignment op to do the copy
    }
  
    XHistory& operator=(const XHistory& rhs)      // OOP244 assigment operator
    {
      if(this != &rhs) {
        cout << "deleting " << sizeof(*data) * rhs.size << " bytes\n";
        if(data) delete [] data;
        size = rhs.size;
        data = new double[size];
        history += "assignment op of [" + rhs.history + "] ";
        cout << "deep copy of " << sizeof(*data) * size << " bytes\n";
        for(int i = 0; i < size; i++)   // deep copy
          data[i] = rhs.data[i];
      }
      return *this;
    }
  
  
    XHistory(XHistory&& rhs)                      // OOP345 move constructor
    {
      data = rhs.data;              // move pointers
      size = rhs.size;
      history += "move ctor of [" + rhs.history + "] ";
      rhs.data = nullptr;
      rhs.size = 0;
    }
  
    XHistory&& operator=(XHistory&& rhs)          // OOP345 move assignment operator
    {
      if(this != &rhs) {
        if(data) delete [] data;
        data = rhs.data;            // move pointers
        size = rhs.size;
        history += "move assignment op of [" + rhs.history + "] ";
        rhs.data = nullptr;
        rhs.size = 0;
      }
      return std::move(*this);
    }
   
  };

  XHistory x(1 * 125 * 1000000,"x");
  x.print();

  XHistory y(2 * 125 * 1000000,"y");
  y.print();

  x = x;
  cout << "x=y\n";
  x = y;
  x.print();

  cout << "XHistory z(x)\n";
  XHistory z(x);
  z.print();

  cout << "XHistory a(std::move(x))\n";
  XHistory a( std::move(x) );
  a.print();
  x.print();

  cout << "x = std::move(a);\n";
  x = std::move(a);
  x.print();
  a.print();
  return 0;
}

void print(int&   x) { cout << "print l-value: " << x << "\n"; }
void print(int&&  x) { cout << "print r-value: " << x << "\n"; }

template <class T>
void betterPrint(T&   x) { cout << "betterPrint l-value: " << x << "\n"; }

template <class T>
void betterPrint(T&&  x) { cout << "betterPrint r-value: " << x << "\n"; }

int main(int argc, char**argv)
{
  main1(argc, argv);
  main2(argc, argv);

  int xyz = 27;
  print(9); //  can we say 9 = ... ?
  print(9+5); //  can we say 9+5 = ... ?
  print(xyz); //  can we say xyz = ... ?
  print(std::move(xyz)); //  can we say xyz = ... ?
  print(xyz); //  can we say xyz = ... ?

  betterPrint(9.9);
  double trouble = 9;
  betterPrint(trouble);
  char broiled = '?';
  betterPrint(broiled);
  betterPrint("123456789 asdfghjk");
  betterPrint(std::move(broiled));
  betterPrint(broiled);

  return 0;
}
