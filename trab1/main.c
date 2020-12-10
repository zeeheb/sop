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
int count1 = 0, count2 = 0, count3 = 0, count4 = 0;
int **mat;
int achou = 0;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t barr;

void *buscaNaMatriz(void *arg)
{

  int *n = (int *)arg;

  switch (*n)
  {
  case 1:
    pthread_barrier_wait(&barr);

    while (achou != 1)
    {
      for (int i = 0; i < lin; i++)
      {
        for (int j = 0; j < col; j++)
        {
          if (mat[i][j] == search)
          {
            pthread_mutex_lock(&mtx);
            if (achou == 0)
            {
              achou = 1;
              count1++;
            }
            pthread_mutex_unlock(&mtx);
          }
        }
      }
    }
    break;
  case 2:
    pthread_barrier_wait(&barr);

    while (achou != 1)
    {
      for (int i = 0; i < lin; i++)
      {
        for (int j = col - 1; j >= 0; j--)
        {
          if (mat[i][j] == search)
          {
            pthread_mutex_lock(&mtx);

            if (achou == 0)
            {
              achou = 1;
              count2++;
            }
            pthread_mutex_unlock(&mtx);
          }
        }
      }
    }
    break;
  case 3:
    pthread_barrier_wait(&barr);

    while (achou != 1)
    {
      for (int i = lin - 1; i >= 0; i--)
      {
        for (int j = 0; j < col; j++)
        {
          if (mat[i][j] == search)
          {
            pthread_mutex_lock(&mtx);
            if (achou == 0)
            {
              achou = 1;
              count3++;
            }
            pthread_mutex_unlock(&mtx);
          }
        }
      }
    }
    break;

  case 4:
    pthread_barrier_wait(&barr);

    while (achou != 1)
    {
      for (int i = lin - 1; i >= 0; i--)
      {
        for (int j = col - 1; j >= 0; j--)
        {
          if (mat[i][j] == search)
          {
            pthread_mutex_lock(&mtx);
            if (achou == 0)
            {
              achou = 1;
              count4++;
            }
            pthread_mutex_unlock(&mtx);
          }
        }
      }
    }
    break;
  default:
    break;
  }

  pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
  // pthread_t t1, t2, t3, t4;
  pthread_t threads[4];
  thread_arg arguments[4];

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

  srand(time(NULL));
  for (int i = 0; i < r; i++)
  {

    // cria número aleatorio para procurar
    search = rand() % (m * n - 1);
    search++;

    // printf("search: %d\n", search);

    achou = 0;

    pthread_barrier_init(&barr, NULL, NTHREADS);
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

  // printa resultado
  printf("\nthread 1 => %d vitórias \n", count1);
  printf("thread 2 => %d vitórias \n", count2);
  printf("thread 3 => %d vitórias \n", count3);
  printf("thread 4 => %d vitórias \n", count4);

  printf("------------------------\n");
  printf("Thread vencedora: ");

  //check winner

  if ((count1 > count2) && (count1 > count3) && (count1 > count4))
    printf("1\n\n");
  else if ((count2 > count1) && (count2 > count3) && (count2 > count4))
    printf("2\n\n");
  else if ((count3 > count2) && (count3 > count1) && (count3 > count4))
    printf("3\n\n");
  else if ((count4 > count2) && (count4 > count3) && (count4 > count1))
    printf("4\n\n");
  else
    (printf("Empate!\n\n"));
  return 0;
}

// compile with cc -o main main.c -pthread
// for i in {1..2000} ; do ./main ; done >logmain
// sort <logmain | uniq -c
