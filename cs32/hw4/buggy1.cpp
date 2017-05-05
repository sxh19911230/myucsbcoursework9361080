//Xianghong Sun

#include <iostream>
#include <string>

using namespace std;

string trackUserAnswer();

int main()
{
  
  string courseNamesTable[5];
  string courseName;
  string userAnswer;

  int courseCounter = 0;

  int n =0;
  do
  {
    n++;
    cout << "Enter a course name:\n";
    getline(cin,courseName,'\n');
    courseNamesTable[courseCounter] = courseName;
    cout << "You are registered for the following " << courseCounter + 1 << " courses:\n";

    for (int i=0; i<=courseCounter; i++)
    {
      cout << i+1 << ". " << courseNamesTable[i] << "\n";
    }

    userAnswer = trackUserAnswer();

    courseCounter++;
   
  } while(n < 5 && userAnswer.compare("y") == 0);

  return 0;
}

string trackUserAnswer()
{
  string userAnswer;

  while (userAnswer.compare("n") && userAnswer.compare("y"))
  {
     cout << "\n Do you Want to register for  another course? (y/n)\n";
     cin >> userAnswer;
     cout << "Your Answer is:" << userAnswer << "\n";
     cin.ignore(200, '\n');
  }

  return userAnswer;     
}
