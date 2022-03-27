package car;

import java.awt.*;
import java.time.LocalDateTime;
import java.util.Random;

/**
 * @author : Alex
 * @created : 10.03.2021, среда
 **/
public class Car {
    private final CarServer carServer;

    private Position position;
    private static int count = 1;
    private int index;
    private int speed = 500;
    private Color color;
    private String name;
    private LocalDateTime lastOperation;

    public Car(CarServer carServer, Position position){
        this.carServer = carServer;
        this.position = position;
        speed = new Random().nextInt(300) + 300;
        index = count++;
        color = new Color((int)(Math.random() * 0x1000000));
        lastOperation = LocalDateTime.now();
    }

    public void setColor(Color color){
        this.color = color;
        carServer.carParameterChanged(this);
    }

    public Color getColor(){return color;}
    public String getName(){return name;}
    public void setName(String name){
        this.name = name;
        carServer.carParameterChanged(this);
    }
    public LocalDateTime getLastOperation(){return lastOperation;}
    public void destroy(){
        carServer.destroyCar(this);
    }

    public boolean moveTo(CarServer.Direction direction){
        try {
            Thread.sleep(speed);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        try {
            lastOperation = LocalDateTime.now();
            if (carServer.moveCarTo(this, direction)) {
                position = position.move(direction);
                return true;
            } else
                return false;
        }catch(ArrayIndexOutOfBoundsException e){
            return false;
        }

    }
    public Position getPosition(){return position;}

    public int getIndex(){return index;}

    @Override
    public String toString(){
        return "Car: index="+index;
    }
}
