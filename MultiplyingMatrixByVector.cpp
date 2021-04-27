#include <stdio.h>
#include <omp.h>

void print_matrix(int n, int m[4][4])
{
    int i, j; 
    printf("\nMatrix Given\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            printf("%3i", m[i][j]);
        printf("\n");
    }
}

void print_vector(int n, int v[4])
{
    int i;
    printf("\nVector Given\n");

    for (i = 0; i < n; i++)
        printf("%3i", v[i]);

    printf("\n");
}


int main()
{

  int n = 4;

  int m1[4] = {1, 2, 3, 4};

  int m2[4][4] = {
    {1,2,3,4},
    {5,6,7,8},
    {9,10,11,12},
    {13,14,15,16}};

  int multiplied_matrix[4][1] = {
    {0},
    {0},
    {0},
    {0}};

   
 
  print_vector(n, m1);
  print_matrix(n, m2);

  printf("\n");

  int i, j; 

 

  int sum = 0;

# pragma omp parallel for num_threads(2) reduction(+:sum)
      for (i = 0; i < n; i++)
      {
          int my_rank = omp_get_thread_num();
          printf("thread num : %d ", my_rank);
          for (j = 0; j < n; j++)
          {     
              sum = m2[j][i] * m1[i];
              multiplied_matrix[j][0] += sum;
          }
      }

  printf("\n");


  for (i = 0; i < n; i++)
      printf("%4i\n", multiplied_matrix[i][0]);


  printf("\n");
}
