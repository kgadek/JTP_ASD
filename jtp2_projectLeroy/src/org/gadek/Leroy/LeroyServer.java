package org.gadek.Leroy;

import java.text.*;
import java.util.*;
import java.net.*;
import java.io.*;
import java.util.Map.*;
import org.xml.sax.*;
import org.xml.sax.helpers.*;

class Msg {
	String sender;
	String msg;
}

class Session {
	Msg[] msgs;
	String date;
	
	Session() {
		date = DateFormat.getDateInstance().format(new Date());
	}
	
	public void setDate(String date) throws ParseException {
		DateFormat df = DateFormat.getDateInstance();
		this.date = df.format(df.parse(date)); // konwersja w obie strony -- sprawdzenie, czy poprawny String
	}
}

class ArchiveHandler extends DefaultHandler {
	private Session s = new Session();
	
	public void startDocument() throws SAXException {
		System.out.println("start");
	}
	public void endDocument() throws SAXException {
		System.out.println("end");
	}
	public void startElement(String namespaceURI, String localName, String qname, Attributes attr) throws SAXException {
		System.out.println("startElem: " + localName + " qname:" + qname + " attr:" + attr.toString());
	}
	public void endElement(String namespaceURI, String localName, String qname) throws SAXException {
		System.out.println("endElem");
	}
	public void characters(char[] ch, int start, int length) throws SAXException {
		System.out.println("chars: " + String.copyValueOf(ch) + " st: " + start + " len: " + length);
	}
}

public class LeroyServer implements Runnable {

	private String nick;
	private Socket clientSocket;
	private static Map<Thread, LeroyServer> threadMap = Collections.synchronizedMap(new HashMap<Thread, LeroyServer>());
	private static int serverPort = 7777;
	private PrintWriter out;
	private BufferedReader in;
	private static ServerSocket serverSocket;
	private static List<String> msgs = new LinkedList<String>();
	
	public LeroyServer(Socket clientSocket) {
		this.clientSocket = clientSocket;
	}
	
	public void receiveMsg(String msg) {
		if(out != null)
			out.println(msg);
	}
	
	public void runServer() throws IOException {
		serverSocket = new ServerSocket(serverPort);
		Socket clSock;
		
		LeroyServer servConn;
		Thread servTh;
		
		while(true) {
			clSock = serverSocket.accept();
			servConn = new LeroyServer(clSock);
			servTh = new Thread(servConn);
			threadMap.put(servTh, servConn);
			servTh.start();
		}
	}
	
	@Override public void run() {
		System.out.println(clientSocket + " startuje");
		try {
			nick = "anonymous" + (new Random()).nextInt(Integer.MAX_VALUE);
			out = new PrintWriter(clientSocket.getOutputStream(), true);
			in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
			
			String inp;
			Iterator<Entry<Thread, LeroyServer>> it;
			Map.Entry<Thread, LeroyServer> thIt;
			
			while(true) {
				Thread.sleep(1000);
				if((inp = in.readLine()) == null)
					break;
				if(inp.startsWith("/nickname ")) {
					nick = inp.substring(10);
					continue;
				}
				System.out.println(clientSocket + " odebrał: " + inp);
				
				
				it = threadMap.entrySet().iterator();
				
				while(it.hasNext()) {
					thIt = it.next();
					thIt.getValue().receiveMsg(nick + "> " + inp);
				}
				
				//sendMsgBroadcast(inp);
				//System.out.println("--> " + clientSocket + " żyje");
				/*if(rnd.nextInt(10) < 2) {
					System.out.println("Th " + threadId + " rzuca!");
					sendMsgBroadcast(threadId);
				}*/
			}
			
			in.close();
			out.close();
			clientSocket.close();
		} catch (InterruptedException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}


	public static void main(String[] args) {
		try {
			XMLReader xr = XMLReaderFactory.createXMLReader();
			xr.setContentHandler(new ArchiveHandler());
			xr.parse(new InputSource(new FileReader(new File("archive.xml"))));
			LeroyServer main = new LeroyServer(null);
			main.runServer();
		} catch (IOException e) {
			e.printStackTrace();
		} catch (SAXException e) {
			e.printStackTrace();
		}
	}

}
