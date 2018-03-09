
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;


class Udp_Ser implements Runnable {

int portNum;

Udp_Ser (int portNum){
        this.portNum = portNum;
}

public void run() {
    try
        {
            byte receivingdata[]=new byte[1024*62];
            DatagramSocket socket=new DatagramSocket(portNum);
            System.out.println("Waiting for Data Packets");
            DatagramPacket recievepacket=new DatagramPacket(receivingdata,receivingdata.length);
            socket.receive(recievepacket);
            byte[] sendData = recievepacket.getData();
            DatagramPacket sendpacket = new DatagramPacket(sendData,sendData.length,recievepacket.getAddress(),recievepacket.getPort());
            socket.send(sendpacket);
            System.out.println(Thread.currentThread().getName() + " is completed");
        }catch (Exception e) {
                e.printStackTrace();
        }
	}
}

public class UDP_Server  {

	public static void main(String args[]) throws IOException {
		Thread[] threads = new Thread[2];
		 int[] port = {10380,11840};
		 for (int i = 0; i < threads.length; i++)
		 {
			 Udp_Ser  udp= new Udp_Ser(port[i]);
			 threads[i] = new Thread (udp);
			 threads[i].start();
		 }
	}

}
