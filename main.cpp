#include <assert.h>
#include <iostream>
#include <stdio.h>
#include <stdint.h>

using namespace std;

class Base {
public:
	Base() { cout << "Base() \n"; }
	virtual ~Base() { cout << "~Base() \n"; }
	virtual void vf1() { cout << "Base::vf1() \n"; }
	virtual void vf2() { cout << "Base::vf2() \n"; }
	void f() { cout << "Base::f() \n"; }
};

class Derived : public Base {
public:
	Derived() { cout << "Derived() \n";}
	~Derived() { cout << "~Derived() \n";}
	void vf1() override {cout << "Derived::vf1() \n";};
	void vf2() override {cout << "Derived::vf2() \n";};
};

class A {
public:
	A() {
		f1();
	}
	~A() {
		f1();
	}
	virtual void f1() {
		cout << "A::f1()" << endl;
	}
};

class B : public A {
public:
	B() {
		f1();
	}
	~B() {
		f1();
	}
	void f1() override {
		cout << "B::f1()" << endl;
	}
};

int f(int *a) {
    int b;

    if (!a)
       f(&b);
    return (&b > a);
}

static uint8_t test_large_array[1024 * 1024 * 128L] = {1, 2, 3, 4};

int main(int argc, char *argv[]) {

  for (uint32_t i = 0; i < sizeof(test_large_array) / sizeof(test_large_array[0]); i++) {
      //test_large_array[i] = 0;
      printf("%d", test_large_array[i]);
  }
  //printf(f(0)? "true \n" : "false \n");
  //std::cout << "sizeof: " << sizeof(Derived) << "\r\n";
  //Derived d;
  //A *a = new A();
  //delete a;

  //B *b = new B();
  //delete b;

#if 0
  try {
	  for (char i = 0;;) {
		  cout << 1 / --i << flush;
	  }
  }
  catch(...) {
	  cout << "end";
  }
#endif
  //std::cout << "\n template makefile project \n";
  return 0;
}


