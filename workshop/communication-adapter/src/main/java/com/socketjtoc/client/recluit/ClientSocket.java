package com.socketjtoc.client.recluit;

import java.net.*;
import java.io.*;

public class ClientSocket{
	
 /*public static void main(String[] args) throws IOException {
  if (args.length < 2) {
   System.err.println("Usage: java Client1 <IP address> <Port number>");
   System.exit(0);
  }
  BufferedReader in = null;
  OutputStream out = null;
  Socket sock = null;

  try {
   sock = new Socket(args[0], Integer.parseInt(args[1]));
   out = sock.getOutputStream();
   in = new BufferedReader(new InputStreamReader(sock.getInputStream()));

    String line = "hey";
    String responseline = null;
char[] strArray;
strArray = line.toCharArray();

while (true) {
for( int index = 0; index < strArray.length; index++){
 out.write(strArray[index]);
}
out.flush();
System.out.println("data sent " );
System.out.println("val returned"+in.readLine());
   }
  }
  catch (IOException ioe) {
   System.err.println(ioe);
  }
  finally {
   if (in != null)
    in.close();

   if (out != null)
    out.close();
   if (sock != null)
    sock.close();
  }
 }*/
}