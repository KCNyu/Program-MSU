package car;

import car.webservice.Direction;
import car.webservice.Server;
import car.webservice.ServerService;

import java.net.MalformedURLException;
import java.net.URL;
import java.util.Random;

public class client implements Runnable {

    public static String url = "http://localhost:8080/CarServer?wsdl";
    private String name;
    private ServerService service;
    private Server serverPort;

    public client(String name) {
        this.name = name;
        try {
            service = new ServerService(new URL(url));
        } catch (MalformedURLException e) {
            e.printStackTrace();
        }
        serverPort = service.getServerPort();
    }

    @Override
    public void run() {

        int carIndex = serverPort.createCar();
        System.out.println("Car index: " + carIndex);
        serverPort.setCarName(carIndex, name);

        Random random = new Random();
        Direction direction = Direction.DOWN;
        serverPort.changeCarColor(carIndex, "red");
        while (true) {
            boolean res = serverPort.moveCarTo(carIndex, direction);
            if (!res) {
                direction= Direction.values()[random.nextInt(Direction.values().length)];
            }
        }
    }

    public static void main(String[] args) throws MalformedURLException {
        new Thread(new client("lsy1")).start();
        new Thread(new client("lsy2")).start();
        new Thread(new client("lsy3")).start();
    }
}
