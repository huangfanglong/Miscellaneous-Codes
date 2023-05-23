public class DemoHorses 
{
    public static void main(String[] args) 
    {
        Horse horse1 = new Horse("Old Paint", "brown", 2009);
        System.out.println(horse1.getName() + " is " + horse1.getColor() + " and was born in " + horse1.getBirthYear() + ".");

        RaceHorse horse2 = new RaceHorse("Champion", "black", 2011, 4);
        System.out.println(horse2.getName() + " is " + horse2.getColor() + " and was born in " + horse2.getBirthYear() + ".");
        System.out.println(horse2.getName() + " has been in " + horse2.getRaces() + " races.");
    }
}