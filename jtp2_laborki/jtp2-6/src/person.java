import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Iterator;
import java.util.List;

public class person implements Comparable<person>
{
	// du¿o niepotrzebnych pól
	
	private String m_Name;
	private String m_Surname;
	private String m_Pesel;
	private Integer m_dPlec;
	private	String m_PhoneNbr;
	private Integer m_LenghtOfBigToe;
	
	// konstruktor
	
	person(String a_Name, String a_Surname, String a_Pesel, int a_dPlec, String a_PhoneNbr, int a_LengthOfBigToe)
	{
		m_Name = a_Name;
		m_Surname = a_Surname;
		m_Pesel = a_Pesel;
		m_dPlec = a_dPlec;
		m_PhoneNbr = a_PhoneNbr;
		m_LenghtOfBigToe = a_LengthOfBigToe;
	}
	
	// naturalny porz¹dek imiê > nazwisko > pesel > dl du¿ego palca u stopy
	
	public int compareTo(person a_PersonToComper)
	{
		int returnValue = m_Name.compareTo(a_PersonToComper.m_Name);
		if (returnValue != 0) return returnValue;
		returnValue = m_Surname.compareTo(a_PersonToComper.m_Surname);
		if (returnValue != 0) return returnValue;
		returnValue = m_Pesel.compareTo(a_PersonToComper.m_Pesel);
		if (returnValue != 0) return returnValue;
		returnValue = m_LenghtOfBigToe.compareTo(a_PersonToComper.m_LenghtOfBigToe);
		return returnValue;
	}
	
	// metody zwaracaj¹c pola do porównania
	
	String GetName()
	{
		return m_Name;
	}
	
	String GetPesel()
	{
		return m_Pesel;
	}
	
	Integer GetLengthOfBigToe()
	{
		return m_LenghtOfBigToe;
	}
	
	// w³asna implementacja ToString
	
	public String toString()
	{
		return m_Name + ' ' + m_Surname + ' ' + m_Pesel + ' ' + m_PhoneNbr + ' ' + m_LenghtOfBigToe;
	}
	
	// wypisanie listy
	static void printList(List<person> a_lista, String a_Title)
	{
		Iterator<person> personIterator = a_lista.iterator();
		System.out.println(a_Title);
		while(personIterator.hasNext())
		{
			System.out.println(personIterator.next().toString());
		}
	}
	
	public static void main(String args[])
	{
		List<person> listaLudzi = new ArrayList<person>();
		listaLudzi.add(new person("Rafa³", "Wojdy³a", "90082400000", 1, "880930169", 12));
		listaLudzi.add(new person("Rafa³", "Sojdy³a", "90082400000", 1, "880930169", 12));
		listaLudzi.add(new person("Rafa³", "Sojdy³a", "10082400000", 1, "880930169", 12));
		listaLudzi.add(new person("Jakub", "Wojdy³a", "90082412345", 1, "902211235", 3));
		listaLudzi.add(new person("£ukasz", "Banach", "13582412430", 1, "123456789", 16));
		listaLudzi.add(new person("Gabriela", "Krupa", "90021013224", 0, "732634762", 7));
		
		printList(listaLudzi, "Pierwotnie:");
		Collections.sort(listaLudzi);
		printList(listaLudzi, "Naturalny:");
		Collections.sort(listaLudzi, ToeIsTheMostImportentThing.GetInstance());
		printList(listaLudzi, "Palec:");
		Collections.sort(listaLudzi, SortByPesel.GetInstance());
		printList(listaLudzi, "Nr Pesel:");
	}
}

// sortowanie wed³ug d³ugoœci du¿ego palca u stopy
// dl palca > imiê > pesel

final class ToeIsTheMostImportentThing implements Comparator<person>
{
	private static ToeIsTheMostImportentThing m_Instance = null;
	
	private ToeIsTheMostImportentThing() {}
	
	public static ToeIsTheMostImportentThing GetInstance()
	{
		if(m_Instance == null)
			m_Instance = new ToeIsTheMostImportentThing();
		return m_Instance;
	}

	public int compare(person a_left, person a_right)
	{
		int returnValue = a_left.GetLengthOfBigToe().compareTo(a_right.GetLengthOfBigToe());
		if(returnValue != 0) return returnValue;
		returnValue = a_left.GetName().compareTo(a_right.GetName());
		if(returnValue != 0) return returnValue;
		returnValue = a_left.GetPesel().compareTo(a_right.GetPesel());
		return returnValue;
	}
}

//sortowanie wed³ug nr pesel
//pesel > imiê > palec

final class SortByPesel implements Comparator<person>
{
	private static SortByPesel m_Instance = null;
	
	private SortByPesel() {}
	
	public static SortByPesel GetInstance()
	{
		if(m_Instance == null)
			m_Instance = new SortByPesel();
		return m_Instance;
	}
	
	public int compare(person a_left, person a_right)
	{
		int returnValue = a_left.GetPesel().compareTo(a_right.GetPesel());
		if(returnValue != 0) return returnValue;
		returnValue = a_left.GetName().compareTo(a_right.GetName());
		if(returnValue != 0) return returnValue;
		returnValue = a_left.GetLengthOfBigToe().compareTo(a_right.GetLengthOfBigToe());
		return returnValue;
	}
}