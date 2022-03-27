package car;

import car.command.Script;
import java.io.InputStream;
import java.io.InputStreamReader;



/**
 * @author : Alex
 * @created : 12.03.2021, пятница
 **/
public class Main {
    public static void main(String[] args) throws Exception{
        InputStream is = CarPainter.class.getClassLoader().getResourceAsStream("Field10x10.txt");
        //System.out.println(is);
        FieldMatrix fm = FieldMatrix.load(new InputStreamReader(is));
        //FieldMatrix fm = new FieldMatrix(10,10);
        CarPainter p = new CarPainter(fm);
        BasicCarServer carServer = BasicCarServer.createCarServer(fm, p);
        Car car = carServer.createCar();
        Script script = Script.load(car, new InputStreamReader(CarPainter.class.getClassLoader().getResourceAsStream("script.txt")));
        script.execute();

    }
}
