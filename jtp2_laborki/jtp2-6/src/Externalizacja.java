import java.io.*;

public class Externalizacja{

	public static void main(String [] args){
	   try{
		Osoba Maciek = new Osoba("Maciej","Janas","90024513453",21);
		ObjectOutputStream out = new ObjectOutputStream(new FileOutputStream("extr.txt"));
		ObjectInputStream in = new ObjectInputStream(new FileInputStream("extr.txt"));
		
		out.writeObject(Maciek);
		Osoba Nieznana = new Osoba();
		Nieznana = (Osoba) in.readObject();
		
		Nieznana.wypiszDane();

	   }catch(IOException exc){
		exc.printStackTrace();
	   }catch(ClassNotFoundException exc){
		exc.printStackTrace();
	   }	
	
	}
}

class Osoba implements Comparable<Osoba>, Externalizable
{
	private String imie;
	private String nazwisko;
	private String PESEL;
	private int wiek;
	
	public Osoba(){}

	public Osoba(String i, String n, String p, int w){
		imie = i;
		nazwisko = n;
		PESEL = p;
		wiek = w;
	}	
	public void wypiszDane(){
		System.out.println(imie+" "+nazwisko+" PESEL: "+PESEL+" wiek: "+wiek);
	}

	public int compareTo(Osoba X){
		if(nazwisko.compareTo(X.nazwisko)>0) return 1;
		if(nazwisko.compareTo(X.nazwisko)<0) return -1;
		return 0;
	}
	
	public String getImie()
	{
		return imie;
	}
	public String getNazwisko()
	{
		return nazwisko;
	}
	public String getPESEL()
	{
		return PESEL;
	}
	public Integer getWiek()
	{
		return wiek;
	}

	public void writeExternal(ObjectOutput out) throws IOException {
		out.writeObject(imie);
		out.writeObject(nazwisko);
		out.writeInt(wiek);
	}

	public void readExternal(ObjectInput in) throws IOException, ClassNotFoundException{
		imie = (String) in.readObject();
		nazwisko = (String) in.readObject();
		wiek = (int) in.readInt();
	}
}
