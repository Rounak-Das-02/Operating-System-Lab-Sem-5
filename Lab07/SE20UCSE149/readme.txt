Author : Rounak Das
SE20UCSE149
CSE3

This is memory management simulation. If you want to visualize the memory, then uncomment line 368.

To run the project, type in 
g++ SE20UCSE149.cpp -o a
./a 1 3

where 1 denotes job profile 1 and 3 denotes First Fit.

This code is made modular. To change the memory size, you can modify line 28.
You can also change time steps by modifying line 16.

Random numbers are generated using seed of srand(time(0)). So, the values may slightly differ in the summary than when you run it in your local machine.