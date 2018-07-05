#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "config.h"

#if defined (OVERRIDE_NEW_DELETE)

static void *my_alloc(size_t size){
      void *ptr = malloc(size);
      printf("p: %p, size: %lu \r\n", ptr, size);
      return ptr;
}

static void my_free(void *ptr) {
      free(ptr);
      printf("p: %p\r\n", ptr);
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
     printf("delete ");
     my_free(ptr);
}

void operator delete[](void *ptr) {
     printf("delete[] ");
     my_free(ptr);
}

#endif
