# SleepingTA
## ABSTRACT
This Projects purpose was to find the solution for the given question – Sleeping Teaching Assistant Problem. We chose this project because we were interested in the algorithm for this project. We have used Pthreads, Mutex and Semaphores to program the solution for the given Question. We have also used the prior knowledge of structures, functions ,Basic C programming etc to write the program. We have used the online C Compiler as the software for our code compilation.
Our Code is running properly as result we are getting the proper output. Through this project we learnt about Pthreads, Mutex and Semaphores.                                                                                         
## CHAPTER 1 – Introduction

1.1 :- Introduction to Work Done

Using Pthreads, n students are created. Each student, as well as the TA, run as a separate thread. Student threads alternate between programming for a period of time and seeking help from the TA. If the TA is available, they obtain help. Otherwise, they either sit in a chair in the hallway, or if no chairs are available, resume programming and seek help at a later time. If a student arrives and notices that the TA is sleeping, the student notifies the TA using a semaphore. When the TA finishes helping a student, the TA checks to see if there are students waiting for help in the hallway. If so, the TA helps each of these students in turn. If no students are present, the TA returns to napping. The number of students present can be specified as a command line parameter. 


1.2 :- Project Statement 

A university computer science department has a teaching assistant (TA) who helps undergraduate students with their programming assignments during regular office hours. The TA’s office is rather small and has room for only one desk with a chair and computer. There are three chairs in the hallway outside the office where students can sit and wait if the TA is currently helping another student. When there are no students who need help during office hours, the TA sits at the desk and takes a nap. If a student arrives during office hours and finds the TA sleeping, the student must awaken the TA to ask for help. If a student arrives and finds the TA currently helping another student, the student sits on one of the chairs in the hallway and waits. If no chairs are available, the student will come back at a later time. 
Using POSIX threads, mutex locks, and semaphores, implement a solution that coordinates the activities of the TA and the students. Details for this assignment are provided below. Using Pthreads, begin by creating n students. Each will run as a separate thread. The TA will run as a separate thread as well. Student threads will alternate between programming for a period of time and seeking help from the TA. If the TA is available, they will obtain help. Otherwise, they will either sit in a chair in the hallway or, if no chairs are available, will resume programming and will seek help at a later time. If a student arrives and notices that the TA is sleeping, the student must notify the TA using a semaphore. When the TA finishes helping a student, the TA must check to see if there are students waiting for help in the hallway. If so, the TA must help each of these students in turn. If no students are present, the TA may return to napping. 

 
## CHAPTER 2 – Background Detail

2.1 :- Conceptual Overview

PTHREADS

(1)The Definition of PThreads
For UNIX systems, a standardized C language threads programming interface has been specified by the IEEE POSIX 1003.1c standard. Implementations that adhere to this standard are referred to as POSIX threads, or Pthreads. POSIX means Portable Operating System Interface which is a kind of interface that the operating system needs to support. The concept of a “procedure” that runs independently from its main program may best describe a thread.
(2) PThread Headers
In order to use the PThread interfaces, we have to include the header pthread.h at the beginning of the CPP script,

#include <pthread.h>

What’s more, we can also import some other headers for some other purposes:
•	iostream because then we can use the I/O stream
•	unistd.h because then we can use the sleep function
•	errno.h because then we can have detailed errors


(3) PThread Creation
We have known that we can create a thread by fork. So,

hThread = fork(proc, args)
where hTread is the handler of our created thread, proc is the program counter that we want to assign for the new thread, and args is some other arguments for our new thread.
For PThread, we should use the pthread_create call to create a thread. While the return value of this call is the error value (return 1 if the creation fails) instead of the handler, we have to manually create a handler by pthread_t type (this is actually defined by typedef unsigned long int pthread_t;),

pthread_t hThread;
And then transfer this handler to the pthread_create call, which has a synopsis of,

Int pthread_create(pthread_t *thread,
                   const pthread_attr_t *attr,
                   void *(*start_routine) (void *),          
                   void *arg);

where thread should be the address of our handler, pthread_attr_t is a data structure that we can specify something about our PThread, start_routine should be the program counter we would like to assign for this thread (similar to proc), and arg is for some other arguments (similar to args).

To create our new thread, we can directly call,

pthread_create(&hThread, NULL, thread, NULL);

Where hThread is the handler that we have initialized and thread is the function for the new thread to start with. We assign NULL (means to use default values) for both the arg and the attr because we don’t want to specify these values now.


(4) PThread Termination
We have also talked about the join function, which allows one thread to wait until another thread completes its execution. For example,

ret = join(hThread);

is used to suspend the current thread until the hThread thread finishes.

For PThread, we have pthread_join to do exactly the same thing. The synopsis of this call is,

int pthread_join(pthread_t thread, void **value_ptr);

To terminate a thread with a handler hThread, we can directly call,

pthread_join(hThread, NULL);

We assign NULL (means to use default values) for value_ptr because we don’t want to specify this value now.





## PROCESS SYNCHRONIZATION AND CRITICAL SECTION

