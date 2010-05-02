#include <cstdio>
#include <climits>
#include <cstdlib>

class node {
public:
	node *l, *r;
	int val;
	node() { l=r=NULL; val=0; }
};

node *h;
int t,res,cnt;
char in[255];

void add(node*,int);
int read(node*,int,int,int);

int main() {
	h = new node;
	res=0; cnt=0;
	h->l=NULL;
	h->r=NULL;
	while(scanf("%s",in)!=EOF) {
		t = atoi(in);
		if(t==0) {
			printf("-1\n");
			return 0;
		}
		res += cnt++ - read(h,t,0,INT_MAX);
		add(h,t);
	}
	printf("%d\n",res);
	delete h;
    return 0;
}

int read(node *h,int t,int l,int p) {
	int ret=0;
	while(l<p && h) {
		if(t<=(p-l)/2+l) {
			p=(p-l)/2+l;
			h=h->l;
		} else {
			//ret += read(h->l,t,l,p);
			ret += h->l!=NULL?h->l->val:0;
			l=(p-l)/2+l+1;
			h=h->r;
		}
	}
	if(p==t && h)
		ret+=h->val;
	return ret;
}

void add(node *h,int t) {
	int l=0, p=INT_MAX;
	h->val++;
	while(l<p) {
		if(t<=(p-l)/2+l) {
			if(h->l==NULL) h->l = new node;
			h=h->l;
			p=(p-l)/2+l;
		} else {
			if(h->r==NULL) h->r = new node;
			h=h->r;
			l=(p-l)/2+l+1;
		}
		h->val++;
	}
}

