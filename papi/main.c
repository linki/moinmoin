#include <stdio.h>
#include <stdlib.h>
#include <papi.h>

#define NUM_PAPI_COUNTERS 2

int main(int argc, const char **argv)
{
  // Must not be const, because PAPI's interface is weird.
  int papi_counters[NUM_PAPI_COUNTERS] = { PAPI_TOT_CYC, PAPI_TOT_INS };

  long long int papi_values_[NUM_PAPI_COUNTERS]; // NOLINT PAPI interface again

  const int status = PAPI_start_counters(papi_counters, NUM_PAPI_COUNTERS);
  
  if (status != PAPI_OK)
  {
    printf("Can't start PAPI Counters (%d).\n", status);
    return EXIT_FAILURE;
  }
  
  char event_name[PAPI_MAX_STR_LEN];
  
  for (int i = 0; i < NUM_PAPI_COUNTERS; ++i)
  {
    PAPI_event_code_to_name(papi_counters[i], event_name);
    printf("%s\n", event_name);
  }
  
  PAPI_read_counters(papi_values_, NUM_PAPI_COUNTERS);
  
  for (int i = 0; i < NUM_PAPI_COUNTERS; ++i)
  {
    printf("%llu\n", papi_values_[i]);
  }
  
  printf("\n");
      
  PAPI_read_counters(papi_values_, NUM_PAPI_COUNTERS);
  
  for (int i = 0; i < NUM_PAPI_COUNTERS; ++i)
  {
    printf("%llu\n", papi_values_[i]);
  }
    
  return EXIT_SUCCESS;
}
