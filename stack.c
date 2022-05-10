#include <stdio.h>
#include <stdlib.h>

/**
 * @brief This file contains an implementation of the stack (Last-in-first-out) 
 * data structure using a linkted list. Every time a new node is to be added,
 * new memory is allocated using malloc() and the HEAD pointer is updated to 
 * point to the newest node. Consequently, peek and pop work with the node
 * corresponding to the HEAD pointer.
 * 
 * @author @glowinginthedark (github)
 * 
 */

// Data structure for stack (linked list)
struct stack_node
{
    int data;
    struct stack_node* below;
};

// Function definitions
struct stack_node* createNewNode(int data);
struct stack_node* createStack(int firstData);
void addNodeToStack(struct stack_node** head, int newData);
int popFromStack(struct stack_node** head);
int peek(struct stack_node* head);
int deleteStack(struct stack_node* head);
void printStack(struct stack_node* head);

/**
 * @brief Create a New Node object
 * 
 * @param data int
 * @return struct stack_node* 
 */
struct stack_node* createNewNode(int data)
{
    // Try to allocate
    struct stack_node* myNode = malloc(sizeof(struct stack_node));
    if (myNode == NULL)
        return NULL;

    // Set data and return.
    myNode->data = data;
    myNode->below = NULL;

    return myNode;
}

/**
 * @brief Create a new Stack consisting of one node
 * 
 * @param firstData int
 * @return struct stack_node* 
 */
struct stack_node* createStack(int firstData)
{
    printf("%d\n", firstData);
    return createNewNode(firstData);
}

/**
 * @brief Add a new node to the stack and return the new head pointer
 * 
 * @param head 
 * @param newData 
 */
void addNodeToStack(struct stack_node** head, int newData)
{
    printf("+ %d\n", newData);
    struct stack_node* newNode = createNewNode(newData);
    newNode->below = *head;
    *head = newNode;
    printStack(*head);
}

/**
 * @brief Pop the top node off the stack and return the next node's pointer
 * N1 (head) -> N2 -> N3
 *              ^Discard this. Original N1 now points to 
 *               N3 and holds N2's data
 * N2 (head) -> N3
 * 
 * @param head 
 * @return int 
 */
int popFromStack(struct stack_node** head)
{
    // Hold ptr to N1
    struct stack_node* headPtr = *head;

    // Store pop data to return it
    int temp = headPtr->data;
    printf("Popping %d from stack.\n", temp);
    
    // HEAD now points to N2 instead of N1, or NULL if there is no N2
    *head = headPtr->below;

    // Free memory for N1
    free(headPtr);

    printStack(*head);
    // Pop return value
    return temp;
}

/**
 * @brief Peek the top node of the stack
 * 
 * @param head 
 * @return int 
 */
int peek(struct stack_node* head)
{
    printf("Peeking %d off stack.\n", head->data);
    return head->data;
}

/**
 * @brief Free allocated memory for a stack
 * 
 * @param head 
 * @return int 
 */
int deleteStack(struct stack_node* head)
{
    struct stack_node* t = head;
    int c = 0;

    printf("Deleted ");

    while (t != NULL)
    {
        struct stack_node* below = t->below;
        free(t);
        printf("%d ", ++c);
        t = below;
    }

    printf("nodes. Deleted stack.\n");
}

/**
 * @brief Print the stack to the screen
 * 
 * @param head 
 */
void printStack(struct stack_node* head)
{
    // printf("Stack: ");
    struct stack_node* t = head;

    while (t != NULL)
    {
        printf("%d", t->data);
        if (t->below != NULL) printf("->");
        t = t->below;
    }

    printf("\n");
}

int main()
{
    struct stack_node* myStack = createStack(13);
    addNodeToStack(&myStack, 15);
    peek(myStack);
    addNodeToStack(&myStack, 17);
    popFromStack(&myStack);
    addNodeToStack(&myStack, 21);
    deleteStack(myStack);

    return 0;
}
