package com.socketjtoc.client.recluit;


import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Vector;


public class ClientJ_to_C {
	
	public Vector<String> info = new Vector<String>();

	public void establishConnection(String rfc){		
		String ip = "127.0.0.1";
		//String msg = "hello from client";
		String msg = rfc;
		int port  = 2007;
		Socket	socket;
		OutputStreamWriter out;
		InputStreamReader in;
		PrintWriter pw;
		BufferedReader br;
		
		try {
			socket = new Socket(ip,port);
			out = new OutputStreamWriter(socket.getOutputStream());
			in = new InputStreamReader(socket.getInputStream());								
			
			
			//send 
			pw = new PrintWriter(out,true);
			System.out.println("Before sending msj: "+msg.length());
			pw.print(msg);
			pw.flush();
			
			
			//receive to reply
			br = new BufferedReader(in);
			char[] buffer = new char[300];
			int count = br.read(buffer,0,300);
			String reply = new String(buffer,0,count);
			System.out.println("After receiving msj: "+reply.length());
			for(int x = 0; x < reply.split("\n\n").length; x++){
				info.add(reply.split("\n\n")[x]);
			}
			//System.out.print(reply);
			for(int x = 0; x < info.size();x++){
				System.out.println(info.get(x));
			}
			
			
		} catch (UnknownHostException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}	

	public void initialization(){
		String rfc = "ROMS260389JSAULO1";
		ClientJ_to_C connection = new ClientJ_to_C();
		
		//System.out.println("Insert your RFC: ");
		connection.establishConnection(rfc);						
	}
	
	public static void main(String[] args) {	
		//new ClientJ_to_C().establishConnection();
		ClientJ_to_C init = new ClientJ_to_C();
		init.initialization();
	}
}
