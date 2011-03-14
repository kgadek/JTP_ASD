package org.gadek.Leroy;

import java.util.*;
import java.net.*;
import java.io.*;
import java.util.Map.*;
import org.xml.sax.*;
import org.xml.sax.helpers.*;

public class LeroyServer implements Runnable {

	private String nick;
	private Socket clientSocket;
	private static Map<Thread, LeroyServer> threadMap = Collections.synchronizedMap(new HashMap<Thread, LeroyServer>());
	private static int serverPort = 7777;
	private PrintWriter out;
	private BufferedReader in;
	private static ServerSocket serverSocket;
	private static Archive ar;
	private static Session se;
	
	class onShutdown extends Thread {
		public void run() {
			System.out.println("BABABABBA");
		}
	}
	
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
				Thread.sleep(10);
				if((inp = in.readLine()) == null)
					break;
				if(inp.startsWith("/nickname ")) {
					String tmp = inp.substring(10);
					inp = "Użytkownik " + nick + " zmienił nazwę na " + tmp;
					nick = tmp;
				}
				System.out.println(clientSocket + " odebrał: " + inp);
				
				Msg m = new Msg();
				m.setMessage(inp);
				m.setSender(nick);
				se.addMsg(m);
				
				it = threadMap.entrySet().iterator();
				
				while(it.hasNext()) {
					thIt = it.next();
					thIt.getValue().receiveMsg(nick + "> " + inp);
				}
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
			ArchiveHandler ah = new ArchiveHandler();
			xr.setContentHandler(ah);
			xr.parse(new InputSource(new FileReader(new File("archive.xml"))));
			ar = ah.getArchive();
			se = new Session();
			//System.out.println(ah.getArchive().toXML());
			
			Runtime.getRuntime().addShutdownHook(new Thread() {
				public void run() {
					System.out.println("Zapisuję archiwum...");
					ar.addSession(se);
					//BufferedWriter fout = new BufferedWriter(new FileOutputStream(new File("archive.xml")));
					PrintWriter out = null;
					try {
						out = new PrintWriter(new BufferedWriter(new FileWriter("archive.xml")));
					} catch (IOException e) {
						e.printStackTrace();
					}
					out.println(ar.toXML());
					out.close();
					System.out.println(ar.toXML());
					System.out.println("Ok.");
				}
			});
			
			LeroyServer main = new LeroyServer(null);
			main.runServer();
			
		} catch (IOException e) {
			e.printStackTrace();
		} catch (SAXException e) {
			e.printStackTrace();
		}
	}

}
