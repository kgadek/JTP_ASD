package jtp2_zad4;

import java.io.*;
import java.util.*;
import java.lang.ref.SoftReference;

public class FileReader {
	private static final WeakHashMap<String,SoftReference<String>> data_tab = new
	WeakHashMap<String,SoftReference<String>>();
	final int rows ;
	FileReader(){
		rows = 5;
	}
	FileReader(int rows){
		this.rows = rows;
	}
	public String readFile(String s) throws IOException{
		String result = null;
		SoftReference<String> ref = data_tab.get(s);
		if (ref != null) {
			result = ref.get();
		}
		if(result == null){
			BufferedReader bf = new BufferedReader(
				 new InputStreamReader(
						new FileInputStream(s)));
			int i = 0;
			String sum_st = "";
			String stmp;
			while(i < rows && (stmp = bf.readLine() ) != null ){
				sum_st = sum_st + "\n"+ stmp;
				i++;
			}
			data_tab.put(s,new SoftReference<String>(sum_st) ); //zapamiêtanie wartoœci pliku
			bf.close();											// key = nazwa pliku
			return sum_st;											
		}
		else{
			return ( data_tab.get(s) ).get();					//wypisanie z cache'a
		}
			
	}
	
	public static void main(String[] args) {
		FileReader F = new FileReader();
		try{
			System.out.println( F.readFile("plik2.txt")  );
			System.out.println( F.readFile("plik.txt")  );
		}
		catch(Exception e){
			System.out.println("B³¹d: \n" + e.getMessage() );
			//e.printStackTrace();
		}
	}
}
