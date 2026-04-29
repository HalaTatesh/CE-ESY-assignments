#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// 1. تعريف الحجم (SIZE) بناءً على الـ Pseudocode
#define SIZE 50 

// 2. تعريف هيكل المخزن الدائري (STRUCT)
typedef struct {
    char buffer[SIZE];
    int head;  // مؤشر القراءة
    int tail;  // مؤشر الكتابة
    int count; // عدد العناصر الحالية
} CircularBuffer;

// 3. دالة التهيئة (Initialization)
void init(CircularBuffer *cb) {
    cb->head = 0;
    cb->tail = 0;
    cb->count = 0;
}

// 4. حالات الامتلاء والفراغ
bool isFull(CircularBuffer *cb) {
    return cb->count == SIZE;
}

bool isEmpty(CircularBuffer *cb) {
    return cb->count == 0;
}

// 5. دالة الكتابة (write)
void write_cb(CircularBuffer *cb, char data) {
    if (isFull(cb)) {
        printf("\nBuffer Overflow!\n");
        return;
    }
    cb->buffer[cb->tail] = data;
    cb->tail = (cb->tail + 1) % SIZE; // العودة للصفر إذا وصلنا للنهاية
    cb->count++;
}

// 6. دالة القراءة (read)
char read_cb(CircularBuffer *cb) {
    if (isEmpty(cb)) {
        printf("\nBuffer Underflow!\n");
        return '\0';
    }
    char data = cb->buffer[cb->head];
    cb->head = (cb->head + 1) % SIZE; // العودة للصفر إذا وصلنا للنهاية
    cb->count--;
    return data;
}

// 7. الدالة الرئيسية (main) وتنفيذ المطلوب
int main() {
    CircularBuffer cb;
    init(&cb);

    char name[SIZE];
    printf("Enter your name: ");
    
    // إدخال الاسم من المستخدم
    if (fgets(name, sizeof(name), stdin)) {
        name[strcspn(name, "\n")] = 0; // إزالة سطر النهاية
    }

    // إضافة السلسلة المطلوبة " CE-ESY"
    strcat(name, " CE-ESY");

    // تخزين كل حرف في المخزن الدائري
    for (int i = 0; i < strlen(name); i++) {
        write_cb(&cb, name[i]);
    }

    // القراءة من المخزن وعرض النتيجة
    printf("Result from Buffer: ");
    while (!isEmpty(&cb)) {
        printf("%c", read_cb(&cb));
    }
    printf("\n");

    // التأكد من أن المخزن أصبح فارغاً
    if (isEmpty(&cb)) {
        printf("Verification: Buffer is empty now.\n");
    }

    return 0;
}
