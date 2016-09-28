1. I inspected main.c and found that a four nested for loop to process each pixel which is
   perfect for multithreading.
2. I put the for loop and some variable used in the loop that are declared in main.c into 
   a new function called multithread.
3. to multithread the loop, I pass the multithread function an argument that tells it the
   the starting point of the outmost for loop. For 1 thread, the starting point is 0, for 2 thread,
   the first thread starts at 0, the second starts at 1... and so on. And for the incrementing of the 
   for loop, I let it increments the number of threads each time.
   Thus, the for loop can be divided into n threads without each threads stepping into one
   another.
4. then I created threads using pthread_create and joined them with
   pthread_join in main.c.
5. After make check clean I noticed that the image created were all messed up. I then found
   that the problem was that since I put the printing of each pixel in the multithread function 
   the printing is not done in the proper order since the threads acts independently of each
   other. Then I changed the scaled-color array into a global and 3D one and stored value of each
   pixel and coordinate(px and py) in the array. Then I print the array later in the main 
   function in the proper order instead of during the multithreading with a double for loop.

then by make check clean, I got the performance of the multithreaded version as follows:
time ./srt 1-test.ppm >1-test.ppm.tmp

real	0m48.907s
user	0m48.910s
sys	0m0.003s
mv 1-test.ppm.tmp 1-test.ppm
time ./srt 2-test.ppm >2-test.ppm.tmp

real	0m25.459s
user	0m50.630s
sys	0m0.008s
mv 2-test.ppm.tmp 2-test.ppm
time ./srt 4-test.ppm >4-test.ppm.tmp

real	0m12.755s
user	0m50.638s
sys	0m0.001s
mv 4-test.ppm.tmp 4-test.ppm
time ./srt 8-test.ppm >8-test.ppm.tmp

real	0m10.698s
user	1m11.262s
sys	0m0.008s

We can see that the time it takes to execute the program is inversely proportional to the 
number of threads. The performance of the program is greatly improved with multithreading.