#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cctype>
using namespace std;
int count = 0;
int maxseat = 30;
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
class booking//for grouping the data of passengers
{
  string name;
  int age;
  int id;
  string destination;
  int seatnumber;
  int price;
  string date;

public:
  bool confirm = true;//converted to false when invalid data input provided 
  booking()
  {
    count++;
    id = 100 + count;
    price = 100;
  }
  void check_date(string);//verifies that date is in correct format
  void line() { cout << "-----------------------------------------------\n"; }
  void create()
  { // taking data (name,age,destination,date) input from the user
    string copy_name, copy_des;
    cout << "enter name:";
    cin.ignore();
    getline(cin, copy_name);
    name = convert(copy_name);
    line();
    cout << "\tNAME : " << name << endl;
    line();
    do{
    cout << "enter age:";
    cin >> age;
    }while(age<0||age>130);
    line();
    cout << "\tAGE : " << age << endl;
    line();
    cout << "enter destination:";
    cin.ignore();
    getline(cin, copy_des);
    destination = convert(copy_des);
    line();
    cout << "\tDESTINATION : " << destination << endl;
    line();
    do
    {
      cout << "enter date (in form: DD-MM-YYYY):";
      cin >> date;
      check_date(date);
    } while (confirm != true);//keeps taking input until date is provided in correct format
  }
  void setseatnumber(vector<booking> b1)//taking input(seatnumber)
  {  
    do{
      confirm=true;
      vector<bool> seat(maxseat, false);
    for (size_t i=0;i<b1.size();i++) {
        if (destination == b1[i].destination && date == b1[i].date) {
            int sn = b1[i].seatnumber;
            if (sn > 0 && sn <= maxseat)
                seat[sn - 1] = true;
        }
    }
    cout << "seats available:-\n";
    for (int i = 0; i < maxseat; ++i) {
        cout << (seat[i] ? "x\t" : to_string(i + 1) + "\t");
        if ((i + 1) % 10 == 0) cout << endl;
    }
      cout << "enter seat number:";
      cin >> seatnumber;
      if (seatnumber> maxseat)
      {
        cout << "-------x-------x-------x-------x-------x-------x--------x-------\n";
        cout << "invalid choice, enter again\n";
        cout << "-------x-------x-------x-------x-------x-------x--------x-------\n";
      confirm=false;
      }else {
      for (size_t i = 0; i < b1.size(); i++)
  {
    if ((destination == b1[i].destination && seatnumber == b1[i].seatnumber && date == b1[i].date && id != b1[i].id))
    {
      cout << "-------x-------x-------x-------x-------x-------x--------x-------\n";
      cout << "seat not available ,change seat number" << endl;
      cout << "-------x-------x-------x-------x-------x-------x--------x-------\n";

      confirm = false;
      }      
    }
  }
} while (confirm!=true);
  
  }
  void setseatnumber(int number)//change seatnumber
  {
    seatnumber = number;
  }
  void setdate(string d){
    date=d;
  }
  void show() // display the acquired data
  {
    cout << "______________________________________________________________________________________________________________\n";
    cout << setw(12) << left << name << setw(5) << age ;
    cout <<right<< setw(15) << destination << right<<setw(7) << seatnumber;
    cout << "\tID:" <<left<< setw(5) << id << setw(4) << "fee:";
    if (age > 10)
    {
      cout << price << "\t\t";
    }
    else
    {
      cout << price * 0.8 << "\t\t";
    }
    cout << "date:" << date << "\t";
    if (confirm)
    {
      cout << "   confirmed" << endl;
    }
    else
    {
      cout << "   cancelled" << endl;
    }
    cout << "______________________________________________________________________________________________________________\n";
  }
  void update_name()
  {
    string newname;
    cout<<"enter new name:";
    getline(cin, newname);
    convert(newname);
    name = newname;
  }
  void update_name(string newname){
    convert(newname);
    name=newname;
  }
  void update_age(){
    int newage;
    cout<<"enter new age:";
    cin>>newage;
    age=newage;
  }
  void update_age(int newage)
  {
    age = newage;
  }
  void update_des(vector<booking> b1){
    string new_des;
    cout<<"enter new destination:";
    getline(cin, new_des);
    convert(new_des);
    destination=new_des;
    setseatnumber(b1);
  }
  void update_des(string new_des)
  {
    convert(new_des);
    destination = new_des;
  }
  void setid(int copy_id)
  {
    id = copy_id;
  }
 
