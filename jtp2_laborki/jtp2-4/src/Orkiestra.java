interface Instrument {
    abstract public void graj();
}

class Gitara implements Instrument {
    public void graj() {
	System.out.println("brzdęk brzdęk");
    }
}

class Flet implements Instrument {
    public void graj() {
	System.out.println("fiu fiu");
    }
}

class Bebny implements Instrument {
    public void graj() {
	System.out.println("bum bum");
    }
}

public class Orkiestra {
    public static void main(String args[]) {
		Instrument tab[] = new Instrument[args.length];
		try {
			for(int i=0; i<args.length; ++i) {
		   		Class tmp = Class.forName(args[i]);
		    	tab[i] = (Instrument)tmp.newInstance();
			}
			for(int i = 0; i<args.length; ++i)
		    	tab[i].graj();
		} catch( Exception e ) {
			System.out.println("Zonk!");
			e.printStackTrace();
		}
	}
}

