package car;

/**
 * @author : Alex
 * @created : 10.03.2021, среда
 **/
public interface CarServer {
    enum Direction{
        UP,DOWN,LEFT,RIGHT
    }

    Car createCar();
    void destroyCar(Car car);
    boolean moveCarTo(Car car, Direction direction);
    void carParameterChanged(Car car);

}
