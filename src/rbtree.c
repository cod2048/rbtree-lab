#include "rbtree.h"
#include <stdlib.h>

rbtree *new_rbtree(void)
{
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  // TODO: initialize struct if needed
  // 새로운 트리 안에 초기노드(nil)을 넣을 공간만 생성 후 해당 공간의 주솟값을 저장
  node_t *nil = (node_t *)calloc(1, sizeof(node_t));

  // 그 공간에 루트값이 들어올 거고, 루트는 무조건 블랙이니까 색깔만 블랙으로 저장
  nil->color = RBTREE_BLACK;

  // 지금 트리가 비었으니 root는 nil노드임
  p->root = p->nil = nil;

  return p;
}

void tree_free(rbtree *t, node_t *d)
{
  if (d != t->nil)
  {
    tree_free(t, d->left);
    tree_free(t, d->right);
    free(d);
  }
}
void delete_rbtree(rbtree *t)
{
  // TODO: reclaim the tree nodes's memory
  tree_free(t, t->root);
  free(t->nil);
  free(t);
}

void l_rotation(rbtree *t, node_t *g_node)
{
  node_t *temp = g_node->right;
  g_node->right = temp->left;
  if (temp->left != t->nil)
  {
    temp->left->parent = g_node;
  }
  temp->parent = g_node->parent;
  if (g_node->parent == t->nil)
  {
    t->root = temp;
  }
  else if (g_node->parent->left == g_node)
  {
    g_node->parent->left = temp;
  }
  else
  {
    g_node->parent->right = temp;
  }
  g_node->parent = temp;
  temp->left = g_node;
}

void r_rotation(rbtree *t, node_t *g_node)
{
  node_t *temp = g_node->left;
  g_node->left = temp->right;
  if (temp->right != t->nil)
  {
    temp->right->parent = g_node;
  }
  temp->parent = g_node->parent;
  if (g_node->parent == t->nil)
  {
    t->root = temp;
  }
  else if (g_node->parent->right == g_node)
  {
    g_node->parent->right = temp;
  }
  else
  {
    g_node->parent->left = temp;
  }
  g_node->parent = temp;
  temp->right = g_node;
}

node_t *rbtree_insert(rbtree *t, const key_t key)
{
  // TODO: implement insert
  // 새로운 값을 저장할 노드 생성
  node_t *new_node = (node_t *)malloc(sizeof(node_t));
  // 해당 노드에 이 함수에 들어온 key 값 저장
  new_node->key = key;
  // 새로운 노드는 항상 빨강
  new_node->color = RBTREE_RED;
  // 왼쪽, 오른쪽 모두 닐을 자식으로 가짐(가르킴)
  new_node->left = new_node->right = new_node->parent = t->nil;

  node_t *location = t->root;
  node_t *head = t->nil;
  while (location != t->nil)
  {
    head = location;
    if (new_node->key <= location->key)
    {
      location = location->left;
    }
    else
    {
      location = location->right;
    }
  }

  if (head == t->nil)
  {
    t->root = new_node;
  }
  else if (head->key > key)
  {
    head->left = new_node;
  }
  else
  {
    head->right = new_node;
  }

  new_node->parent = head;

  while (new_node->parent->color == RBTREE_RED)
  {
    if (new_node->parent == new_node->parent->parent->left)
    {
      if (new_node->parent->parent->right->color == RBTREE_BLACK)
      {
        if (new_node->parent->right == new_node)
        {
          new_node = new_node->parent;
          l_rotation(t, new_node);
        }
        new_node->parent->parent->color = RBTREE_RED;
        new_node->parent->color = RBTREE_BLACK;
        r_rotation(t, new_node->parent->parent);
        // rotation
      }
      else
      {
        new_node->parent->parent->color = RBTREE_RED;
        new_node->parent->parent->right->color = RBTREE_BLACK;
        new_node->parent->color = RBTREE_BLACK;
        new_node = new_node->parent->parent;
      }
    }
    else
    {
      if (new_node->parent->parent->left->color == RBTREE_BLACK)
      {
        if (new_node->key < new_node->parent->key)
        {
          new_node = new_node->parent;
          r_rotation(t, new_node);
        }
        new_node->parent->parent->color = RBTREE_RED;
        new_node->parent->color = RBTREE_BLACK;
        l_rotation(t, new_node->parent->parent);
        // rotation
      }
      else
      {
        new_node->parent->parent->color = RBTREE_RED;
        new_node->parent->parent->left->color = RBTREE_BLACK;
        new_node->parent->color = RBTREE_BLACK;
        new_node = new_node->parent->parent;
      }
    }
  }

  t->root->color = RBTREE_BLACK;
  return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key)
{
  // TODO: implement find
  node_t *find = t->root;
  while (find->key != key)
  {
    if (find == t->nil)
    {
      return NULL;
    }
    else if (find->key < key)
    {
      find = find->right;
    }
    else
    {
      find = find->left;
    }
  }
  return find;
}

