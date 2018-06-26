#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

static void *my_alloc(size_t size){
      void *ptr = malloc(size);
      printf("alloc: size: %lu, p: %p \r\n", size, ptr);
      return ptr;
}

static void my_free(void *ptr) {
      free(ptr);
      printf("free: %p\r\n", ptr);
}

void* operator new (size_t size){
      printf("new ");
      return my_alloc(size);
}

void* operator new[] (size_t size){
      printf("new[] ");
      return my_alloc(size);
}

void operator delete(void *ptr) {
     printf("delete: ");
     my_free(ptr);
}

void operator delete[](void *ptr) {
     printf("delete[]: ");
     my_free(ptr);
}
