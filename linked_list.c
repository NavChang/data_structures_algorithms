#include <stdio.h>
#include <stdlib.h>

struct LinkedListElement {
    int payload;
    struct LinkedList * next;
};

struct LinkedList {
    struct LinkedListElement * head;
    struct LinkedListElement * tail;
};

struct LinkedList * createLinkedList(){
    struct LinkedList *list = (struct LinkedList*) malloc(sizeof(struct LinkedList));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

int size(struct LinkedList * list){
    int len = 0;
    struct LinkedListElement * temp = list->head;
    while (temp != NULL){
        len++;
        temp = temp->next;
    }
    return len;
}

void pushFront(struct LinkedList* list, int payload){
    struct LinkedListElement * newNode = (struct LinkedListElement*) malloc(sizeof(struct LinkedListElement));
    newNode->payload = payload;
    newNode->next = list->head;
    if (list->head == NULL)
        list->tail = newNode;
    list->head = newNode;
}

int popFront(struct LinkedList * list){
    if (list->head == NULL){
        printf("List is empty, cannot pop\n");
        exit(EXIT_FAILURE);
    }
    int payload = list->head->payload;
    struct LinkedListElement * newHead = list->head->next;
    free(list->head);
    list->head = newHead;
    if (newHead == NULL)
        list->tail = newHead;
    return payload;
}

int popback(struct LinkedList * list){
    if (list->tail == NULL){
        printf("List is empty, cannot pop\n");
        exit(EXIT_FAILURE);
    }
    int payload = list->tail->payload;
    struct LinkedListElement * temp = list->head;
    if (list->head == list->tail){
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
        return payload;
    }
    for(temp; temp->next ==list->tail; temp = temp->next){
        if (temp->next == list->tail){
            free(list->tail);
            temp->next = NULL;
            list->tail = temp;
            return payload;
        }
    }   
}

void pushBack(struct LinkedList* list, int payload){
    struct LinkedListElement * newNode = (struct LinkedListElement*) malloc(sizeof(struct LinkedListElement));
    newNode->payload = payload;
    newNode->next = NULL;
    if (list->tail == NULL)   
        list->head = newNode;
    else
        list->tail->next = newNode;
    list->tail = newNode;
}

void insert(struct LinkedList * list, int index, int value){
    struct LinkedListElement * newNode = (struct LinkedListElement *) malloc(sizeof(struct LinkedListElement));
    newNode->payload = value;
    struct LinkedListElement * current = list->head;
    while (index > 1){
        if (current == NULL){
            printf("index error.\n");
            exit(EXIT_FAILURE);
        }
        current = current->next;
        index--;
    }
    newNode->next = current->next;
    current->next = newNode;
}

void printList(struct LinkedList * list){
    struct LinkedListElement * temp = list->head;
    printf("Contents of list: [");
    while(temp != NULL){
        printf("%d%s", temp->payload, (temp->next == NULL) ? "]\n" : ", ");
        temp = temp->next;
    }
}

void printStatus(struct LinkedList * list){
    if (isEmpty(list)){
        printf("list is empty\n");
    }
    else{
    printf("Head of list: %d\n", list->head->payload);
    printf("Tail of list: %d\n", list->tail->payload);
    printList(list);
    }
}

void reverse(struct LinkedList * list){
    // struct LinkedList * newList = createLinkedList();
    // while (!isEmpty(list))
    //     pushFront(newList, popFront(list));
    // free(list);
    // list = newList;
    // printStatus(list);
    struct LinkedListElement * prev, *current, *next;
    prev = NULL;
    current = list->head;
    list->tail = list->head;
    while(current != NULL){
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    list->head = prev;
}

int isEmpty(struct LinkedList * list){
    if (list->head == NULL)
        return 1;
    return 0;
}

main(){
    struct LinkedList * list = createLinkedList();
    int s = size(list);
    printf("size of list is %d\n", s);
    pushFront(list, 6);
    pushFront(list, 8);
    printList(list);
    int p = popFront(list);
    printf("Popped front to get: %d\n", p);
    pushBack(list, 99);
    printStatus(list);
    int x = popback(list);
    int y = popback(list);
    printStatus(list);
    for (int i = 0; i < 19; i++)
        pushBack(list, i);
    printStatus(list);
    insert(list, 5, 500);
    printStatus(list);
    printf("Reversing the list\n");
    reverse(list);
    printStatus(list);
}