#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 50 

typedef struct {
    char buffer[SIZE];
    int head;   // مؤشر القراءة
    int tail;   // مؤشر الكتابة
    int count;  // عداد العناصر
} CircularBuffer;

// دالة تهيئة المخزن
void init(CircularBuffer *cb) {
    cb->head = 0;
    cb->tail = 0;
    cb->count = 0;
}

// فحص هل المخزن ممتلئ
bool isFull(CircularBuffer *cb) {
    return cb->count == SIZE;
}

// فحص هل المخزن فارغ
bool isEmpty(CircularBuffer *cb) {
    return cb->count == 0;
}

// دالة الكتابة في المخزن
void write_cb(CircularBuffer *cb, char data) {
    if (isFull(cb)) {
        printf("\nBuffer Overflow!\n");
        return;
    }
    cb->buffer[cb->tail] = data;
    cb->tail = (cb->tail + 1) % SIZE; // الالتفاف الدائري
    cb->count++;
}

// دالة القراءة والإزالة من المخزن
char read_cb(CircularBuffer *cb) {
    if (isEmpty(cb)) {
        printf("\nBuffer Underflow!\n");
        return '\0';
    }
    char data = cb->buffer[cb->head];
    cb->head = (cb->head + 1) % SIZE; // الالتفاف الدائري
    cb->count--;
    return data;
}

int main() {
    CircularBuffer cb;
    init(&cb); // البداية

    char name[SIZE];
    printf("Enter your name: ");
    
    // إدخال الاسم
    if (fgets(name, sizeof(name), stdin)) {
        name[strcspn(name, "\n")] = 0; 
    }

    strcat(name, " CE-ESY"); // إضافة النص المطلوب

    // تخزين الاسم في المخزن
    for (int i = 0; i < strlen(name); i++) {
        write_cb(&cb, name[i]);
    }

    // قراءة وعرض النتيجة
    printf("Result from Buffer: ");
    while (!isEmpty(&cb)) {
        printf("%c", read_cb(&cb));
    }
    printf("\n");

    // التأكد من فراغ المخزن
    if (isEmpty(&cb)) {
        printf("Verification: Buffer is empty now.\n");
    }

    return 0;
}
