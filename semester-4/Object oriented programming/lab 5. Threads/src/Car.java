public abstract class Car {
    private static class Engine {}
    private static class Wheel {}

    public String color;
    public float speed;

    abstract void setColor(String color);

}