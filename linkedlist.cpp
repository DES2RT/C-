#include <iostream>
#include <string>
#include <functional>


void Expressions()
{
	int i = 2;
	std::cout << "i=" << i << "\n";
	i = i++;
	std::cout << "after 'i = i++;',  the value of i is " << i << "\n";

	std::cout << "what happens if we have an array 'a[i] = a[i++];'?\n";
	double trouble[] = { 1, 2, 3, 4, 5 };
	std::cout << "double trouble:"; for (auto e : trouble) std::cout << e; std::cout << "\n";

	i = 2;
	std::cout << "i=" << i << "\n";
	trouble[i] = trouble[i++];
	std::cout << "i=" << i << "\n";

	std::cout << "double trouble:"; for (auto e : trouble) std::cout << e; std::cout << "\n";
} // Expressions
/*
void SimpleDIYPrintf(const char *fmt, ...)  // a variable argument function (variadic function)
{
	va_list va;           // allocate a va_list variable 'va'
	va_start(va, fmt);    // initialize 'va' to start after 'fmt'

	for (const char *f = fmt; *f; f++) { // process fmt string, one char at a time
		if (*f == '%') { // process format character
			f++;  // want character after %
			double d;
			int    i;
			char   c;
			char  *s;
			switch (*f) {
			case 'f': d = va_arg(va, double); std::cout << d; break;
			case 's': s = va_arg(va, char*);  std::cout << s; break;
			case 'c': c = va_arg(va, int);    std::cout << c; break;  // use 'int' to fetch 'char' variable
			case 'd': i = va_arg(va, int);    std::cout << i; break;
			default: std::cout << '%' << *f; break; // don't understand format charcter, print it along with %
			}
		}
		else { // not a format character, just print it
			std::cout << *f;
		}
	}
	va_end(va); // clean up
}*/

void Functions()
{
	// 1. C pointer to a function - OOP144
	double(*f)(double arg);  // a pointer to a function that returns a dounble and takes a double as an argument

#define F(FUN,ARG) f=FUN; std::cout <<  #FUN "(" #ARG ")=" << f(ARG) << "\n"; 
	F(sqrt, 1000.)
	F(fabs, -1000.)
#undef F

		// 2. C++ pointer to a function
		std::function<double(double)> g;
#define G(FUN,ARG) g=FUN; std::cout <<  #FUN "(" #ARG ")=" << g(ARG) << "\n"; 
//G(sqrt, 81.)
//	G(fabs, -123.)
#undef G

		// 3. function objects or functors  (overload operator() for a class)
	class MyFunctionObject {
	public:
		int operator() (int arg) { return 2 * arg; }
	};
	MyFunctionObject mfo;
	std::cout << "mfo(99)=" << mfo(99) << "\n";

	// 4. lambda functions
	auto lambda = [](int arg) { return 3 * arg; };

	std::cout << "lambda(99)=" << lambda(99) << "\n";

	//SimpleDIYPrintf("variable argument function SimpleDIYPrintf: char '%c', string '%s', int '%d', float '%f'\n", '?', "QWERTY", 99, 199.);
} // Functions

void ErrorHandling()
{
	try {
		double trouble = 30 / 1.001;
	}
	catch (const std::string& e) {
		std::cout << e << "\n";
	}
	catch (...) {
		std::cout << "Unknown error\n";
	}

	try {
		for (int i = 0; i < 10; i++) {
			if (i == 7) throw std::string("i is 7");
		}
	}
	catch (const std::string& e) {
		std::cout << e << "\n";
	}
	catch (...) {
		std::cout << "Unknown error\n";
	}
} // ErrorHandling

template <class T>  // templates have to be global
class DIYStack {
	class Node {
	public: T     data;
			Node *link;
	} *head;

public:
	DIYStack() : head(nullptr) {}
	void Insert(T d)
	{
		Node* n = new Node;
		n->data = d;
		n->link = head;
		head = n;
	}
	void Print()
	{
		for (Node* p = head; p; p = p->link)
			std::cout << p->data << "\n";
	}
	size_t Size()
	{
		size_t size = 0;
		for (Node* p = head; p; p = p->link)
			size++;
		return size;
	}

};


void LinkedLists()
{
	DIYStack<std::string> s;
	s.Insert("rat");
	s.Insert("ox");
	s.Insert("tiger");
	s.Insert("rabbit");
	s.Insert("dragon");
	s.Insert("snake");
	s.Insert("horse");
	s.Insert("sheep");
	s.Insert("monkey");
	s.Insert("rooster");
	s.Insert("dog");
	s.Insert("pig");

	std::cout << s.Size() << " Chinese animals - NOTE print order is opposite of insert order\n";
	std::cout << "'rat' was inserted first. 'pig' was inserted last.\n";
	std::cout << "This list is a stack, a LILO: last in, last out.\n";
	s.Print();
} // LinkedLists

int main() {
	Expressions();
	Functions();
	ErrorHandling();
	LinkedLists();
}