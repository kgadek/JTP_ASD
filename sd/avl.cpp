#ifndef __AVL
#define __AVL

#include <cstdlib>
#include <cassert>
#include <cppunit/TestAssert.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

#define MEMALLOC(type) ((type*)malloc(sizeof(type)))
#define MEMFREE(obj) free(obj)

struct _avlNode {
	int key;			/* klucz w węźle */
	int bal;
	struct _avlNode *l[2];		/* link do dzieci */
};
typedef struct _avlNode avlNode;

void avlInit(avlNode*);
avlNode* avlQuery(avlNode *,int);
avlNode* avlInsert(avlNode *,int);
void avlFree(avlNode*);

namespace print_tree {
        int a=1, b=0, c=5;
        void _print(avlNode *x, int h) {
                if(h<=0) return;
                if(x==NULL) {
                        for(h=(1<<(h-1))-1;h>=0;--h)
                                putchar('\n');
                        return;
                }
                int i=a*(c*(h-1))+b+1;
                _print(x->l[0],h-1);
                while(--i>0) putchar(' ');
                printf("%c[;%dm(%3d)%c[%dm\n",
                                0x1B,32+x->bal,x->key,
                                0x1B,0);
                _print(x->l[1],h-1);
        }
        void print_rev(avlNode *x, int h) {
                a=1;
                _print(x,h);
        }
        void print_norm(avlNode *x, int h) {
		/*dbg*/printf("__________________________________________________\n");
                a=-1;
                b+=(h-1)*c;
                _print(x,h);
                b-=(h-1)*c;
        }
};

/***********************************************************************/
/**************************** implementacje ****************************/
/***********************************************************************/

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
		/*dbg*/printf("pre  p:%d r:%d s:%d\n",p->key,r->key,s->key);
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

/***********************************************************************/
/********************************* testy *******************************/
/***********************************************************************/
class avl_testCase1 : public CppUnit::TestFixture {		/* podst. testy popr. */
	CPPUNIT_TEST_SUITE( avl_testCase1 );
	CPPUNIT_TEST(testA);
	CPPUNIT_TEST(testB);
	CPPUNIT_TEST(testC);
	CPPUNIT_TEST(testD);
	CPPUNIT_TEST_SUITE_END();
	avlNode *root;
	int balanceCheck(avlNode*);
public:
	void setUp();
	void tearDown();
	void testA();
	void testB();
	void testC();
	void testD();
};

void avl_testCase1::setUp() {
	root = NULL;
}

void avl_testCase1::tearDown() {
	avlFree(root);
}

int avl_testCase1::balanceCheck(avlNode* x) {
	if(x==NULL)
		return 0;
	int r,l;
	l = balanceCheck(x->l[0]);
	r = balanceCheck(x->l[1]);
	if( l>=0 && r>=0 && r - l == x->bal && -1 <= x->bal && x->bal <= 1)
		return l>r?l:r;
	return -1;
}

void avl_testCase1::testA() {		/* testy pustego drzewa */
	CPPUNIT_ASSERT( root == NULL );			/* self */
	CPPUNIT_ASSERT( avlQuery(root,5) == NULL );	/* avlQuery */
	CPPUNIT_ASSERT( avlQuery(root,6) == NULL);
	CPPUNIT_ASSERT( avlQuery(root,5) == NULL);
	CPPUNIT_ASSERT( avlQuery(root,6) == NULL);
	CPPUNIT_ASSERT( avlQuery(root,-10000) == NULL);
	CPPUNIT_ASSERT( avlQuery(root,10000) == NULL);
}

void avl_testCase1::testB() {		/* testy drzewa z jednym wierz. */
	CPPUNIT_ASSERT( root == NULL );	/* self */
	CPPUNIT_ASSERT( avlInsert(&root,7) != NULL );	/* avlInsert */
	CPPUNIT_ASSERT( avlQuery(root,5) == NULL );	/* avlQuery */
	CPPUNIT_ASSERT( avlQuery(root,6) == NULL );
	CPPUNIT_ASSERT( avlQuery(root,7) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,7)->key == 7 );
	CPPUNIT_ASSERT( balanceCheck(root) >= 0 );	/* balans */
}

