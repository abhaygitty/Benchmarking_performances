
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;

public class TCP_Server extends Thread {

	protected Socket sendersocket;

	public static void main(String[] args) throws IOException {
	
		Scanner in = new Scanner(System.in);
		System.out.println("Enter Number of threads 1/2/4/8");
		String s = in.nextLine();
		in.close();
		int a = Integer.parseInt(s);
		
		ServerSocket Socket1 = null;
		ServerSocket Socket2 = null;
		ServerSocket Socket3 = null;
		ServerSocket Socket4 = null;
		ServerSocket Socket5 = null;
		ServerSocket Socket6 = null;
		ServerSocket Socket7 = null;
		ServerSocket Socket8 = null;

		try {
			//Creates server Socket bound to specified port provided
			Socket1 = new ServerSocket(11379);
			Socket2 = new ServerSocket(11279);
			Socket3 = new ServerSocket(11280);
			Socket4 = new ServerSocket(11281);
			Socket5 = new ServerSocket(11380);
			Socket6 = new ServerSocket(11381);
			Socket7 = new ServerSocket(11385);
			Socket8 = new ServerSocket(11388);
			try {
				while (true) {
					new TCP_Server(Socket1.accept());
					if(a >= 2)
					{
						new TCP_Server(Socket2.accept());
					}
					if(a >= 3)
					{
						new TCP_Server(Socket3.accept());
					}
					if(a >= 4)
					{
						new TCP_Server(Socket4.accept());
					}
					if(a >= 5)
					{
						new TCP_Server(Socket5.accept());
					}
					if(a >= 6)
					{
						new TCP_Server(Socket6.accept());
					}
					if(a >= 7)
					{
						new TCP_Server(Socket7.accept());
						if(a > 7)
							new TCP_Server(Socket8.accept());
					}
				}
			} catch (Exception e) {
				System.out.println("Connection failure.");
				System.exit(1);
			}
		} catch (Exception e) {
		
			System.exit(1);
		} finally {
			try {
				// Socket is closed
				Socket1.close();
				Socket2.close();
				Socket3.close();
				Socket4.close();
				Socket5.close();
				Socket6.close();
				Socket7.close();
				Socket8.close();
			} catch (Exception e) {
				System.exit(1);
			}
		}
	}

	private TCP_Server(Socket clientSoc) {
		sendersocket = clientSoc;
		start();
	}

	public void run() {
		try {
			InputStream input = sendersocket.getInputStream(); 
			OutputStream output = sendersocket.getOutputStream(); 
			DataInputStream DIN = new DataInputStream(input);
			int length = DIN.readInt(); 
			byte[] RecievedPacket = new byte[length];
			DIN.readFully(RecievedPacket); 
			DataOutputStream DOUT = new DataOutputStream(output);
			DOUT.write(RecievedPacket); 
		} catch (Exception e) {
			System.exit(1);
		}
	}
}

