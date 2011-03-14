package org.gadek.Leroy;

import java.util.*;
import java.net.*;
import java.io.*;
import java.util.Map.*;

public class LeroyServer implements Runnable {

	private String nick;
	private Socket clientSocket;
	private static Map<Thread, LeroyServer> threadMap = Collections.synchronizedMap(new HashMap<Thread, LeroyServer>());
	private static int serverPort = 7777;
	private PrintWriter out;
	private BufferedReader in;
	private static ServerSocket serverSocket;
	
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
			LeroyServer main = new LeroyServer(null);
			main.runServer();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

}
