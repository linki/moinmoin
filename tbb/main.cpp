#include <stdio.h>
#include "tbb/task_scheduler_init.h"
#include "tbb/parallel_for.h"
#include "tbb/blocked_range.h"

class ArraySquarer {
   int *_source;
   int *_target;

public:
   ArraySquarer(int *source, int *target)
   {
      _source = source;
      _target = target;
   };

   void operator()(const tbb::blocked_range<int> &range) const
   {
      for (int i = range.begin(); i != range.end(); ++i)
      {
         _target[i] = _source[i] * _source[i];
      }
   }
};

int main(int argc, const char **argv)
{
   if (argc != 2)
   {
      printf("USAGE: %s NR_OF_VALUES\n", argv[0]);
      return EXIT_FAILURE;
   }
   
   // http://www.lyratechnicalsystems.com/tbb/doc/20/ref/TbbRef20_8_2.html
   tbb::task_scheduler_init init;

   int count = atoi(argv[1]);

   int *source = (int *)malloc(count * sizeof(int));
   int *target = (int *)malloc(count * sizeof(int));

   for (int i = 0; i < count; ++i)
   {
      source[i] = i;
   }

   tbb::parallel_for(
      tbb::blocked_range<int>(0, count, 100),
      ArraySquarer(source, target)
   );
   
   for (int i = 0; i < count; ++i)
   {
      printf("%d * %d = %d\n", source[i], source[i], target[i]);
   }   

   free(source);
   free(target);

   return EXIT_SUCCESS;
}
