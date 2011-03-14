#!/usr/bin/env ruby

# Ruby 1.9 introduced fibers to the language. Although the name suggests some kind of
# lightweight thread, in reality Ruby’s fibers are really just a very simple coroutine mechanism.
# They allow you to write programs that look like you are manually scheduling threads
# without incurring any of the complexity inherent in threading. Let’s look at a simple example.
# We’d like to analyze a text file, counting the occurrence of each word. We could do this
# (without using fibers) in a simple loop:

counts = Hash.new(0)

File.foreach(__FILE__) do |line|
  line.scan(/\w+/) do |word|
    word = word.downcase
    counts[word] += 1
  end
end

# counts.keys.sort.each { |k| puts "#{k}\t#{counts[k]}" }

# However, this code is messy because it conflates the concepts of finding words with the
# counting of the words.

# We could fix this by writing a method that reads the file and yields each successive word.
# But fibers give us a simpler solution

words = Fiber.new do
  File.foreach(__FILE__) do |line|
    line.scan(/\w+/) do |word|
      Fiber.yield word.downcase
    end
  end
end

counts = Hash.new(0)

while word = words.resume
  counts[word] += 1
end

counts.keys.sort.each { |k| puts "#{k}\t#{counts[k]}" }

# The constructor for the Fiber class takes a block and returns a fiber object. For now, the code
# in the block is not executed.

# Subsequently, we can call resume on the fiber object. This causes the block to start execution.
# The file is opened, and the scan method starts extracting individual words. However, at
# this point, Fiber.yield is invoked. This suspends execution of the block — the resume method
# that we called to run the block returns any value given to Fiber.yield.

# Our main program enters the body of the loop and increments the count for the first word
# returned by the fiber. It then loops back up to the top of the while loop, which again calls
# words.resume while evaluating the condition. The resume call goes back into the block,
# continuing just after it left off (at the line after the Fiber.yield call).

# When the fiber runs out of words in the file, the block exits. The next time resume is called,
# it returns nil (because the block has exited). (You’ll get a FiberError if you attempt to call
# resume again after this.)

puts

# Fibers are often used to generate values from infinite sequences on demand. Here’s a fiber
# that returns successive integers divisible by 2 and not divisible by 3:

twos = Fiber.new do
  num = 2
  loop do
    Fiber.yield(num) unless num % 3 == 0
    num += 2
  end
end

10.times { puts twos.resume }

# Because fibers are just objects, you can pass them around, store them in variables, and so
# on. Fibers can be resumed only in the thread that created them.

puts
