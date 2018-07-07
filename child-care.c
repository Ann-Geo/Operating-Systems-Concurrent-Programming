/*State licensing rules require a child-care center to have no more than three infants
present for each adult. You could enforce this rule using a state variable to track the re-
maining capacity, that is, the number of additional infants that may be accepted. Imple-
ment the following routines (pseudo code) adult enters(), adult leaves(), infant enters(),
infant leaves() with semaphores and mutexes such that the state licensing rules are sat-
isfied.*/

#define MAX 3
cond_t e;
mutex_t m, s;

int Infants = 0;
int adults = 0;

void adult_enters() {
    mutex_lock(&m);
	adults++;
	signal(e);
    mutex_unlock(&m);
}

void infant_enters() {
    mutex_lock(&m);
	while(Infants/adults >= MAX){
		wait(e, s);
	}
	Infants++;
	mutex_unlock(&m);	
}

void adult_leaves() {
    mutex_lock(&m);
	while(Infants/(adults-1) > MAX){
		wait(e, s);
	}
	adults--;
	mutex_unlock(&m);
}

void infant_leaves() {
    mutex_lock(&m);
	Infants--;
	signal(e);
    mutex_unlock(&m);
}
