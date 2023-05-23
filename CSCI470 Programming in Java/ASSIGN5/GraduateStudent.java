public class GraduateStudent extends Student 
{
    public GraduateStudent(int id, String lastName) 
    {
        super(id, lastName);
        setTuition();
    }

    @Override
    public void setTuition() 
    {
        super.tuition = 6000.0;
    }
}