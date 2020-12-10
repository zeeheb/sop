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

typedef struct
{
  int idx
} thread_arg, *ptr_thread_arg;

long aux;
int roundA, lin, col, search;
int **mat;
int achou = 0;

void *buscaNaMatriz(void *arg)
{

  int *n = (int *)arg;
  long i;

  switch (*n)
  {
  case 1:
    // sleep(1);
    while (achou != 1)
    {
      for (int i = 0; i < lin; i++)
      {
        for (int j = 0; j < col; j++)
        {
          if (mat[i][j] == search)
          {
            achou = 1;
            printf("Achou no 1\n");
            // printf("achou case 1 em [%d] [%d]\n", i + 1, j + 1);
          }
        }
      }
    }
    // printf("1");
    break;
  case 2:
    // sleep(1);
    while (achou != 1)
    {
      for (int i = 0; i < lin; i++)
      {
        for (int j = col - 1; j >= 0; j--)
        {
          if (mat[i][j] == search)
          {
            achou = 1;
            printf("Achou no 2\n");
            // printf("achou case 2 em [%d] [%d]\n", i + 1, j + 1);
          }
        }
      }
    }
    break;
  case 3:
    while (achou != 1)
    {
      for (int i = lin - 1; i >= 0; i--)
      {
        for (int j = 0; j < col; j++)
        {
          if (mat[i][j] == search)
          {
            achou = 1;
            printf("Achou no 3\n");
            // printf("achou case 3 em [%d] [%d]\n", i + 1, j + 1);
          }
        }
      }
    }
    break;

  case 4:
    while (achou != 1)
    {
      for (int i = lin - 1; i >= 0; i--)
      {
        for (int j = col - 1; j >= 0; j--)
        {
          if (mat[i][j] == search)
          {
            achou = 1;
            printf("Achou no 4\n");
            // printf("achou case 4 em [%d] [%d]\n", i + 1, j + 1);
          }
        }
      }
    }
    break;
  default:
    break;
  }

  // for (i = 0; i < MAX; i++)
  // {
  //   down(&mutex);
  //   aux++; /* r1 <- n ; add r1, 1 ; n <- r1 */
  //   up(&mutex);
  // }
  // printf("\n");
  pthread_exit(NULL);
}

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
  // pthread_t t1, t2, t3, t4;
  pthread_t threads[4];
  thread_arg arguments[4];
  int rc;

  // le args

  int m = atoi(argv[1]);
  int n = atoi(argv[2]);
  int r = atoi(argv[3]);
  lin = m;
  col = n;

  //constroi matriz

  // int **mat;

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
  // int max = getMax(m, n);
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

  // for (int i = 0; i < m; i++)
  // {
  //   for (int j = 0; j < n; j++)
  //   {
  //     printf(" %d ", mat[i][j]);
  //   }
  //   printf("\n");
  // }

  for (int i = 0; i < r; i++)
  {
    srand(time(NULL));

    // cria número aleatorio para procurar
    search = rand() % (m * n - 1);
    search++;

    // printf("search: %d\n", search);

    aux = 0;
    sem_init(&mutex, 0, 1); /* mutex = 1 */
    achou = 0;
    for (int i = 0; i < NTHREADS; i++)
    {
      arguments[i].idx = i + 1;
      pthread_create(&(threads[i]), NULL, buscaNaMatriz, &(arguments[i]));
    }

    for (int i = 0; i < NTHREADS; i++)
    {
      pthread_join(threads[i], NULL);
    }
  }

  return 0;
}

// compile with cc -o main main.c -pthread
// for i in {1..2000} ; do ./main ; done >logmain
// sort <logmain | uniq -c
