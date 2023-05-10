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
    printf("%d\n", t->root->key);
    printf("%d\n", t->root->color);
    printf("%d\n", t->root->left->key);
    printf("%d\n", t->root->left->color);
    printf("%d\n", t->root->right->key);
    printf("%d\n", t->root->right->color);
    printf("%d\n", t->root->left->left->key);
    printf("%d\n", t->root->left->left->color);
    printf("%d\n", t->root->left->right->key);
    printf("%d\n", t->root->left->right->color);
    printf("%d\n", t->root->right->left->key);
    printf("%d\n", t->root->right->left->color);
    printf("%d\n", t->root->right->right->key);
    printf("%d\n", t->root->right->right->color);
    printf("%d\n", t->root->left->right->right->key);
    printf("%d\n", t->root->left->right->right->color);
    printf("%d\n", t->root->left->left->left->key);
    printf("%d\n", t->root->left->left->left->color);
    printf("%d\n", t->root->right->right->right->key);
    printf("%d\n", t->root->right->right->right->color);
    printf("최솟값:%d\n",rbtree_min(t)->key);
    printf("최댓값:%d\n",rbtree_max(t)->key);
    }
    else{
        printf("확인");
    }
}