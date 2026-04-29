#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 50 

typedef struct {
    char buffer[SIZE];
    int head;  
    int tail;  
    int count; 
} CircularBuffer;

void init(CircularBuffer *cb) {
    cb->head = 0;
    cb->tail = 0;
    cb->count = 0;
}

bool isFull(CircularBuffer *cb) {
    return cb->count == SIZE;
}

bool isEmpty(CircularBuffer *cb) {
    return cb->count == 0;
}

void write_cb(CircularBuffer *cb, char data) {
    if (isFull(cb)) {
        printf("\nBuffer Overflow!\n");
        return;
    }
    cb->buffer[cb->tail] = data;
    cb->tail = (cb->tail + 1) % SIZE; 
    cb->count++;
}

char read_cb(CircularBuffer *cb) {
    if (isEmpty(cb)) {
        printf("\nBuffer Underflow!\n");
        return '\0';
    }
    char data = cb->buffer[cb->head];
    cb->head = (cb->head + 1) % SIZE; 
    cb->count--;
    return data;
}

int main() {
    CircularBuffer cb;
    init(&cb);

    char name[SIZE];
    printf("Enter your name: ");
    
    if (fgets(name, sizeof(name), stdin)) {
        name[strcspn(name, "\n")] = 0; 
    }

    strcat(name, " CE-ESY");

    for (int i = 0; i < strlen(name); i++) {
        write_cb(&cb, name[i]);
    }

    printf("Result from Buffer: ");
    while (!isEmpty(&cb)) {
        printf("%c", read_cb(&cb));
    }
    printf("\n");

    if (isEmpty(&cb)) {
        printf("Verification: Buffer is empty now.\n");
    }

    return 0;
}
