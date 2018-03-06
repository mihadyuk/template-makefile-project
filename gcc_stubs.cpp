#include <stdio.h>
#include <errno.h>

#include "gcc_stubs.hpp"

/**
 *
 */
#ifdef __cplusplus
extern "C" {
#endif
void _exit(int status){
   (void) status;
   while(1){}
}
#ifdef __cplusplus
}
#endif

/**
 *
 */
#ifdef __cplusplus
extern "C" {
#endif
pid_t _getpid(void){
   return 1;
}
/**
 *
 */
void _open_r(void){
  return;
}
void _fstat_r(void) {}
void _sbrk_r(void) {}
void _write_r(void) {}
void _close_r(void) {}
void _isatty_r(void) {}
void _lseek_r(void) {}
void _read_r(void) {}

#ifdef __cplusplus
}
#endif

/**
 *
 */
#undef errno
extern int errno;
#ifdef __cplusplus
extern "C" {
#endif
int _kill(int pid, int sig) {
  (void)pid;
  (void)sig;
  errno = EINVAL;
  return -1;
}
#ifdef __cplusplus
}
#endif



/**
 *
 */
#ifdef __cplusplus
extern "C" {
#endif
  void __cxa_pure_virtual() { }
#ifdef __cplusplus
}
#endif
