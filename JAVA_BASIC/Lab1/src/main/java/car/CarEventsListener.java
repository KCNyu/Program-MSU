package car;

/**
 * @author : Alex
 * @created : 10.03.2021, среда
 **/
public interface CarEventsListener {
    void carCreated(Car car);
    void carDestroyed(Car car);
    void carMoved(Car car, Position from, Position to, boolean success);
    void carParameterChanged(Car car);
}
