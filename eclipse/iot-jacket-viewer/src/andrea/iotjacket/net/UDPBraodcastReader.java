package andrea.iotjacket.net;


import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;


public class UDPBraodcastReader implements Runnable {
	
	
    private String ip;
	private int port;
	private int messageSize;
	
	
	public UDPBraodcastReader(int port, int messageSize) {
		super();
		this.ip = "0.0.0.0";
		this.port = port;
		this.messageSize = messageSize;
	}
	


	public String receiveData() {
		return receiveData(";");
	}
	
	public String receiveData(String delim) {
		
		String rtn = null;
		
		try {
			DatagramSocket socket = new DatagramSocket(this.port, InetAddress.getByName(this.ip));
			DatagramPacket data = new DatagramPacket( new byte[this.messageSize], this.messageSize);
			socket.receive(data);
			
			String dataString = new String( data.getData(), "UTF-8" );
			
			socket.close();
		
			int idx = dataString.lastIndexOf(delim);
			 rtn = dataString.substring(0,idx);
			
		} catch (SocketException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (UnknownHostException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} 
		
		return rtn;
	}

	
	public static void main(String[] args) {
		UDPBraodcastReader udp = new UDPBraodcastReader(2390,100);
		
		
		while(true){
		System.out.println(udp.receiveData());
		}
	}

	@Override
	public void run() {
		// TODO Auto-generated method stub
		
	}

}