node_t *rbtree_min(const rbtree *t)
{
  // TODO: implement find
  node_t *min = t->root;
  while (min->left != t->nil)
  {
    min = min->left;
  }
  return min;
}

node_t *rbtree_max(const rbtree *t)
{
  // TODO: implement find
  node_t *max = t->root;
  while (max->right != t->nil)
  {
    max = max->right;
  }
  return max;
}

void transplant(rbtree *t, node_t *u, node_t *v)
{
  if (u->parent == t->nil)
  {
    t->root = v;
  }
  else if (u == u->parent->left)
  {
    u->parent->left = v;
  }
  else
  {
    u->parent->right = v;
  }
  v->parent = u->parent;
}
int rbtree_erase(rbtree *t, node_t *p)
{
  // TODO: implement erase
  node_t *node = p;
  node_t *x = t->nil;
  node_t *w = t->nil;
  color_t originalcolor = node->color;
  if (p->left == t->nil)
  {
    x = p->right;
    transplant(t, p, p->right);
  }
  else if (p->right == t->nil)
  {
    x = p->left;
    transplant(t, p, p->left);
  }
  else
  {
    // p의 자식이 둘일 때
    node = node->right;
    while (node->left != t->nil)
    {
      node = node->left;
    }
    originalcolor = node->color;
    x = node->right;
    if (node->parent == p)
    {
      x->parent = node;
    }
    else
    {
      transplant(t, node, node->right);
      node->right = p->right;
      node->right->parent = node;
    }
    transplant(t, p, node);
    node->left = p->left;
    node->left->parent = node;
    node->color = p->color;
  }
  if (originalcolor == RBTREE_BLACK)
  {
    // fixup
    while (x != t->root && x->color == RBTREE_BLACK)
    {
      if (x == x->parent->left)
      {
        w = x->parent->right;
        if (w->color == RBTREE_RED)
        {
          w->color = RBTREE_BLACK;
          x->parent->color = RBTREE_RED;
          l_rotation(t, x->parent);
          w = x->parent->right;
        }
        if (w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK)
        {
          w->color = RBTREE_RED;
          x = x->parent;
        }
        else
        {
          if (w->right->color == RBTREE_BLACK)
          {
            w->left->color = RBTREE_BLACK;
            w->color = RBTREE_RED;
            r_rotation(t, w);
            w = x->parent->right;
          }
          w->color = x->parent->color;
          x->parent->color = RBTREE_BLACK;
          w->right->color = RBTREE_BLACK;
          l_rotation(t, x->parent);
          x = t->root;
        }
      }
      else
      {
        w = x->parent->left;
        if (w->color == RBTREE_RED)
        {
          w->color = RBTREE_BLACK;
          x->parent->color = RBTREE_RED;
          r_rotation(t, x->parent);
          w = x->parent->left;
        }
        if (w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK)
        {
          w->color = RBTREE_RED;
          x = x->parent;
        }
        else
        {
          if (w->left->color == RBTREE_BLACK)
          {
            w->right->color = RBTREE_BLACK;
            w->color = RBTREE_RED;
            l_rotation(t, w);
            w = x->parent->left;
          }
          w->color = x->parent->color;
          x->parent->color = RBTREE_BLACK;
          w->left->color = RBTREE_BLACK;
          r_rotation(t, x->parent);
          x = t->root;
        }
      }
    }
  }
  x->color = RBTREE_BLACK;
  return 0;
}
// Tree to In-order Array
int Inorder(const rbtree *t, node_t *node, key_t *arr, const size_t n, int idx)
{
  if (idx < n)
  {
    if (node->left != t->nil)
    {
      idx = Inorder(t, node->left, arr, n, idx);
    }
    arr[idx++] = node->key;
    if (node->right != t->nil)
    {
      idx = Inorder(t, node->right, arr, n, idx);
    }
  }
  return idx;
}
int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n)
{
  // TODO: implement to_array
  Inorder(t, t->root, arr, n, 0);
  return 0;
}
