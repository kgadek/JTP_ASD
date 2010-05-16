#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define INPUTLEN 1000
char input[INPUTLEN], X[INPUTLEN], Xb[INPUTLEN], R[INPUTLEN], Y[INPUTLEN],
     Yb[INPUTLEN];

typedef int node;

struct _trie {
	node *l;		/* link do node'a */
	struct trie *ch[256];
};
typedef struct _trie trie;
trie *trieRoot;
void trieInit(trie *);
node* trieIns(trie*,char*);
node* trieQuery(trie*,char*);

int main() {
	trieRoot = (trie*)malloc(sizeof(trie));
	trieInit(trieRoot);
	node *x,*y;
	while( fgets(input,INPUTLEN,stdin) != NULL ) {
		/*dbg*/printf("========================================\n");
		sscanf(input," %s %s %s %s %s ",X, Xb, R, Y, Yb);

		strcat(X," ");
		strcat(X,Xb);
		strcat(Y," ");
		strcat(Y,Yb);

		/*dbg*/int i;
		/*dbg*/printf("\n");
		/*dbg*/printf("X: .%s.\nR: .%s.\nY: .%s.\n",X,R,Y);
		/*dbg*/for(i=0;i<strlen(X);++i) printf("%d.",X[i]+128);
		/*dbg*/printf("\n");
		/*dbg*/for(i=0;i<strlen(Y);++i) printf("%d.",Y[i]+128);
		/*dbg*/printf("\n");

		if((x=trieQuery(trieRoot,X))==NULL)
			x = trieIns(trieRoot,X);
		assert(x!=NULL);
		if((y=trieQuery(trieRoot,Y))==NULL)
			y = trieIns(trieRoot,Y);
		assert(y!=NULL);

		if(strcmp(R,":")==0) {
			/*dbg*/printf("\tthis is query!\n");
		} else {
			if(strcmp(R,"grandparent-of")==0) {
			} else if(strcmp(R,"grandchild-of")==0) {
			} else if(strcmp(R,"cousin-of")==0) {
			} else if(strcmp(R,"sibling-of")==0) {
			} else if(strcmp(R,"parent-of")==0) {
			} else { /*if(strcmp(R,"child-of")==0) {*/
			}
		}

	}
	return 0;
}

void trieInit(trie *x) {
	int i=-1;
	x->l = NULL;
	while(i<255) x->ch[++i]=NULL;
}

node* trieIns(trie *x, char *tx) {
	char ch;
	while( (ch=*(tx++)) != NULL ) {
	}
}

node* trieQuery(trie *x,char *tx) {
	return NULL;
}

