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


int main() {

    Node node = createNode( 5, NULL );
    printList(node);
    return 0;

}
/*ErrorCode mergeSortedLists( Node list1, Node list2, Node *merged_array )
{
    int a = (list1->x > list2->x ) ? list1->x : list2->x;
    printList(list1);
    printList(list2);
    return SUCCESS;
}
*/
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
    ptr->x = num;
    ptr->next = next_node;
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
    int val;
    while( list )
    {
        if(val > list->x)
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