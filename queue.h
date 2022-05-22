

#ifndef QUEUE
#define QUEUE 1

/*
Priority Queue : FIFO
10(0) : head-> 10(0)
20(1) : head-> 20(1) -> 10(0)
30(2) : head-> 30(2) -> 20(1) -> 10(1)
40(0) : head-> 30(2) -> 20(1) -> 10(1) -> 40(0)
*/

enum priority
{
    LOW = 0, // 4 bytes
    MEDIUM,  // 4 bytes
    HIGH     // 4 bytes
};

struct queue
{
    struct node(*head_node);                             // 8 bytes
    int size;                                            // 4 bytes
    int (*enqueue)(struct queue(*), int, enum priority); // 8 bytes
    int (*dequeue)(struct queue(*));                     // 8 bytes
    int (*peek)(struct queue(*), int);                   // 8 bytes
};

struct node
{
    int data;                    // 4 bytes
    enum priority priority;      // 12 bytes (if no aligment)
    struct node(*previous_node); // 8 bytes
};

struct queue init_queue_stack(void);
struct queue *init_queue_heap(void);
// member funcs
int enqueue(struct queue(*), int, enum priority); // append
int dequeue(struct queue(*));                     // remove
int peek(struct queue(*), int);                   // observe

#endif
