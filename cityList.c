#include <stdlib.h>
#include <stdio.h>

#include "shortPath.h"

struct cityListNode
{
    char *city;

    struct cityListNode* next;
    struct cityListNode* prev;

};

struct CityList
{
    // Number of elements in the list
    int size;

    // Start and end of our list
    struct cityListNode* head;
    struct cityListNode* tail;
};

// Allocate a new listNode with the provided value
struct cityListNode* cityListNodeConstructor(char* city)
{
    struct cityListNode* newNode;

    char* cityCopy = malloc(sizeof(char) * strlen(city));

    // Reserve memory for a node
    newNode = malloc(sizeof(struct cityListNode));

    strcpy(cityCopy, city);

    // Set its values
    newNode->city = city;
    newNode->next = NULL;
    newNode->prev = NULL;

    // And return it
    return newNode;
}

// Release the memory of the provided node
void cityListNodeDestructor(struct cityListNode* node)
{
    // We have no extra memory other than this node so simply free it
    free(node);
}

// Create a new linked list
struct CityList* cityListConstructor()
{
    // Check we are using the right list implementation
    printf("Linked list constructor\n");

    // Reserve memory for the list
    struct CityList* newLinkedList;
    newLinkedList = malloc(sizeof(struct CityList));

    // Initialise it appropriately
    newLinkedList->size = 0;
    newLinkedList->head = NULL;
    newLinkedList->tail = NULL;

    // And return it
    return newLinkedList;
}

void cityListDestructor(struct CityList* linkedList)
{
    printf("Linked list destructor\n");

    // We need these to traverse the list
    struct cityListNode* currentRecord;
    struct cityListNode* nextRecord = linkedList->head;

    // As long as the record to process exists
    while(nextRecord != NULL)
    {
        // Move to it
        currentRecord = nextRecord;

        // And update where to go next
        nextRecord = currentRecord->next;

        // And release the memory associated with this node
        cityListNodeDestructor(currentRecord);
    }

    // Now all of the nodes have been release so we can release the list too
    free(linkedList);
}

// Add a new item to the end of the list
int cityListAdd(struct CityList* list, char* city)
{
    int unique =1;

    // Build our new node
    struct cityListNode* newNode = cityListNodeConstructor(city);

    struct cityListNode* scan = list->head;

    while((scan != NULL) && unique == 1)
    {

            //strings compared and if they are the same it returns 0 which will
            //change the unique flag back to 0 so it doesnt
            if(strcmp(city, scan->city) == 0)
            {
                unique = 0;
            }
            scan = scan->next;
    }

    if (unique == 1)
    {
        // The node that will come before this node is currently the list tail
        // Note that this also works if the list is empty
        newNode->prev = list->tail;

        // And we will not have a next element
        newNode->next = NULL;
    }
    // If the list is not empty
    if(list->tail != NULL)
    {
        // Tell the current tail that it now has a next element
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

void cityListDisplay(struct CityList* list)
{

    // We start with the head of the list
    struct cityListNode* currentNode = list->head;

    // And print each element in turn until we are looking at NULL
    while(currentNode != NULL)
    {
        // Print a comma before the values after the first
        if(currentNode != list->head)
        {
            printf(",");
        }

        // Print the current value
        printf("%s\n", currentNode->city);

        // Move to the next node
        currentNode = currentNode->next;
    }
}

int cityListSearch(struct CityList* list, char city)
{
    // Start at the first node
    struct cityListNode* node = list->head;
    int index = 0;

    // As long as we have an element to test
    while(node != NULL)
    {
        // Check its value and return its index if we have a match
        if(node->city == city)
            return index;

        // If this node is not the one we are looking for then move on
        node = node->next;
       index++;
    }

    // If we reach here this point then we have not found the item in our list and should return our failure value
    return -1;
}
