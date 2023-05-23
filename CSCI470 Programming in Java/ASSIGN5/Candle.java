public class Candle 
{
    private String color;
    private int height;
    protected double price;

    public Candle(String color, int height) 
    {
        this.color = color;
        this.height = height;
        setPrice();
    }

    public String getColor() 
    {
        return color;
    }

    public void setColor(String color) 
    {
        this.color = color;
    }

    public int getHeight() 
    {
        return height;
    }

    public void setHeight(int height) 
    {
        this.height = height;
        setPrice();
    }

    public double getPrice() 
    {
        return price;
    }

    private void setPrice() 
    {
        price = height * 2.0;
    }
}