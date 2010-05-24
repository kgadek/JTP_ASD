% Przykładowy program
L	IS	500			ilosc znajdywanych liczb pierwszych
t	IS	$255			temp
n	GREG	0			sprawdzane liczby pierwsze
q	GREG	0
r	GREG	0
jj	GREG	0			wskaznik miejsca w tablicy
kk	GREG	0
pk	GREG	0
mm	IS	kk

% Segment danych ______________________________
	LOC	Data_Segment
PRIME1	WYDE	2			prime[1] = 2
	LOC	PRIME1+2*L
ptop	GREG	@			prime[501]
j0	GREG	PRIME1+2-@		-499
BUF	OCTA	0			bufor

% Segment kodu ________________________________
	LOC	#100
Main	SET	n,3			zaczynamy od 3
	SET	jj,j0			j=-499
2H	STWU	n,ptop,jj		N JEST PIERWSZA : prime[2, 3, ..., 500]
	INCL	jj,2			zwieksz jj o jeden
3H	BZ	jj,2F			jesli jj-->prime[501] to idz do wyswietlania
4H	INCL	n,2			NASTEPNE N
	SET	kk,j0			sprawdzamy podzielnosc
6H	LDWU	pk,ptop,kk		z
	DIV	q,n,pk
	GET	r,rR
	BZ	r,4B
7H	CMP	t,q,pk
	BNP	t,2B
8H	INCL	kk,2
	JMP	6B

	GREG 	@
Title	BYTE	"First Five Hundred Primes"
NewLn	BYTE	#a,0
Blanks	BYTE	"   ",0

2H	LDA	t,Title			WYSWIETLANIE
	TRAP	0,Fputs,StdOut
	NEG	mm,2
3H	ADD	mm,mm,j0
	LDA	t,Blanks
	TRAP	0,Fputs,StdOut
2H	LDWU	pk,ptop,mm
0H	GREG	#2030303030000000
	STOU	0B,BUF
	LDA	t,BUF+4
1H	DIV	pk,pk,10
	GET	r,rR
	INCL	r,'0'
	STBU	r,t,0
	SUB	t,t,1
	PBNZ	pk,1B
	LDA	t,BUF
	TRAP	0,Fputs,StdOut
	INCL	mm,2*L/10
	PBN	mm,2B
	LDA	t,NewLn
	TRAP	0,Fputs,StdOut
	CMP	t,mm,2*(L/10-1)
	PBNZ	t,3B
	TRAP	0,Halt,0
