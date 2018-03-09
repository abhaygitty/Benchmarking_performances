import java.util.Scanner;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.concurrent.ThreadLocalRandom;

class Client_UDP implements Runnable{
	int buff = 0;
	int port=0;
	String localhost=null;
	
	//constructor
	public Client_UDP(int buff, int port,String localhost) {
		this.buff = buff;
		this.port=port;
		this.localhost=localhost;
	}

	//run method to be implemented as Runnable interface is implemented
	public void run() 
	{
	    DatagramSocket socket = null;
        try  
        {
            InetAddress host = InetAddress.getByName(localhost);
            socket = new DatagramSocket();
            byte[] spts = new byte[buff];
            ThreadLocalRandom.current().nextBytes(spts);
            int plenght = spts.length;
            DatagramPacket Sndpackets = new DatagramPacket(spts, plenght, host, port);
            socket.send(Sndpackets);
            byte[] RC = new byte[buff];
            DatagramPacket RDP = new DatagramPacket(RC, RC.length);
            socket.receive(RDP);
        }
        catch(Exception e){System.out.println(e.getMessage());}
	}
}

public class UDP_Client {
	
	public static void main (String args[])
	{
		System.out.println("Enter the server's IP");
		Scanner sc = new Scanner(System.in);
		String host="";
		host=sc.nextLine();
		host = !host.isEmpty() ? host : "";
		int buff=0;
		int nt=0;
		System.out.println("Enter no of Threads 1/2/3/4");
		nt=Integer.parseInt(sc.nextLine());
		
		System.out.println("Enter buffer size in Bytes");
		buff=Integer.parseInt(sc.nextLine());
		sc.close();
		
		 int[] numThreads = {nt};
//		 for (int i : numThreads)
		 int i = 0;
		 int k = 0;
		 while(k<=numThreads.length-1)
		 {
			 i = numThreads[k];
			 long startTime = System.currentTimeMillis();
			 try{
				 Thread[] threads = new Thread[i];
				 int[] port = {10380,11840};
				 for (int j = 0; j < threads.length; j++)
				 {
					 Client_UDP th = new Client_UDP(buff,port[j],host);
					 threads[j] = new Thread (th);
					 threads[j].start();
				 }
				 for (Thread thread : threads)  
						thread.join();
			 }
			 catch (Exception e)
			 {
				 
			 }   
			 long endTime = System.currentTimeMillis();
			 long totalTime = (endTime-startTime);
		     System.out.println("Time " + totalTime + " ms" );
			 long timetaken = (long) (totalTime );					
			 float throughput = (float)(i*buff*2*8/(timetaken));
			 System.out.println("No of Threads " + i );
			 System.out.println("Buffer Size " + buff);
			 System.out.println("Throughput = " + throughput/1000 + " Mb/S\n" );
		 }
	}
}
