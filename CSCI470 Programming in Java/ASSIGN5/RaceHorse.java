public class RaceHorse extends Horse 
{
    private int races;

    public RaceHorse(String name, String color, int birthYear, int races) 
    {
        super(name, color, birthYear);
        this.races = races;
    }

    public int getRaces() 
    {
        return races;
    }

    public void setRaces(int races) 
    {
        this.races = races;
    }
}