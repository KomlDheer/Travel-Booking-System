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
int maxseat=20;
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
}
bool checkname(string n){
  int num=0;
  for(size_t i=0;i<n.size();i++){
    if((!isalpha(n[i]))&&(!isspace(n[i]))){
      return false;
    }else if(isalpha(n[i])){
      num=1;
    }
  }
  if(num==0){
    return false;
  }else{
    return true;
  }
}
class booking//for grouping the data of passengers
{
  string name;
  int age;
  string destination;
  int seatnumber; 
  int price=100;
  string date;
  int id;
public:
  bool confirm = true;//converted to false when invalid data input provided 
  booking(){
    srand(static_cast<unsigned int>(time(0)));
    id=rand();
  }
  booking(string name_,int age_,string destination_,int seatnumber_,int id_,string date_){
    name=name_;
    age=age_;
    destination=destination_;
    date=date_;
    seatnumber=seatnumber_;
    id=id_;


  }
  void check_date(string);//verifies that date is in correct format
  void updatedate(vector<booking>);
  void line() { cout << "-----------------------------------------------\n"; }
  void line2(){cout << "-------x-------x-------x-------x-------x-------x--------x-------\n";}
  void setdestination(){
     int ch;
     cout<<"\t\t----SELECT DESTINATION----\n";
    cout<<"1)Ajmer\n2)Alwar\n3)Barmer\n4)Bikaner\n5)Jaipur\n";
    cout<<"enter destination bhoice:";
    do{
    cin>>ch;
    if(ch==1){destination="Ajmer";break;}
    else if(ch==2){destination="Alwar";break;}
    else if(ch==3){destination="Barmer";break;}
    else if(ch==4){destination="Bikaner";break;}
    else if(ch==5){destination="Jaipur";break;}
    else{
      cout<<"invalid choice, enter again:";
    }
  }while(true);
  }
  void create()
  {
    int i=0;
    string copy_name, copy_des, copy_age;
    do {
      if(i==0){
    cout << "enter name:";
     cin.ignore();
     getline(cin, copy_name);
      }else{
      cout<<"enter again:";
      getline(cin,copy_name);
      }
      i++;
        if (!checkname(copy_name)) {
            cout << "invalid name\n";
        }
    } while (checkname(copy_name) != true);
    name=convert(copy_name);
    i=0;
    line();
    cout << "\tNAME : " << name << endl;
    line();
    do{
      cout<<"enter age:";
      cin>>age;
          if (cin.fail()) // Check for invalid input
    {
      cin.clear(); // Clear the error flag
      cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
      cout << "Invalid input, please enter a number.\n";
      age=-1;
      continue; // Skip to the next iteration of the loop
    }
    }while(age<0||age>150);
    line();
    cout << "\tAGE : " << age << endl;
    line(); 
     setdestination();
   line();cout<<"\tDESTINATION:"<<destination<<endl;line();
    do {
        cout << "enter date (in form: DD-MM-YYYY):";
        cin >> date;
        check_date(date);
    } while (confirm != true);
  
  }
  void setseatnumber(vector<booking> b1)//taking input(seatnumber)
  {  
    seatnumber=0;
    do{
      int booked=0;
      confirm=true;
      vector<bool> seat(maxseat, false);
    for (size_t i=0;i<b1.size();i++) {
        if (destination == b1[i].destination && date == b1[i].date && id!=b1[i].id) {
            int sn = b1[i].seatnumber;
            if (sn > 0 && sn <= maxseat){
                seat[sn - 1] = true;
                booked++;
            }
        }
      }
    if(booked==maxseat){
      cout<<"no seat available. choose another date for travel.\n";
      update_date(b1);
    }else{
    cout << "seats available:-\n";
    for (int i = 0; i < maxseat; ++i) {
        cout << (seat[i] ? "x\t" : to_string(i + 1) + "\t");
        if ((i + 1) % 10 == 0) cout << endl;
    }
  
    do{
      cout << "enter seat number:";
      cin >> seatnumber;
      if(cin.fail())
       {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Invalid input, please enter a number.\n";
      continue;
    }else{
      break;
    }
  }while(true);
      if (seatnumber> maxseat){
        line2();cout << "invalid choice, enter again\n";line2();
      confirm=false;
      }else {
      for (size_t i = 0; i < b1.size(); i++){
    if ((destination == b1[i].destination && seatnumber == b1[i].seatnumber && date == b1[i].date && id != b1[i].id)){
      line2();cout << "seat not available ,change seat number" << endl;line2();
      confirm = false;
        }
      }      
    }
  }
} while (confirm!=true);
  
  }
  void show() // display the acquired data
  {
    cout << "_______________________________________________________________________________________________________________________________\n";
    cout <<"Name:"<< setw(12) << left << name <<"Age:"<< setw(5) << age ;
    cout <<"Destination:"<<left<< setw(15) << destination <<"Seat No.:"<< right<<setw(3) << seatnumber;
    cout << "\tID:" <<left<< setw(12) << id << setw(4) << "fee:";
    if (age > 10)
    {
      cout << price << "\t";
    }
    else
    {
      cout << price * 0.8 << "\t";
    }
    cout << "date:" << date << "\t";
    if (confirm){cout << "   confirmed" << endl;}
    else{cout << "   cancelled" << endl;}
    cout << "_______________________________________________________________________________________________________________________________\n";
  }
  void display(){
    cout<<"|"<<setw(12)<<left<<name<<"|"<<setw(5)<<age<<"|"<<setw(15)<<left<<destination<<"|"<<setw(7)<<left<<seatnumber<<"|"<<setw(12)<<left<<id<<"|"<<setw(14)<<date<<"|";
    if(age<10){cout<<setw(4)<<"80"<<"|"<<endl;}
    else{cout<<setw(4)<<"100"<<"|"<<endl;}
  }
  void update_name()
  {
    string newname;
    int i=0;
    do{
      if(i==0){
    cout<<"enter new name:";
    cin.ignore();
    getline(cin, newname);
      }else{
        cout<<"enter again:";
        getline(cin,newname);
      }
    if(checkname(newname)!=true){
      cout<<"invalid name"<<endl;
    }
    i++;
  }while(!checkname(newname));
  name=convert(newname);
    }
  void update_age(){
    int newage;
    cout<<"enter new age:";
    cin>>newage;
    age=newage;
  }
  void update_des(vector<booking> b1){
    setdestination();
    setseatnumber(b1);
  }
  void update_date(vector<booking> b1){
    string new_date;
    do{
    cout<<"enter date:";
    cin>>new_date;
    check_date(new_date);
    }while(confirm!=true);
    date=new_date;
    confirm=false;
    setseatnumber(b1);
  }
  string _name(){return name;}
  int _age(){return age;}
  string _destination(){return destination;}
  int _seatnumber(){return seatnumber;}
  string _date(){return date;}
  int _id(){return id;}
  int _price(){if (age > 10){return price;}
                else{return price * 0.8;}    
              }
  void cancel()
  {
    cout << "\nbooking with ID:" << id << " is cancelled\n\n";
    confirm = false;
    show();
    this->id = 0;
    seatnumber=0;
  }
};
void booking::check_date(string){
  if (date.size() != 10){
    cout<<"incorrect date format , enter again\n";
    confirm = false;
  }
  else{
    if (date[2] != '-' || date[5] != '-'){
      cout << "invalid date format, enter again\n";
      confirm = false;
    }else{
      int day, month, year;
      year = stoi(date.substr(6, 4));
      month = stoi(date.substr(3, 2));
      day = stoi(date.substr(0, 2));
      if (month < 1 || month > 12 || day < 1 || day > 31 ||((year % 4 != 0) && (month == 2 && day > 28)) ||((year % 4 == 0) && (month == 2 && day > 29)) || year < 2025||year>2026)
      {
        cout << "invalid date, enter again\n";
        confirm = false;
        if ((year%4!=0 &&month == 2 && day>28 ) ||(year%4==0 && month==2 && day>29)){
          cout << "February cannot have the given date\n";
        }
      }else{
        if (month == 4 || month == 6 || month == 9 || month == 11){
          if (day > 30){
            cout << "This month cannot have more than 30 days\n";
          }
        }
        else {
          confirm = true;
        }
      }
    }
  }
}
void line2(){cout << "-------x-------x-------x-------x-------x-------x--------x-------\n";}
int main()
{
  cout << "\n\n"<<setw(60)<<"TRAVEL BOOKING SYSTEM";
  vector<booking> array;
  ifstream in("C:\\Users\\DELL\\.vscode\\.vscode\\bookings.csv");
  while (in)//adding already existing booking data to vector<booking> array
  {
    string line;
    getline(in, line);
    if (line.empty())
      continue; // Skip empty lines
    size_t pos = 0;
    vector<string> data;
    if (line.at(0) == '[')
    {
      continue;
    }
    while ((pos = line.find(',')) != string::npos)
    {
      data.push_back(line.substr(0, pos));
      line.erase(0, pos + 1);
    }
    data.push_back(line); // Last element after the last comma
    if (data.size() == 6)
    {
     booking b(data[0],stoi(data[1]),data[2],stoi(data[3]),stoi(data[4]),data[5]);
      array.push_back(b);
    }
  }
  cout << "\n------------------------------------------------------------------------------\n";
  cout << "number of already existing bookings:" << array.size() << "\n";
  cout << "-------------------------------------------------------------------------------\n";
 
  int ch_1;
  int found=0;
  do
  {
    cout << "\tpress 1 to add booking\n\tpress 2 to update booking\n\tpress 3 to search [by ID/name/destination/date]\n\tpress 4 to cancel booking\n\tpress 5 to show all bookings\n\tpress 6 to Exit\n";
    cin >> ch_1;
    if(cin.fail())
    {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(),'\n');
      cout<<"Invalid input, please enter a number\n";
      continue;
    }
    int ID;
    size_t y;
    string New;
    if (ch_1 == 1)
    {
      booking b;
      b.create();
      b.setseatnumber(array);
      array.push_back(b);
      b.show();
    }
    else if (ch_1 == 2)
    {
      char ch2;
      cout << "press 'a' to update name\npredd 'b' to update age\npress 'c' to update seatnumber\npress 'd' to update destination\npress 'e' to update date\n";
      cin >> ch2;
      cout<<"enter ID of passenger:";
      cin>>ID;
      for(size_t i=0;i<array.size();i++){
      if(array[i]._id()==ID ){
          y=i;
      }
      found=0;
      }
      if(ch2=='a'){
          array[y].update_name(); 
          array[y].show();  
      }else if(ch2=='b'){
          array[y].update_age();
          array[y].show();
      }else if(ch2=='c'){
          array[y].confirm=false;
          array[y].setseatnumber(array);
          array[y].show();
      }else if(ch2=='d'){
          array[y].confirm=false;
          array[y].update_des(array);
          array[y].show();
      }else if(ch2=='e'){
          array[y].update_date(array);
          array[y].show();
      }else{
      cout<<"invalid choice"<<endl;
      }
    }
    else if (ch_1 == 3)
    { //-------------------searching
      char ch_2;
      cout << "press 'a' to search by ID\npress 'b' to search by name\npress 'c' to search by destination\npress 'd' to search by date\n";
      cin >> ch_2;
      switch (ch_2)
      {
      case 'a':
        cout << "enter ID:";
        cin >> ID;
        for (size_t i = 0; i < array.size(); i++)
        {
          if (array[i]._id() == ID)
          {
            array[i].show();
            found=1;
          }
        }
        if(found==0){
          line2();cout<<"no booking found with given ID\n";line2();
        }
        found=0;
        break;
      case 'b':
        cout << "enter name:";
        cin.ignore();
        getline(cin, New);
        convert(New);
        for (size_t i = 0; i < array.size(); i++)
        {
          if (array[i]._name() == New)
          {
            array[i].show();
            found=1;
          }
        }
        if(found==0){
          line2();cout<<"no booking found with given name\n";line2();
        }
        found=0;
        break;
      case 'c':
        cout << "enter name:";
        cin.ignore();
        getline(cin, New);
        convert(New);
        for (size_t i = 0; i < array.size(); i++)
        {
          if (array[i]._destination() == New)
          {
            array[i].show();
            found=1;
          }
        }
        if(found==0){
         line2(); cout<<"no booking found with given destination\n";line2();
        }
        found=0;
        break;
      case 'd':
        cout << "enter date:";
        cin >> New;
        for (size_t i = 0; i < array.size(); i++)
        {
          if (array[i]._date() == New)
          {
            array[i].show();
            found=1;
          }
        }
        if(found==0){
          line2();cout<<"no booking found with given date \n";line2();
        }
        found=0;
        break;
      default:
        cout << "invalid choice\n";
        break;
      }
    }
    else if (ch_1 == 4)
    {
      cout << "enter id of passenger :";
      cin >> ID;
      for (size_t i = 0; i < array.size(); i++)
      {
        if (array[i]._id() == ID)
        {
          array[i].cancel();
          found=1;
        }
      }
      if(found==0){
        line2();cout<<"no booking found having given ID\n";line2();
      }
      found=0;
    }
    else if (ch_1 == 5)
    {
      cout<<endl;
      cout<<"_____________________________________________________________________________\n";
       cout<<"|"<<left<<setw(12)<<"NAME"<<"|"<<setw(5)<<left<<"AGE"<<"|"<<left<<setw(15)<<"DESTINASTION"<<"|"<<left<<setw(7)<<"SEAT.No"<<"|"<<setw(12)<<left<<"ID"<<"|"<<setw(14)<<"Date"<<"|"<<setw(4)<<"fee"<<"|"<<endl;
       cout<<"-----------------------------------------------------------------------------\n";
     for(size_t i=0;i<array.size();i++)
       {
        if(array[i]._id()!=0){
        array[i].display();
        cout<<"|____________|_____|_______________|_______|____________|______________|____|\n";
      }
    }
    }
    else
    {
      if(ch_1==6){
        cout<<"Thankyou :)\n";
      }else{
        cout<<"invalid choice\n";
      }
    }
  } while (ch_1 != 6);
   ofstream out("C:\\Users\\DELL\\.vscode\\.vscode\\bookings.csv", ios::trunc);
  out << "[name,age,destination,seatnumber,id,date]\n";
  for (size_t i = 0; i < array.size(); i++)
  {
    if (array[i]._id() != 0)
    {
      out << array[i]._name() << "," << array[i]._age() << "," << array[i]._destination()<<"," << array[i]._seatnumber() << "," << array[i]._id() << "," << array[i]._date() << endl;
    }
  }
  return 0;
}
