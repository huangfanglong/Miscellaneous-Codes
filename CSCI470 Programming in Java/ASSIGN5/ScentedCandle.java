public class ScentedCandle extends Candle 
{
    private String scent;

    public ScentedCandle(String color, int height, String scent) 
    {
        super(color, height);
        this.scent = scent;
    }

    public String getScent() 
    {
        return scent;
    }

    public void setScent(String scent) 
    {
        this.scent = scent;
    }

    @Override
    public void setHeight(int height) 
    {
        super.setHeight(height);
        setPrice();
    }

	@Override
    private void setPrice() 
    {
        super.price = getHeight() * 3.0;
    }
}