import java.util.Random;

class mojeBledy extends Exception {
	public mojeBledy(String msg) {
		super(msg);
	}
}

class BledneParametry extends mojeBledy {
	public BledneParametry(String msg) {
		super(msg);
	}
}

class BlednyRozmiar extends mojeBledy {
	public BlednyRozmiar(String msg) {
		super(msg);
	}
}

class NiewlasciweWspolrzedneMacierzy extends mojeBledy {
	public NiewlasciweWspolrzedneMacierzy(String msg) {
		super(msg);
	}
}

class pair {
	int x, y;
	public pair(int a, int b) {
		x = a;
		y = b;
	}
}

class wspolrzedneMacierzy extends pair {
	boolean ok;
	public wspolrzedneMacierzy(int a, int b, boolean kk) throws NiewlasciweWspolrzedneMacierzy {
		super(a,b);
		if(a<0 || b<0)
			throw new NiewlasciweWspolrzedneMacierzy("Podano ujemne współrzędne macierzy!");
		ok = kk;
	}
	public boolean isOk() {
		return ok;
	}
}

class Macierz {
	static int randSize = 10;
	int m,n;
	int [][] tab;
	public Macierz(int a, int b) {
		m = a;
		n = b;
		tab = new int[a][b];
	}
	public Macierz mul(Macierz b) throws BlednyRozmiar {
		if(n != b.m)
			throw new BlednyRozmiar("Macierze nie dają się wymnożyć!");
		Macierz ret = new Macierz(m, b.n);
		for(int i=0;i<m;++i) {
			for(int j=0;j<b.n;++j) {
				ret.tab[i][j] = 0;
				for(int k=0;k<n;++k)
					ret.tab[i][j] = ret.tab[i][j] + tab[i][k] * b.tab[k][j];
			}
		}
		return ret;
	}
	public void print() {
		for(int i=0;i<m;++i) {
			for(int j=0;j<n;++j)
				System.out.format("%4d ",tab[i][j]);
			System.out.println();
		}
	}
	public void fillRandom(Random rrr) {
		for(int i=0;i<m;++i) {
			for(int j=0;j<n;++j)
				tab[i][j] = rrr.nextInt(randSize);
		}
	}
	public wspolrzedneMacierzy findZero() {
		try {
			int i=0,j=0;
			escape:
			for(i=0;i<m;++i) {
				for(j=0;j<n;++j) {
					if(tab[i][j] == 0)
						break escape;
				}
			}
			return new wspolrzedneMacierzy(i,j,i<m);
		} catch( NiewlasciweWspolrzedneMacierzy e ) {
			System.out.println("ZONK WEWNĘTRZNY!");
			e.printStackTrace();
		}
		return null;
	}
}

class MacierzTrojkatna {
	int m, n;
	int tab[][];
	public MacierzTrojkatna(int a, int b) throws BlednyRozmiar {
		if(b>a)
			throw new BlednyRozmiar("Szerokość macierzy trójkątnej nie może być mniejsza niż jej wysokość!");
		m = a; // szerokość
		n = b; // wysokość
		tab = new int[a][];
		for(int i=0;i<m && b-i>0;++i)
			tab[i] = new int[b-i-1];
	}
	public void print() {
		for(int i=0;i<m;++i) {
			for(int j=0;j<n-i;++j)
				System.out.format("%4d ",tab[i][j]);
			System.out.println();
		}
	}
	public void fillRandom(Random rrr) {
		for(int i=0;i<m;++i) {
			for(int j=0;j<n-i-1;++j)
				tab[i][j] = rrr.nextInt(1000);
		}
	}
}

public class Macierze {
	public static void main(String args[]) {
		try {
			if( args.length < 6 )
				throw new BledneParametry("Podano za mało parametrów do programu!");
			Macierz A, B, C;
			Random rnd = new Random();
			A = new Macierz(Integer.parseInt(args[0]), Integer.parseInt(args[1]));
			A.fillRandom(rnd);
			System.out.println("A=");
			A.print();
			B = new Macierz(Integer.parseInt(args[2]), Integer.parseInt(args[3]));
			B.fillRandom(rnd);
			System.out.println("B=");
			B.print();
			C = A.mul(B);
			System.out.println("A*B=");
			C.print();

			wspolrzedneMacierzy found = A.findZero();
			if(found.isOk()) System.out.format("A.findZero() = (%d,%d)\n",found.x, found.y);
			else System.out.format("A.findZero() = ---\n");
			found = B.findZero();
			if(found.isOk()) System.out.format("B.findZero() = (%d,%d)\n",found.x, found.y);
			else System.out.format("B.findZero() = ---\n");

			MacierzTrojkatna D = new MacierzTrojkatna(Integer.parseInt(args[4]), Integer.parseInt(args[5]));
			D.fillRandom(rnd);
		} catch( mojeBledy e ) {
			System.out.println("ZONK!");
			e.printStackTrace();
		}
	}
}

