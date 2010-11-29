public class kwa
{
	/**
		jakiś opis
	
	*/
	public static void main(String args[]) {
		try {
			f(Integer.parseInt(args[0]));
		}
		catch(Exception e) {
			e.printStackTrace();
		}
		finally {
			System.err.println("finally in main()");
		}
	}
	
	static void f(int ile) throws MyException {
		try {
		 	int t[] = new int[ile];
		 	
		 	for(int i=0; i<t.length; ++i)
		 		t[i] = i*i;
		
			for(int e : t) {
				if(e == 81) throw new MyException();
				System.out.println(e);		
			}
		}
		finally {
			System.err.println("finally in f()");
		}
	}
}

class MyException extends Exception
{
	public void printStackTrace() {
		System.err.println("pam pam pam");
		super.printStackTrace();
	}
}
	
