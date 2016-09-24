#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>
#include "ptr_range_map.h"

typedef struct PRMNode PRMNode;

struct PRMObj
{
  PRMNode* root;
  pthread_mutex_t lock;
};

struct PRMNode {
  void* ptr_low;
  void* ptr_high;
  OPMSlot* slot;
  PRMNode* left;
  PRMNode* right;
};

static void PRMDestroyNode(PRMNode* node);
static PRMNode* PRMSplay(PRMNode* node, void* ptr_low);
// TODO need a non-blocking find for OPFree


int PRMCreate(PRMObj** tree)
{
  if (!(*tree = calloc(sizeof(PRMObj), 1)))
    return -1;
  return 0;
}
    
void PRMDestroy(PRMObj* tree)
{
  if (tree == NULL) return;
  
  pthread_mutex_lock(&(tree->lock));
  PRMDestroyNode(tree->root);
  pthread_mutex_unlock(&(tree->lock));
  free(tree);
}

void PRMInsert(PRMObj* tree, void* ptr_low, void* ptr_high, OPMSlot* slot)
{
  if (tree == NULL) return;
  
  pthread_mutex_lock(&(tree->lock));

  PRMNode* node = malloc(sizeof(PRMNode));
  op_assert(node, "malloc failed\n");
  node->ptr_low = ptr_low;
  node->ptr_high = ptr_high;
  node->slot = slot;

  if (tree->root == NULL)
    {
      node->left = node->right = NULL;
      tree->root = node;
      return;
    }
  tree->root = PRMSplay(tree->root, ptr_low);
  op_assert(ptr_low >= tree->root->ptr_high ||
         ptr_high < tree->root->ptr_low,
         "ptr range map address collision\n");

  if (ptr_low < tree->root->ptr_low)
    {
      node->left = tree->root->left;
      node->right = tree->root;
      tree->root->left = NULL;
      tree->root = node;
    }
  else if (ptr_low >= tree->root->ptr_high) 
    {
      node->right = tree->root->right;
      node->left = tree->root;
      tree->root->right = NULL;
      tree->root = node;
    }
  else
    {
      op_assert(false, "ptr range map address collision\n");
    }

  pthread_mutex_unlock(&(tree->lock));
}

void PRMDelete(PRMObj* tree, void* ptr)
{
  if (tree == NULL) return;

  pthread_mutex_lock(&(tree->lock));
  tree->root = PRMSplay(tree->root, ptr);
  if (ptr >= tree->root->ptr_low &&
      ptr < tree->root->ptr_high)
    {
      PRMNode* new_root;
      if (tree->root->left == NULL)
        {
          new_root = tree->root->right;
        }
      else
        {
          new_root = PRMSplay(tree->root->left, ptr);
          new_root->right = tree->root->right;
        }
      free(tree->root);
      tree->root = new_root;
    }
  pthread_mutex_unlock(&(tree->lock));
}

OPMSlot* PRMFind(PRMObj* tree, void* ptr)
{
  op_assert(tree, "Tree should not be NULL\n");

  OPMSlot* ret = NULL;

  pthread_mutex_lock(&(tree->lock));
  tree->root = PRMSplay(tree->root, ptr);
  op_assert(ptr >= tree->root->ptr_low &&
            ptr < tree->root->ptr_high,
            "Ptr %p not found in pointer range map\n", ptr);
  
  ret = tree->root->slot;
  pthread_mutex_unlock(&(tree->lock));
  return ret;
}

/****************************
  static methods
*****************************/

void PRMDestroyNode(PRMNode* node)
{
  if (node->left)
    {
      PRMDestroyNode(node->left);
    }
  if (node->right)
    {
      PRMDestroyNode(node->right);
    }
  free(node);
}

PRMNode* PRMSplay(PRMNode* node, void* ptr)
{
  PRMNode *r_tree = NULL, *l_tree = NULL, *tmp;
  PRMNode **r = &r_tree;
  PRMNode **l = &l_tree;
  
  for (;;)
    {
      if (ptr < node->ptr_low)
        {
          if (node->left == NULL) break;
          if (ptr < node->left->ptr_low &&
              node->left->left)
            {
              // zig zig
              tmp = node->left;              
              *r = node->left;
              node->left = tmp->right;
              tmp->right = node;
              node = tmp->left;
              r = &(tmp->left);
            }
          else
            {
              // zig
              *r = node;
              r = &(node->left);
              node = node->left;
            }
        }
      else if (ptr >= node->ptr_high)
        {
          if (node->right == NULL) break;
          if (ptr >= node->right->ptr_high &&
              node->right->right)
            {
              // zig zig
              tmp = node->right;         
              *l = node->right;
              node->right = tmp->left;
              tmp->left = node;
              node = tmp->right;
              l = &(tmp->right);
            }
          else
            {
              // zig
              *l = node;
              l = &(node->right);
              node = node->right;
            }
        }
      else
        {
          break;
        }
    }
  *r = node->right;
  *l = node->left;
  node->right = r_tree;
  node->left = l_tree;
  return node;
}

              
