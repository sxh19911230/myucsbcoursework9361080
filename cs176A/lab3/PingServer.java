import java.io.*;
import java.net.*;
/*
 * Server to process ping requests over UDP.
 */
public class PingServer
{
        private static final double LOSS_RATE = 0.3;
        private static final int AVERAGE_DELAY = 100;  // milliseconds
        DatagramSocket socket;
        
        public static void main(String[] args) throws Exception {
                if (args.length != 1) {
                        System.out.println("Required arguments: port");
                        return;
                }
                new PingServer(Integer.parseInt(args[0])); // Use command line argument
        }
        
        PingServer(int port) throws IOException {
                // Create a datagram socket for receiving and sending UDP packets
                // through the port specified on the command line.
                socket = new DatagramSocket(port);
                // Processing loop:
                        // 1. Create a datagram packet to hold incoming UDP packet (1 per thread).
                // 2. Block until the host receives a UDP packet.
                // 3. Spawn a worker thread to reply eventually (or drop it).
                while (true) {
                        DatagramPacket request = new DatagramPacket(new byte[1024], 1024);
                        socket.receive(request);
                        new Thread(this.new Echo((request))).start();
                }
        }
        class Echo implements Runnable {
                DatagramPacket request;
                
                Echo(DatagramPacket packet) { request = packet; }
                
                public void run() {
                        System.out.print("Received from " + request.getAddress().getHostAddress() + ": ");
                        // Decide whether to reply, or simulate packet loss.
                        if (Math.random() < LOSS_RATE) {
                                System.out.println("DROPPED.");
                        } else {
                                try {
                                        int delay = (int) (Math.random() * 2 * AVERAGE_DELAY);
                                        System.out.println("Echoing after " + delay + " ms.");
                                        Thread.sleep(delay);        // Simulate network delay.
                                        socket.send(request);        // Send same packet back.
                                } catch (Exception e) {}
                        }
                }
                
        }
}