  void update_date(vector<booking> b1){
    string new_date;
    do{
    cout<<"enter date:";
    cin>>new_date;
    check_date(new_date);
    }while(confirm!=true);
    date=new_date;
    setseatnumber(b1);
  }
  string _name()
  {
    return name;
  }
  int _age()
  {
    return age;
  }
  string _destination()
  {
    return destination;
  }
  int _seatnumber()
  {
    return seatnumber;
  }
  string _date()
  {
    return date;
  }
  int _id(){
    return id;
  }
  int _price()
  {
    if (age > 10)
    {
      return price;
    }
    else
    {
      return price * 0.8;
    }
  }
  void cancel()
  {
    cout << "\nbooking with ID:" << id << " is cancelled\n\n";
    confirm = false;
    show();
    id = 0;
    seatnumber=0;
  }
};
void booking::check_date(string)
{
  // check the date format or check for specific conditions
  if (date.size() != 10)
  {
    confirm = false;
  }
  else
  {
    if (date[2] != '-' || date[5] != '-')
    {
      cout << "invalid date format, enter again\n";
      confirm = false;
    }else{
      int day, month, year;
      year = stoi(date.substr(6, 4));
      month = stoi(date.substr(3, 2));
      day = stoi(date.substr(0, 2));
      if (month < 1 || month > 12 || day < 1 || day > 31 || (month == 2 && day > 29) || year < 2025)
      {
        cout << "invalid date, enter again\n";
        confirm = false;
        if ((year%4!=0 &&month == 2 && day>28 ) ||(year%4==0 && month==2 && day>29))
        {
          cout << "February cannot have more than 29 days\n";
        }
      }else{
        if (month == 4 || month == 6 || month == 9 || month == 11)
        {
          if (day > 30)
          {
            cout << "This month cannot have more than 30 days\n";
          }
        }
        else
        {
          confirm = true;
        }
      }
    }
  }
}
int main()
{
  cout << "\n\n\t\t\t\tTRAVEL BOOKING SYSTEM";
  int amount = 0;
  vector<booking> array;
  ifstream in("C:\\Users\\DELL\\.vscode\\.vscode\\bookings.csv");
  while (in)//adding already existing booking data to vector<booking> array
  {
    booking b;
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
      b.update_name(data[0]);
      b.update_age(stoi(data[1]));
      b.update_des(data[2]);
      b.setseatnumber(stoi(data[3]));
      b.confirm = true;
      b.setid(stoi(data[4]));
      b.setdate(data[5]);
      array.push_back(b);
    }
  }
  cout << "\n~~~o~~~o~~~o~~~o~~~o~~~o~~~o~~~o~~~o~~~o~~~o~~~o~~~o~~~o~~~o~~~o~~~o~~~o~~~o~~~\n";
  cout << "number of already existing bookings:" << array.size() << "\n";
  cout << "~~~o~~~o~~~o~~~o~~~o~~~o~~~o~~~o~~~o~~~o~~~o~~~o~~~o~~~o~~~o~~~o~~~o~~~o~~~o~~~\n";
  ofstream out("C:\\Users\\DELL\\.vscode\\.vscode\\bookings.csv", ios::trunc);
  int ch_1;
  do
  {
    cout << "\tpress 1 to add booking\n";
    cout << "\tpress 2 to update booking\n\tpress 3 to search [by ID/name/age/destination/date]\n";
    cout << "\tpress 4 to cancel booking\n\tpress 5 to show all bookings\n";
    cout << "\tpress 6 to Exit\n";
    cin >> ch_1;
    int ID;
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
      char ch_2;
      cout << "press 'a' to update name\n";
      cout << "predd 'b' to update age\n";
      cout << "press 'c' to update seatnumber\n";
      cout << "press 'd' to update destination\n";
      cout << "press 'e' to update date\n";
      cin >> ch_2;
      switch (ch_2)
      {
      case 'a':
        cout<<"enter id of passenger:";
        cin>>ID;
        for(size_t i=0;i<array.size();i++){
          if(array[i]._id()==ID){
            array[i].update_name(); 
            array[i].show();  
          }
        }
        break;
      case 'b':
      cout<<"enter ID of passenger:";
      cin>>ID;
        for(size_t t=0;t<array.size();t++){
          if(array[t]._id()==ID){
             array[t].update_age();
             array[t].show();
          }
        }
       
        break;
      case 'c':
      cout<<"enter ID of passenger:";
      cin>>ID;
      for(size_t t=0;t<array.size();t++){
        if(array[t]._id()==ID){
          array[t].setseatnumber(array);
          array[t].show();
        }
      }
        break;

      case 'd':
      cout<<"enter ID of passenger:";
      cin>>ID;
        for(size_t t=0;t<array.size();t++){
          if(array[t]._id()==ID){
        array[t].update_des(array);
        array[t].show();
      }
    }
        break;
      case 'e':
      cout<<"enter ID of passenger:";
      cin>>ID;
      for(size_t t=0;t<array.size();t++){
        if(array[t]._id()==ID){
        array[t].update_date(array);
        array[t].show();
      }
    }
        break;
      default:
        break;
      }
    }
    else if (ch_1 == 3)
    { //-------------------searching
      char ch_2;
      cout << "press 'a' to search by ID\n";
      cout << "press 'b' to search by name\npress 'c' to search by age\n";
      cout << "press 'd' to search by destination\npress 'e' to search by date\n";
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
          }
        }
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
          }
        }
        break;
      case 'c':
        int Age;
        cout << "enter age:";
        cin >> Age;
        for (size_t i = 0; i < array.size(); i++)
        {
          if (array[i]._age() == Age)
          {
            array[i].show();
          }
        }
        break;
      case 'd':
        cout << "enter name:";
        cin.ignore();
        getline(cin, New);
        convert(New);
        for (size_t i = 0; i < array.size(); i++)
        {
          if (array[i]._destination() == New)
          {
            array[i].show();
          }
        }
        break;
      case 'e':
        cout << "enter date:";
        cin >> New;
        for (size_t i = 0; i < array.size(); i++)
        {
          if (array[i]._date() == New)
          {
            array[i].show();
          }
        }
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
        }
      }
    }
    else if (ch_1 == 5)
    {
      cout<<endl;
       cout<<left<<setw(12)<<"NAME"<<setw(5)<<"AGE"<<right<<setw(15)<<"DESTINSTION"<<right<<setw(7)<<"SEAT.No"<<endl;
      for (size_t i = 0; i < array.size(); i++)
      {
        array[i].show();
        amount += array[i]._price();
      }
      cout << "______________________________________________________________________________________________________________\n";
      cout << "net amount:" << amount << "\n"
           << endl;
      amount = 0;
    }
    else
    {
      if(ch_1>6){
        cout<<"invalid choice\n";
      }
    }
  } while (ch_1 != 6);
  out << "[name,age,destination,seatnumber,id,date]\n";
  for (size_t i = 0; i < array.size(); i++)
  {
    if (array[i]._id() != 0)
    {
      out << array[i]._name() << "," << array[i]._age() << "," << array[i]._destination();
      out << "," << array[i]._seatnumber() << "," << array[i]._id() << "," << array[i]._date() << endl;
    }
  }
  return 0;
}
