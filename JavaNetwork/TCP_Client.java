import java.util.Scanner;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.util.concurrent.ThreadLocalRandom;

class Tcp_Client_N implements Runnable
{
	String localhost = null;
	int buff = 0;
	int port=0;
	
	//no args constructor
	public Tcp_Client_N(){
	}
	
	// args constructor
	public Tcp_Client_N(int buff, int port,String host) {
		this.buff = buff;
		this.port=port;
		this.localhost=host;
	}
	
	
	public void run() {
		DataOutputStream DO ;
		DataInputStream DI ;
		Socket socket ;
		OutputStream OPS ;
		InputStream IPS ;
		try {
			socket = new Socket(localhost, port);
			//Returns Output Stream for this socket
			OPS = socket.getOutputStream();
			
			byte[] sendPackets = new byte[buff];
			//Generates random bytes and places them in sendPackets array
			ThreadLocalRandom.current().nextBytes(sendPackets);
	     
			DO = new DataOutputStream(OPS);
			DO.writeInt(sendPackets.length);
			//Writes Data into Output Stream provided
			DO.write(sendPackets); 
			//Returns Input Stream for this socket
			IPS = socket.getInputStream();
			DI = new DataInputStream(IPS);
			//Creating byte array for receiving packets back from server
			byte[] RecievePackets = new byte[buff];
			//Reads the byte from contained IPS stream
			DI.readFully(RecievePackets);
			System.out.println("Communicating With Thread : "+Thread.currentThread().getName());
			System.out.println("Recieved Packet Size: "+ RecievePackets.length);
			socket.close();
			OPS.close();
		} catch (Exception e) {
			System.out.println(e.getMessage());
		}
	}
}

public class TCP_Client{    
	
	 public static void main(String args[])
	 {
		 String s=null;
		 String nthread=null;
		 int threadcount=0;
		 
	     Scanner in = new Scanner(System.in);
	     System.out.println("Enter IP address of the Server");
		 s = in.nextLine();
		 
		 
		 Scanner in1 = new Scanner(System.in);
		 System.out.println("Enter no of Threads 1/2/3/4");
		 nthread = in1.nextLine();
		 	 
		 threadcount=Integer.parseInt(nthread);
		 
		 TCP_Client tcp= new TCP_Client();
		 int[] noOfThreads = {threadcount};
		 int[] buffSize = {8,8*1024,80*1024,80*1024*1024};
		
		 
		 for (int i : noOfThreads) {
			 for (int j : buffSize){
				long startTime = System.currentTimeMillis();
				try
				{
					Thread[] threads = new Thread[i];
					int[] port = {11379,11279,11280,11281,11380,11381,11385,11388};
					for (int k = 0; k < threads.length; k++)
					{
						Tcp_Client_N th = new Tcp_Client_N(j,port[k],s);
						threads[k] = new Thread (th);
						threads[k].start();
					}
					for (Thread thread : threads) 
					{
						thread.join();
					}
				}
				catch (Exception e)
				{System.out.println(e.getMessage());}   
				float time_tot = (float) ((System.currentTimeMillis()-startTime)/1000.0 );
				int eight = 8;
				int two = 2;
				int x = i*j*two*eight;
				float throughput = x/(time_tot*1000000);
				System.out.println("Time " + time_tot + " \nNo of Threads " + i + " \nBuffer Size " + j + "\nThroughput = " + throughput + " Mb/S" );
			}
		 }	
	}

}
