#include <iostream>
#include <cstdlib>
#include <fstream>
#include <limits>
#include <windows.h>
#include <vector>

using namespace std;

struct Contact
{
    int id;
    string name;
    string surname;
    string mail;
    string numberOfPhone;
    string address;
};

vector<Contact> sendTheContact(vector<Contact> friends)
{
    Contact newContact;
    char sign = '|';
    int numberOfFriends = 0;
    int numberOfSign = 0;
    string partOfLine;
    fstream file;
    file.open("MojeKontakty.txt", ios::in);
    if (file.good() == true)
    {
        while(getline(file, partOfLine, sign))
        {
            switch(numberOfSign)
            {
            case 0:
                newContact.id = atoi(partOfLine.c_str());
                break;
            case 1:
                newContact.name = partOfLine;
                break;
            case 2:
                newContact.surname = partOfLine;
                break;
            case 3:
                newContact.numberOfPhone = partOfLine;
                break;
            case 4:
                newContact.mail = partOfLine;
                break;
            case 5:
                newContact.address = partOfLine;
                break;
            }
            if (numberOfSign >= 5)
            {
                numberOfSign = 0;
                numberOfFriends++;
                friends.push_back(newContact);
            }
            else
            {
                numberOfSign++;
            }
        }
        file.close();
    }
    return friends;
}

vector<Contact> addContact(vector<Contact> friends)
{
    int id = 0;
    Contact newContact;
    fstream file;
    if (friends.size() == 0)
        id = 0;
    else
        id = friends[friends.size()-1].id;
    string name, surname, numberOfPhone, mail, address;
    cout << "Podaj imie nowego kontaktu: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, name);
    cout << "Podaj nazwisko nowego kontaktu: ";
    getline(cin, surname);
    cout << "Podaj e-mail: ";
    getline(cin, mail);
    cout << "Podaj numer telefonu: ";
    getline(cin, numberOfPhone);
    cout << "Podaj adres: ";
    getline(cin, address);
    newContact.id = id + 1;
    newContact.name = name;
    newContact.surname = surname;
    newContact.mail = mail;
    newContact.numberOfPhone = numberOfPhone;
    newContact.address = address;
    friends.push_back(newContact);
    file.open("MojeKontakty.txt", ios::out | ios::app);
    file << newContact.id << '|';
    file << newContact.name << '|';
    file << newContact.surname << '|';
    file << newContact.mail << '|';
    file << newContact.numberOfPhone << '|';
    file << newContact.address << '|' << endl;
    file.close();
    cout << "Dodano nowy kontakt!" << endl;
    system("pause");
    return friends;
}

int findContactByName(vector<Contact> friends)
{
    string findingName;
    cout << "Podaj imie: ";
    cin >> findingName;
    for (int i = 0; i < friends.size(); i++)
    {
        if (friends[i].name == findingName)
        {
            cout << friends[i].id << '|';
            cout << friends[i].name << '|';
            cout << friends[i].surname << '|';
            cout << friends[i].mail << '|';
            cout << friends[i].numberOfPhone << '|';
            cout << friends[i].address << '|' << endl;
        }
    }
    system("pause");
    return 0;
}

int findContactBySurname(vector<Contact> friends)
{
    string findingSurname;
    cout << "Podaj nazwisko: ";
    cin >> findingSurname;
    for (int i = 0; i < friends.size(); i++)
    {
        if (friends[i].surname == findingSurname)
        {
            cout << friends[i].id << '|';
            cout << friends[i].name << '|';
            cout << friends[i].surname << '|';
            cout << friends[i].mail << '|';
            cout << friends[i].numberOfPhone << '|';
            cout << friends[i].address << '|' << endl;
        }
    }
    system("pause");
    return 0;
}

void showAllContact(vector<Contact> friends, int numberOfFriends)
{
    for (int i = 0; i < friends.size(); ++i)
    {
        cout << friends[i].id << '|';
        cout << friends[i].name << '|';
        cout << friends[i].surname << '|';
        cout << friends[i].mail << '|';
        cout << friends[i].numberOfPhone << '|';
        cout << friends[i].address << '|' << endl;
    }
    system("pause");
}

void changeFile (vector<Contact> friends)
{
    ofstream file("MojeKontakty.txt", ios::out | ios::trunc);
    for (int i = 0; i < friends.size(); ++i)
    {
        file << friends[i].id << '|';
        file << friends[i].name << '|';
        file << friends[i].surname << '|';
        file << friends[i].numberOfPhone << '|';
        file << friends[i].mail << '|';
        file << friends[i].address << '|' << endl;
    }
}

