package net.rmi;

import net.CommandCode;
import net.command.SerializableCommand;

import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.Random;
import java.util.Stack;

public class RemoteCarClient implements Runnable {
    static String[] colors = {"red", "blue", "green", "yellow", "black", "white"};
    public static int port = 8080;
    public static String name = "RMICarServer";
    public static String host = "185.188.181.184";
    public static Registry registry;

    static {
        try {
            registry = LocateRegistry.getRegistry(host, port);
        } catch (RemoteException e) {
            e.printStackTrace();
        }
    }

    public RemoteCarServer server;
    public String carname;

    public RemoteCarClient(String carname) throws NotBoundException, RemoteException {
        this.server = (RemoteCarServer) registry.lookup(name);
        System.out.println("server = " + server);
        this.carname = carname;
    }
    public static void main(String[] args) throws RemoteException, NotBoundException, InterruptedException {
        new Thread(new RemoteCarClient("GN-East")).start();
        // Thread.sleep(1000);
        new Thread(new RemoteCarClient("GN-West")).start();
    }

    @Override
    public void run() {
        int carIndex = 0;
        try {
            carIndex = server.executeCommand(new SerializableCommand(0, "CREATECAR", ""));
        } catch (RemoteException e) {
            e.printStackTrace();
        }
        try {
            server.executeCommand(new SerializableCommand(carIndex, "SETNAME", carname));
        } catch (RemoteException e) {
            e.printStackTrace();
        }

        Random random = new Random();
        String param = "1";
        CommandCode commandCode = CommandCode.DOWN;
        while (true) {
            if (commandCode == CommandCode.CHANGECOLOR) {
                param = colors[random.nextInt(colors.length)];
            } else {
                param = "1";
            }
            boolean res = false;
            try {
                res = server.executeCommand(new SerializableCommand(carIndex, commandCode.name(), param));
            } catch (RemoteException e) {
                e.printStackTrace();
            }
            if (!res || commandCode == CommandCode.CHANGECOLOR) {
                commandCode = CommandCode.values()[random.nextInt(CommandCode.values().length - 1)];
                // avoid Command SetName
            }
        }
    }
}