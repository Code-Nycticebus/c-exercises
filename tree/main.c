#include <assert.h>
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

TreeNode *tree_find_min(TreeNode **root) {
  return (*root)->left ? tree_find_min(&(*root)->left) : *root;
}

void tree_delete(TreeNode **root, uint64_t value) {
  if (*root == NULL) {
    return;
  }

  if ((*root)->value < value) {
    tree_delete(&(*root)->right, value);
  } else if ((*root)->value > value) {
    tree_delete(&(*root)->left, value);
  } else {
    if (!(*root)->left && !(*root)->right) {
      // Leaf
      TreeNode *temp = *root;
      *root = NULL;
      free(temp);
    } else if ((*root)->left && (*root)->right) {
      // Two children i dont touch that shit with a 20 inch pole
      TreeNode *temp = tree_find_min(&(*root)->right);
      (*root)->value = temp->value;
      tree_delete(&(*root)->right, temp->value);
      printf("Deleting %lld\n", value);
    } else if ((*root)->left || (*root)->right) {
      // Only left or right
      TreeNode *temp = *root;
      *root = (*root)->left ? (*root)->left : (*root)->right;
      free(temp);
    }
  }
}

bool tree_find(TreeNode **root, uint64_t value) {
  if (*root != NULL) {
    if ((*root)->value == value) {
      return true;
    }
    if ((*root)->value < value) {
      return tree_find(&(*root)->right, value);
    } else if ((*root)->value > value) {
      return tree_find(&(*root)->left, value);
    }
  }
  return false;
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

void tree_destroy(TreeNode **root) {
  if (*root == NULL) {
    return;
  }
  tree_destroy(&(*root)->left);
  tree_destroy(&(*root)->right);
  free(*root);
}

int main(void) {
  TreeNode *root = NULL;

  for (int i = 0; i < 45; ++i) {
    tree_insert(&root, rand() % 100);
  }

  assert(tree_find(&root, 1000) == false);
  assert(tree_find_min(&root)->value == 0);
  tree_delete(&root, 18);
  tree_delete(&root, 27);
  tree_delete(&root, 5);

  FILE *file = fopen("tree.dot", "w");
  tree_dump(file, root);
  fclose(file);

  tree_destroy(&root);
}