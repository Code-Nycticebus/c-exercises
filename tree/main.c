#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define TREE_CHILDREN_MAX 5

typedef struct TreeNode {
  uint64_t value;
  struct TreeNode *left;
  struct TreeNode *right;
} TreeNode;

TreeNode *treenode(uint64_t value) {
  TreeNode *node = malloc(sizeof(TreeNode));
  node->left = NULL;
  node->right = NULL;
  node->value = value;
  return node;
}

void tree_insert(TreeNode **root, uint64_t value) {
  if (*root == NULL) {
    *root = treenode(value);
    return;
  }
  if ((*root)->value < value) {
    tree_insert(&(*root)->right, value);
  } else if ((*root)->value > value) {
    tree_insert(&(*root)->left, value);
  }
}

void _tree_dump_r(FILE *file, TreeNode *node) {
  if (node != NULL) {
    if (node->left) {
      fprintf(file, "\t%lld -> %lld\n", node->value, node->left->value);
      _tree_dump_r(file, node->left);
    }
    if (node->right) {
      fprintf(file, "\t%lld -> %lld\n", node->value, node->right->value);
      _tree_dump_r(file, node->right);
    }
    if (!node->right && !node->left) {
      fprintf(file, "\t%lld\n", node->value);
    }
  }
}

void tree_dump(FILE *file, TreeNode *node) {
  fprintf(file, "digraph Tree {\n");
  _tree_dump_r(file, node);
  fprintf(file, "}\n");
}

int main(void) {
  TreeNode *root = NULL;

  for (int i = 0; i < 100; ++i) {
    tree_insert(&root, rand() % 1000);
  }

  FILE *file = fopen("tree.dot", "w");
  tree_dump(file, root);
  fclose(file);
}