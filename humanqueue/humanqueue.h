//humanqueue.h
//Helpers for humanqueue.

typedef struct HumanPerson{
	double arrivaltime;
	double servicetime;
	double waitedtime;
} *human;

typedef struct QueuePosition{
	human containedperson;
	struct QueuePosition *hasasbehind;
} *qpos;

typedef struct Queue{
	qpos front;
	qpos back;
} *q;

human newHuman(double arrivaltime, double waitedtime);
qpos newQPos(human containedperson, qpos hasasbehind);
q newQueue();

human newHuman(double arrivaltime, double servicetime);
void freeHuman(human person);
human clone(human person);
qpos newQPos(human containedperson, qpos hasasbehind);
void freeQPos(qpos queueposition);
q newQueue();
void freeQueue(q queue);
void enqueue(q queue, human person);
human dequeue(q queue);

void queuesimulator(FILE *queuefile);

int processqueue(char *filepath);