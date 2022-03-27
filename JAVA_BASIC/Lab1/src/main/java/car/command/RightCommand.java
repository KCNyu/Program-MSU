package car.command;

import car.Car;
import car.CarServer;

/**
 * @author : Alex
 * @created : 12.03.2021, пятница
 **/
public class RightCommand extends MoveCommand{
    public RightCommand(Integer parameter, Car car){
        super(parameter, car, CarServer.Direction.RIGHT);
    }
    static{
        factory.put(RightCommand.class, (param, car)->new RightCommand(Integer.parseInt(param),car));
    }
}
