#ifndef __AVL
#define __AVL

#include "avl.h"
#include "common.h"
#include <cstdio>
#include <cstdlib>
#include <cassert>


void avlInit(avlNode *x) {
	x->bal = 0;
	x->l[0] = x->l[1] = NULL;
}

avlNode* avlInsert(avlNode **R, int k) {
	/*dbg*/printf("insert(%d)\n",k);
	if(*R == NULL) {			/* Knuth zaklada niepuste drzewo */
		(*R) = MEMALLOC(avlNode);
		avlInit(*R);
		(*R)->key = k;
		return *R;
	}
	/*dbg*/assert( *R != NULL );
	avlNode *head, *p, *q, *r, *s, *t, *u;
	int a,d;
	head = MEMALLOC(avlNode); 		/* utworzenie HEAD */
	avlInit(head);
	/*dbg*/assert( head != NULL );
	head->l[0] = *R;					/* A1. inicjacja */
	t = head;
	q = p = s = *R;
	while(q != NULL) {					/* A2. szukanie */
		/*dbg*/assert( p != NULL );
		if(k == p->key)	 {				/* exit_success */
			return p;
		}
		d = (k > p->key);
		q = p->l[d];					/* A3/A4. przejscie
									lewo/prawo */
		if(q == NULL) {
			/*dbg*/assert( p != NULL );
			p->l[d] = u = q = MEMALLOC(avlNode);
			avlInit(q);
			break;
		} else if(q->bal != 0) {
			t = p;
			s = q;
		}
		p = q;
	}
	//q = MEMALLOC(avlNode);				/* A5. wstawienie */
	/*dbg*/assert( q != NULL );
	//avlInit(q);
	q->key = k;
	/*dbg*/assert( s != NULL );
	r = p = s->l[ k > s->key ];				/* A6. poprawa wartosci
									balansow */
	/*dbg*/assert( q->key == k );
	/*dbg*/assert( p != NULL );
	while(p!=q) {
		/*dbg*/assert( p != NULL );
		/*dbg*/assert( p->key != k );
		d = (k > p->key);
		p->bal = 2*d - 1;
		p = p->l[d];
	}
	/*dbg*/assert( s != NULL );
	a = (k < s->key)?-1:1;					/* A7. ustawienie
								   	balansu drzewa */
	if(s->bal == 0) {				/* A7.i */
		s->bal = a;
		return u;
	} else if(s->bal == -a) {			/* A7.ii */
		s->bal = 0;
		return u;
	}						/* A7.iii */
	/*dbg*/assert( s->bal == a );
	/*dbg*/assert( a <= 1 );
	/*dbg*/assert( -1 <= a );
	/*dbg*/printf("pre balance print:\n");
	print_tree::print_norm(*R,7);
	if(r->bal == a ) {				/* A8. pojedyncza
							   	rotacja */
		/*dbg*/printf("single-rot\n");
		d = a<0?0:1;
		p = r;
		s->l[d] = r->l[1-d];
		r->l[1-d] = s;
		s->bal = r->bal = 0;
	} else {					/* A9. podwojna
								rotacja */
		/*dbg*/printf("double-rot\n");
		d = a<0?0:1;
		p = r->l[1-d];
		/*dbg*/printf("pre  p:%d r:%d s:%d\n",p->key,r->key,s->key);
		r->l[1-d] = p->l[d];
		p->l[d] = r;
		s->l[d] = p->l[1-d];
		p->l[1-d] = s;
		s->bal = r->bal = 0;
		if(p->bal == a)
			s->bal = -a;
		else if(p->bal == -a)
			r->bal = a;
		/*dbg*/printf("post p:%d r:%d s:%d\n",p->key,r->key,s->key);
	}
	if(s == t->l[1])
		t->l[1] = p;
	else
		t->l[0] = p;
	(*R) = t->l[0];
	return u;
}

avlNode* avlQuery(avlNode *R, int k) {
	while(R && R->key != k)
		R = R->l[k > R->key];
	return R;
}

void avlFree(avlNode *x) {
	if(x==NULL)
		return;
	avlFree(x->l[0]);
	avlFree(x->l[1]);
	MEMFREE(x);
}

#endif
