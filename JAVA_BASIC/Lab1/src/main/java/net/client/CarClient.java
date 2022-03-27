package net.client;

import net.CommandCode;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.util.Random;


public class CarClient implements Runnable {
    static String[] colors = {"red", "blue", "green", "yellow", "black", "white"};

    String host;
    int port;
    String name;
    DataInputStream in;
    DataOutputStream out;
    Socket socket;

    CarClient(String host, int port, String name) throws IOException {
        this.host = host;
        this.port = port;
        this.name = name;

        socket = new Socket(host, port);
    }

    boolean executeCommand(CommandCode command, String param) throws IOException {
        out.writeUTF(command.name());
        out.flush();
        out.writeUTF(param);
        out.flush();
        return in.readBoolean();
    }

    @Override
    public void run() {

        System.out.println("Connected to server");
        try {
            in = new DataInputStream(socket.getInputStream());
            out = new DataOutputStream(socket.getOutputStream());

            // SetName
            executeCommand(CommandCode.SETNAME, name);

            // send first command to server
            Random random = new Random();
            CommandCode comm = CommandCode.DOWN;
            String param = "1";

            while (true) {
                if (comm == CommandCode.CHANGECOLOR) {
                    param = colors[random.nextInt(colors.length)];
                } else {
                    param = "1";
                }
                if (!executeCommand(comm, param) || comm == CommandCode.CHANGECOLOR) {
                    comm = CommandCode.values()[random.nextInt(CommandCode.values().length - 1)];
                    // avoid Command SetName
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) throws InterruptedException, IOException {
        new Thread(new CarClient("localhost", 8080, "lsy1")).start();
        // new Thread(new CarClient("185.188.181.184", 8080, "lsy1")).start();
        new Thread(new CarClient("localhost", 8080, "lsy2")).start();
    }
}