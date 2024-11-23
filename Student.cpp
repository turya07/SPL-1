#include "Student.h"

Student::Student(int r, std::string n)
{
    roll = r;
    name = n;
}
void Student::display(){
    
    std::cout << name<<", "<<roll<<std::endl;
}
Student::~Student(){
    std::cout << "Destructor called for "<<name<<std::endl;
}