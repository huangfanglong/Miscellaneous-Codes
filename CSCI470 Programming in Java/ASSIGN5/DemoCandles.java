public class DemoCandles 
{
    public static void main(String[] args) 
    {
        Candle candle1 = new Candle("pink", 6);
        System.out.println("The " + candle1.getHeight() + " inch " + candle1.getColor() + " candle costs $" + candle1.getPrice());

        ScentedCandle candle2 = new ScentedCandle("white", 6, "gardenia");
        System.out.println("The " + candle2.getHeight() + " inch " + candle2.getScent() + " " + candle2.getColor() + " candle costs $" + candle2.getPrice());
    }
}