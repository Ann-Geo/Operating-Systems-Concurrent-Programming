/*A particular river crossing is shared by both Linux Hackers and Microsoft em-
ployees. A boat is used to cross the river, but it only seats four people, and must always
carry a full load. In order to guarantee the safety of the hackers, you cannot put three
employees and one hacker in the same boat (because the employees would gang up and
convert the hacker). Similarly, you cannot put three hackers in the same boat as an
employee (because the hackers would gang up and convert the employee). All other
combinations are safe.
Two procedures are needed: HackerArrives() and EmployeeArrives(), called by a
hacker or employee when he/she arrives at the river bank. The procedures arrange the
arriving hackers and employees into safe boatloads; once the boat is full, one thread
calls Rowboat() and only after the call to Rowboat(), the four threads representing the
people in the boat can return.
Use condition variables to implement the solution. Any order is acceptable and there
should be no busy-waiting and no undue waiting – hackers and employees should not
wait if there are enough of them for a safe boatload. Your code should be clearly com-
mented, in particular, you should comment each condition variable operation to specify
how correctness properties are preserved.*/


int WHacker = 0, WEmployee = 0; // shared variables tracking waiting people

Lock mutex = FREE; // Lock to enforce correctness property

Condition Hacker; // Used to wait for enough people to cross river

Condition Employee // Same as Hacker

void HackerArrives() 
{
mutex->Acquire(); // Enter the critical section so we can check state vars

if (WH == 3) // We’ve already got three waiting hackers. 
{ 
Hacker->signal(mutex); // Wake three hackers (any three)
Hacker->signal(mutex);
Hacker->signal(mutex);
WH –= 3; // Decrement state vars (this must be done here, not later)
Rowboat(); // Cross the river

} 

else if ((WH >= 1) && (WE >= 2) // 1 other hacker, 2 employees
{ 
Hacker->signal(mutex); // Wake up one hacker, two employees
Employee->signal(mutex);
Employee->signal(mutex);
WH – –; // Decrement state vars
WE –= 2;
Rowboat();
} 

else 

{
WH++; // Wait for more Hackers to arrive
Hacker->wait(mutex); // No need to check state vars
}
mutex->Release(); // Done with critical section
}






























//using semaphores

Semaphore Hackers = 0; // Start with zero hackers
Semaphore Employees = 0; // Start with zero employees
int HackerCount = 0; // Count of waiting hackers
int EmployeeCount = 0; // Count of waiting employees
Semaphore Mutex = 1; // Semaphore for critical region (checking counts)
Semaphore Rowing =0; // Semaphore to prevent riders from returning from
// Hacker/Employee Arrival call until Rowboat call
void HackerArrives() {
Mutex.P(); // Acquire lock for rider variables
if (HackerCount == 3) { // Three other waiting hackers
HackerCount –= 3; // Decrement count of waiters
Mutex.V(); // Release lock
Hackers.V(); // Wake up three other waiting hackers
Hackers.V();
Hackers.V();
} else if ((HackerCount >= 1) && (EmployeeCount >=2)) {
HackerCount –= 1 // Decrement count of waiters;
EmployeeCount –= 2;
Mutex.V(); // Release lock
Hackers.V();
Employees.V();
Employees.V();
} else {
HackerCount += 1; // New waiting hacker
Mutex.V(); // Release lock
Hackers.P(); // Go to sleep until other riders arrive to fill boat
Rowing.P(); // Wait for Rowboat, once we get in the boat
return;
}
// Only the rider that fills the boat (didn’t sleep) makes it to this point
RowBoat();
Rowing.V(); // Wake up waiting boat occupants
Rowing.V();
Rowing.V();
}
