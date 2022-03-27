package net.server;

import car.BasicCarServer;
import car.Car;
import car.command.Command;
import net.CommandCode;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;

/**
 * @author : Alex
 * @created : 18.03.2021, четверг
 **/
public class ClientWorker implements Runnable {
    private final Socket clientSocket;
    private final DataInputStream dis;
    private final DataOutputStream dos;
    private final BasicCarServer carServer;
    private final Car car;

    public ClientWorker(Socket clientSocket, BasicCarServer carServer) throws IOException {
        this.clientSocket = clientSocket;
        this.carServer = carServer;
        this.car = carServer.createCar();
        this.dis = new DataInputStream(clientSocket.getInputStream());
        this.dos = new DataOutputStream(clientSocket.getOutputStream());
    }

    @Override
    public void run() {
        try {
            while (true) {
                String stringCommand = dis.readUTF();
                String parameter = dis.readUTF();
                Command command = Command.createCommand(car, stringCommand + " " + parameter);
                boolean result = false;
                try {
                    result = command.execute();
                }catch (Exception e){}
                dos.writeBoolean(result);
            }
        } catch (IOException e) {
            carServer.destroyCar(car);
            e.printStackTrace();
        }
    }
}
