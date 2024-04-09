package P1.P2;

public class Point {
    public static void main(String[] args) {
        Point2D point2D = new Point2D(3, 4);
        Point3D point3D = new Point3D(3, 4, 5);

        System.out.println("Расстояние от точки 2D до начала координат: " + point2D.distanceFromOrigin());
        System.out.println("Расстояние от точки 3D до начала координат: " + point3D.distanceFromOrigin());
    }
}

class Point2D {
    private double x, y;

    public Point2D(double x, double y) {
        this.x = x;
        this.y = y;
    }

    public double distanceFromOrigin() {
        return Math.sqrt(x * x + y * y);
    }
}

class Point3D extends Point2D {
    private double z;

    public Point3D(double x, double y, double z) {
        super(x, y);
        this.z = z;
    }

    @Override
    public double distanceFromOrigin() {
        return Math.sqrt(super.distanceFromOrigin() + z * z);
    }
}
