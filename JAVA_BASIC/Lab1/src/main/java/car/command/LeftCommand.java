package car.command;

import car.Car;
import car.CarServer;

/**
 * @author : Alex
 * @created : 12.03.2021, пятница
 **/
public class LeftCommand extends MoveCommand {

    public LeftCommand(Integer parameter, Car car){
        super(parameter, car, CarServer.Direction.LEFT);
    }

    static{
        factory.put(LeftCommand.class, (param, car)->new LeftCommand(Integer.parseInt(param),car));
    }
}
