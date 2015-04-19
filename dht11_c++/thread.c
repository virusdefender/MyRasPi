/* thread.c  */

#include <pthread.h>
#include <stdio.h>
/*
int pthread_create(pthread_t * thread, pthread_attr_t * attr, void * (*start_routine)(void *), void * arg)
*/

void* tprocess1(void* args) {
    // while(1) {
          printf("tprocess1\n");
      //  }
    return NULL;
}

void* tprocess2(void* args) {
      //  while(1) {
           printf("tprocess2\n");
       //}
      return NULL;
}


int main() {
     pthread_t t1;
     pthread_t t2;
     pthread_create(&t1,NULL,tprocess1,NULL);
     pthread_create(&t2,NULL,tprocess2,NULL);
     pthread_join(t1,NULL);
     return 0;
}


