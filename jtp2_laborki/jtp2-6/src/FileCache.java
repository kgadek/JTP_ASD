import java.util.*;
import java.lang.ref.*;
import java.io.*;

public class FileCache
{
	public static void main(String[] args) {
		FileMap fm = new FileMap();
		System.out.print(fm.get("FileCache.java"));
	}
}



class FileMap extends AbstractMap<String,String>
{
	private Map<String,SoftReference<String>> innerMap = new HashMap<String,SoftReference<String>>();
	
	public String get(Object key) {
		String filename = (String)key;
		if(!innerMap.containsKey(filename) || innerMap.get(filename).get()==null) {
			try {
				BufferedReader br = new BufferedReader(new FileReader(filename));
				StringBuffer sb = new StringBuffer();
				String str;
				while((str = br.readLine()) != null)
					sb.append(str + "\n");
				innerMap.put(filename, new SoftReference<String>(sb.toString()));
			}
			catch(Exception e) {System.err.println(e.getMessage());}
		}
		return innerMap.get(filename).get();
	}
	
	public Set<Map.Entry<String,String>> entrySet() {
		Map<String,String> outerMap = new HashMap<String,String>();
		for(Map.Entry<String,SoftReference<String>> it: innerMap.entrySet())
			outerMap.put(it.getKey(), it.getValue().get());
		return outerMap.entrySet();
	}
}
