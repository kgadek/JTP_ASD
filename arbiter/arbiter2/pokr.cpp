#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cstring>

#define INPUTLEN 1000

char input[INPUTLEN], X[INPUTLEN], Xb[INPUTLEN],
     R[INPUTLEN], Y[INPUTLEN], Yb[INPUTLEN];

class node {
public:
	char *name;
	node();
};

node *x, *y;

class trie {
public:
	node *l;
	trie *ch[256];
	trie();
	~trie();
	node* query(char*);
	node* add(char*);
};

int main() {
	trie spis;
	while( fgets(input,INPUTLEN,stdin) != NULL ) {
		sscanf(input," %s %s %s %s %s ", X, Xb, R, Y, Yb);
		strcat(X," "); strcat(X,Xb);
		strcat(Y," "); strcat(Y,Yb);
		/*dbg*/printf("==================================================\n");
		/*dbg*/printf("X: %s\nR: %s\nY: %s\n",X, R, Y);
		/*dbg*/printf("\n\n");
		if( (x=spis.query(X)) == NULL ) {
			/*dbg*/printf("\tnie ma %s\n",X);
			x = spis.add(X);
		}
		if( (y=spis.query(Y)) == NULL ) {
			/*dbg*/printf("\tnie ma %s\n",Y);
			y = spis.add(Y);
		}
	}
	return 0;
}

trie::trie() {
	int i;
	for(i=0;i<256;++i)
		ch[i] = NULL;
	l = NULL;
}

trie::~trie() {
	int i;
	for(i=0;i<256;++i)
		if(ch[i] != NULL)
			delete ch[i];
	if(l) {
		delete l;
		l = NULL;
	}
}

node* trie::query(char *t) {
	char c;
	trie *x = this;
	while( (c=*(t++)) != '\n' && c != 0 ) {
		if(ch[c+128] == NULL)
			return NULL;
		x = ch[c+128];
	}
	return x->l;
}

node* trie::add(char *t) {
	char c;
	char *o = t;
	trie *x = this;
	while( (c=*(t++)) != '\n' && c != 0 ) {
		if( x->ch[c+128] == NULL)
			x->ch[c+128] = new trie;
		x = x->ch[c+128];
	}
	if(x->l == NULL)
		x->l = new node;
	strcpy(x->l->name,o);
	return x->l;
}

node::node() {
	name = new char[INPUTLEN];
}
