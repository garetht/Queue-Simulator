//hqfunctions.c
//Functions and data types for the human queue.
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "humanqueue.h"

human newHuman(double arrivaltime, double servicetime){
	human person = (human) malloc(sizeof (struct HumanPerson));

	person->arrivaltime = arrivaltime;
	person->servicetime = servicetime;
	person->waitedtime = 0.0;

	return person;
}

void freeHuman(human person){
	free((void *) person);
}

human clone(human person){
	human clone = (human) malloc(sizeof(struct HumanPerson));

	clone->arrivaltime = person->arrivaltime;
	clone->servicetime = person->servicetime;
	clone->waitedtime = person->waitedtime;

	return clone;
}

qpos newQPos(human containedperson, qpos hasasbehind){
	qpos thisposition = (qpos) malloc(sizeof(struct QueuePosition));

	thisposition->containedperson = containedperson;
	thisposition->hasasbehind = hasasbehind;

	return thisposition;
}

void freeQPos(qpos queueposition){
	free ((void *) queueposition);
}

q newQueue(){
	q queue = (q) malloc(sizeof(struct Queue));
	assert (queue != NULL);

	queue->front = NULL;
	queue->back = NULL;

	return queue;
}

void freeQueue(q queue){
	qpos current = queue->front;
	while (current != NULL){
		freeHuman(current->containedperson);
		freeQPos(current);
		current = current->hasasbehind;
	}
	free((void *) queue);
}

void enqueue(q queue, human person){
	qpos newqueueposition = newQPos(person, NULL);

	if (queue->front == NULL){
		queue->front = newqueueposition;
		queue->back = newqueueposition;
	}
	else{
		queue->back->hasasbehind = newqueueposition;
		queue->back = newqueueposition;
	}
}

human dequeue(q queue){
	assert(queue->front != NULL);

	human person = queue->front->containedperson;
	qpos oldfront = queue->front;
	queue->front = oldfront->hasasbehind;

	freeQPos(oldfront);
	return person;
}