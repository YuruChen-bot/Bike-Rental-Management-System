#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// to create the class Bike
class Bike
{
    private:
        string name;    
    public:
        bool reserved;
        void setter(string n, bool r)
        {
            name=n;
            reserved=r;
        }
        string getName(){return name;}
};

// to create the class Customer
class Customer
{
    friend class ListOfCustomer;
    private:

        string FirstName;
        string LastName;
        string Street;
        int PostalCode;
        string City;
        int YearOfBirth;
        int Telephone;
        bool License;

        Customer *next;

    public:
        Customer(){next=0;};

        Customer *get_next(){return next;}

        bool getLicense(){return License;}

        // to overload operator >>
        friend istream &operator>> (istream &istr, Customer &c)
        {
            cout<<"Enter First Name: ";
            cin>>c.FirstName;
            cout<<"Enter Surname: ";
            cin>>c.LastName;
            cout<<"Enter Street: ";
            cin>>c.Street;
            cout<<"Enter Postal Code: ";
            cin>>c.PostalCode;            
            cout<<"Enter City: ";
            cin>>c.City;
            cout<<"Enter Year of Birth: ";
            cin>>c.YearOfBirth;
            cout<<"Enter Telephone Number: ";
            cin>>c.Telephone;
            cout<<"Do you have Class A driving license (if Yes enter 1, if No enter 0): ";
            cin>>c.License;

            return istr;
        }

        // to overload operator <<
        friend ostream &operator<< (ostream &ostr, Customer &c)
        {
            ostr<<"Name: "<<c.FirstName<<" "<<c.LastName<<endl<<"Address: "<<c.Street<<", "<<c.PostalCode<<", "<<c.City<<endl<<"Birthyear: "<<c.YearOfBirth<<endl
            <<"Telephone Number: "<<c.Telephone<<endl<<"Driving License (1 for Yes, 0 for No): "<<c.License<<endl<<endl;
            
            return ostr;
        }
};


// to create the linked list of Customer
class ListOfCustomer
{
    private:
        Customer *head;
    public:
        ListOfCustomer(){head=0;}

        Customer *begin(){return head;}

        // to insert new Customer in the linked list
        void insert(Customer *c)
        {
            c->next=head;
            head=c;
        }

        // to find a Customer object in the linked class by firstname and last
        Customer *find(string firstname, string lastname)
        {
            Customer *a;
            for(a=head;a!=0;a=a->get_next())
            {
                if(a->FirstName==firstname && a->LastName==lastname) return a;
            }
            return 0;
        }

};

ListOfCustomer customer_list;

// to register a new customer
void Register()
{
    Customer *c = new Customer;
    cin>>*c;
    customer_list.insert(c);
}

// to display the information of all registered customers
void Display()
{
    Customer *c;
    for(c=customer_list.begin(); c!=0; c=c->get_next())
    {
        cout<<*c;
    }
}

// to find a Customer object in the linked class by firstname and lastname
Customer *C_Search(string firstname, string lastname)
{
    Customer *c;
    c=customer_list.find(firstname, lastname);
    return c;
    
}

// to create the class Reservation
class Reservation
{
    friend class ListOfReservation;

    private:
        string FirstName;
        string LastName;
        int BikeNumber;
        Reservation *next;
    public:
        Reservation(string f, string l, int b):FirstName(f),LastName(l),BikeNumber(b){next=0;}
        Reservation *getNext(){return next;}
        string getFirstname(){return FirstName;}
        string getLastname(){return LastName;}
        int getBikeNumber(){return BikeNumber;}

};

// to create the linked list of Customer
class ListOfReservation
{
    private:
        Reservation *head;
    public:
        ListOfReservation(){head=0;}
        Reservation *begin(){return head;}

        // to insert new Reservation in the linked list
        void insert(Reservation *c)
        {
            c->next=head;
            head=c;
        }

        // to find a Reservation object in the linked class by firstname and lastname
        Reservation *find(string firstname, string lastname)
        {
            Reservation *a;
            for(a=head;a!=0;a=a->getNext())
            {
                if(a->FirstName==firstname && a->LastName==lastname) return a;
            }
            return 0;
        }

        // to remove a Reservation object in the linked class when a motorbike is handed over
        void remove(Reservation *old_project)
        {
            if(head!=NULL&&old_project!=NULL)
            {
                if(head==old_project)
                {
                    head=head->getNext();
                    delete old_project;
                }
                else
                {
                    Reservation *np;
                    for(np=head;np!=0;np=np->getNext())
                    {
                        if(np->getNext()==old_project) 
                        {
                            np->next=np->getNext()->getNext();
                            delete old_project;
                            break;
                        }
                    }
                    
                }
            }
        }

};

ListOfReservation reservation_list;

// to remove a Reservation object in the linked class when a motorbike is handed over
void remove(string firstname, string lastname)
{
    Reservation *r;
    r=reservation_list.find(firstname, lastname);
    reservation_list.remove(r);

}

// to find a Reservation object in the linked class by firstname and lastname
Reservation *R_Search(string firstname, string lastname)
{
    Reservation *r;
    r=reservation_list.find(firstname, lastname);
    return r;
    
}

