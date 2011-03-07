__kernel void square(__global float *source, __global float *target, const int count)                           \
{
   int i = get_global_id(0);
   
   if (i < count)
   {
      target[i] = source[i] * source[i];
   }
}
