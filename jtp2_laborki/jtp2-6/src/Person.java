package jtp2_zad4;

import java.util.Comparator;
import java.io.*;


public class Person implements Externalizable{
	String firstname;
	String lastname;
	int age;
	
	public void writeExternal(ObjectOutput out) throws IOException {
		out.writeObject(firstname);
     	out.writeObject(lastname);
     	out.writeInt(age);
	}
	public void readExternal(ObjectInput in) throws IOException, ClassNotFoundException{
		firstname=(String)in.readObject();
		lastname=(String)in.readObject();
		age=in.readInt();	
	}
	String getFirstname(){
		return firstname;
	}
	String getLastname(){
		return lastname;
	}
	int getAge(){
		return age;
	}
	void setFirstname(String firstname){
		this.firstname = firstname;
	}
	void setLastname(String lastname){
		this.lastname = lastname;
	}
	void getAge(int age){
		this.age = age;
	}
	
	Person(String fname, String lname, int ag){
		firstname = fname;
		lastname = lname;
		age = ag;
	}
	
	public int compareTo(Person p) {
		int cmp = this.getLastname().compareTo(p.getLastname());
		if (cmp > 0)
			return 1;
		if (cmp < 0)
			return -1;
		else{
			cmp = this.getFirstname().compareTo(p.getFirstname());
			if (cmp > 0)
				return 1;
			if (cmp < 0)
				return -1;
			else
				return 0;
		}
	}
	
	class PersonComparator implements Comparator <Person> {
		public int compare(Person p, Person r) {
			int cmp = p.getLastname().compareTo(r.getLastname());
			if (cmp > 0)
				return 1;
			if (cmp == 0)
				return 0;
			else
				return -1;
		}
	}
	
	public static void main(String[] args) {
		Person one = new Person( "Jan", "Kowalski",21);
		Person two = new Person( "michal", "abc",22);
		try{
			FileOutputStream out = new FileOutputStream("plik.txt");
			ObjectOutputStream out_o = new ObjectOutputStream(out);
			
			one.writeExternal(out_o);
			out_o.flush();
			out.close();
			
			FileInputStream in = new FileInputStream("plik.txt");
			ObjectInputStream in_o = new ObjectInputStream(in);
			System.out.println(two.getFirstname()+" "+two.getLastname()+" "+two.getAge());
			two.readExternal(in_o);
			in.close();
			System.out.println(two.getFirstname()+" "+two.getLastname()+" "+two.getAge());
		}
		catch (Exception e) {
			System.out.println("B³¹d " + e.getMessage() );
			e.printStackTrace();
		}
	}
}

