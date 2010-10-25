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
	Instrument tab[] = new Instrument[3];
	tab[0] = new Gitara();
	tab[1] = new Flet();
	tab[2] = new Bebny();
	for(int i = 0; i<3; ++i)
	    tab[i].graj();
    }
}

