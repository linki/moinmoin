#include <gtest/gtest.h>

static const char *fibo = "nacci";

static long fibonacci(long n)
{
   if (n < 2)
   {
      return n;
   }
   
   return fibonacci(n - 1) + fibonacci(n - 2);
}

static int is_fibonacci()
{
   return true;
}

TEST(Fibonacci, Examples)
{
   EXPECT_EQ(0, fibonacci(0));
   EXPECT_EQ(1, fibonacci(1));
   EXPECT_EQ(1, fibonacci(2));
   EXPECT_EQ(2, fibonacci(3));
   EXPECT_EQ(3, fibonacci(4));
   EXPECT_EQ(5, fibonacci(5));   
   EXPECT_EQ(8, fibonacci(6));
   EXPECT_EQ(13, fibonacci(7));
   EXPECT_EQ(21, fibonacci(8));
   EXPECT_EQ(34, fibonacci(9));         
   EXPECT_EQ(55, fibonacci(10));
   EXPECT_EQ(6765, fibonacci(20));
   EXPECT_EQ(832040, fibonacci(30));
   EXPECT_EQ(102334155, fibonacci(40));
   // EXPECT_EQ(7778742049L, fibonacci(49)); takes a little

   EXPECT_STREQ("nacci", fibo);

   EXPECT_TRUE(is_fibonacci());
   EXPECT_FALSE(!is_fibonacci());
}
