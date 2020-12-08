/* Exercicio 6 da lista de pthreads */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#define down(x) sem_wait(x)
#define up(x) sem_post(x)

sem_t mutex;

#define MAX 2000
#define NTHREADS 4

// long aux;

// void *f1(void *argp)
// {
//   long i;
//   for (i = 0; i < MAX; i++)
//   {
//     down(&mutex);
//     n++; /* r1 <- n ; add r1, 1 ; n <- r1 */
//     up(&mutex);
//   }
//   pthread_exit(NULL);
// }

// void *f2(void *argp)
// {
//   long i;
//   for (i = 0; i < MAX; i++)
//   {
//     down(&mutex);
//     n--;
//     up(&mutex);
//   }
//   pthread_exit(NULL);
// }

int getMax(int a, int b)
{
  if (a >= b)
  {
    return a;
  }
  else
  {
    return b;
  }
}

int main(int argc, char *argv[])
{
  pthread_t t1, t2, t3, t4;
  int rc;

  // le args

  int m = atoi(argv[1]);
  int n = atoi(argv[2]);
  int r = atoi(argv[3]);

  //constroi matriz

  int **mat;

  mat = malloc(m * sizeof(int *));

  for (int k = 0; k < m; k++)
  {
    mat[k] = malloc(n * sizeof(int));
  }

  int count = 1;

  for (int i = 0; i < m; i++)
  {
    for (int j = 0; j < n; j++)
    {
      mat[i][j] = count;
      count++;
    }
  }

  // rearrranjo
  int max = getMax(m, n);
  srand(time(NULL));

  for (int i = 0; i < m; i++)
  {
    for (int j = 0; j < n; j++)
    {

      int rd = (rand() % (m));
      int rd2 = (rand() % (n));
      int aux = mat[i][j];
      int aux2 = mat[rd][rd2];

      mat[i][j] = aux2;
      mat[rd][rd2] = aux;
    }
  }

  // print matriz

  for (int i = 0; i < m; i++)
  {
    for (int j = 0; j < n; j++)
    {
      printf(" %d ", mat[i][j]);
    }
    printf("\n");
  }

  // aux = 0;
  // sem_init(&mutex, 0, 1); /* mutex = 1 */
  // rc = pthread_create(&t1, NULL, f1, NULL);
  // assert(rc == 0);
  // rc = pthread_create(&t2, NULL, f2, NULL);
  // assert(rc == 0);
  // rc = pthread_create(&t3, NULL, f2, NULL);
  // assert(rc == 0);
  // rc = pthread_create(&t4, NULL, f2, NULL);
  // assert(rc == 0);
  // rc = pthread_join(t1, NULL);
  // assert(rc == 0);
  // rc = pthread_join(t2, NULL);
  // assert(rc == 0);
  // rc = pthread_join(t3, NULL);
  // assert(rc == 0);
  // rc = pthread_join(t4, NULL);
  // assert(rc == 0);
  // printf("%ld\n", aux);
  return 0;
}

// compile with cc -o main main.c -pthread
// for i in {1..2000} ; do ./main ; done >logmain
// sort <logmain | uniq -c
