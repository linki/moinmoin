__kernel void square(__global const float *source, __global float *target, __constant int count)
{
   int i = get_global_id(0);
   
   if (i < count)
   {
      target[i] = source[i] * source[i];
   }
}
