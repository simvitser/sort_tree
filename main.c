#include <stdio.h>

#include "tree.h"
#include "log.h"

int main() {
    logInit("log.htm");
    log("<pre>");

    // node_t *root = treeAddNode(NULL, 10);
    // treeAddNode(root, 20);
    // treeAddNode(root, 40);
    // treeAddNode(root, 80);
    // treeAddNode(root, 30);
    // treeAddNode(root, 10);
    // treeAddNode(root, 20);
    // treeAddNode(root, 100);
    // treeAddNode(root, 30);
    //
    // prePrint(root);
    // treeWrite(root, "tree.tree");
    
    node_t *root = treeRead("tree.tree");
    printf("data root: " TREE_ELEMENT_FORMATER "\n", root->data);
    prePrint(root);

    treeDump(root);
    // treeAddNode(root, 10000);

    treeDestroy(root);
    log("</pre>");
    logDestroy();
}
