#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node* next;

}node;

typedef struct stack
{
    node* top;
}stack;

void init_stack(stack* s)
{
    s->top = NULL;
}

void append(stack* s, int value){
    
    node* new_node = (node *)malloc(sizeof(node));
    // 처음에 선언자체를 malloc으로 해야되는구나 그래야지 pop했을 때 메모리가 다시 줄어들음
    
    new_node->data = value;
    // 스택에 node를 넣음 
    
    new_node->next = s->top;
    // 다음 값에 null넣어놓음

    s->top = new_node;
    // stack의 top이 방금 만든 node가르키게 함(스택 만든 척 하는거임, 사실 스택처럼 안생김)
}

int pop(stack* s){
    
    if (s->top != NULL){
        node *a = s->top;
        // stack에 맨 위에 있는 데이터를 a에 저장해놓음

        int result = a->data;
        // 리턴시킬라고 result에 저장시킴

        s->top = a->next;
        // top이 가르키는걸 한칸 내림(내린 척하는거임, 사실 내려간건 아님)

        free(a);
        // a지워버림

        return result;
    }
    else{
        printf("값이 없습니다.");
        return -1;
    }
}

void print_stack(stack* s){
    if (s->top == NULL) {
        printf("스택이 비어있습니다.\n");
        return;
    }
    
    node *a = s->top;

    while (a != NULL){
        printf("%d ", a->data);
        a = a->next;
    }
}

int main(void)
{
    stack s;
    init_stack(&s);

    append(&s, 1);
    append(&s, 2);
    append(&s, 3);

    print_stack(&s);

    printf("값: %d\n", pop(&s));
    printf("값: %d\n", pop(&s));
    printf("값: %d\n", pop(&s));
    

    return 0;
}