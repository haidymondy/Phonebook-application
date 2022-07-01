#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>

using namespace std;
char filename[] = "contacts.txt";

struct person
{
    string name;
    string gender;
    string phone;
    string email;
};
person contacts[1000];
int contactsCount;

void menu();
void addContact();
void showContacts();
bool saveContactToFile(person p);
void getContactsFromFile();
bool retContact(string name, person& pp);
void editContact();
bool deleteContactFromFile(string nm);
void deleteContact();
void searchContacts();
string lowercase(string ss)
{
    for (int i = 0; i < ss.length(); i++)
        ss[i] = tolower(ss[i]);

    return ss;
}

int main()
{
    menu();
    return 0;
}
void menu()
{
    system("cls");
    cout << ("\t\t**PhoneBook*");

    cout << ("\n\n\t\t\tMENU\t\t\n\n");
    cout << ("\t1.Add New Contact   \t2.Show Saved Contacts   \t3.Edit Contact  \n\t4.Search Contacts \t5.Delete Contacts\t6.Exit\n\n\n");
    cout << "Enter Your Choice: ";
    char choice;
    cin >> choice;
    switch (choice)
    {
    case '1':
        addContact();
        break;
    case '2':
        showContacts();
        break;
    case '3':
        editContact();
        break;
    case '4':
        searchContacts();
        break;
    case '5':
        deleteContact();
        break;
    case '6':
        exit(0);
        break;
    default:
        system("cls");
        printf("\nEnter a choice from 1 to 6 only");
        printf("\n Enter any key");
        cin.ignore();
        getchar();

        menu();
    }
}
void addContact()
{
    system("cls");
    person p;
    cout << ("Enter Contact's Name: ");
    cin >> p.name;
    cout << ("Enter Contact's Phone Number: ");
    cin >> p.phone;
    cout << "\n1. Male\t\t2. Female\n";
    cout << "Choose Contact's Gender: ";

    int gender;
    cin >> gender;
    if (gender == 1)
        p.gender = "Male";
    else
        p.gender = "Female";

    cout << "Enter Contact's email:";
    cin >> p.email;

    bool saved = saveContactToFile(p);
    if (saved)
        cout << "\nContact Added Successfully!";
    else
        cout << "\nCouldn't open file! Please try again.";
    cout << "\n\nEnter any key to continue:\n";
    cin.ignore();
    getchar();
    system("cls");
    menu();
}
bool saveContactToFile(person p)
{
    ofstream save_contacts(filename, fstream::in | fstream::out | fstream::app);

    if (!save_contacts.is_open())
        return false;

    save_contacts << p.name << endl
        << p.gender << endl
        << p.phone << endl
        << p.email << endl;
    save_contacts.close();

    return true;
}
void getContactsFromFile()
{
    contactsCount = 0;
    ifstream read_contacts(filename);
    if (read_contacts.is_open())
    {
        while (!read_contacts.eof())
        {
            contacts[contactsCount].name = "";
            read_contacts >> contacts[contactsCount].name >> contacts[contactsCount].gender >> contacts[contactsCount].phone >> contacts[contactsCount].email;
            if (!contacts[contactsCount].name.empty())
                contactsCount++;
        }
    }
    read_contacts.close();
}

bool retContact(string name, person& pp)
{
    name = lowercase(name);
    bool found = 0;
    ifstream read_contacts(filename);
    if (read_contacts.is_open())
    {
        while (!read_contacts.eof())
        {
            pp.name = "";
            read_contacts >> pp.name >> pp.gender >> pp.phone >> pp.email;
            if (pp.name.compare(name) == 0)
            {
                found = 1;
                break;
            }
        }
    }
    read_contacts.close();

    return found;
}

