package net.rmi;

import car.*;
import car.command.*;
import net.command.SerializableCommand;

import java.io.InputStream;
import java.io.InputStreamReader;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.Objects;
import java.util.function.Function;
import java.util.stream.Stream;

public class RMICarServer extends BasicCarServer implements RemoteCarServer {

    public static final int PORT = 8080;
    public static final String NAME = "RMICarServer";

    @Override
    public Object executeCommand(SerializableCommand command) {
        Function<Integer, Car> carProvider = carIndex -> Objects.equals(command.commandName, "CREATE")
                ? carServer.createCar()
                : carServer.getCar(carIndex);

        Command comm = Stream.of(command)
                .map(cmd -> cmd.commandName + " " + cmd.commandparameter)
                .map(cmdStr -> Command.createCommand(carProvider.apply(command.carIndex), cmdStr))
                .findFirst()
                .orElseThrow();

        System.out.println(comm);
        return comm.execute();
    }

    public RMICarServer(FieldMatrix fieldMatrix, CarEventsListener carEventsListener) {
        super(fieldMatrix, carEventsListener);
    }

    public static void main(String[] args) throws Exception {
        FieldMatrix fieldMatrix = loadFieldMatrix("Field10x10.txt");
        CarPainter carPainter = new CarPainter(fieldMatrix);
        RMICarServer server = new RMICarServer(fieldMatrix, carPainter);
        startRMIServer(server);
    }

    private static FieldMatrix loadFieldMatrix(String fileName) throws Exception {
        InputStream inputStream = CarPainter.class.getClassLoader().getResourceAsStream(fileName);
        return FieldMatrix.load(new InputStreamReader(inputStream));
    }

    private static void startRMIServer(RMICarServer server) throws Exception {
        Registry registry = LocateRegistry.createRegistry(server.PORT);
        RemoteCarServer remoteCarServer = (RemoteCarServer) UnicastRemoteObject.exportObject(server, 0);
        registry.bind(NAME, remoteCarServer);
        System.out.println("Server started on port: " + server.PORT);
    }
}
