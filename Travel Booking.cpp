#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cctype>
#include<cstdlib>
#include<ctime>
#include<limits>
using namespace std;
int maxseat=20;//variable to store total number of seats
string convert(string &str)//converts first alphabet of each word of a line to uppercase
{
    bool capitalize = true;
    for (size_t i = 0; i < str.size(); ++i) {
        if (isalpha(str[i])) {
            if (capitalize) {
                str[i] = static_cast<char>(toupper(static_cast<unsigned char>(str[i])));
                capitalize = false;
            } else {
                str[i] = static_cast<char>(tolower(static_cast<unsigned char>(str[i])));
            }
        } else if (isspace(str[i])) {
            capitalize = true;
        }
    }
    return str;
}//checks if the provided name is valid(letters and spaces only, atleast one letter)
bool checkname(string n){
  for(char c : n)if(!isalpha(c) && !isspace(c)){cout<<"invalid name\n";return false;}
  for(char c : n)if(isalpha(c)){return true;}
  cout<<"No input provided\n";
  return false;
}//checks whether entered age is in correct format or not(DD-MM-YYYY)
bool check_date(string date){//assuming present date as 01-01-2025
  if (date.size() != 10){
    cout<<"incorrect date format , enter again\n";
    return false;
  }
  else{
    if (date[2] != '-' || date[5] != '-'||!isdigit(date[0])||!isdigit(date[1])||!isdigit(date[3])||!isdigit(date[4])||!isdigit(date[6])|| !isdigit(date[7])  ||!isdigit(date[8]) ||!isdigit(date[9]) ){
      cout << "invalid date format, enter again\n";
      return false;
    }else{
      int day, month, year;
      year = stoi(date.substr(6, 4));
      month = stoi(date.substr(3, 2));
      day = stoi(date.substr(0, 2));
      if (month < 1 || month > 12 || day < 1 || day > 31 ||(month==2 && day>28)||year>2026||year<2025)
      {
        cout << "invalid date, enter again\n";
        if (month == 2 && day>28){
          cout << "(February cannot have the given date)\n";return false;
        }
        if(year<2025||year>2026){
          cout<<"(booking not permitted for this date)";return false;
        }
        return false;
      }else{
        if (month == 4 || month == 6 || month == 9 || month == 11){
          if (day > 30){
            cout << "This month cannot have more than 30 days\n";
            return false;
          } else {
            return true;
          }
        }
        else {
          return true;
        }
      }
    }
  }
}//checks that integer variables are provided with integer input
int getvalidInt(const string &line) {
  int value;
  while (true) {
    cout << line;
    cin >> value;
    if (!cin.fail() && value > 0) {
      cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
      return value;
    }
    cin.clear(); // Clear the error flag
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
    cout << "Invalid input. Please enter a positive integer.\n";
  }
}//takes name input for creating booking and checks the format using checkname function
string getName(){
  string name,copyname;
  do{
  cout<<"enter name:";
  getline(cin,copyname);
  if(checkname(copyname)){
    name=convert(copyname);
    return name;}
  }while(true);
}//takes date input for creating booking and checks the format using check_date function
string getDate(){
  string date;
  do{
  cout<<"enter date (form : DD-MM-YYYY):";
  getline(cin,date);
  if(check_date(date))return date;
  }while(true);
}
//checks whether entered age is valid or not
int getvalidAge(){
  int age;
  while(true){
    age=getvalidInt("Enter Age :");
    if(age>0 && age<=150)return age;
    else cout<<"invalid age\n";
  }
  return 0;
}//for showing the enterd data  clearly and separate from other inputs
  void line() { cout << "-----------------------------------------------\n"; }
  void line2(){cout << "-------x-------x-------x-------x-------x-------x--------x-------\n";}
  void line3(){ cout << "_______________________________________________________________________________________________________________________________\n";}
