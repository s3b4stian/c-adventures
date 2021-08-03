//The volatile variable is a variable whose value may change beyond our control and without our intervention.
//Is it possible anyway? Are there such variables in the known universe?
//Yes and yes.

//Imagine that a certain variable is accessible by more than one thread, 
//or may be modified by any independent program, 
//or is just a hardware register accessed by an external device. 

//In all these cases, the variable’s value may be changed uncontrollably and unpredictably.
//The restrict keyword is a promise. 
//The volatile keyword is a warning.

//It says to the compiler: the variable is fickle; don’t try to store it in the processor’s register, 
//as it may be modified and you won’t notice; anytime you need its value, fetch it from the memory anew.
//Look, the pointers may be volatile, the values they point to may be volatile too, 
//and both these cases may be combined.


//a variable may be volatile and const at the same time
const volatile int ticks;
//The variable ticks (which may be a part of a hardware clock) is volatile 
//(because it’s incremented periodically by an external factor), 
//and is also a const (as you’re not allowed to change its value yourself)

//the volatile keyword is not a mutex replacement

void athread(void)
{
    external int stop;

    while(!stop)
        do_something();
}
//The stop variable is declared somewhere out of the thread code and it’s initialized to zero.


void otherthread(void)
{
    external int stop;

    time_consuming_job();
    stop = 1;
}

//The compiler may want to optimize the athread() function’s 
//code and to fetch the stop variable once and to store it in a register.
//The code won’t notice that the variable’s value has been changed
//    |
//   \|/
//solution
void athread(void)
{
    external volatile int stop;

    while(!stop)
        do_something();
}
