import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.StringTokenizer;

public class wc
{
	static final private String m_ver = "0.0aplha";
	
	private	List<String> m_NamesOfFiles;
	private List<Integer> m_Options;
		
	private boolean m_version;
	private boolean m_help;
	private boolean m_files;
	
	private int m_Results[];	//bytes/chars/words/lines/maxline
	
	private wc(String a_args[])
	{
		m_NamesOfFiles = new ArrayList<String>();
		m_Options = new ArrayList<Integer>();
		
		m_help = false;
		m_version = false;
		m_files = false;
		
		m_Results = new int[5];
		for(int i = 0 ; i < m_Results.length ; ++i)
			m_Results[i] = 0;
		
		AnalizCmd(a_args);
	}
	
	private void AnalizCmd(String a_args[]) throws RuntimeException
	{
		try
		{
			if(a_args.length == 0)
				throw new IllegalArgumentException("Zero argumentow!");
			for(int i = 0 ; i < a_args.length ; ++i)
			{
				if(!GetCmd(a_args[i]))	//GetCmd spr poszczególne tokeny
					return;		
			}
			this.AnalizFiles();
		} catch(IndexOutOfBoundsException exeption) {
			throw new RuntimeException(exeption.getMessage(), exeption.getCause());
		} catch(IllegalArgumentException exeption) {
			throw new RuntimeException(exeption.getMessage(), exeption.getCause());
		} catch (IOException exeption) {
			throw new RuntimeException(exeption.getMessage(), exeption.getCause());
		} finally {}
	}
	
	private boolean GetCmd(String a_arg) throws IllegalArgumentException 
	{
		if(a_arg.substring(0, 2).compareTo("--") == 0)		//obs³uga pe³nych opcji
		{
			if(a_arg.compareTo("--bytes") == 0)
			{
				m_Options.add(0);
				return true;
			}
			if(a_arg.compareTo("--chars") == 0)
			{
				m_Options.add(1);
				return true;
			}
			if(a_arg.compareTo("--lines") == 0)
			{
				m_Options.add(3);
				return true;
			}
			if(a_arg.compareTo("--words") == 0)
			{
				m_Options.add(2);
				return true;
			}
			if(a_arg.compareTo("--max-line-length") == 0)
			{
				m_Options.add(4);
				return true;
			}
			if(a_arg.compareTo("--help") == 0)
			{
				m_help = true;
				return false;
			}
			if(a_arg.compareTo("--version") == 0)
			{
				m_version = true;
				return false;
			}
		} else if(a_arg.charAt(0) == '-')			//obsuga skróconych obcji
		{
			char znak;
			for(int i = 1 ; i < a_arg.length() ; ++i)
			{
				znak = a_arg.charAt(i);
				switch(znak)
				{
				case 'c':
					m_Options.add(1);
					break;
				case 'w':
					m_Options.add(2);
					break;
				case 'l':
					m_Options.add(3);
					break;
				case 'L':
					m_Options.add(4);
					break;
				case 'b':
					m_Options.add(0);
					break;
				default:
					throw new IllegalArgumentException("Zla opcja!");
				}
			}
			return true;
		}
		// jezelie nic powyzej nie wylapalismy to spr czy nie jest to przypadkiem nazwa pliku
		// jezeli nie to wyrzucamy wyjatek
		try
		{
			File testFile = new File(a_arg);
			if(!testFile.exists())
				throw new FileNotFoundException("Plik o podanej nazwie nie istnieje!");
			m_NamesOfFiles.add(a_arg);
			return true;
		} catch (FileNotFoundException exeption) {
			throw new IllegalArgumentException(exeption.getMessage(),exeption.getCause());
		} finally {}
	}
	
	private void AnalizFiles() throws IOException
	{
		int nbrOfResults[] = new int[5];
		Iterator<String> fileIterator = m_NamesOfFiles.iterator();
		while(fileIterator.hasNext())
		{
			for(int i = 0 ; i < nbrOfResults.length ; ++i)
				nbrOfResults[i] = 0;
			String fileName = fileIterator.next();
			BufferedReader bufReader = new BufferedReader(new FileReader(fileName));
			String line;
			int lineLength;
			while((line = bufReader.readLine()) != null)
			{
				lineLength = line.length() + 1;	// zliczamy znaki + znak koñca lini
				if(nbrOfResults[4] < lineLength)
					nbrOfResults[4] = lineLength;
				nbrOfResults[1] += lineLength;	
				nbrOfResults[3]++;	// dodajemy po jednej linie
				nbrOfResults[2] += new StringTokenizer(line).countTokens();	// zliczamy tokeny czyli wyrazy
			}
			m_Results[1] += nbrOfResults[1];
			m_Results[3] += nbrOfResults[3];
			m_Results[2] += nbrOfResults[2];
			if(m_Results[4] < nbrOfResults[4])
				m_Results[4] = nbrOfResults[4];
			FileInputStream inputStream = new FileInputStream(fileName);
			nbrOfResults[0] = inputStream.available();
			m_Results[0] += nbrOfResults[0];
			PrintResult(nbrOfResults, fileName);
		}
	}
	
	public void GetFinalResult()
	{
		if(m_version)
		{
			System.out.println(m_ver);
			return;
		}
		if(m_help)
		{
			System.out.println("HELP:...");
			return;
		}
		if(m_NamesOfFiles.size() > 1)
			PrintResult(m_Results, "total");
	}
	
	private void PrintResult(int a_Results[], String a_FileName)
	{
		if(m_Options.size() == 0)
			System.out.println(Integer.toString(a_Results[1]) + ' ' + Integer.toString(a_Results[2]) + ' ' + Integer.toString(a_Results[3]) + ' ' + Integer.toString(a_Results[0])  +' ' + a_FileName);
		else 
		{
			StringBuilder result = new StringBuilder();
			Iterator<Integer> intIterator = m_Options.iterator();
			while(intIterator.hasNext())
			{
				result.append(a_Results[intIterator.next()]);
				result.append(' ');
			}
			result.append(a_FileName);
			System.out.println(result);	
		}
	}
	
	public static void main(String args[])
	{
		try 
		{
			wc plikDoAnlizy = new wc(args);
			plikDoAnlizy.GetFinalResult();
		} catch (RuntimeException exeption) {
			exeption.printStackTrace();
		} finally {}
	}
}