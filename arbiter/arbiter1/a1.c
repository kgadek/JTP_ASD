#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#define LEFT(i) (2*((i)+1)-1)
#define RIGHT(i) (2*((i)+1))
#define PARENT(i) (((i)-1)/2)
#define INHP(i) ((i)<end-1)
 
struct _probka {
    int pos;
    void *ptr;
};
typedef struct _probka probka;
typedef unsigned int uint;

int cmp(probka*,probka*);

void partition(void **a,uint *p,void **b,uint *q,uint n) {
}

void quicksort(void *a,uint n) {
    uint i,j;
    void *b;
    if(n<2)
	return;
    partition(&a,&i,&b,&j,n);
    quicksort(a,i);
    quicksort(b,j);
}
 
uint N,start,end,step,ps,hs,sum,in;
char type;
probka **tab;
probka *tmp;
 
void swtop(probka**);
void insert(probka**);
void swap(void**,void**);
int comp(const void*,const void*);
 
int main() {
    uint i;
    sum = hs = 0;
    /*dbg*///printf("wczytuje\n");
    scanf("%d %c %d%d%d",&N,&type,&start,&end,&step);
    switch(type) {
        case 'd': ps=sizeof(int);
            break;
        case 'f': ps=sizeof(double);
            break;
        case 's':
        default:
            ps=100*sizeof(char);
            break;
    }
    tab = malloc(end*sizeof(probka*));
    tmp = malloc(sizeof(probka));
    tmp->ptr = (int*)malloc(ps);  
    for(i=0;i<N;++i) {
        tmp->pos=i+1;
        switch(type) {
            case 'd':
		/*dbg*///printf("jeah d: %d\n",*(int*)(tmp->ptr));
                scanf("%d",(int*)(tmp->ptr));
                /*dbg*///printf("# %d: .%d.\n",tmp->pos,*(int*)(tmp->ptr));
                break;
            case 'f':
                scanf("%lf",(double*)(tmp->ptr));
                /*dbg*///printf("# %d: .%lf.\n",tmp->pos,*(double*)(tmp->ptr));
                break;
            case 's':
            default:
                scanf("%s",(char*)(tmp->ptr));
                /*dbg*///printf("# %d: .%s.\n",tmp->pos,(char*)(tmp->ptr));
        }
        if(hs<end-1)
            insert(&tmp);
        else if(cmp(tmp,tab[0])<0)
            swtop(&tmp);
        /*dbg*///switch(type) {
            /*dbg*///case 'd':
                /*dbg*///printf("## %d: .%d.\n\n",tab[i]->pos,*(int*)(tab[i]->ptr));
                /*dbg*///break;
            /*dbg*///case 'f':
                /*dbg*///printf("## %d: .%lf.\n\n",tab[i]->pos,*(double*)(tab[i]->ptr));
                /*dbg*///break;
            /*dbg*///case 's':
            /*dbg*///default:
                /*dbg*///printf("## %d: .%s.\n\n",tab[i]->pos,(char*)(tab[i]->ptr));
        /*dbg*///}
    }
    qsort(tab,end-1,sizeof(probka*),comp);
    for(i=start-1;i<end-1;i+=step)
        sum += tab[i]->pos;
    printf("%d\n",sum);
    return 0;
}
 
void swtop(probka **x) {
    /*dbg*///printf("swtop(%d,%d)\n",(*x)->pos,*(int*)((*x)->ptr));
    uint mx,i=0;
    tab[0]->pos=(*x)->pos;
    memcpy(tab[0]->ptr,(*x)->ptr,ps);
    do {
        mx = i;
        if(INHP(LEFT(i)) && cmp(tab[i],tab[LEFT(i)])<0)
            mx = LEFT(i);                   
        if(INHP(RIGHT(i)) && cmp(tab[mx],tab[RIGHT(i)])<0)
            mx = RIGHT(i);
        if(mx == i) break;
        swap((void*)(tab+i),(void*)(tab+mx));
        i = mx;
    } while(i);                     
    /*dbg*///printf("\tswtop done\n");
}
 
int cmp(probka *a, probka *b) {
    switch(type) {
        case 'd':
            return (*(int*)(a->ptr))-(*(int*)(b->ptr));
        case 'f':
            return (*(double*)(a->ptr))-(*(double*)(b->ptr));
        case 's':
        default:
            return strcmp(a->ptr,b->ptr);
    }
}
 
void insert(probka **x) {
    /*dbg*///printf("insert(%d,%d)\n",(*x)->pos,*(int*)((*x)->ptr));
    uint i = hs;
    tab[hs++] = *x;
    (*x) = malloc(sizeof(probka));
    (*x)->ptr = malloc(ps);
    while(i>0 && cmp(tab[i],tab[PARENT(i)])>0) {
        swap((void*)(tab+i),(void*)(tab+PARENT(i)));
        i = PARENT(i);
    }
}
 
void swap(void **x, void **y) {
    void *z = (*x);
    (*x) = (*y);
    (*y) = z;
}
 
int comp(const void *x,const void *y) {
    return cmp((*((probka**)x)),(*((probka**)y)));
}

