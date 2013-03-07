//humanqueue.c
//Simulates a queue with actual people

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "humanqueue.h"

/* Main function. Error codes:
1: Wrong number of arguments.
*/
int main(int argc, char **argv){
	if (argc < 2){
		printf("Wrong number of arguments. \nUsage: humanqueue filename\n");
		exit(0);
	}
	FILE *queuefile;
	queuefile = fopen(argv[1], "r");
	queuesimulator(queuefile);
	assert(queuefile != NULL);
}

void queuesimulator(FILE *queuefile){
	double queuetimer = 0.00;
	double arrivaltime;
	double servicetime;
	double epsilon = 0.0001;
	human inwaiting;

	int queuebuffer = 0;
	int thislength = 0;
	int maxlength = 0;
	double maxwait = 0.00;
	double thiswait;

	q queue = newQueue();
	
	do{
		//Decrements service time of first person, dequeue if finished
		if (queue->front != NULL){
			queue->front->containedperson->servicetime -= 0.01;
			if (queue->front->containedperson->servicetime < epsilon){
				human finished = dequeue(queue);
				//printf("Person arrived at %lf dequeued, waited %lf\n", finished->arrivaltime, finished->waitedtime);
				thiswait = finished->waitedtime;
				if (thiswait > maxwait)
					maxwait = thiswait;
				freeHuman(finished);
			}			
		}

		//Grab a person from the data ether, and make him wait until his time has come.
		if (queuebuffer == 0){
			if (!feof(queuefile)){
				fscanf(queuefile, "%lf %lf", &arrivaltime, &servicetime);
				inwaiting = newHuman(arrivaltime, servicetime);
				//printf("%lf %lf\n", arrivaltime, servicetime);
			}
			queuebuffer = 1;
		}
		//The etheral person's time has come! Place him in the queue.
		if (!feof(queuefile)){
			if (abs(queuetimer - inwaiting->arrivaltime) < epsilon){
				enqueue(queue, clone(inwaiting));
				freeHuman(inwaiting);
				queuebuffer = 0;
			}
		}
		//Increment waiting times for each cycle, and determine queue's length.
		//We start from hasasbehind to not count service time as waiting time.
		if(queue->front != NULL && queue->front->hasasbehind != NULL){
			for(qpos queuepos = queue->front->hasasbehind; queuepos != NULL; queuepos = queuepos->hasasbehind){
				queuepos->containedperson->waitedtime += 0.01;
				thislength += 1;
			}
			if (thislength + 1 > maxlength){
				maxlength = thislength + 1;
			}
			thislength = 0;

		}
		queuetimer += 0.01;
	} while (!feof(queuefile) || queue->front != NULL);
	printf("Maximum wait: %lf \nMaximum length: %d\n", maxwait, maxlength);
}
