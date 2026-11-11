#ifndef _TREE_H
#define _TREE_H

#include <stdbool.h>
#include <stdlib.h>

typedef int treeElement_t;
#define TREE_ELEMENT_FORMATER "%d"

struct _node_t {
    struct _node_t *left;
    struct _node_t *right;

    treeElement_t data;
};

typedef struct _node_t node_t;

node_t* treeAddNode(node_t *root, treeElement_t el);

void   inPrint(const node_t *node);
void  prePrint(const node_t *node);
void postPrint(const node_t *node);

void treeDestroy(node_t *node);

bool treeWrite(node_t *node, char *filename);

void treeDump(node_t *root);

node_t* treeRead(char *filename);

#endif