void avl_testCase1::testC() {		/* testy drzewa z ponad 1 wierzcholkiem */
	CPPUNIT_ASSERT( avlInsert(&root,7) != NULL );	/* dodawanie wierzcholkow */
	CPPUNIT_ASSERT( avlQuery(root,7) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,7)->key == 7 );
	/*dbg*/print_tree::print_norm(root,7);
	CPPUNIT_ASSERT( avlInsert(&root,1) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,1) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,1)->key == 1 );
	CPPUNIT_ASSERT( avlQuery(root,7) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,7)->key == 7 );
	/*dbg*/print_tree::print_norm(root,7);
	CPPUNIT_ASSERT( avlInsert(&root,2) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,1) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,1)->key == 1 );
	CPPUNIT_ASSERT( avlQuery(root,7) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,7)->key == 7 );
	CPPUNIT_ASSERT( avlQuery(root,2) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,2)->key == 2 );
	/*dbg*/print_tree::print_norm(root,7);
	CPPUNIT_ASSERT( avlInsert(&root,7) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,7) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,7)->key == 7 );
	/*dbg*/print_tree::print_norm(root,7);
	CPPUNIT_ASSERT( avlInsert(&root,3) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,1) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,1)->key == 1 );
	CPPUNIT_ASSERT( avlQuery(root,7) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,7)->key == 7 );
	CPPUNIT_ASSERT( avlQuery(root,2) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,2)->key == 2 );
	CPPUNIT_ASSERT( avlQuery(root,3) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,3)->key == 3 );
	/*dbg*/print_tree::print_norm(root,7);
	CPPUNIT_ASSERT( avlInsert(&root,7) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,7) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,7)->key == 7 );
	/*dbg*/print_tree::print_norm(root,7);
	CPPUNIT_ASSERT( avlInsert(&root,4) != NULL );
	/*dbg*/printf("dodatkowy print:\n");
	/*dbg*/print_tree::print_norm(root,7);
	CPPUNIT_ASSERT( avlQuery(root,1) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,1)->key == 1 );
	CPPUNIT_ASSERT( avlQuery(root,7) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,7)->key == 7 );
	CPPUNIT_ASSERT( avlQuery(root,2) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,2)->key == 2 );
	CPPUNIT_ASSERT( avlQuery(root,3) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,3)->key == 3 );
	CPPUNIT_ASSERT( avlQuery(root,4) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,4)->key == 4 );
	/*dbg*/print_tree::print_norm(root,7);
	CPPUNIT_ASSERT( avlInsert(&root,5) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,1) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,1)->key == 1 );
	CPPUNIT_ASSERT( avlQuery(root,7) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,7)->key == 7 );
	CPPUNIT_ASSERT( avlQuery(root,2) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,2)->key == 2 );
	CPPUNIT_ASSERT( avlQuery(root,3) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,3)->key == 3 );
	CPPUNIT_ASSERT( avlQuery(root,4) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,4)->key == 4 );
	CPPUNIT_ASSERT( avlQuery(root,5) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,5)->key == 5 );
	/*dbg*/print_tree::print_norm(root,7);
	CPPUNIT_ASSERT( avlInsert(&root,6) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,1) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,1)->key == 1 );
	CPPUNIT_ASSERT( avlQuery(root,7) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,7)->key == 7 );
	CPPUNIT_ASSERT( avlQuery(root,2) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,2)->key == 2 );
	CPPUNIT_ASSERT( avlQuery(root,3) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,3)->key == 3 );
	CPPUNIT_ASSERT( avlQuery(root,4) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,4)->key == 4 );
	CPPUNIT_ASSERT( avlQuery(root,5) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,5)->key == 5 );
	CPPUNIT_ASSERT( avlQuery(root,6) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,6)->key == 6 );
	/*dbg*/print_tree::print_norm(root,7);
	CPPUNIT_ASSERT( avlInsert(&root,7) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,7) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,7)->key == 7 );
	/*dbg*/print_tree::print_norm(root,7);
	CPPUNIT_ASSERT( balanceCheck(root) >= 0 );
	CPPUNIT_ASSERT( avlInsert(&root,8) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,1) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,1)->key == 1 );
	CPPUNIT_ASSERT( avlQuery(root,7) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,7)->key == 7 );
	CPPUNIT_ASSERT( avlQuery(root,2) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,2)->key == 2 );
	CPPUNIT_ASSERT( avlQuery(root,3) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,3)->key == 3 );
	CPPUNIT_ASSERT( avlQuery(root,4) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,4)->key == 4 );
	CPPUNIT_ASSERT( avlQuery(root,5) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,5)->key == 5 );
	CPPUNIT_ASSERT( avlQuery(root,6) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,6)->key == 6 );
	CPPUNIT_ASSERT( avlQuery(root,8) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,8)->key == 8 );
	/*dbg*/print_tree::print_norm(root,7);
	CPPUNIT_ASSERT( avlInsert(&root,9) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,1) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,1)->key == 1 );
	CPPUNIT_ASSERT( avlQuery(root,7) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,7)->key == 7 );
	CPPUNIT_ASSERT( avlQuery(root,2) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,2)->key == 2 );
	CPPUNIT_ASSERT( avlQuery(root,3) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,3)->key == 3 );
	CPPUNIT_ASSERT( avlQuery(root,4) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,4)->key == 4 );
	CPPUNIT_ASSERT( avlQuery(root,5) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,5)->key == 5 );
	CPPUNIT_ASSERT( avlQuery(root,6) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,6)->key == 6 );
	CPPUNIT_ASSERT( avlQuery(root,8) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,8)->key == 8 );
	CPPUNIT_ASSERT( avlQuery(root,9) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,9)->key == 9 );
	/*dbg*/print_tree::print_norm(root,7);
	CPPUNIT_ASSERT( avlInsert(&root,5) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,5) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,5)->key == 5 );
	/*dbg*/print_tree::print_norm(root,7);
	CPPUNIT_ASSERT( avlInsert(&root,1) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,1) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,1)->key == 1 );
	/*dbg*/print_tree::print_norm(root,7);
	CPPUNIT_ASSERT( avlInsert(&root,2) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,2) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,2)->key == 2 );
	/*dbg*/print_tree::print_norm(root,7);
	CPPUNIT_ASSERT( avlInsert(&root,10) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,1) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,1)->key == 1 );
	CPPUNIT_ASSERT( avlQuery(root,7) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,7)->key == 7 );
	CPPUNIT_ASSERT( avlQuery(root,2) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,2)->key == 2 );
	CPPUNIT_ASSERT( avlQuery(root,3) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,3)->key == 3 );
	CPPUNIT_ASSERT( avlQuery(root,4) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,4)->key == 4 );
	CPPUNIT_ASSERT( avlQuery(root,5) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,5)->key == 5 );
	CPPUNIT_ASSERT( avlQuery(root,6) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,6)->key == 6 );
	CPPUNIT_ASSERT( avlQuery(root,8) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,8)->key == 8 );
	CPPUNIT_ASSERT( avlQuery(root,9) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,9)->key == 9 );
	CPPUNIT_ASSERT( avlQuery(root,10) != NULL );
	CPPUNIT_ASSERT( avlQuery(root,10)->key == 10 );
	/*dbg*/print_tree::print_norm(root,7);
	CPPUNIT_ASSERT( balanceCheck(root) >= 0 );	/* sprawdzenie balansu
							   drzewa */
}

void avl_testCase1::testD() {		/* test usuwania drzewa */
	avlFree(root);
	CPPUNIT_ASSERT( balanceCheck(root) == 0 );	/* self */
	CPPUNIT_ASSERT( root == NULL );
	CPPUNIT_ASSERT( avlQuery(root,1) == NULL );
	CPPUNIT_ASSERT( avlQuery(root,7) == NULL );
	CPPUNIT_ASSERT( avlQuery(root,1) == NULL );
	CPPUNIT_ASSERT( avlQuery(root,7) == NULL );
	CPPUNIT_ASSERT( avlQuery(root,3) == NULL );
	CPPUNIT_ASSERT( avlQuery(root,-1000) == NULL );
}

CPPUNIT_TEST_SUITE_REGISTRATION( avl_testCase1 );

#endif
