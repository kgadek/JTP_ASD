/* 
UWAGA! Poniewaz znak "*" automatycznie odnosi sie do sciezki biezacego katalogu, dzialanie 
mnozenia nalezy wykonywac uzywajac "\*" - wtedy znak faktycznie jest traktowany jako "*" 
*/

import java.util.Stack;

public class Kalkulet{
	
	public enum TypOperatora{
	   SUMA { float wynik(float x, float y) { return x+y; } },
	   ROZNICA { float wynik(float x, float y) { return x-y; } },
	   ILOCZYN { float wynik(float x, float y) { return x*y; } },
	   ILORAZ { float wynik(float x, float y) { return x/y; } },
	   POTEGA { float wynik(float x, float y) { 
			float t = 1;
			float w = y;
			if(y<0) w = -y;
			for(int i=0; i<w; i++) t=t*x;
			if(y<0) return (float)1/t;
			return t; } };
 	  abstract float wynik(float x, float y);
	}

    public static void main(String [] args){
     	
     try{		
	Stack<Float> Liczby = new Stack<Float>();
	Stack<TypOperatora> Operatory = new Stack<TypOperatora>();
	int i=0;
	Liczby.push(Float.parseFloat(args[i++]));
	while(i<args.length){
		if(Operatory.empty()){
			   Operatory.push(ZwrocOp(args[i++]));
			   Liczby.push(Float.parseFloat(args[i++]));
					
		}else{
			TypOperatora lastOp = Operatory.pop();
			if(lastOp.compareTo(ZwrocOp(args[i]))>=0){
				Float b = Liczby.pop();
				Float a = Liczby.pop();
				Float c = lastOp.wynik(a,b);
				Liczby.push(c);
			}else{
				Operatory.push(lastOp);
				Operatory.push(ZwrocOp(args[i++]));
				Liczby.push(Float.parseFloat(args[i++]));
			}
		}
	}
	while(!Operatory.empty()){
		Float b = Liczby.pop();
		Float a = Liczby.pop();
		Float c = Operatory.pop().wynik(a,b);
		Liczby.push(c);
	}
	
	System.out.println("Wynik: " + Liczby.pop());

     }catch(BadCalculatorException exc){
	exc.printStackTrace();
     }catch(NumberFormatException exc){
	System.out.println("\nBledny operand! Popraw dane wejciowe.\n");
	exc.printStackTrace();
     }	
		
    }


    static TypOperatora ZwrocOp(String a) throws BadCalculatorException{
	if(a.compareTo("+")==0) return TypOperatora.SUMA;
	if(a.compareTo("-")==0) return TypOperatora.ROZNICA;
	if(a.compareTo("*")==0) return TypOperatora.ILOCZYN;
	if(a.compareTo("/")==0) return TypOperatora.ILORAZ;
	if(a.compareTo("^")==0) return TypOperatora.POTEGA;
	throw new BadCalculatorException("Nie ma takiego operatora! Popraw dane wejsciowe.");
    }

}

class BadCalculatorException extends Exception
{
	public BadCalculatorException(){}
	public BadCalculatorException(String txt){
		super(txt);
	}
}
