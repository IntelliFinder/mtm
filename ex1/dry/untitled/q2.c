#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
#include <assert.h>
#include <stdbool.h>


typedef struct node_t{
    int x;
    struct node_t *next;
} *Node;

typedef enum {
    SUCCESS=0,
    MEMORY_ERROR,
    EMPTY_LIST,
    UNSORTED_LIST,
    NULL_ARGUMENT,

} ErrorCode;

/* returns length of list */
int getListLength( Node list );

/* returns true if list sorted, false otherwise*/
bool isListSorted( Node list );

/* merged two sorted lists */
ErrorCode mergeSortedLists( Node list1, Node list2, Node* merged_array );

/* prints list up to this point*/
void printList( Node list );

/* create node  */
Node createNode( int num, Node next_node );

/*delete node*/
void deleteNode( Node list );

ErrorCode mergeSortedLists( Node list1, Node list2, Node *mergedOut);

//default
int main() {

    Node list1 = createNode( 2, createNode( 4, createNode( 8, NULL )));
    Node list2 = createNode( 1, createNode( 4, createNode( 9, NULL )));
    Node tmp = createNode(0,NULL);
    Node *mergedOut = &tmp;
    ErrorCode er = mergeSortedLists(list1,list2, mergedOut);
    printList(*mergedOut);

    return 0;

}
//null
int main2() {

    Node list1 =NULL;
    Node list2 = createNode( 1, createNode( 4, createNode( 9, NULL )));
    Node tmp = createNode(0,NULL);
    Node *mergedOut = &tmp;
    ErrorCode er = mergeSortedLists(list1,list2, mergedOut);
    printList(*mergedOut);

    return 0;

}
//not sorted
int main3() {

    Node list1 = createNode( 2, createNode( 4, createNode( 8, NULL )));
    Node list2 = createNode( 1, createNode( 9, createNode( 9, NULL )));
    Node tmp = createNode(0,NULL);
    Node *mergedOut = &tmp;
    ErrorCode er = mergeSortedLists(list1,list2, mergedOut);
    printList(*mergedOut);

    return 0;

}
//kaze
int main4() {

    Node list1 = createNode( 2, NULL );
    Node list2 = createNode( 3, NULL);
    Node tmp = createNode(0,NULL);
    Node *mergedOut = &tmp;
    ErrorCode er = mergeSortedLists(list1,list2, mergedOut);
    printList(*mergedOut);

    return 0;

}

ErrorCode mergeSortedLists( Node list1, Node list2, Node *mergedOut)
{
    if(list1 == NULL || list2 == NULL || mergedOut == NULL)
    {
        return EMPTY_LIST;
    }
    if(!isListSorted(list1) || !isListSorted(list2)){
        return UNSORTED_LIST;
    }
    Node start = createNode(0,NULL);
    if(start->x == NULL){
        *mergedOut = NULL;
        return MEMORY_ERROR;
    }
    if(list1->x < list2->x){
        start->x = list1->x;
        list1 = list1->next;
    }
    else{
        assert(list2->x <= list1->x); //nice
        start->x = list2->x;
        list2 = list2->next;
    }
    Node run = start; //memory leak
    while (list1 != NULL || list2 != NULL)
    {
        run->next = createNode(0,NULL); //0 is default
        run = run->next;
        if(run == NULL){
            do {
                run = start->next;
                deleteNode(start);
                start = run;
            }
            while (run != NULL);
            *mergedOut = NULL;
            return MEMORY_ERROR;
        }
        if(list1 == NULL){
            run->x = list2->x;
            list2 = list2->next;
        }
        else if(list2 == NULL) {
            run->x = list1->x;
            list1 = list1->next;
        }
        else if(list1->x < list2->x){
            run->x = list1->x;
            list1 = list1->next;
        }
        else{
            assert(list2->x <= list1->x);
            run->x = list2->x;
            list2 = list2->next;
        }
    }
    (*mergedOut)->x = start->x;
    (*mergedOut)->next = start->next; //where is start->next
    return SUCCESS;
}
void printList(Node list)
{
    while(list)
    {
        printf("%d\n", list->x);
        list=list->next;
    }
}

Node createNode( int num, Node next_node )
{
    Node ptr = malloc( sizeof(*ptr) );
    assert(ptr);
    if(ptr!=NULL){
        ptr->x = num;
        ptr->next = next_node;
    }

    return ptr;
}
void deleteNode( Node list )
{
    if( !list )
        return;
    deleteNode( list->next );
    free( list );
}
bool isListSorted( Node list )
{
    int val = list->x;
    while( list )
    {
        if(val > list->x) //uprising order
            return false;
        val = list->x;
        list = list->next;
    }
    return true;
}

int getListLength( Node list )
{
    int idx=0;
    while(list)
    {
        idx++;
        list= list->next;
    }
    return idx;
}

