# ParallelAssignment1
 
In order to compile this program, install clang 15.0.6 on your computer. Then, compile the code using the command:

 clang Assignment1.cpp

 Finally, run the code using the command: 
 
 ./a

To solve this, I chose to first use a classic Sieve of Eratosthenes algorithm. In the solution, which is O(nlog(log(N))), we traverse every number from 2 to the square root of N. We then calculate the factors that lead up to N, which reveal them to, by definition, not be prime. Finally, all numbers that are not marked must be prime.

In order to make it multithreaded, I divided the loop up to the square root of N into 8 separate equal chunks. Then, each thread worked on calculating the numbers in the range of ((N/8) * i) to ((N/8) * i+1), where i is the current chunk starting from 0. Each thread works simultaneously, and then joins after all are completed. 

In my own environment, I was able to reduce the time to around 1.8 seconds. This seems to be a reasonable amount of time, but I do feel as though this is likely not the best solution.