#include <stdlib.h>
#include <stdio.h>
#include "shortPath.h"


struct energyListNode
{
    // The values to store in this node
    char *startCity;
    char *endCity;
    int energy;

    // And the pointers to the nodes either side
    struct energyListNode* next;
    struct energyListNode* prev;
};

struct energyList
{
    //number of elements in the list
    int size;

    //the markers to the start and end of the list
    struct energyListNode* head;
    struct energyListNode* tail;
};

//list node constructor
struct energyListNode* energyListNodeConstructor(char* startCity, char* endCity, int energy)
{
    //declare a new node structure
    struct energyListNode* newNode;

    //allocating memory in accordance to the length of the city names
    //city names will be taken from energy file
    char* startCopied = malloc(sizeof(char) * strlen(startCity));
    char* endCopied = malloc(sizeof(char) * strlen(endCity));

    //reserve memory for the node being created
    newNode = malloc(sizeof(struct energyListNode));

    //copy the strings so they arent overwritten
    strcpy(startCopied, startCity);
    strcpy(endCopied, endCity);

    //setting the nodes values
    newNode->startCity = startCopied;
    newNode->endCity = endCopied;
    newNode->energy = energy;
    newNode->next = NULL;
    newNode->prev = NULL;

    // And return it
    return newNode;
}

// Release the memory of the provided node
void energyListNodeDestructor(struct energyListNode* node)
{
    // We have no extra memory other than this node so simply free it
    free(node);
}

//create a new linked list
struct energyList* energyListConstructor()
{
    //reserve memory for the list
    struct energyList* newLinkedList;
    newLinkedList = malloc(sizeof(struct energyList));

    //initialise it appropriately
    newLinkedList->size = 0;
    newLinkedList->head = NULL;
    newLinkedList->tail = NULL;

    // And return it
    return newLinkedList;
}

void energyListDestructor(struct energyList* linkedList)
{
    printf("Linked list destructor\n");

    //we need these to traverse the list
    struct energyListNode* currentRecord;
    struct energyListNode* nextRecord = linkedList->head;

    // As long as the record to process exists
    while(nextRecord != NULL)
    {
        // Move to it
        currentRecord = nextRecord;

        // And update where to go next
        nextRecord = currentRecord->next;

        // And release the memory associated with this node
        energyListNodeDestructor(currentRecord);
    }

    // Now all of the nodes have been release so we can release the list too
    free(linkedList);
}

int energyListSize(struct energyList* list)
{
    return list->size;
}

int energyListIsEmpty(struct energyList* list)
{
    if(energyListSize(list) == 0)
    {
        return 1;
    }
    else
    {
    return 0;
    }
}

//add a new item to the end of the list
int energyListAdd(struct energyList* list, char* start, char* end, int energy)
{
    //creating the new node
    struct energyListNode* newNode = energyListNodeConstructor(start, end, energy);

    //the node that will come before this node is currently the list tail
    newNode->prev = list->tail;

    //we will not have a next element as it is at the end
    newNode->next = NULL;

    //if the list is not empty
    if(list->tail != NULL)
    {
        //telling the current tail that it now has a next element
        list->tail->next = newNode;
    }

    // And update the list to make the new node the tail
    list->tail = newNode;

    // List is empty
    if(list->head == NULL)
    {
        // So we are also the head
        list->head = newNode;
    }

    // Update the element count
    list->size++;

    // And indicate success
    return 1;
}

void energyListDisplay(struct energyList* list)
{

    // We start with the head of the list
    struct energyListNode* currentNode = list->head;

    // And print each element in turn until we are looking at NULL
    while(currentNode != NULL)
    {
        // Print a comma before the values after the first
        if(currentNode != list->head)
        {
            printf("\n");
        }

        // Print the current value
        printf("%s\t%s\t%d\n", currentNode->startCity, currentNode->endCity, currentNode->energy);

        // Move to the next node
        currentNode = currentNode->next;
    }

}

struct energyListNode* energyListGetNode(struct energyList* list, int index)
{
    // Sanity check the index
    if(index < 0 || index >= list->size)
    {
        // And indicate failure if it is invalid
        return NULL;
    }

    // Check if we should start from the head or tail
    if(index < (list->size / 2))
    {
        // We are closer to the start of the list so start at the head and move forwards
        struct energyListNode* currentItem = list->head;

        // Move through index items
        for(int i = 0; i < index; i++)
        {
            // Make sure our links are not corrupt
            if(currentItem->next == NULL)
            {
                // And indicate failure if they are
                return NULL;
            }

            // Otherwise move on
            currentItem = currentItem->next;
        }

        // We have now moved to the requested item so return it
        return currentItem;
    }
    else
    {
        // We are closer to the end of the list so start at the tail and move backwards
        struct energyListNode* currentItem = list->tail;

        // How many items should we move through?
        // If the index is size-1 then we move through 0 items
        // so we should move through (size-1) - index items
        int elementsToMoveThrough = (list->size - 1) - index;

        // Move through the elements in reverse
        for(int i = 0; i < elementsToMoveThrough; i++)
        {
            // Make sure our links are not corrupt
            if(currentItem->prev == NULL)
            {
                // And indicate failure if they are
                return NULL;
            }

            // Otherwise move back through the list
            currentItem = currentItem->prev;
        }

        // We have moved to the required element so can return it
        return currentItem;
    }
}

int energyListRead(struct energyList* list, int index, char* start, char* end, int* energy)
{
    // Get the requested node
    struct energyListNode* node = energyListGetNode(list, index);

    // If it does not exist then indicate failure
    if(node == NULL)
        return 0;

    // Otherwise set the output value
    *start = node->startCity;
    *end = node->endCity;
    *energy = node->energy;

    // And indicate success
    return 1;
}

int energyListRemove(struct energyList* list, int index)
{
    // Get the requested node
    struct energyListNode* node = energyListGetNode(list, index);

    // If the requested node is invalid then return failure now and do nothing else
    if(node == NULL)
        return 0;

    // We now know that the node exists and can start to remove it

    // If we have a previous item make it point to this node's next item
    if(node->prev != NULL)
        node->prev->next = node->next;

    // And similarly for the next node's previous item
    if(node->next != NULL)
        node->next->prev = node->prev;

    // We now need to check if our node was the first item
    // and if so make the head of the list the current node's next item
    if(node == list->head)
        list->head = node->next;

    // And similar for the last item
    if(node == list->tail)
        list->tail = node->prev;

    // There should now be no pointers to our list anywhere in our list structure
    // so we are free to release the memory associated with this node
    energyListNodeDestructor(node);

    // And update the element count
    list->size--;

    // Indicate success
    return 1;
}

int energyListSearch(struct energyList* list, char start, char end, int energy)
{
    // Start at the first node
    struct energyListNode* node = list->head;
    int index = 0;

    // As long as we have an element to test
    while(node != NULL)
    {
        // Check its value and return its index if we have a match
        if(node->energy == energy)
            return index;

        // If this node is not the one we are looking for then move on
        node = node->next;
       index++;
    }

    // If we reach here this point then we have not found the item in our list and should return our failure value
    return -1;
}