In an Operating System, we have a number of processes and these processes require a number of resources. Now, think of a situation where we have two processes and these processes are using the same variable "a". They are reading the variable and then updating the value to the variable and finally writing the data in the memory.
The shared resources can be used by all the processes but the processes should make sure that at a particular time, only one process should be using that shared resource. This is called process synchronization.
So, to apply process synchronization, two methods are used. They are:
1.	Mutex
2.	Semaphore

Mutex
Mutex or Mutual Exclusion Object is used to give access to a resource to only one process at a time. The mutex object allows all the processes to use the same resource but at a time, only one process is allowed to use the resource. Mutex uses the lock-based technique to handle the critical section problem.
Whenever a process requests for a resource from the system, then the system will create a mutex object with a unique name or ID. So, whenever the process wants to use that resource, then the process occupies a lock on the object. After locking, the process uses the resource and finally releases the mutex object. After that, other processes can create the mutex object in the same manner and use it.
By locking the object, that particular resource is allocated to that particular process and no other process can take that resource. So, in the critical section, no other processes are allowed to use the shared resource. In this way, the process synchronization can be achieved with the help of a mutex object.

Semaphore
Semaphore is an integer variable S, that is initialized with the number of resources present in the system and is used for process synchronization. It uses two functions to change the value of S i.e. wait() and signal(). Both these functions are used to modify the value of semaphore but the functions allow only one process to change the value at a particular time i.e. no two processes can change the value of semaphore simultaneously. There are two categories of semaphores i.e. Counting semaphores and Binary semaphores.
In Counting semaphores, firstly, the semaphore variable is initialized with the number of resources available. After that, whenever a process needs some resource, then the wait() function is called and the value of the semaphore variable is decreased by one. The process then uses the resource and after using the resource, the signal() function is called and the value of the semaphore variable is increased by one. So, when the value of the semaphore variable goes to 0 i.e all the resources are taken by the process and there is no resource left to be used, then if some other process wants to use resources then that process has to wait for its turn. In this way, we achieve the process synchronization.
In Binary semaphores, the value of the semaphore variable will be 0 or 1. Initially, the value of semaphore variable is set to 1 and if some process wants to use some resource then the wait() function is called and the value of the semaphore is changed to 0 from 1. The process then uses the resource and when it releases the resource then the signal() function is called and the value of the semaphore variable is increased to 1. If at a particular instant of time, the value of the semaphore variable is 0 and some other process wants to use the same resource then it has to wait for the release of the resource by the previous process. In this way, process synchronization can be achieved. It is similar to mutex but here locking is not performed.








## Difference between Mutex and Semaphore:
Till now, we have learned about mutex and semaphore. Most of you might have guessed the difference between these two. Let's have a look into the difference between mutex and semaphore:
•	Mutex uses a locking mechanism i.e. if a process wants to use a resource then it locks the resource, uses it and then release it. But on the other hand, semaphore uses a signalling mechanism where wait() and signal() methods are used to show if a process is releasing a resource or taking a resource.
•	A mutex is an object but semaphore is an integer variable.
•	In semaphore, we have wait() and signal() functions. But in mutex, there is no such function.
•	A mutex object allows multiple process threads to access a single shared resource but only one at a time. On the other hand, semaphore allows multiple process threads to access the finite instance of the resource until available.
•	In mutex, the lock can be acquired and released by the same process at a time. But the value of the semaphore variable can be modified by any process that needs some resource but only one process can change the value at a time.















2.2 :- Hardware & Software Requirement

HARDWARE

PC or Laptop


SOFTWARE

Online C compiler OR C Compiler on Linux.




















## CHAPTER 3 – Methodology

3.1 :- Flow Chart/ Block Diagram



                                                   


                     Yes                                               No
 


 
















                                                    


3.2 :- Methodology/Algorithm/Procedure



Step 1:- START

Step 2:- Take input for number of students

Step 3:- IF Students Arrive, While(Total number of      students helped<N) :
   
•	If, Students arrive is greater than 4 , then After 4 students all leave and comeback at a later time when the teaching assistant is free and chairs are available.

•	Else, 1 student enters and wakes up the teaching assistant and the rest wait outside on the chair and wait for their turn.


Step 4:- ELSE Teaching Assistant continues sleeping

Step 5:- STOP


















## Chapter 4 – IMPLEMENTATION

4.1 :- Implementation Modules

The various functions/methods used in the project are describes below:

pthread_t *Students is the thread created for N students. pthread_t TA is the thread created for Teaching Assistant. 

int helped which is initialized to 0 is the variable which decides the number of students that can be helped by the TA 

TA_check() is the  function which checks if the TA is sleeping and wakes him up when the student arrives. If no student is there i.e. chair is empty, we unlock chair mutex which will allow the chair to be occupied. When the chair is occupied, chair count decrements. And TA helps the student.

void *Student_Check(void *threadID) is the function which checks if a student is with the TA and during this time no other student can go inside the room, so we put mutex on chairs. Students occupy the chairs till all 3 chairs are full. If all the chairs are occupied and a student arrives, he/she will have to leave and come later when waiting room chairs are unoccupied.

Int main() is the function is which we take input from the user for the number of students. If the number of students is 0, the TA will continue sleeping. The TA thread and the Student Thread are created. After this we will wait for TA thread and N Student threads.

