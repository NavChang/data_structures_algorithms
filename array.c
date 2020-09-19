#include <stdio.h>
#include <stdlib.h>

const int GROWTH_FACTOR = 2;
const int START_CAPACITY = 16;

struct Vector * makeVector();
int size(struct Vector *);
int isEmpty(struct Vector *);
void push(struct Vector *, int);
void insert(struct Vector *, int, int);
void delete(struct Vector *, int);
void prepend(struct Vector*, int);
int capacity(struct Vector *);
int pop(struct Vector *);
void printVector(struct Vector *);
void resize(struct Vector*);
void removeV(struct Vector *, int);
void printStatus(struct Vector *);
int get(struct Vector *, int );

typedef struct Vector{
    int capacity;
    int size;
    int * array;
};

main(){
    struct Vector *vector = makeVector();
    for (int i = 0; i < 25; i++){
        push(vector, i);
    }
    printStatus(vector);
    int p = get(vector, 18);
    printf("Element at index 18 is %d\n", p);
    insert(vector, 18, 500);
    printStatus(vector);

    p = pop(vector);
    printf("pop to get %d\n", p);
    printStatus(vector);

    printf("deleting at index 5\n");
    delete(vector, 5);
    printStatus(vector);

    printf("Removing 500\n");
    removeV(vector, 500);
    printStatus(vector);

    free(vector->array);
    free(vector);
}

void printStatus(struct Vector *vector){
    printf("size of vector is %d\n", size(vector));
    printf("capacity of vector is %d\n", capacity(vector));
    printf("the vector is %sempty\n", isEmpty(vector) ? "" : "not ");
    printVector(vector);
    printf("\n");
}


struct Vector * makeVector(){
    struct Vector *vector = malloc(sizeof(*vector));
    vector->capacity = START_CAPACITY;
    vector->size = 0;
    vector->array = (int *) malloc(sizeof(int) * vector->capacity);
    return vector;
}

int size(struct Vector *v){
    return v->size;
}

int capacity(struct Vector *v){
    return v->capacity;
}

int isEmpty(struct Vector *v){
    return (v->size == 0);
}

void push(struct Vector *v, int i){
    (v->array)[v->size++] = i;
    if (v->capacity == v->size)
        resize(v);
}

void resize(struct Vector *v){
    int *newArray = (int *) malloc(sizeof(int) * v->capacity * GROWTH_FACTOR);
    for (int i = 0; i < v->size; i++)
        newArray[i] = v->array[i];
    v->capacity *= GROWTH_FACTOR;
    free(v->array);
    v->array = newArray;
}

int get(struct Vector * v, int i){
    if (i < 0 || i >= v->size){
        printf("Index out of bounds. Tried to access index %d of array of size %d.\n", i, v->size);
        exit(EXIT_FAILURE);
    }
    return v->array[i];
}

void insert(struct Vector * v, int index, int item){
    if (index < 0 || index >= v->size){
        printf("Index out of bounds. Tried to insert at index %d of array of size %d.\n", index, v->size);
        exit(EXIT_FAILURE);
    }
    for (int i = ++v->size; i > index; i--){
        v->array[i] = v->array[i-1];
    }
    v->array[index] = item;
}

void prepend(struct Vector * v, int item){
    insert(v, 0, item);
}

int pop(struct Vector * v){
    if (v->size < 1){
        printf("vector is empty");
        exit(EXIT_FAILURE);
    }
    return v->array[--v->size];
}

void delete(struct Vector * v, int index) {
    if (index < 0 || index >= v->size){
        printf("Index out of bounds. Tried to delete at index %d of array of size %d.\n", index, v->size);
        exit(EXIT_FAILURE);
    }
    for (int i = index; i < v->size; i++)
        v->array[i] = v->array[i+1];
    v->size--;
}

void removeV(struct Vector * v, int item){
    for (int i = 0; i < v->size; i++){
        if (v->array[i] == item){
            delete(v, i);
        }
    }
}

void printVector(struct Vector *v){
    printf("Contents : [");
    for (int i = 0; i < v->size; i++)
        printf("%d%s", v->array[i], (i == v->size -1) ? "]\n" : ", ");
}