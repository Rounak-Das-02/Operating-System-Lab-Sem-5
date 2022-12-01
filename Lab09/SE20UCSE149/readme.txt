Author : Rounak Das
SE20UCSE149
CSE3

Execute the file SE20UCSE149.cpp to run various page replacement algorithms. In case of taking input from a file input.txt, uncomment line 166.

FIFO page replacement is pretty simple and is implemented using a queue data structure. This queue is however implemented using vectors.

OPTIMAL and LRU are pretty similar in terms of implementation. In OPTIMAL, the farthest string is chosen. In LRU, the reference string is reversed and then the farthest string is found, which in turn is the least recently used string.