class booking//for grouping the data of passengers
{
  string name;
  int age;
  string destination;
  int seatnumber; 
  int price;
  string date;
  int id;
public:
  bool confirm = true;//converted to false when invalid data input provided 
  booking(){//used for creating booking while execution of program
   id=rand();//for unique identification for each booking
   if(id<10000)id*=10; //so that all IDs have same number of digits
  }
  booking(string name_,int age_,string destination_,int seatnumber_,int id_,string date_){//used for adding bookings already existing in bookings.csv
    name=name_;
    age=age_;
    destination=destination_;
    date=date_;
    seatnumber=seatnumber_;
    id=id_;
    if(destination=="Ajmer"){price=100;}//setting price according to chosen destination
    else if(destination=="Alwar"){price=150;}
    else if(destination=="Barmer"){price=200;}
    else if(destination=="Bikaner"){price=250;}
    else if(destination=="Jaipur"){price=300;}
    else{price=0;}//if destination not selected

  }//to edit date of travel
  void updatedate(vector<booking>);
  void setdestination(){//for taking destination input 
     cout<<"\t\t----SELECT DESTINATION----\n";
    cout<<"1)Ajmer\n2)Alwar\n3)Barmer\n4)Bikaner\n5)Jaipur\n";
    do{
    int ch=getvalidInt("enter destination choice:");
    if(ch==1){destination="Ajmer";price=100;break;}//setting price according to chosen destination
    else if(ch==2){destination="Alwar";price=150;break;}
    else if(ch==3){destination="Barmer";price=200;break;}
    else if(ch==4){destination="Bikaner";price=250;break;}
    else if(ch==5){destination="Jaipur";price=300;break;}
    else{
      cout<<"invalid choice, enter again:\n";
    }
  }while(true);
  }
  void create()//to create booking using functions getname, getvalidAge, setdestination and getDate.
  {
    name=getName();
    line();  cout << "\tNAME : " << name << endl;line();
    age=getvalidAge();
    line();  cout << "\tAGE : " << age << endl;line(); 
    setdestination();
   line();cout<<"\tDESTINATION:"<<destination<<endl;line();
    date=getDate();
 
  }
  void setseatnumber(vector<booking> b1)//taking input(seatnumber)
  {  
    seatnumber=0;
    do{
      int booked=0;//to count the number of seats booked
      confirm=true;
      vector<bool> seat(maxseat, false);//vector to store true for booked seats and false for available seats
    for (size_t i=0;i<b1.size();i++) {
        if (destination == b1[i].destination && date == b1[i].date && id!=b1[i].id) {
            int sn = b1[i].seatnumber;
            if (sn > 0 && sn <= maxseat){
                seat[sn - 1] = true;
                booked++;
            }
        }
      }
    if(booked==maxseat){//allows to change travel date if no seat is available for given destination and date
      cout<<"no seat available. choose another date for travel.\n";
      update_date(b1);
    }else{
    cout << "seats available:-\n";
    for (int i = 0; i < maxseat; ++i) {
        cout << (seat[i] ? "x\t" : to_string(i + 1) + "\t");//shows 'x' at the place of booked seats(where vector bool is true)
        if ((i + 1) % 10 == 0) cout << endl;
    }
      int number=getvalidInt("Enter seat number:");//taking input
      if (number> maxseat||number<1){//checks whether entered seat is valid /available(if valid)
          line2();cout << "invalid choice, enter again\n";line2();
          confirm=false;
        }else {
          for (size_t i = 0; i < b1.size(); i++){
            if ((destination == b1[i].destination && number == b1[i].seatnumber && date == b1[i].date && id != b1[i].id)){
            line2();cout << "seat not available ,change seat number" << endl;line2();
            confirm = false;
            }
          }      
        }
    seatnumber=number;//alotting available seat to passenger
  }
} while (confirm!=true);
  }
  void show(string ch) // show the acquired data {parameter ch to decide whether to show the status of booking(confirm/cancel) or not}
  {
   line3();
    cout <<"Name:"<< setw(12) << left << name <<"Age:"<< setw(5) << age <<"Destination:"<<left<< setw(15) << destination <<"Seat No.:"<< right<<setw(3) << seatnumber << "\tID:" <<left<< setw(12) << id <<"date:" << date << "\t"<<"fee:"<<price<<"\t";
    if(ch=="y"){  if (confirm){cout << "   confirmed" << endl;}else{cout << "   cancelled" << endl;}}
    else{cout<<endl;}
    line3();
  }
  void display(){//display the acquired data in tabular form
    cout<<"|"<<setw(12)<<left<<name<<"|"<<setw(5)<<age<<"|"<<setw(15)<<left<<destination<<"|"<<setw(7)<<left<<seatnumber<<"|"<<setw(12)<<left<<id<<"|"<<setw(14)<<date<<"|"<<setw(4)<<price<<"|"<<endl;
  }
  void update_name()//to change the name of passenger
  {
    name=getName();
  }
  void update_age(){//to change the age of passenger
    age=getvalidAge();
  }
  void update_des(vector<booking> b1){//to change destination of passenger
    setdestination();
    update_date(b1);//select date of travel to new destination as well as seatnumber
  }
  void update_date(vector<booking> b1){//to change the date of travel
    string new_date;
    do{
    cout<<"enter date:";
    cin>>new_date;
    check_date(new_date);
    }while(confirm!=true);
    date=new_date;
    setseatnumber(b1);//select seat for updated date of travel
  }
  string _name(){return name;}              //get name in order to transfer data to csv file and search booking having given name
  int _age(){return age;}                   //to transfer data to csv file 
  string _destination(){return destination;}//to tansfer data to csv file and to search booking having given destination
  string _date(){return date;}              //to transfer data to csv file and to search bookimg having given date
  int _seatnumber(){return seatnumber;}     //to transfer data to bookings.csv
  int _id(){return id;}                     //to transfer data to bookings.csv
  void cancel()//cancel an existing booking
  {
    cout << "\nbooking with ID:" << id << " is cancelled\n\n";
    confirm = false;
    show("y");
    this->id = 0;
    seatnumber=0;
  }
};
int showmainMenu(){//to show the main menu and return user's choice
  int choice=getvalidInt("\tpress 1 to add booking\n\tpress 2 to update booking\n\tpress 3 to search [by ID/name/destination/date]\n\tpress 4 to cancel booking\n\tpress 5 to show booking\n\tpress 6 to exit\n");
  return choice;
}
int main()
{
  srand(static_cast<unsigned int>(time(0)));
  cout << "\n"<<setw(60)<<"TRAVEL BOOKING SYSTEM";
  vector<booking> myVector;
  ifstream in("bookings.csv");//take input from file bookings.csv
  while (in)//adding already existing booking data to vector<booking> array
  {
    string line;
    getline(in, line);
    if (line.empty())
      continue; // Skip empty lines
    size_t pos = 0;
    vector<string> data;//vector to store data of a particular booking
    if (line.at(0) == '[')//skip the first line[name,age,destination,seatnumber,id,date]
    {
      continue;
    }
    while ((pos = line.find(',')) != string::npos)
    {
      data.push_back(line.substr(0, pos));//adding data to vector 'data'
      line.erase(0, pos + 1);//erasing the entered data
    }
    data.push_back(line); // Last element after the last comma
    if (data.size() == 6)//when all data of a particular booking is retrieved
    {
     booking b(data[0],stoi(data[1]),data[2],stoi(data[3]),stoi(data[4]),data[5]);//create booking with aquired data
      myVector.push_back(b);//add booking to vector of booking 'array'
    }
  }
  cout << "\n------------------------------------------------------------------------------\n";
  cout << "number of already existing bookings:" << myVector.size() << "\n";//shows number of bookings that have been retrieved from the csv file
  cout << "-------------------------------------------------------------------------------\n";
  bool found;//used for searching booking 
  do{
    int ch_1 = showmainMenu();
    int ID;
    size_t y;//to store position of o booking in the vector of bookings 'array'
    string New;//variable to store new values of name , destination, and date
    if (ch_1 == 1)//1-->create booking
    {
      booking b;
      b.create();
      b.setseatnumber(myVector);
      myVector.push_back(b);
      b.show("y");
    }
    else if (ch_1 == 2)//2-->update booking
    {
      char ch2;//variable to store choice of update(name,age,seatnumber,destination,date)
      found=false;
      cout << "press 'a' to update name\npress 'b' to update age\npress 'c' to update seatnumber\npress 'd' to update destination\npress 'e' to update date\n";
      cin >> ch2;
      if(ch2=='a'||ch2=='b'||ch2=='c'||ch2=='d'||ch2=='e'){
      int ID=getvalidInt("Enter ID:");
      for(size_t i=0;i<myVector.size();i++){
      if(myVector[i]._id()==ID ){
          y=i;
          found=true;
          break;
      }
    }
      if(!found){
        line2();cout<<"no booking found with given ID\n";line2();
        continue;
      }
      if(ch2=='a'){             //update name and show updated booking
          myVector[y].update_name(); 
          myVector[y].show("n");  
      }else if(ch2=='b'){       //update age and show updated booking
          myVector[y].update_age();
          myVector[y].show("n");
      }else if(ch2=='c'){       //update seat number and show updated booking
          myVector[y].setseatnumber(myVector);
          myVector[y].show("n");   
      }else if(ch2=='d'){       //update destination and show the updated booking
          myVector[y].update_des(myVector);
          myVector[y].show("n");
      }else if(ch2=='e'){       //update date and show the updated booking
          myVector[y].update_date(myVector);
          myVector[y].show("n");
      }
    }else{
      cout<<"invalid input\n";
    }
  }
    else if (ch_1 == 3)//3-->search booking
    { 
     char ch_2;//variable to store choice of search(ID, name, destination, date)
      cout << "press 'a' to search by ID\npress 'b' to search by name\npress 'c' to search by destination\npress 'd' to search by date\n";
      cin >> ch_2;
      if(isalpha(ch_2)){
      switch (ch_2)
      {
      case 'a'://search by ID
      found=false;
        cout << "enter ID:";
        cin >> ID;
        for (size_t i = 0; i < myVector.size(); i++)//searching for given ID in vector of bookings myVector
        {
          if (myVector[i]._id() == ID && ID!=0)//show the booking when found
          {
            myVector[i].show("n");
            found=true;
          }
        }
        if(!found){line2();cout<<"no booking found with given ID\n";line2();}
        break;
      case 'b'://search by name
      found=false;
        cout << "enter name:";
        cin.ignore();
        getline(cin, New);
        convert(New);
       for (size_t i = 0; i < myVector.size(); i++){
        if(myVector[i]._name()==New){
          myVector[i].show("n");
          found= true;
        }
        }
        if(!found){line2();cout<<"no booking found with given name\n";line2();}
        break;
      case 'c'://search by destination
      found=false;
        cout << "enter destination:";
        cin.ignore();
        getline(cin, New);
        convert(New);
        for (size_t i = 0; i < myVector.size(); i++)
        {
          if (myVector[i]._destination() == New&& myVector[i]._id()!=0)
          {
            myVector[i].show("n");
            found=true;
          }
        }
        if(!found){line2(); cout<<"no booking found with given destination\n";line2();}
        break;
      case 'd'://search by date
      found=false;
        cout << "enter date:";
        cin >> New;
        for (size_t i = 0; i < myVector.size(); i++)
        {
          if (myVector[i]._date() == New&& myVector[i]._id()!=0)
          {
            myVector[i].show("n");
            found=true;
          }
        }
        if(!found){line2();cout<<"no booking found with given date \n";line2();}
        break;
      default:
        cout << "invalid choice\n";
        break;
      }
    }else{
      cout<<"Invalid input\n";
    }
    }
    else if (ch_1 == 4)//4-->cancel booking
    {
      found=false;
      ID=getvalidInt("enter ID of passenger:");
      for (size_t i = 0; i < myVector.size(); i++)
      {
        if (myVector[i]._id() == ID && ID!=0)
        {
          myVector[i].cancel();
          found=true;
        }
    }
      if(!found){line2();cout<<"no booking found having given ID\n";line2();}
    }
    else if (ch_1 == 5)//5-->to show all bookings
    {
       cout<<"\n_____________________________________________________________________________\n";
       cout<<"|"<<left<<setw(12)<<"NAME"<<"|"<<setw(5)<<left<<"AGE"<<"|"<<left<<setw(15)<<"DESTINATION"<<"|"<<left<<setw(7)<<"SEAT.No"<<"|"<<setw(12)<<left<<"ID"<<"|"<<setw(14)<<"Date"<<"|"<<setw(4)<<"fee"<<"|"<<endl;
       cout<<"-----------------------------------------------------------------------------\n";
     for(size_t i=0;i<myVector.size();i++)
       {
        if(myVector[i]._id()!=0){//to display only the bookings that have not been cancelled
        myVector[i].display();
        cout<<"|____________|_____|_______________|_______|____________|______________|____|\n";//to display data in tabular form
      }
    }
    }
    else
    {
      if(ch_1==6){//6-->Exit program
      cout<<"Thankyou :)\n";
      break;
       } else {
      cout<<"invalid choice\n";//warning of invalid input
      }
    }
  } while (true);
   ofstream out("bookings.csv", ios::trunc);//for transferring data to bookings.csv
  out << "[name,age,destination,seatnumber,id,date]\n";
  for (size_t i = 0; i < myVector.size(); i++)
  {
    if (myVector[i]._id() != 0)//storing the bookings that have not been cancelled(have non zero id)
    {
      out << myVector[i]._name() << "," << myVector[i]._age() << "," << myVector[i]._destination()<<"," << myVector[i]._seatnumber() << "," << myVector[i]._id() << "," << myVector[i]._date() << endl;
    }
  }

  return 0;
}
