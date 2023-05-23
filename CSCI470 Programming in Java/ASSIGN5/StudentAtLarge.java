public class StudentAtLarge extends Student 
{
    public StudentAtLarge(int id, String lastName) 
    {
        super(id, lastName);
        setTuition();
    }

    @Override
    public void setTuition() 
    {
        super.tuition = 2000.0;
    }
}