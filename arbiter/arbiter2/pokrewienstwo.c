#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUTLEN 1000
char input[INPUTLEN], Xa[INPUTLEN], Xb[INPUTLEN], R[INPUTLEN], Ya[INPUTLEN],
     Yb[INPUTLEN];

struct _trie {
	int* t;
	struct _trie *c;
};
typedef struct _trie trie;
trie *trieRoot;
void trie_init(trie *);

int main() {
	char input[INPUTLEN];
	trieRoot = (trie*)malloc(sizeof(trie));
	while( fgets(input,INPUTLEN,stdin) != NULL ) {
		/*dbg*/printf("========================================\n");
		sscanf(input," %s %s %s %s %s ",Xa, Xb, R, Ya, Yb);
		/*dbg*/printf("X: .%s.%s.\nR: .%s.\nY: .%s.%s.\n",Xa,Xb,R,Ya,Yb);

		if(strcmp(R,":")==0) {
			/*dbg*/printf("\tthis is query!\n");
		} else if(strcmp(R,"grandparent-of")==0) {
		} else if(strcmp(R,"grandchild-of")==0) {
		} else if(strcmp(R,"cousin-of")==0) {
		} else if(strcmp(R,"sibling-of")==0) {
		} else if(strcmp(R,"parent-of")==0) {
		} else { /*if(strcmp(R,"child-of")==0) {*/
		}

	}
	return 0;
}

void trie_init(trie *x) {
	x->t = NULL;
	x->c = (trie*)malloc(255*sizeof(trie));
}