void showContacts()
{
    cin.ignore();
    system("cls");
    getContactsFromFile();
    if (contactsCount > 0)
    {
        for (int i = 0; i < contactsCount; i++)
        {
            system("cls");
            cout << "Contact #" << i + 1 << ":\n";
            cout << "Contact Name: " << contacts[i].name << "\n";
            cout << "Contact Phone: " << contacts[i].phone << "\n";
            cout << "Contact Email: " << contacts[i].email << "\n";
            cout << "Contact Gender: " << contacts[i].gender << "\n";
            cout << "\n1.press any key to show next contact\t\t\t2. to exit press q or Q\n";
            char cc = getchar();

            if (cc == 'q' || cc == 'Q')
                break;
        }
    }
    else
    {
        cout << "\n No Contacts Found! Enter any key to continue. \n"
            << endl;
        getchar();
    }

    system("cls");
    menu();
}
void searchContacts()
{
    system("cls");

    cout << "Enter Contact's name to search:\n";
    string name;
    cin >> name;

    person n;
    bool found = retContact(name, n);
    if (found)
    {
        cout << "Contact Name: " << n.name << "\n";
        cout << "Contact Phone: " << n.phone << "\n";
        cout << "Contact Email: " << n.email << "\n";
        cout << "Contact Gender: " << n.gender << "\n";
    }
    else
    {
        cout << "Contact Not Found!";
    }
    cout << "\n\nEnter any key to continue:\n";

    cin.ignore();
    getchar();
    system("cls");
    menu();
}
bool deleteContactFromFile(string name)
{
    person p;
    ifstream read_contacts(filename);
    ofstream tempfile("temp.txt", fstream::in | fstream::out | fstream::app);
    bool flag = 0;
    if (read_contacts.is_open())
    {
        if (tempfile.is_open())
        {
            while (!read_contacts.eof())
            {
                p.name = "";
                read_contacts >> p.name >> p.gender >> p.phone >> p.email;
                if (!p.name.empty())
                {
                    if (p.name.compare(name) != 0)
                        tempfile << p.name << endl
                        << p.gender << endl
                        << p.phone << endl
                        << p.email << endl;
                    else
                        flag = 1;
                }
            }
            read_contacts.close();
            tempfile.close();
            if (flag != 1)
                remove("temp.txt");
            else
            {
                remove(filename);
                rename("temp.txt", filename);
            }
        }
    }
    return flag;
}

void deleteContact()
{
    system("cls");

    bool flag = 0;
    string name;
    cout << "Enter Contact's Name:" << endl;
    cin >> name;
    bool deleted = deleteContactFromFile(name);
    if (deleted)
        cout << "Contact Deleted Successfully!" << endl;
    else
        cout << "Contact Not Found!" << endl;

    cout << "\n Enter any key to continue..." << endl;

    cin.ignore();
    getchar();
    system("cls");
    menu();
}

void editContact()
{
    system("cls");
    string name;
    cout << "Enter Name:";
    cin >> name;
    person n, m;
    bool found = retContact(name, n);
    if (found)
    {
        cout << endl
            << "Name: " << n.name << endl;
        cout << "Phone: " << n.phone << endl;
        cout << "Email: " << n.email << endl;
        cout << "Gender: " << n.gender << endl
            << endl;
        deleteContactFromFile(name);
        cout << "Enter New Contact's Name: ";
        cin >> m.name;
        cout << "Enter New Contact's Phone: ";
        cin >> m.phone;

        cout << "\n1.Male \t\t 2.Female" << endl;
        cout << "Choose New Contact's Gender: ";
        int gender;
        cin >> gender;
        if (gender == 1)
            m.gender = "Male";
        else
            m.gender = "Female";

        cout << "Enter New Contact's Email: ";
        cin >> m.email;

        saveContactToFile(m);
        cout << "\nContact Edited Successfully !" << endl;
    }
    else
    {
        cout << "\nContact Not Found!";
    }

    cout << "\nEnter any key to continue" << endl;
    cin.ignore();
    getchar();
    system("cls");
    menu();
}