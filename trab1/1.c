/* Programa para mostrar sincronizacao de threads. O programa deveria
 *  imprimir "SOP", mas isso nem sempre ocorre.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <pthread.h>
#include <semaphore.h>

#define down(x) sem_wait(x)
#define up(x) sem_post(x)

sem_t sA, sB, sC, sM, sD;
int type = 0;


void *a(void *argp)
{
    while(1) {


      down(&sC); // printou CA
      printf("O");
      up(&sA); // vai printar S

    }
     pthread_exit(NULL);
}

void *b(void *argp)
{
  
    while(1) {

      printf("CA");

      up(&sC); // vai printar outra coisa

      down(&sB);
      printf("!\n");
    }

    pthread_exit(NULL);
}

void *c(void *argp)
{
   while(1) {
     
     down(&sA); //printou O
     printf("S");
     up(&sB);

    }
     pthread_exit(NULL);
}     

int main(void)
{
     pthread_t t1, t2, t3;
     int rc;

     sem_init(&sA, 0, 0);     
     sem_init(&sB, 0, 0);
     sem_init(&sC, 0, 0);
     sem_init(&sM, 0, 1);
     sem_init(&sD, 0, 0);


     rc = pthread_create(&t1, NULL, a, NULL);   assert(rc == 0);
     rc = pthread_create(&t2, NULL, b, NULL);   assert(rc == 0);
     rc = pthread_create(&t3, NULL, c, NULL);   assert(rc == 0);
     rc = pthread_join(t1, NULL);   assert(rc == 0);
     rc = pthread_join(t2, NULL);   assert(rc == 0);
     rc = pthread_join(t3, NULL);   assert(rc == 0);
     putchar('\n');
     return 0;
}
