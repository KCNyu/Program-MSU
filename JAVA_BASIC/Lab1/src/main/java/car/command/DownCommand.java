package car.command;

import car.Car;
import car.CarServer;

/**
 * @author : Alex
 * @created : 11.03.2021, четверг
 **/
public class DownCommand extends MoveCommand {
    public DownCommand(Integer parameter, Car car){
        super(parameter, car, CarServer.Direction.DOWN);
    }

    static{
        factory.put(DownCommand.class, (param, car)->new DownCommand(Integer.parseInt(param),car));
    }
}
