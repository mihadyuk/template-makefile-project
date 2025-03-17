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

typedef struct CUSTOM_LIST_T {
    void *next;
    int value;
} custom_list_t;



custom_list_t item_3 = {nullptr, 3};
custom_list_t item_2 = {&item_3, 2};
custom_list_t item_1 = {&item_2, 1};

custom_list_t *reverse(custom_list_t *list) {

    custom_list_t *prev = nullptr;
    custom_list_t *curr = list;
    custom_list_t *next = nullptr;

    while (curr != nullptr) {
      next = (custom_list_t *)curr->next; // Store the next node
      curr->next = prev; // Reverse the current node's pointer
      prev = curr;       // Move the previous pointer forward
      curr = next;       // Move the current pointer forward
    }

    return prev;
}

int main(int argc, char *argv[]) {

  custom_list_t *first = reverse(&item_1);
  //custom_list_t *first = &item_1;

  if (first) {
      while (first) {
          printf("item %d\n", first->value);
          first = (custom_list_t *)first->next;
      }
  }
  else
      printf("no list");
  return 0;


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


