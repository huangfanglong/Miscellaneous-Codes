public class UndergraduateStudent extends Student 
{
    public UndergraduateStudent(int id, String lastName) 
    {
        super(id, lastName);
        setTuition();
    }

    @Override
    public void setTuition() 
    {
        super.tuition = 4000.0;
    }
}