#ifndef __AVL_H
#define __AVL_H

struct _avlNode {
	int key;			/* klucz w węźle */
	int bal;
	struct _avlNode *l[2];		/* link do dzieci */
};
typedef struct _avlNode avlNode;

#define MEMALLOC(type) ((type*)malloc(sizeof(type)))
#define MEMFREE(obj) free(obj)

void avlInit(avlNode*);
avlNode* avlQuery(avlNode *,int);
avlNode* avlInsert(avlNode **,int);
void avlFree(avlNode*);

#endif
