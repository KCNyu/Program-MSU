package car;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.Timer;
import java.util.TimerTask;
import java.util.stream.Collectors;

/**
 * @author : Alex
 * @created : 10.03.2021, среда
 **/
public class BasicCarServer implements CarServer {
    protected final FieldMatrix fieldMatrix;
    protected final List<Car> cars;
    protected final CarEventsListener carEventsListener;
    protected static BasicCarServer carServer;
    public static final int maxCarSecondsDonNotMove = 10;

    public static BasicCarServer getServer(){return carServer;}
    public static  synchronized BasicCarServer createCarServer(FieldMatrix fieldMatrix, CarEventsListener carEventsListener){
        if (carServer == null) carServer = new BasicCarServer(fieldMatrix,carEventsListener);
        return carServer;
    }
    protected BasicCarServer(FieldMatrix fieldMatrix, CarEventsListener carEventsListener){
        cars = new ArrayList<>();
        this.fieldMatrix = fieldMatrix;
        this.carEventsListener = carEventsListener;
        carServer = this;

        TimerTask carCleaner = new TimerTask() {
            @Override
            public void run() {
                //System.out.println("start cleaner...");
                List<Car> carsToRemove = cars.stream()
                        .filter(
                                (car)->car.getLastOperation().isBefore(LocalDateTime.now().minusSeconds(maxCarSecondsDonNotMove))
                        ).collect(Collectors.toList());
                for(Car car:carsToRemove) {
                    System.out.println("destroy "+car);
                    car.destroy();
                }
            }
        };
        Timer timer = new Timer("CarCleaner");
        timer.scheduleAtFixedRate(carCleaner,0,10000);

    }

    public Car getCar(int index){
        return cars.stream()
                .filter((car)->car.getIndex()==index)
                .findAny()
                .orElse(null);
    }

    @Override
    public synchronized Car createCar() {
        Position freeCell = fieldMatrix.occupyFirstFreeCellByCar();
        Car car = new Car(this, freeCell);
        cars.add(car);
        carEventsListener.carCreated(car);
        return car;
    }

    @Override
    public void destroyCar(Car car) {
        cars.remove(car);
        fieldMatrix.freeCellFromCar(car.getPosition());
        carEventsListener.carDestroyed(car);
    }

    @Override
    public boolean moveCarTo(Car car, Direction direction) {
        Position from = car.getPosition();
        Position to = from.move(direction);
        boolean ret = fieldMatrix.moveCarTo(from.row, from.col, to.row, to.col);
        carEventsListener.carMoved(car,from,to,ret);
        return ret;
    }

    @Override
    public void carParameterChanged(Car car) {
        carEventsListener.carParameterChanged(car);
    }

}
