# processes and threads 

### how a program is developed :
- write program 
- the program needs to be converted to binary executable code ( machine code )
- so we need a compiler to do that.
- untill the moment the program doesn't know what to do.
- it has to be loaded on memory, and needs some resources. (CPU...)
- the OS will provide us with that.
- now we have a progarm in execution it's called a :  **PROCESS**

	> a process is a program in execution 

### Threads
- every process has from one to many small tasks working similutanously (running at the same time)
- they are basic unit of a proces and they are known as : **THREADS**
- a thread is a basic unit of CPU utilisation

  

#### what defines a threads ?
Each thread has : 
- Thread Id
- Program counter
- register set
- stack
And it shares with other threads belonging to same process :
- code section
- data section
- OS resources like open files and signals

Threads are usefull cuz they can perform multiple tasks at a time, 
we say they work similtanously  
 
