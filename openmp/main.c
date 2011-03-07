#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, const char **argv)
{
   if (argc != 2)
   {
      printf("USAGE: %s NR_OF_VALUES\n", argv[0]);
      return EXIT_FAILURE;
   }
   
   int count = atoi(argv[1]);

   int *source = malloc(count * sizeof(int));
   int *target = malloc(count * sizeof(int));

   for (int i = 0; i < count; ++i)
   {
      source[i] = i;
   }
   
   // 4 threads per core, defaults to 1 i guess
   int num_threads = 4 * omp_get_num_procs();
    
   #pragma omp parallel for num_threads(num_threads)
   for (int i = 0; i < count; ++i)
   {
      printf("compute %d * %d with thread %d\n", source[i], source[i], omp_get_thread_num());

      target[i] = source[i] * source[i];
   }
   
   for (int i = 0; i < count; ++i)
   {
      // printf("%d * %d = %d\n", source[i], source[i], target[i]);
   }   

   free(source);
   free(target);

   return EXIT_SUCCESS;
}
