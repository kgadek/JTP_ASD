#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define INPUTLEN 1000
char input[INPUTLEN], X[INPUTLEN], Xb[INPUTLEN], R[INPUTLEN], Y[INPUTLEN],
     Yb[INPUTLEN];

typedef struct _node node;
typedef struct _ndlist ndlist;

/*********************[ LIST ]*********************/
struct _ndlist {
	struct _ndlist *n;		/* nastepny */
	struct _node *p;
};
void listInit(ndlist*);
void listAdd(ndlist**,struct _node*);
node* listSearch(ndlist*,char*);

/*********************[ NODE ]*********************/
struct _node {
	char *name;
	struct _node *p;
	ndlist *ch;
};
void nodeInit(node*);
node* nodeJoin(node**,node**);

/*********************[ TRIE ]*********************/
struct _trie {
	node *l;		/* link do node'a */
	struct _trie *ch[256];
};
typedef struct _trie trie;
trie *trieRoot;
void trieInit(trie *);
node* trieIns(trie*,char*);
node* trieQuery(trie*,char*);

/*********************[ MAIN ]*********************/
int main() {
	trieRoot = (trie*)malloc(sizeof(trie));
	trieInit(trieRoot);
	node *x,*y,*t;
	while( fgets(input,INPUTLEN,stdin) != NULL ) {
		/*dbg*/printf("\n\n============================================================\n");
		sscanf(input," %s %s %s %s %s ",X, Xb, R, Y, Yb);
		strcat(X," "); strcat(X,Xb);
		strcat(Y," "); strcat(Y,Yb);
		/*dbg*/int i; printf("\nX: .%s.\nR: .%s.\nY: .%s.\n",X,R,Y);
		/*dbg*/for(i=0;i<strlen(X);++i) printf("%d.",X[i]+128); printf("\n");
		/*dbg*/for(i=0;i<strlen(Y);++i) printf("%d.",Y[i]+128); printf("\n");
		/*dbg*/printf("pytanie o %s: ",X);
		if((x=trieQuery(trieRoot,X))==NULL) {
			/*dbg*/printf("nie ma\n");
			x = trieIns(trieRoot,X);
		} /*dbg*/else printf("jest: %s\n",x->name);
		assert(x!=NULL);
		/*dbg*/printf("pytanie o %s: ",Y);
		if((y=trieQuery(trieRoot,Y))==NULL) {
			/*dbg*/printf("nie ma\n");
			y = trieIns(trieRoot,Y);
		} /*dbg*/else printf("jest: %s\n",y->name);
		assert(y!=NULL);

		if(strcmp(R,":")==0) {
			/*dbg*/printf("\tthis is query!\n");
		} else {
			if(strcmp(R,"grandparent-of")==0) {
			} else if(strcmp(R,"grandchild-of")==0) {
				// przejdz do ojca lub utworz ojca-widmo
				// ustaw ojca + wzajemnosci
			} else if(strcmp(R,"cousin-of")==0) {
				// przejdz do ojca X lub utworz ojca-widmo (A)
				// przejdz do ojca Y lub utworz ojca-widmo (B)
				// przejdz do dziadka lub utworz dziadka-widmo
				// ustaw dziadka + wzajemnosci
				// ustaw ojcow + wzajemnosci
			} else if(strcmp(R,"sibling-of")==0) {
				// przejdz do ojca lub utworz ojca-widmo
				// ustaw ojca + wzajemnosci
			} else if(strcmp(R,"parent-of")==0) {
				t = listSearch(x->ch,Y);
				if(y->p == x && t != NULL)
					continue;		/* wszystko zrobione */
				if(y->p == NULL)
					y->p = x;
				else 
					nodeJoin(&(y->p), &x);
				if(t == NULL)
					listAdd(&(x->ch),y);
			} else { /*if(strcmp(R,"child-of")==0) {*/
				// ustaw ojca + wzajemnosci
			}
		}

	}
	return 0;
}

void trieInit(trie *x) {
	int i=-1;
	x->l = NULL;
	while(i<255) {
		x->ch[++i] = NULL;
	}
}

node* trieIns(trie *x, char *tx) {
	char ch;
	char *or = tx;
	while( (ch=*(tx++)) != '\n' && ch != 0 ) {
		if(x->ch[ch+128] == NULL) {
			x->ch[ch+128] = (trie*)malloc(sizeof(trie));
			trieInit(x->ch[ch+128]);
		}
		x = x->ch[ch+128];
	}
	if(x->l == NULL) {
		x->l = (node*)malloc(sizeof(node));
		nodeInit(x->l);
		x->l->name = (char*)malloc(INPUTLEN*sizeof(char));
	}
	strcpy(x->l->name,or);
	return x->l;
}

node* trieQuery(trie *x,char *tx) {
	char ch;
	while( (ch=*(tx++)) != '\n' && ch != 0 ) {
		if(x->ch[ch+128] == NULL)
			return NULL;
		x = x->ch[ch+128];
	}
	return x->l;
}

void nodeInit(node *x) {
}

void listInit(ndlist *x) {
	x->p = NULL;
	x->n = NULL;
}

void listAdd(ndlist **x, node *p) {
	assert(p!=NULL);
	/*dbg*/printf("jestem\n");
	ndlist *y = *x;
	assert(*x);
	assert(y->p);
	while( y != NULL && y->p != p) {
		/*dbg*/printf("kp\n");
		x = &(y->n);
		y = y->n;
	}
	if(y->p == p)
		return;
	if((*x)==NULL) {
		(*x) = (ndlist*)malloc(sizeof(ndlist));
		listInit(*x);
	}
	(*x)->p = p;
}

node* nodeJoin(node **x, node **y) {
	return NULL;
}

node* listSearch(ndlist *x, char *tx) {
	return NULL;
}
