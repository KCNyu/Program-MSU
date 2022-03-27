package car.command;

import car.Car;
import car.CarServer;

/**
 * @author : Alex
 * @created : 12.03.2021, пятница
 **/
public class UpCommand extends MoveCommand{
    public UpCommand(Integer parameter, Car car){
        super(parameter, car, CarServer.Direction.UP);
    }

    static{
        factory.put(UpCommand.class, (param, car)->new UpCommand(Integer.parseInt(param),car));
    }
}
