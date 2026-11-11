#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "tree.h"
#include "log.h"

static void   _inPrint(const node_t *root);
static void  _prePrint(const node_t *root, FILE *file);
static void _postPrint(const node_t *root);

static void writeNodeGraph(FILE *file, node_t *node);

static int GLOBAL_FILE_LOG_PNG_NUM = 0;

node_t* treeAddNode(node_t *root, treeElement_t el) {
    log("Try to add el " TREE_ELEMENT_FORMATER " to %p", el, root);

    node_t *true_root = root;

    node_t *old_root = root;
    while (root) {
        old_root = root;
        if (root->data < el) root = root->right;
        else                 root = root->left;
    }

    node_t *new_node = (node_t*)calloc(1, sizeof(node_t));
    if (new_node == NULL) return NULL;

    new_node->data = el;

    if (true_root) {
        if (old_root->data < el) old_root->right = new_node;
        else                     old_root->left  = new_node; 

        treeDump(true_root);
    } 

    logOK("Add el " TREE_ELEMENT_FORMATER, el);
    return new_node;
}

void   inPrint(const node_t *root) {  _inPrint(root);         printf("\n");}
void  prePrint(const node_t *root) { _prePrint(root, stdout); printf("\n");}
void postPrint(const node_t *root) {_postPrint(root);         printf("\n");}

static void _inPrint(const node_t *node) {
    // log("_inPrint(%p)", node);

    if (node == NULL) return;

    printf("(");

    _inPrint(node->left);
    printf(TREE_ELEMENT_FORMATER, node->data);
    _inPrint(node->right);

    printf(")");
}

static void _prePrint(const node_t *node, FILE *file) {
    // log("_prePrint(%p)", node);
    assert(file);

    if (node == NULL) {
        fprintf(file, "()");
        return;
    }

    fprintf(file, "(");

    fprintf(file, TREE_ELEMENT_FORMATER, node->data);
    _prePrint(node->left, file);
    _prePrint(node->right, file);

    fprintf(file, ")");
}

static void _postPrint(const node_t *node) {
    // log("_postPrint(%p)", node);

    if (node == NULL) return;

    printf("(");

    _postPrint(node->left);
    _postPrint(node->right);
    printf(TREE_ELEMENT_FORMATER, node->data);

    printf(")");
}

void treeDump(node_t *root) {
    assert(root);

    log("--TREE-DUMP--");

    FILE *file = fopen("graph.txt", "w");
    if (file == NULL) return;

    fprintf(file, "digraph {\n");
    fprintf(file, "splines=line\n");
    fprintf(file, "V%p[shape=Mrecord]\n", root);
    writeNodeGraph(file, root);
    fprintf(file, "}");

    fclose(file);

    char filename[20] = {};
    sprintf(filename, "gr%d.png", GLOBAL_FILE_LOG_PNG_NUM);

    char command[60] = {};
    sprintf(command, "dot graph.txt -Tpng -o %s", filename);
    system(command);
    log("<img height=100 src=\"%s\">", filename);

    GLOBAL_FILE_LOG_PNG_NUM++;

    log("--END-TREE-DUMP--");
}

static void writeNodeGraph(FILE *file, node_t *node) {
    assert(file);
    assert(node);

    if (node == NULL) return;

    fprintf(file, "V%p[label=\"{data=" TREE_ELEMENT_FORMATER " | name=%p | {<left> left | <right> right}}\"]\n", node, node->data, node);

    if (node->left) {
        fprintf(file, "V%p:left -> V%p[label=\"left\"]\n", node, node->left);
        fprintf(file, "V%p[shape=\"record\"]\n", node->left);
        writeNodeGraph(file, node->left);
    } else if (node->right) {
        fprintf(file, "V%p:left -> NULL%p[color=\"white\"]\n", node, node);
        fprintf(file, "NULL%p[color=\"white\", label=\"\"]\n", node);
    }
    if (node->right) {
        fprintf(file, "V%p:right -> V%p[label=\"right\"]\n", node, node->right);
        fprintf(file, "V%p[shape=\"Mrecord\"]\n", node->right);
        writeNodeGraph(file, node->right);
    } else if (node->left) {
        fprintf(file, "V%p:right -> NULL%p[color=\"white\"]\n", node, node);
        fprintf(file, "NULL%p[color=\"white\", label=\"\"]\n", node);
    }
}

void treeDestroy(node_t *node) {
    assert(node);

    if (node->left) {
        treeDestroy(node->left);
    }
    if (node->right) {
        treeDestroy(node->right);
    }
    free(node);
}

bool treeWrite(node_t *root, char *filename) {
    assert(root);
    assert(filename);

    FILE *file = fopen(filename, "wb");
    
    if (!file) return false;
    
    _prePrint(root, file);

    fclose(file);
    
    return true;
}

static node_t* readNode(FILE *file) {
    assert(file);

    int c = fgetc(file);
    // log("start readNode: symb %c", c);

    treeElement_t data = 0;
    if (!fscanf(file, TREE_ELEMENT_FORMATER, &data)) {
        fgetc(file);
        return NULL;
    }

    // log("now read node_data " TREE_ELEMENT_FORMATER, data);

    node_t *node = (node_t*)calloc(1, sizeof(node_t));
    if (!node) return NULL;

    node->data = data;
    node->left  = readNode(file);
    node->right = readNode(file);

    log("node at %p data = " TREE_ELEMENT_FORMATER " left: %p, right: %p", node, node->data, node->left, node->right);


    fgetc(file);

    return node;
}

// (10(10()())(20(20()())(40(30(30()())())(80()(100()())))))
node_t* treeRead(char *filename) {
    assert(filename);
    
    FILE *file = fopen(filename, "rb");
    if (!file) return NULL;

    node_t *root = readNode(file);

    fclose(file);
    
    if (!root) return NULL;

    return root;
}
