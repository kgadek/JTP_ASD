class BezArgumentow extends Exception {
	public BezArgumentow(String msg) {
		super(msg);
	}
}

public class Tablica_wlasneWyjatki {
    public static void f(int n) {
		int [] tab = new int[n+1];
		for(int i = 0; i<=n; ++i)
		    tab[i] = i*i;
		for(int j = 0; j<=n; ++j) {
		    System.out.print("tab[");
		    System.out.print(j);
		    System.out.print("] = ");
		    System.out.println(tab[j]);
		}
    }
    public static void main(String args[]) {
		try {
		    if( args.length == 0 )
				throw new BezArgumentow("Nie podano argumentów do programu");
		    f( Integer.parseInt(args[0]) );
		} catch( BezArgumentow e ) {
		    System.out.println("ZONK:");
		    e.printStackTrace();
		}
    }
}

