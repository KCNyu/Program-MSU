package car.command;

import car.Car;

import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

/**
 * @author : Alex
 * @created : 11.03.2021, четверг
 **/
public class Script {
    private List<Command> commands;
    public Script(){
        commands = new ArrayList<>();
    }


    public void addCommand(Command command){
        commands.add(command);
    }

    public void execute(){
        for (Command command : commands)
            command.execute();
    }

    public static Script load(Car car, InputStreamReader isr){
        Scanner scanner = new Scanner(isr);
        Script script = new Script();
        while(scanner.hasNextLine()){
            Command command = Command.createCommand(car, scanner.nextLine());
            script.addCommand(command);
        }
        return script;
    }
}
