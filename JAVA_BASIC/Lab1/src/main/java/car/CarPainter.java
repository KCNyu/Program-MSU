package car;

import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;

import static javax.swing.WindowConstants.EXIT_ON_CLOSE;

/**
 * @author : Alex
 * @created : 10.03.2021, среда
 **/
public class CarPainter extends JPanel implements CarEventsListener {

    private final FieldMatrix fieldMatrix;
    private final static int preferedCellSize = 50;
    private final static int preferedGap = 20;

    private final java.util.List<Car> cars;

    public CarPainter(FieldMatrix fieldMatrix) {
        super();
        cars = new ArrayList<>();
        this.fieldMatrix = fieldMatrix;
        JFrame f = new JFrame("Cars");
        setBackground(Color.LIGHT_GRAY);
        f.setSize(fieldMatrix.cols * preferedCellSize + 2 * preferedGap, fieldMatrix.rows * preferedCellSize + 2 * preferedGap);
        f.add(this);
        f.setDefaultCloseOperation(EXIT_ON_CLOSE);
        f.setVisible(true);
    }

    @Override
    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        int screenWidth = getWidth();
        int screenHeight = getHeight();
        FontMetrics fm = g.getFontMetrics();
        g.setColor(Color.BLACK);
        int width = Math.min(screenHeight - 2 * preferedGap, screenWidth - 2 * preferedGap);
        int step = width / Math.max(fieldMatrix.cols, fieldMatrix.rows);
        for (int i = 0; i <= fieldMatrix.rows; i++)
            for (int j = 0; j <= fieldMatrix.cols; j++) {
                g.drawLine(i * step + preferedGap, j * step + preferedGap, fieldMatrix.rows * step, j * step + preferedGap);
                g.drawLine(i * step + preferedGap, j * step + preferedGap, i * step + preferedGap, fieldMatrix.cols * step);
                if ( i<fieldMatrix.rows && j<fieldMatrix.cols && fieldMatrix.getCellState(i,j) == FieldMatrix.CellState.WALL) {
                    g.setColor(Color.RED);
                    g.fill3DRect(j * step + preferedGap, i * step + preferedGap, step, step, false);
                    g.setColor(Color.BLACK);
                }
            }
        for (Car car : cars) {
            Position p = car.getPosition();
            g.setColor(car.getColor());
            g.fill3DRect(p.col * step + preferedGap, p.row * step + preferedGap, step, step, false);
            if (car.getName() != null){
                int stringWith = fm.stringWidth(car.getName());
                g.setColor(Color.WHITE);
                g.drawString(car.getName(),p.col * step + preferedGap + (step - stringWith)/2, p.row * step + preferedGap + step/2);
            }

        }
    }

    @Override
    public void carCreated(Car car) {
        cars.add(car);
    }

    @Override
    public void carDestroyed(Car car) {
        cars.remove(car);
        repaint();
    }

    @Override
    public void carMoved(Car car, Position from, Position to, boolean success) {
        repaint();
    }

    @Override
    public void carParameterChanged(Car car) {repaint();}


}
