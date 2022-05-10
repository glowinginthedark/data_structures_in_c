#include <stdio.h>
#include <stdlib.h>

/**
 * @brief This file contains an implementation of the queue (first-in-first-out) 
 * data structure using a linkted list.
 * 
 * @author @glowinginthedark (github)
 * 
 */

// Data structures for queue (linked list)
struct Q
{
    /** 
     * Keep track of head and tail at the same time.
     * Reduces time complexity since we push from one
     * side and pop from the other.
     */
    struct Qnode* tail;
    struct Qnode* head;
};

struct Qnode
{
    int data;
    struct Qnode* next_in_q;
};

// Function definitions
struct Qnode* createNewNode(int data);
struct Q* createNewQ(struct Qnode* firstNode);
struct Q* createQueue(int firstData);
void push(struct Q* q, int newData);
int pop(struct Q* q);
int peek(struct Q* q);
int deleteQueue(struct Q* q);
void printQueue(struct Q* q);

/**
 * @brief Create a New Qnode structure
 * 
 * @param data int
 * @return struct Qnode* 
 */
struct Qnode* createNewNode(int data)
{
    // Try to allocate
    struct Qnode* myNode = malloc(sizeof(struct Qnode));
    if (myNode == NULL)
        return NULL;

    // Set data and return.
    myNode->data = data;
    myNode->next_in_q = NULL;

    return myNode;
}

/**
 * @brief Create a New Q structure
 * 
 * @param data int
 * @return struct Q* 
 */
struct Q* createNewQ(struct Qnode* firstNode)
{
    // Try to allocate
    struct Q* myQ = malloc(sizeof(struct Q));
    if (myQ == NULL)
        return NULL;

    // Set data and return.
    myQ->head = myQ->tail = firstNode;

    return myQ;
}

/**
 * @brief Create a new queue consisting of one node
 * 
 * @param firstData int
 * @return struct Q* 
 */
struct Q* createQueue(int firstData)
{
    printf("Creating queue with first node => %d\n", firstData);
    struct Qnode* newNode = createNewNode(firstData);
    return createNewQ(newNode);
}

/**
 * @brief Add a new node to the queue and update the 
 * next_in_q and tail
 * 
 * @param q struct Q*
 * @param newData int
 */
void push(struct Q* q, int newData)
{
    printf("+ %d\n", newData);

    // Create new node
    struct Qnode* newNode = createNewNode(newData);

    // Update current tail to have new next_in_q and
    // update tail to point to new node
    q->tail->next_in_q = newNode;
    q->tail = newNode;

    printQueue(q);
}

/**
 * @brief Pop the first in line using the head ptr
 * 
 * @param q struct Q*
 * @return int 
 */
int pop(struct Q* q)
{
    // Hold ptr to next_in_q
    struct Qnode* next = q->head->next_in_q;

    // Store pop data to return it
    int temp = q->head->data;
    printf("Popping %d from front of queue.\n", temp);

    // Free memory for the popped Qnode
    free(q->head);
    
    // HEAD now points to next_in_q
    q->head = next;

    printQueue(q);

    // Return popped data
    return temp;
}

/**
 * @brief Peek the front of the queue
 * 
 * @param q struct Q*
 * @return int 
 */
int peek(struct Q* q)
{
    printf("Peeking first node - %d - from queue.\n", q->head->data);
    return q->head->data;
}

/**
 * @brief Free allocated memory for a queue
 * 
 * @param q struct Q* 
 * @return int 
 */
int deleteQueue(struct Q* q)
{
    struct Qnode* node = q->head;
    int c = 0;

    printf("Deleted ");

    // For each node from front, until none left
    while (node != NULL)
    {
        // Store next in queue before deleting this node
        struct Qnode* next = node->next_in_q;
        free(node);
        printf("%d ", ++c);
        node = next;
    }

    printf("nodes. Deleted queue.\n");
}

/**
 * @brief Print the queue to the screen
 * 
 * @param q struct Q* 
 */
void printQueue(struct Q* q)
{
    printf("Queue (front): ");
    struct Qnode* node = q->head;

    while (node != NULL)
    {
        printf("%d", node->data);
        if (node->next_in_q != NULL) printf("->");
        node = node->next_in_q;
    }

    printf(" (back)\n");
}

int main()
{
    struct Q* myQueue = createQueue(13);
    push(myQueue, 15);
    peek(myQueue);
    push(myQueue, 17);
    pop(myQueue);
    push(myQueue, 69);
    push(myQueue, 888);
    push(myQueue, 374);
    push(myQueue, 2);
    deleteQueue(myQueue);

    return 0;
}
