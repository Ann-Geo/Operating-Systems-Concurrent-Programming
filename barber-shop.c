/*A barbershop consists of a waiting room with n chairs, and the barber room containing
the barber chair. If there are no customers to be served, the barber goes to sleep. If
a customer enters the barbershop and all chairs are occupied, then the customer leaves
the shop. If the barber is busy, but chairs are available, then the customer sits in one
of the free chairs. If the barber is asleep, the customer wakes up the barber. Use the
following information helper functions:
• Customer threads should invoke a function named getHairCut().
• If a customer thread arrives when the shop is full, it can invoke balk, which does
not return.
• The barber thread should invoke cutHair().
• When the barber invokes cutHair there should be exactly one thread invoking
getHairCut() concurrently. Write the Barber() and Customer() thread routines
that implements a solution to the problem that guarantees these constraints using
semaphores.
*/


sem_init(&customers, 0, 0);
sem_init(&barber, 0, 0);
sem_init(&cutting, 0, 0);
sem_init(&mutex, 0, 1);

int customer_no = 0;



void barber() 
{
while(true) 
{
sem_wait(customers); //sleep when there are no waiting customers
sem_wait(mutex); //mutex for accessing customer_no
customer_no = customer_no - 1;
sem_post(barber);
sem_post(mutex);
cut_hair();
}
}

void customer() 
{
sem_wait(mutex); //mutex for accessing customer_no
if (customer_no < n) //n is maximum number of customers allowed
{
customer_no = customer_no + 1;
sem_post(customers);
sem_post(mutex);
sem_wait(barber); //sem_wait for available barbers
get_haircut();
}
else 
{ //do nothing (leave) when all chairs are used.
sem_post(mutex);
}
}

cut_hair()
{
waiting(cutting);
}

get_haircut()
{
get hair cut and finish;
sem_post(cutting);
}