vector<Contact> deleteContact(vector<Contact> friends)
{
    char ifErase;
    int userID;
    for (int i = 0; i < friends.size(); ++i)
    {
        cout << friends[i].id << " " << friends[i].name << endl;
    }
    cout << "Podaj id adresata, ktorego chcesz usunac: ";
    cin >> userID;
    for (int i = 0; i < friends.size(); ++i)
    {
        if (friends[i].id == userID)
        {

            cout << "Czy na pewno chcesz usunac " << friends[i].name << " " << friends[i].surname << " z ksiazki adresowej? Jeœli tak wcisnij 't' ";
            cin >> ifErase;
            if (ifErase == 't')
            {
                for (int j = i; j < friends.size()-1; j++)
                {
                    friends[j].id = friends[j+1].id;
                    friends[j].name = friends[j+1].name;
                    friends[j].surname = friends[j+1].surname;
                    friends[j].mail = friends[j+1].mail;
                    friends[j].numberOfPhone = friends[j+1].numberOfPhone;
                    friends[j].address = friends[j+1].address;
                }
                friends.erase(friends.end()-1);
                changeFile(friends);
            }
            else
                return friends;
        }
    }
    system("pause");
    return friends;
}

vector<Contact> editContactByName(vector<Contact> friends, int idUsers)
{
    string newName;
    for (int i =0; i < friends.size(); ++i)
    {
        if (friends[i].id == idUsers)
        {
            cout << "Podaj nowe imie: ";
            cin >> newName;
            friends[i].name = newName;
            changeFile(friends);
        }
    }
    cout << "Dane zostaly zmienione!" << endl;
    system("pause");
    return friends;
}

vector<Contact> editContactBySurname(vector<Contact> friends, int idUsers)
{
    string newSurname;
    for (int i =0; i < friends.size(); ++i)
    {
        if (friends[i].id == idUsers)
        {
            cout << "Podaj nowe nazwisko: ";
            cin >> newSurname;
            friends[i].surname = newSurname;
            changeFile(friends);
        }
    }
    cout << "Dane zostaly zmienione!" << endl;
    system("pause");
    return friends;
}

vector<Contact> editContactByMail(vector<Contact> friends, int idUsers)
{
    string newMail;
    for (int i =0; i < friends.size(); ++i)
    {
        if (friends[i].id == idUsers)
        {
            cout << "Podaj nowy mail: ";
            cin >> newMail;
            friends[i].mail = newMail;
            changeFile(friends);
        }
    }
    cout << "Dane zostaly zmienione!" << endl;
    system("pause");
    return friends;
}

vector<Contact> editContactByPhoneNumber(vector<Contact> friends, int idUsers)
{
    string newPhoneNumber;
    for (int i =0; i < friends.size(); ++i)
    {
        if (friends[i].id == idUsers)
        {
            cout << "Podaj nowy numer telefonu: ";
            cin >> newPhoneNumber;
            friends[i].numberOfPhone = newPhoneNumber;
            changeFile(friends);
        }
    }
    cout << "Dane zostaly zmienione!" << endl;
    system("pause");
    return friends;
}

vector<Contact> editContactByAddress(vector<Contact> friends, int idUsers)
{
    string newAddress;
    for (int i =0; i < friends.size(); ++i)
    {
        if (friends[i].id == idUsers)
        {
            cout << "Podaj nowy adres: ";
            getline(cin, newAddress);
            friends[i].address = newAddress;
            changeFile(friends);
        }
    }
    cout << "Dane zostaly zmienione!" << endl;
    system("pause");
    return friends;
}

int main()
{
    int id;
    vector<Contact> friends;
    friends = sendTheContact(friends);
    int numberOfFriends = 0;
    int changingMenu = 0;
    char choice;

    while (1)
    {
        if (changingMenu == 0)
        {
            system("cls");
            cout << "KSIAZKA ADRESOWA" << endl;
            cout << "1. Dodaj nowy kontakt" << endl;
            cout << "2. Wyszukaj znajomych po imieniu" << endl;
            cout << "3. Wyszukaj znajomych po nazwisku" << endl;
            cout << "4. Wyswietl wszystkie kontakty" << endl;
            cout << "5. Usun adresata" << endl;
            cout << "6. Edytuj adresata" << endl;
            cout << "7. Zakoncz program" << endl;
            cin >> choice;

            if (choice == '1')
                friends = addContact(friends);
            else if (choice == '2')
                findContactByName(friends);
            else if (choice == '3')
                findContactBySurname(friends);
            else if (choice == '4')
                showAllContact(friends, numberOfFriends);
            else if (choice == '5')
                friends = deleteContact(friends);
            else if (choice == '6')
                changingMenu+=1;
            else if (choice == '7')
                exit(0);
        }
        else if (changingMenu == 1)
        {
            system("cls");
            cout << "EDYCJA" << endl;
            cout << "1. Imie" << endl;
            cout << "2. Nazwisko" << endl;
            cout << "3. Numer telefonu" << endl;
            cout << "4. Email" << endl;
            cout << "5. Adres" << endl;
            cout << "6. Powrot do menu" << endl;

            cout << "Podaj id uzytkownia, ktorego chcesz edytowac: ";
            cin >> id;
            cout << "Podaj ktora dane chcesz edytowac: ";
            cin >> choice;

            if (choice == '1')
                friends = editContactByName(friends, id);
            else if (choice == '2')
                friends = editContactBySurname(friends, id);
            else if (choice == '3')
                friends = editContactByPhoneNumber(friends, id);
            else if (choice == '4')
                friends = editContactByMail(friends, id);
            else if (choice == '5')
                friends = editContactByAddress(friends, id);
            else if (choice == '6')
                changingMenu = 0;
        }
    }
    return 0;
}
