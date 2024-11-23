#include <iostream>
#include <string>

class Student
{
private:
    int roll;
    std::string name;
public:
    Student(int,std::string);
    void display();
    ~Student();
};
