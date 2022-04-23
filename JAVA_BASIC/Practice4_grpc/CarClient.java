package grpc.carservice;

import grpc.carservice.AddNewCarRequest;
import grpc.carservice.MoveCarRequest;
import grpc.carservice.SetCarColorRequest;
import io.grpc.Channel;
import io.grpc.ManagedChannel;
import io.grpc.ManagedChannelBuilder;

import java.util.Random;

public class CarClient implements Runnable {
    static String [] colors = {"red", "blue", "green", "yellow", "black", "white"};
    private static grpc.carservice.CarServiceGrpc.CarServiceBlockingStub createClient(String host, int port) {
        Channel channel = ManagedChannelBuilder.forAddress(host, port).usePlaintext().build();
        return grpc.carservice.CarServiceGrpc.newBlockingStub(channel);
    }
    String name;

    public CarClient(String name) {
        this.name = name;
    }

    public static void main(String[] args) {
        new Thread(new CarClient("cxd-0")).start();
        new Thread(new CarClient("cxd-00")).start();
        new Thread(new CarClient("cxd-000")).start();
    }

    @Override
    public void run() {
        grpc.carservice.CarServiceGrpc.CarServiceBlockingStub client = createClient("185.188.181.184", 8080);

        AddNewCarRequest request = AddNewCarRequest.newBuilder().setName(name).setColor("blue").build();
        grpc.carservice.AddNewCarResponse response = client.createCar(request);
        int id = response.getCarIndex();

        MoveCarRequest request2 = MoveCarRequest.newBuilder().setCarIndex(id).setDirection(grpc.carservice.Direction.DOWN).setCount(1).build();
        grpc.carservice.Direction direction = grpc.carservice.Direction.DOWN;
        Random random = new Random();
        while(true) {
            grpc.carservice.MoveCarResponse response2 = client.moveCar(request2);
            boolean res = response2.getResult();
            if(!res){
                direction = grpc.carservice.Direction.values()[random.nextInt(grpc.carservice.Direction.values().length-1)];
                SetCarColorRequest request3 = SetCarColorRequest.newBuilder().setCarIndex(id).setColor(colors[random.nextInt(colors.length)]).build();
                client.setCarColor(request3);
            }
            request2 = MoveCarRequest.newBuilder().setCarIndex(id).setDirection(direction).setCount(1).build();
        }
    }
}
