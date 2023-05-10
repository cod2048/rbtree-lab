#include "rbtree.h"
#include "rbtree.c"
#include <stdio.h>

int main(int argc, char *argv[])
{
    rbtree *t = new_rbtree();

    rbtree_insert(t, 10);
    rbtree_insert(t, 5);
    rbtree_insert(t, 8);
    rbtree_insert(t, 34);
    rbtree_insert(t, 67);
    rbtree_insert(t, 23);
    rbtree_insert(t, 156);
    rbtree_insert(t, 24);
    rbtree_insert(t, 2);
    rbtree_insert(t, 12);
    if(t->root != t->nil){
    printf("최솟값:%d\n",rbtree_min(t)->key);
    printf("최댓값:%d\n",rbtree_max(t)->key);
    printf("찾는값:%d\n",rbtree_find(t, 12)->key);
    }
    else{
        printf("확인");
    }
}