int main()
{
    // to create an array with 4 bikes
    Bike bike[4];
    bike[0].setter("Suzuki Bandit",0);
    bike[1].setter("Honda TransAlp",0);
    bike[2].setter("BMW F 650 GS",0);
    bike[3].setter("Kawasaki ZZR1400",0);

    string firstname, lastname;
    int bikenumber;


    // to create the reservations.txt if it doesn't exist
    ofstream writer("reservations.txt",ios::app);
    writer.close();

    // to read the existed reservations.txt, extract data from the txt file, and fill out the linked list of Reservation
    ifstream reader ("reservations.txt");
    string text;
    while(!reader.eof())
    {
        getline(reader,text);
        if(text.length()>0)
        {
            cout<<text<<endl;
            firstname=text.substr(0,text.find(" "));
            lastname=text.substr(text.find(" ")+1,text.find(" reserved")-text.find(" ")-1);

            stringstream ss;
            ss<<text.substr(text.find(".")+1,1);
            ss>>bikenumber;

            Reservation *re=new Reservation(firstname,lastname,bikenumber);
            reservation_list.insert(re);
            bike[bikenumber-1].reserved=1;
        }
    }
    reader.close();

    // a number to decide which function to use in the menu
    int meun_number;

    do
    {
        // print out the menu.
        cout<<"----------MENU-----------"<<endl<<endl;
        cout<<"[1] New customer registration"<<endl;
        cout<<"[2] Output all customer data"<<endl;
        cout<<"[3] Reserve a motorbike"<<endl;
        cout<<"[4] Return a motorbike"<<endl;
        cout<<"[5] Quit the program"<<endl<<endl;

        cout<<"What do you want to do? Please enter the menu number: "<<endl;
        cin>>meun_number;
 

        switch (meun_number)
        {
        // enter 1 to create a new Customer object and add it the the Customer linked list
        case 1:
            Register();
            break;
        
        // enter 2 to display the information of all customers in the Customer linked list
        case 2:
            Display();
            break;

        // enter 3 to help a registered customer to reserve a motorbike
        case 3:
            
            // to ask firstname and lastname of the customer who wants to reserve a motorbike
            cout<<"Who wants to rent a motobike? Please enter the first name: "<<endl;
            cin>>firstname;
            cout<<"Please enter the last name: "<<endl;
            cin>>lastname;            

            // to check if the customer has registered
            if(C_Search(firstname,lastname)==NULL){cout<<"Customer "<<firstname<<" "<<lastname<<" not found."<<endl;}
            else
            {
                // to check if the customer has a driving licence
                if(C_Search(firstname,lastname)->getLicense()==0){cout<<"Customer "<<firstname<<" "<<lastname<<" don't have license."<<endl;}
                else
                {
                    // to ask which motobike the customer wants to reserve
                    int bikenumber;
                    cout<<"Which motorbike do tou want to reserve? Please enter number:"<<endl<<"[1] Suzuki Bandit"<<endl
                    <<"[2] Honda TransAlp"<<endl<<"[3] BMW F 650 GS"<<endl<<"[4] Kawasaki ZZR1400"<<endl;
                    cin>>bikenumber;
                    // to check if the motobike is available
                    if(bike[bikenumber-1].reserved==1)
                    {
                        cout<<bike[bikenumber-1].getName()<<" has already been reserved. "<<endl;
                    }
                    else
                    {
                        // to set the reserved bike to be unavailable
                        bike[bikenumber-1].reserved=1;

                        // to add a new reservation in the reservation linked list
                        Reservation *re=new Reservation(firstname,lastname,bikenumber);
                        reservation_list.insert(re);

                        // to update the information of all reservations in the reservations.txt
                        ofstream writer("reservations.txt");
                        Reservation *r;
                        for(r=reservation_list.begin(); r!=0; r=r->getNext())
                        {
                            writer<<r->getFirstname()<<" "<<r->getLastname()<<" reserved the Motorbike No."<<r->getBikeNumber()<<" "<<bike[r->getBikeNumber()-1].getName()<<endl;
                        }
                        writer.close();
                    }
                }
            }
            break;

        // enter 4 to help a registered customer to return a motorbike
        case 4:
            // to ask firstname and lastname of the customer who wants to return a motorbike
            cout<<"Who wants to return the motobike? Please enter the first name: "<<endl;
            cin>>firstname;
            cout<<"Please enter the last name: "<<endl;
            cin>>lastname;

            // to check if the customer has reserved a motorbike
            if(R_Search(firstname,lastname)==NULL){cout<<"Customer "<<firstname<<" "<<lastname<<" not found."<<endl;}
            else
            {
                // to set the returned bike to be available
                bike[R_Search(firstname,lastname)->getBikeNumber()-1].reserved=0;
                
                // to remove the reservation in the reservation linked list
                remove(firstname,lastname); 

                // to update the information of all reservations in the reservations.txt
                ofstream writer("reservations.txt");
                Reservation *r;
                for(r=reservation_list.begin(); r!=0; r=r->getNext())
                {
                    writer<<r->getFirstname()<<" "<<r->getLastname()<<" reserved the Motorbike No."<<r->getBikeNumber()<<" "<<bike[r->getBikeNumber()-1].getName()<<endl;
                }
                writer.close();                                    
            }
            break;

        default:
            break;
        }

    // enter 5 to quit the application
    } while (meun_number!=5);

    return 0;
    
}