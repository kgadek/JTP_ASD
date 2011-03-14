/**
 * 
 */
package org.gadek.Leroy;

import java.io.*;
import java.net.*;
import java.util.Random;
import java.util.logging.*;


public class LeroyClient {
	
	static byte[] serverIp = {(byte) 192, (byte) 168, (byte) 100, (byte) 103};
	static int serverPort = 7777;
	static String myName;
	
	Socket echoSocket = null;
	PrintWriter out = null;
	BufferedReader in = null;
	
	private static Logger log;
	
	
	/**
	 * @author konrad
	 * Nasłuchuj wiadomości od serwera.
	 */
	private class msgListener implements Runnable {
		@Override public void run() {
			String inp;
			try {				
				while((inp = in.readLine()) != null) {
					if(inp.contains(myName))
						System.out.print("\007");
					else if(inp.equalsIgnoreCase("/quit"))
						return;
					System.out.println(inp);
					Thread.sleep(1);
				}
			} catch (InterruptedException e) {
				return;
			} catch (IOException e) {
				e.printStackTrace();
				System.exit(-1);
			}
		}
	}
	
	private void startClient() throws IOException {
		log.fine("EchoClient.startClient()");
		try {
			echoSocket = new Socket(InetAddress.getByAddress(serverIp),serverPort);
			if(echoSocket.isClosed() || !echoSocket.isConnected())
				throw new Exception();
			out = new PrintWriter(echoSocket.getOutputStream(), true);
			in = new BufferedReader(new InputStreamReader(echoSocket.getInputStream()));
		} catch (Exception e) {
			e.printStackTrace();
		}
		log.fine("EchoClient.startClient() -- connected");
		
		Thread l = new Thread(new msgListener());
		l.start();
		
		BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in));
		String userInput;
		
		try {
			out.println("/nickname " + myName);
			while ((userInput = stdIn.readLine()) != null ) {
				out.println(userInput);
				if(userInput.equalsIgnoreCase("/quit")) {
					l.interrupt();
					l.join(1000);
					break;
				}
			}
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		out.close();
		in.close();
		stdIn.close();
		echoSocket.close();
	}
	
	public static void main(String args[]) {
		if(args.length == 1) // wczytaj nick
			myName = args[0];
		else {
			myName = "anonymous" + (new Random()).nextInt(Integer.MAX_VALUE);
		}
		
		try {
			Handler fh = new FileHandler("gadek.log");
			fh.setFormatter(new SimpleFormatter());
			log = Logger.getLogger("org.gadek.Leroy.EchoClient");
			log.addHandler(fh);
			log.setLevel(Level.ALL);
		} catch (IOException e1) {
			e1.printStackTrace();
		}
		
		LeroyClient cl = new LeroyClient();
		log.fine("created new EchoClient instance");
		
		try {
			cl.startClient();
		} catch (IOException e) {
			e.printStackTrace();
		}
		log.fine("EchoClient -- quit");
	}
	
}
