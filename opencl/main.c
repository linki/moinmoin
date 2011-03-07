/*
 * apple's opencl example code
 * http://developer.apple.com/library/mac/samplecode/OpenCL_Hello_World_Example/OpenCL_Hello_World_Example.zip
 */

#include <stdio.h>
#include <stdlib.h>

#ifdef __APPLE__
   #include <OpenCL/opencl.h>
#else
   #include <CL/cl.h>
#endif

char *read_from_file(const char *filename);

int main(int argc, const char **argv)
{
   if (argc != 2)
   {
      printf("USAGE: %s NR_OF_VALUES\n", argv[0]);
      return EXIT_FAILURE;
   }

   int count = atoi(argv[1]);

   float *source = malloc(count * sizeof(int));
   float *target = malloc(count * sizeof(int));

   for (int i = 0; i < count; ++i)
   {
      source[i] = (float)i;
   }

   // we need the kernel code as c-string
   char *kernel_code = read_from_file("square.cl");

   // opencl starts here

   cl_int           err;         // error code returned from api calls

   cl_uint          num_platforms;
   cl_uint          num_devices;

   size_t           local;         // local domain size for our calculation
   size_t           global;        // global domain size for our calculation

   cl_device_id     *device_ids;   // compute device ids
   cl_context       context;       // compute context
   cl_command_queue commands;      // compute command queue
   cl_program       program;       // compute program
   cl_kernel        kernel;        // compute kernel

   cl_mem           device_source; // handles to memory on device
   cl_mem           device_target;

   clGetPlatformIDs(0, NULL, &num_platforms);
   printf("Number of platforms: %d\n", num_platforms);

   /*
    * CL_DEVICE_TYPE_CPU   An OpenCL device that is the host processor. The host processor runs the OpenCL implementations and is a single or multi-core CPU.
    * CL_DEVICE_TYPE_GPU   An OpenCL device that is a GPU. By this we mean that the device can also be used to accelerate a 3D API such as OpenGL or DirectX.
    * CL_DEVICE_TYPE_ACCELERATOR   Dedicated OpenCL accelerators (for example the IBM CELL Blade). These devices communicate with the host processor using a peripheral interconnect such as PCIe.
    * CL_DEVICE_TYPE_DEFAULT   The default OpenCL device in the system.
    * CL_DEVICE_TYPE_ALL   All OpenCL devices available in the system.
    */
   clGetDeviceIDs(NULL, CL_DEVICE_TYPE_GPU, 0, NULL, &num_devices);
   printf("Number of gpu devices: %d\n", num_devices);

   device_ids = malloc(num_devices * sizeof(cl_device_id));

   clGetDeviceIDs(NULL, CL_DEVICE_TYPE_GPU, num_devices, device_ids, NULL);

   // Create a compute context on first device
   context = clCreateContext(NULL, 1, device_ids, NULL, NULL, &err);

   // Create command queue for first device
   commands = clCreateCommandQueue(context, device_ids[0], 0, &err);

   // Create the compute program from the source buffer
   program = clCreateProgramWithSource(context, 1, (const char **) &kernel_code, NULL, &err);

   // Build the program executable
   err = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
   if (err != CL_SUCCESS)
   {
      printf("Error: Failed to build program executable! %d\n", err);
      
      // print error details
      char buffer[2048];
      clGetProgramBuildInfo(program, device_ids[0], CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, NULL);

      printf("%s\n", buffer);

      return EXIT_FAILURE;
   }

   // Create the compute kernel in the program we wish to run (name of the kernel function)
   kernel = clCreateKernel(program, "square", &err);
   if (err != CL_SUCCESS)
   {
      printf("Error: Failed to create compute kernel! %d\n", err);
      return EXIT_FAILURE;
   }

   device_source = clCreateBuffer(context, CL_MEM_READ_ONLY, count * sizeof(float), NULL, &err);
   device_target = clCreateBuffer(context, CL_MEM_WRITE_ONLY, count * sizeof(float), NULL, &err);
   if (!device_source || !device_target)
   {
      printf("Error: Failed to allocate device memory! %d\n", err);
      return EXIT_FAILURE;
   }

   // Write our data set into the input array in device memory
   err = clEnqueueWriteBuffer(commands, device_source, CL_TRUE, 0, count * sizeof(float), source, 0, NULL, NULL);
   if (err != CL_SUCCESS)
   {
      printf("Error: Failed to write to device source array! %d\n", err);
      return EXIT_FAILURE;
   }

   err  = clSetKernelArg(kernel, 0, sizeof(cl_mem), &device_source);
   err |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &device_target);
   err |= clSetKernelArg(kernel, 2, sizeof(int), &count);
   if (err != CL_SUCCESS)
   {
      printf("Error: Failed to set kernel arguments! %d\n", err);
      return EXIT_FAILURE;
   }

   // Get the maximum work group size for executing the kernel on the device
   err = clGetKernelWorkGroupInfo(kernel, device_ids[0], CL_KERNEL_WORK_GROUP_SIZE, sizeof(local), &local, NULL);
   if (err != CL_SUCCESS)
   {
      printf("Error: Failed to retrieve kernel work group info! %d\n", err);
      return EXIT_FAILURE;
   }

   global = count;

   // global needs to a multiple of local
   if (global % local != 0)
   {
      global = local * (count / local + 1);
   }

   printf("local:  %lu\n", local);
   printf("global: %lu\n", global);

   // Execute the kernel over the entire range of our 1d input data set
   // using the maximum number of work group items for this device
   err = clEnqueueNDRangeKernel(commands, kernel, 1, NULL, &global, &local, 0, NULL, NULL);
   if (err != CL_SUCCESS)
   {
      printf("Error: Failed to execute kernel! %d\n", err);
      return EXIT_FAILURE;
   }

   // Wait for the command commands to get serviced before reading back results
   clFinish(commands);

   // Read back the results from the device to verify the output
   err = clEnqueueReadBuffer(commands, device_target, CL_TRUE, 0, count * sizeof(float), target, 0, NULL, NULL);
   if (err != CL_SUCCESS)
   {
      printf("Error: Failed to read output array from device! %d\n", err);
      return EXIT_FAILURE;
   }

   // print it
   for (int i = 0; i < count; ++i)
   {
      printf("%f * %f = %f\n", source[i], source[i], target[i]);
   }

   // Shutdown and cleanup
   clReleaseMemObject(device_source);
   clReleaseMemObject(device_target);
   clReleaseProgram(program);
   clReleaseKernel(kernel);
   clReleaseCommandQueue(commands);
   clReleaseContext(context);

   free(kernel_code);
   free(source);
   free(target);

   return EXIT_SUCCESS;
}

// http://www.cplusplus.com/reference/clibrary/cstdio/fread/
char *read_from_file(const char *filename)
{
   FILE *file = fopen(filename, "rb");

   fseek(file, 0, SEEK_END);

   size_t size = ftell(file);
   char *content = malloc(size + 1);

   rewind(file);
   fread(content, 1, size, file);

   fclose(file);

   content[size] = '\0';

   return content;
}
