// simple.cpp -- shows some simple inheritance features
// Xianghong Sun

#include <iostream>
using namespace std;

class Parent {

public:
  Parent() : age(45) { }

  void setAge(int years) { 
     cout << "SetAge method from Parent class" << endl;
     age = years;
  }

  int getAge() { return age; }

  int increaseAge() { 
     cout << "This is Parent::increaseAge: My age: " << age
          << " And now I am one year older" << endl; 
     return age = age + 1;
  }

  int getSSN() { return ssn; }

protected:
  int age;
 
private:
  int ssn; //Social Security Number
};

class Child : public Parent {

public:
  Child() { age = 7; }

  int change() {
    age = increaseAge();
    return age;
  }

  void setAge(int years) {
    age = years;
    Parent::setAge(years); 
    cout << "This is Child::setAge" << endl;
  }

  void printAge() { 
      cout << "Parent::age " << Parent::age << endl;
      cout << "getAge() " << getAge() << endl;
      cout << "Parent::getAge() " << Parent::getAge() << endl;
      cout << "age " << age << endl;
 }
  
  
  void printSSN ()
  {
    cout << "My SSN number is: " << getSSN() << endl;
  }
 
};

int main() {
 
  cout << "sizeof(Parent) = " << sizeof(Parent) << endl;
  cout << "sizeof(Child) = "
       << sizeof(Child) << endl;

  Child C;


  C.change();
  C.printAge();


  C.increaseAge();
  C.printAge();
  

  
  C.Parent::setAge(50); //Invoke parent version
  C.setAge(55);
  C.printAge();
  
      
  Parent P;

  //P.increaseAge();
  //P.printAge();

}
