public abstract class Student 
{
    private int id;
    private String lastName;
    protected double tuition;

    public Student(int id, String lastName) 
    {
        this.id = id;
        this.lastName = lastName;
    }

    public int getId() 
    {
        return id;
    }

    public void setId(int id) 
    {
        this.id = id;
    }

    public String getLastName() 
    {
        return lastName;
    }

    public void setLastName(String lastName) 
    {
        this.lastName = lastName;
    }

    public double getTuition() 
    {
        return tuition;
    }

    public abstract void setTuition();

    public String toString() 
    {
        return "Student # " + id + " Name: " + lastName + "  Tuition: " + tuition + " per year";
    }
}