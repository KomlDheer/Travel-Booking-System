#include <iostream>
#include <fstream>
#include <string>
#include<vector>
#include<iomanip>
using namespace std;
int count = 0;
int maxseat=30;
class booking
{
  int number;
  string name;
  int age;
  int id;
  string destination;
  int seatnumber;
  int price;
  

public:
void check(vector<booking>);  //checks whether seats is available
void avlbl(vector<booking>);  //shows available seats
 bool confirm=true; 
  booking()
{
    count++;
    number = count;
    id=number*1001 +2;
    price=100;
  }
  void create(){          //taking data input from the user
    cout<<"enter name:";
    cin>>name;
    cout<<"enter age:";
    cin>>age;
    cout<<"enter destination:";
    cin>>destination;
  }
  void setseatnumber(){
    do{
    cout<<"enter seat number:";
    cin>>seatnumber;
    if(seatnumber>maxseat){
      cout<<"-------x-------x-------x-------x-------x-------x--------x-------\n";
        cout<<"invalid choice, enter again\n";
        cout<<"-------x-------x-------x-------x-------x-------x--------x-------\n";
    }
    }while(seatnumber>maxseat);
    confirm=true;
  }
  void show()               //display the acquired data
  {
    cout << "______________________________________________________________________________________________________________\n";
    cout <<setw(2)<<number<<")"<<setw(12)<<left<< name << "\t" << "age:"<<setw(3) << age << "\t" ;
    cout<<setw(15)<< destination << "\t"<< "S.No:"<<setw(3) << seatnumber;
    cout << "\tID :"<<setw(7) << id <<setw(4)<< "\tfee:";
    if (age > 10)
    {
      cout << price <<"\t";
    }
    else
    {
      cout << price * 0.8 <<"\t";
    }
    if(confirm){
      cout<<"   confirmed"<<endl;
    }else{
      cout<<"   cancelled"<<endl;
    }
    cout << "______________________________________________________________________________________________________________\n";
  }
  void update_name(string newname)
  {
    name = newname;
    show();
  }
  void update_age(int newage)
  {
    age = newage;
    show();
  }
  void update_des(string new_des)
  {
    destination = new_des;
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
  int _id()
  {
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
  int _num(){
    return number;
  }
  void cancelseat(){
    seatnumber=0;
  }
   void cancel()
  {
    cout<<"\nbooking with ID:"<<id<<" is cancelled\n\n";
    confirm=false;
    show();
    id = 0;
    cancelseat();
  }
  
};

  void booking::check(vector<booking> b1){
    for(int i=0;i<b1.size();i++){
      if((destination==b1[i].destination && seatnumber==b1[i].seatnumber&&id!=b1[i].id)||seatnumber>maxseat){
        cout<<"-------x-------x-------x-------x-------x-------x--------x-------\n";
        cout<<"seat not available ,change seat number"<<endl;
        cout<<"-------x-------x-------x-------x-------x-------x--------x-------\n";

        confirm=false;
      }
    }
  }
  void booking::avlbl(vector<booking> b1){
    int n=b1.size();
    int seat[maxseat]={0};
    int temp[n]={0};
    cout<<"seats available:-\n";
    for(int i=0;i<n;i++){
      if(destination==b1[i]._destination()){
        temp[i]=b1[i]._seatnumber();
      }
    }
    if(n==0){
    for(int i=0;i<maxseat;i++){
      cout<<i+1<<"\t";
      if((i+1)%10==0){cout<<endl;}
    }
    cout<<endl;
  }else{

    for(int i=0;i<maxseat;i++){
      for(int j=0;j<n;j++){
        if(i+1==temp[j]){
          seat[i]=1;
        }
      }
    }
    for(int i=0;i<maxseat;i++){
      if(seat[i]==0){
      cout<<i+1<<"\t";
      }else{
        cout<<"x\t";
      }
      if((i+1)%10==0){cout<<endl;}
    }

  }
}
    
int main()
{
  int amount=0;
  vector<booking> array;
  ofstream out("C:\\Users\\DELL\\.vscode\\.vscode\\bookings.csv");
  out << "name,age,destination,seat number,id\n";
  int ch_1;
  do
  {
    cout<<"press 1 to add booking\n";
    cout << "press 2 to update booking\npress 3 to search [by ID/name/age/destination]\n";
    cout << "press 4 to cancel booking\npress 5 to show all bookings\n";
    cout<<"press 6 to Exit\n";
    cin >> ch_1;
    int nn;
    string newname;
    string newdes;
    if(ch_1==1)
    {
      booking b;
      b.create();
      b.avlbl(array);
      do{
      b.setseatnumber();
      b.check(array);
      }while(b.confirm!=true);
      array.push_back(b);
      b.show();
    }else if(ch_1==2){
        char ch_2;
        cout<<"press 'a' to update name\n";
        cout<<"predd 'b' to update age\n";
        cout<<"press 'c' to update seatnumber\n";
        cout<<"press 'd' to update destination\n";
        cin>>ch_2;
        switch (ch_2)
        {
        case 'a':
      cout << "enter id of passenger :";
      cin >> nn;
      cout << "enter new name :";
      cin >> newname;
      for (int i = 0; i <array.size(); i++)
      {
        if (array[i]._id() == nn)
        {
          array[i].update_name(newname);
        }
      }
            break;
            case 'b':
      int newage;
      cout << "enter id of passenger :";
      cin >> nn;
      cout << "enter new age :";
      cin >> newage;
      for (int i = 0; i < array.size(); i++)
      {
        if (array[i]._id() == nn)
        {
          array[i].update_age(newage);
        }
      }
        break;
        case 'c':
        cout<<"enter id of passenger:";
        cin>>nn;
      for (int i = 0; i <array.size(); i++)
      {
        if (array[i]._id() == nn)
        {
          array[i].cancelseat();
           array[i].avlbl(array);
      do{
      array[i].setseatnumber();
      array[i].check(array);
      }while(array[i].confirm!=true);
        array[i].show();
        }
      }
  
        break;
        case 'd':
          cout << "enter id of passenger :";
      cin >> nn;
      cout << "enter new destination :";
      cin >> newdes;
      for (int i = 0; i <array.size(); i++)
      {
        if (array[i]._id() == nn)
        {
          array[i].update_des(newdes);
          array[i].cancelseat();
           array[i].avlbl(array);
      do{
      array[i].setseatnumber();
      array[i].check(array);
      }while(array[i].confirm!=true);
        array[i].show();
        }
      }
        break;
        default:
            break;
        }
    }else if(ch_1==3){//-------------------searching
    char ch_2;
    cout<<"press 'a' to search by ID\n";
    cout<<"press 'b' to search by name\npress 'c' to search by age\n";
    cout<<"press 'd' to search by destination\n";
    cin>>ch_2;
    switch (ch_2)
    {
    case 'a':
        cout<<"enter ID:";
        cin>>nn;
        for(int i=0;i<array.size();i++){
            if(array[i]._id()==nn){
                array[i].show();
            }
        }
        break;
    case 'b':
    cout<<"enter name:";
    cin>>newname;
        for(int i=0;i<array.size();i++){
            if(array[i]._name()==newname){
                array[i].show();
            }
        }
        break;
    case 'c':
     int Age;
    cout<<"enter age:";
    cin>>Age;
        for(int i=0;i<array.size();i++){
            if(array[i]._age()==Age){
                array[i].show();
            }
        }
        break;
    case 'd':
    cout<<"enter name:";
    cin>>newdes;
        for(int i=0;i<array.size();i++){
            if(array[i]._destination()==newdes){
                array[i].show();
            }
        }
        break;
    default:
    cout<<"invalid choice\n";
        break;
    }
    }else if(ch_1==4){
      cout << "enter id of passenger :";
      cin >> nn;
      for (int i = 0; i <array.size(); i++)
      {
        if (array[i]._id() == nn)
        {
          array[i].cancel();
        }
      }
    }else if(ch_1==5){
      for(int i=0;i<array.size();i++){
        if(array[i]._id()!=0){
          array[i].show();
          amount+=array[i]._price();
        }
      }
      cout<<"________________________________________________________________________________________________\n";
      cout<<"net amount:"<<amount<<"\n"<<endl;
      amount=0;
    }else{
    }
  } while (ch_1 != 6);

  for (int i = 0; i <array.size(); i++)
  {
    if (array[i]._id()!=0)
    {
      out << array[i]._name() << "," << array[i]._age() << "," << array[i]._destination();
      out << "," << array[i]._seatnumber() << "," << array[i]._id() << endl;
    }
  }
out.close();
  return 0;
}
