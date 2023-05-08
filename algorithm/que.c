#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next;
} node;
// 스택이랑 동일하게 노드 생성(데이터와 다음 데이터를 가리키는 포인터 포함)

typedef struct queue {
    node* front;
    node* rear;
} queue;
// 큐는 앞, 뒤를 가르키는 포인터 필요

void init_queue(queue* q) {
    q->front = NULL;
    q->rear = NULL;
}
// 맨앞, 포인터값을 초기화

void enqueue(queue* q, int value) {
    node* new_node = (node*)malloc(sizeof(node));
    //동적 메모리로 node 공간 확보
    new_node->data = value;
    //노드를 생성해고 이 함수에 들어온 value값을 data에 저장
    new_node->next = NULL;
    //일단 next에 NULL값 넣음

    if (q->rear == NULL) {
        q->front = new_node;
        q->rear = new_node;
    } // 뒤에 값이 없으면 front와 rear 둘 다 새로 생긴 값으로 초기화
    else {
        q->rear->next = new_node;
        q->rear = new_node;
    } // 맨뒤랑 다음 포인터 둘다 새로 들어온 노드 가르키게 해야댐
}

int dequeue(queue* q) {
    if (q->front != NULL) {
        node* temp = q->front;
        int result = temp->data;

        q->front = temp->next;
        free(temp);

        if (q->front == NULL) {
            q->rear = NULL;
        }

        return result;
    }
    else {
        printf("값이 없음\n");
        return -1;
    }
}

void print_queue(queue* q) {
    if (q->front == NULL) {
        printf("큐가 비어있음\n");
        return;
    }

    node* temp = q->front;

    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
}

int main(void)
{
    queue q;
    init_queue(&q);

    enqueue(&q, 1);
    enqueue(&q, 2);
    enqueue(&q, 3);

    print_queue(&q);

    printf("값: %d\n", dequeue(&q));
    printf("값: %d\n", dequeue(&q));
    printf("값: %d\n", dequeue(&q));

    return 0;
}