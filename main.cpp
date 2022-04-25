#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <windows.h>
#include <conio.h>
#include <algorithm>

using namespace std;

struct Person
{
    int userID;
    int ID;
    string name;
    string surname;
    string phoneNumber;
    string emailAdress;
    string adress;
};

struct User
{
    int ID;
    string login;
    string password;
};

void displayLoginMenu()
{
    cout << "1. Rejestracja " << endl;
    cout << "2. Logowanie " << endl;
    cout << "9. Wyjdz z programu " << endl;
    cout << "--------------------" << endl;
    cout << "Twoj wybor: ";
}

void saveUsersToTextFile(vector<User> users)
{
    fstream textFile;
    textFile.open("Uzytkownicy.txt",fstream::out);

    for(auto it1 = users.begin(); it1 != users.end(); it1++ )
    {
        textFile << it1->ID <<"|"<< it1->login <<"|"<< it1->password << "|" << endl;
    }
    textFile.close();
}

bool checkIfUserAlreadyExists(vector <User> &users,string checkedUserLogin)
{
    for(auto it1 = users.begin(); it1 != users.end() ; it1++ )
    {
        if(it1->login == checkedUserLogin) return true;
    }
    return false;
}

void registration(vector <User> &users)
{
    User user;
    if(users.empty()) user.ID = 1;
    else user.ID =  users.back().ID +1;

    string login;
    string password;

    cout << "Podaj nazwe uzytkownika: ";
    cin >> login;

    while(checkIfUserAlreadyExists(users, login))
    {
        cout << "Nazwa uzytkownika jest juz zajeta" << endl;
        cout << "Sprobuj jeszcze raz" << endl;
        cin >> login;
    }
    cout << "Podaj haslo: ";
    cin >> password;

    user.login = login;
    user.password = password;
    users.push_back(user);

    saveUsersToTextFile(users);
    cout << "Pomyslnie zarejestrowano uzytkownika!" << endl;
}

int checkIfCorrectPassword(vector<User> users, string login, string password)
{
    for(auto it1 = users.begin() ; it1 != users.end(); it1++)
    {
        if(it1->login == login)
        {
            if(it1->password == password) return it1->ID;
            else return 0;
        }
    }
    return 0;
}

void changePassword(vector<User> &users,int ID)
{
    string newPassword;

    cout << "Podaj nowe haslo: ";
    cin >> newPassword;

    for(auto it1 = users.begin(); it1 != users.end(); it1++ )
    {
        if (it1 -> ID == ID)
        {
            it1 -> password = newPassword;
            cout << "Haslo zostalo zmienione pomyslnie." << endl;
        }
    }
    saveUsersToTextFile(users);
}

void loadUserDataFromTextFileToVector(vector<User> &users)
{
    fstream textFile;
    textFile.open("Uzytkownicy.txt",fstream::in | fstream::out | fstream::app);

    string textFileLine;
    int startPosition;

    while(getline(textFile,textFileLine))
    {
        User user;
        startPosition = 0;
        user.ID = stoi(textFileLine.substr(startPosition,textFileLine.find("|",startPosition) - startPosition));

        startPosition = textFileLine.find("|",startPosition)+1;
        user.login = textFileLine.substr(startPosition,textFileLine.find("|",startPosition) - startPosition);

        startPosition = textFileLine.find("|",startPosition)+1;
        user.password = textFileLine.substr(startPosition,textFileLine.find("|",startPosition) - startPosition);

        users.push_back(user);
    }
}

int loggingIn(vector<User> users)
{
    string login;
    string password;

    cout << "Podaj login: ";
    cin >> login;

    int number;

    if(checkIfUserAlreadyExists(users,login))
    {
        for(int i = 0 ; i < 3 ; i++)
        {
            cout << "Podaj haslo: ";
            cin >> password;
            number = checkIfCorrectPassword(users,login,password);
            if(number)
            {
                cout << "Pomyslnie zalogowano." << endl;
                return number;
            }
            else
            {
                cout << "Zle haslo. Pozostalo ci " << 2 - i << " proby. " << endl;
            }
        }
    }
    else
    {
        cout << "Nie ma takiego uzytkownika!" << endl;
        return 0;
    }
    return 0;
}





string changeFirstLetterToUpperCaseRestToLowerCase(string word)
{
    if (!word.empty())
    {
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        word[0] = toupper(word[0]);
    }
    return word;
}

bool isChar(char c)
{
    if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) return true;
    else return false;
}

bool isDigit(char c)
{
    if(c >= '0' && c <= '9') return true;
    else return false;
}

bool isEmailAdressValid(string emailAdress)
{
    int atIndex = -1;
    int lastDotIndex = -1;

    if(!isChar(emailAdress[0])) return false;
    else if(!isChar(emailAdress[emailAdress.length()-1])) return false;

    for(int i = 0 ; i < emailAdress.length(); i++)
    {
        if(emailAdress[i] == '@') atIndex = i;
        else if(emailAdress[i] == '.') lastDotIndex = i;
    }
    if(atIndex == -1 || lastDotIndex == -1) return false;
    else if(lastDotIndex < atIndex) return false;

    return true;
}

bool isNameOrSurnameValid(string word)
{
    for(int i = 0 ; i < word.length(); i++)
    {
        if(!isChar(word[i])) return false;
    }
    return true;
}

void saveVectorToTextFile(vector<Person> adressBook)
{
    fstream textFile;
    textFile.open("KsiazkaAdresowaNowaFormula.txt",ios::out);

    if (textFile.good() == false)
    {
        cout << "Problem z plikiem!";
        exit(0);
    }

    for(auto it1 = adressBook.begin(); it1 != adressBook.end(); it1++ )
    {
        textFile << it1->ID <<"|"<< it1->name <<"|"<< it1->surname << "|" << it1->phoneNumber << "|";
        textFile << it1->emailAdress << "|" << it1->adress << "|" << endl;
    }
    textFile.close();
}

void addPersonToBook(vector<Person> &adressBook)
{
    Person person;

    if(adressBook.empty()) person.ID = 1;
    else person.ID = adressBook.back().ID +1;

    cout << "PODAJ IMIE: ";
    cin >> person.name;

    while(!isNameOrSurnameValid(person.name))
    {
        cout<<"Niepoprawne imie " << endl;
        cout<< "Podaj imie ponownie: ";
        cin >> person.name;
    }
    person.name = changeFirstLetterToUpperCaseRestToLowerCase(person.name);

    cout << "PODAJ NAZWISKO: ";
    cin >> person.surname;

    while(!isNameOrSurnameValid(person.surname))
    {
        cout<<"Niepoprawne nazwisko " << endl;
        cout<< "Podaj nazwisko ponownie: ";
        cin >> person.surname;
    }
    person.surname = changeFirstLetterToUpperCaseRestToLowerCase(person.surname);

    cout << "PODAJ NUMER TELEFONU: ";
    cin.sync();
    getline(cin,person.phoneNumber);

    cout << "PODAJ ADRES EMAIL: " ;
    cin.sync();
    getline(cin,person.emailAdress);

    while(!isEmailAdressValid(person.emailAdress))
    {
        cout<<"Niepoprawnie wpisany adres email. Przyklad: jan.kowalski@wp.pl" <<endl;
        cout<<"Podaj adres email ponownie: ";
        cin.sync();
        getline(cin,person.emailAdress);
    }

    cout << "PODAJ ADRES: " ;
    cin.sync();
    getline(cin,person.adress);

    adressBook.push_back(person);
    saveVectorToTextFile(adressBook);

    cout << "Dodawanie przebieglo pomyslnie" << endl;
}

int personCount(vector<Person> adressBook)
{
    int counter;
    counter = adressBook.size();

    return counter;
}

void printPersonData(Person person)
{
    cout << "Imie: " << person.name << endl;
    cout << "Nazwisko: " << person.surname << endl;
    cout << "Numer telefonu: " << person.phoneNumber << endl;
    cout << "Ares Email: " << person.emailAdress << endl;
    cout << "Adres: " << person.adress << endl;
    cout <<"-----------------------------------------------" << endl;
}

void displayWholeAdressBook(vector<Person> adressBook)
{
    if(adressBook.empty()) cout<<"Ksiazka Adresowa jest pusta!Dodaj do niej kogos."<<endl;

    else
    {
        auto it1 = adressBook.begin();

        for(it1 ; it1 != adressBook.end(); it1++)
        {
            printPersonData(*it1);
        }
        cout<<"Wyswietlono "<<personCount(adressBook)<<" kontaktow"<<endl;
    }
}

void loadPersonDataFromTextFileToVector(vector<Person> &adressBook)
{
    fstream textFile;
    textFile.open("KsiazkaAdresowaNowaFormula.txt",ios::out | ios::in);

    if (textFile.good() == false)
    {
        cout << "Problem z plikiem!";
        exit(0);
    }

    string textLine;
    int counter;
    string personInfo;
    int startPosition;

    while(getline(textFile,textLine))
    {
        Person person;
        counter = 0;
        startPosition = 0;

        for(int searchedSignPosition = 0 ; searchedSignPosition < textLine.size(); searchedSignPosition++)
        {
            if(textLine[searchedSignPosition] == '|')
            {
                personInfo = textLine.substr(startPosition,searchedSignPosition-startPosition);
                counter++;

                switch(counter)
                {
                case 1:
                    person.ID = stoi(personInfo);
                    break;
                case 2:
                    person.name = personInfo;
                    break;
                case 3:
                    person.surname = personInfo;
                    break;
                case 4:
                    person.phoneNumber = personInfo;
                    break;
                case 5:
                    person.emailAdress = personInfo;
                    break;
                case 6:
                    person.adress = personInfo;
                    break;
                }
                startPosition = searchedSignPosition+1;
            }
            if(counter == 6)
            {
                break;
            }
        }
        adressBook.push_back(person);
    }
    textFile.close();
}

void searchByName (vector<Person> adressBook)
{
    string searchedName;
    bool exist = false;

    cout << "Podaj wyszukiwane imie: " << endl;
    cin >> searchedName;
    cout << endl;

    for(auto it1 = adressBook.begin(); it1 != adressBook.end(); it1++)
    {
        if (searchedName == it1->name)
        {
            exist = true;
            cout << "Wyniki dla wyszukiwanego imienia: " << endl;
            cout <<"-----------------------------------------------" << endl;
            printPersonData(*it1);
        }
    }
    if(!exist) cout << "Niestety nie posiadasz kontaktu o podanym imieniu" << endl;
}

void searchBySurname (vector<Person> adressBook)
{
    string searchedSurname;
    bool exist = false;

    cout << "Podaj wyszukiwane nazwisko: " << endl;
    cin >> searchedSurname;
    cout << endl;

    for(auto it1 = adressBook.begin(); it1 != adressBook.end(); it1++)
    {
        if (searchedSurname == it1 -> surname)
        {
            exist = true;
            cout << "Wyniki dla wyszukiwanego nazwiska " << endl;
            cout <<"-----------------------------------------------" << endl;
            printPersonData(*it1);
        }
    }
    if(!exist) cout << "Niestety nie posiadasz kontaktu o podanym nazwisku" << endl;
}

bool checkIfPersonExistsInAdressBook(vector<Person> adressBook,int checkedID)
{
    bool exist = false;

    for(auto it1 = adressBook.begin(); it1 != adressBook.end(); it1++ )
    {
        if (it1 -> ID == checkedID)  exist = true;
    }
    return exist;
}

void deletePerson(vector<Person> &adressBook)
{
    int personID;
    char prove;
    char repeat;
    bool isDeleted = false;

    cout << "Podaj ID osoby do usuniecia: " << endl;
    cin >> personID;
    if(checkIfPersonExistsInAdressBook(adressBook,personID))
    {
        for(auto it1 = adressBook.begin(); it1 <= adressBook.end(); it1++)
        {
            if (it1 -> ID == personID)
            {
                cout<<"Czy na pewno usunac osobe z ksiazki adresowej t/n: ";
                cin>> prove;
                if(prove == 't')
                {
                    adressBook.erase(it1);
                    cout<<"Osoba zostala pomyslnie usunieta z ksiazki adresowej!" << endl;
                    break;
                }
                else  break;
            }
        }
        saveVectorToTextFile(adressBook);
    }
    else
    {
        cout<<"Nie ma osoby o podanym ID w ksiazce adresowej"<<endl;
        cout<<"Wybierz m jesli chcesz powrocic do menu, d jesli chcesz sprobowac ponownie: "<<endl;

        cin >> repeat;

        if(repeat == 'm') cout<<"Powrot do MENU"<<endl;
        else deletePerson(adressBook);
    }
}

void displayEditMenu()
{
    cout<<"WYBIERZ KTORA POZYCJE CHCESZ EDYTOWAC"<<endl;
    cout<<"1 - name"<<endl;
    cout<<"2 - surname"<<endl;
    cout<<"3 - numer telefonu"<<endl;
    cout<<"4 - email"<<endl;
    cout<<"5 - adres"<<endl;
    cout<<"6 - powrot do menu"<<endl;
}

void editPersonData(vector<Person> &adressBook)
{
    int editingPersonID;
    int userChoice;
    string editedData;

    cout << "Wprowadz ID uzytkownika ktorego chcesz edytowac " << endl;
    cin >> editingPersonID;
    if(checkIfPersonExistsInAdressBook(adressBook,editingPersonID))
    {
        displayEditMenu();

        cin >> userChoice;
        cin.sync();

        if(userChoice < 6)
        {
            for(auto it1 = adressBook.begin(); it1 != adressBook.end(); it1++)
            {
                if (it1 -> ID == editingPersonID)
                {
                    switch(userChoice)
                    {
                    case 1:
                        cout << "Wprowadz nowe imie: ";
                        getline(cin,editedData);
                        it1 -> name = editedData;
                        break;
                    case 2:
                        cout << "Wprowadz nowe nazwisko: ";
                        getline(cin,editedData);
                        it1 -> surname = editedData;
                        break;
                    case 3:
                        cout << "Wprowadz nowy numer telefonu: ";
                        getline(cin,editedData);
                        it1 -> phoneNumber = editedData;
                        break;
                    case 4:
                        cout << "Wprowadz nowy adres email: ";
                        getline(cin,editedData);
                        it1 -> emailAdress = editedData;
                        break;
                    case 5:
                        cout << "Wprowadz nowy adres: ";
                        getline(cin,editedData);
                        it1 -> adress = editedData;
                        break;
                    default:
                        break;
                    }
                    cout<<"Kontakt po edycji: "<<endl;
                    cout <<"-----------------------------------------------" << endl;
                    printPersonData(*it1);
                    cout<<"Wcisnij dowolny przycisk by wrocic do menu glownego"<<endl;
                    getch();
                    saveVectorToTextFile(adressBook);
                }
            }
        }
    }
    else cout<<"Nie ma osoby o podanym ID w ksiazce adresowej"<<endl;
}

void displayMainMenu()
{
    cout << "1. Dodaj osobe" << endl;
    cout << "2. Wyszukaj po imieniu" << endl;
    cout << "3. Wyszukaj po nazwisku" << endl;
    cout << "4. Wyswietl wszystkich adresatow" << endl;
    cout << "5. Usun osobe" << endl;
    cout << "6. Edytuj osobe" << endl;
    cout << "9. Zakoncz program" << endl;
    cout << "Twoj wybor: ";
}


int main()
{
    vector<Person> adressBook;
    int userChoice;
    fstream textFile("KsiazkaAdresowaNowaFormula.txt",ios::out);
    textFile.close();

    loadPersonDataFromTextFileToVector(adressBook);

    while(1)
    {
        displayMainMenu();
        cin >> userChoice;

        switch(userChoice)
        {
        case 1:
            system("cls");
            addPersonToBook(adressBook);
            cout << "Nacisnij dowolny przycisk by powrocic do Menu Glownego" << endl;
            getch();
            system("cls");
            break;
        case 2:
            system("cls");
            searchByName(adressBook);
            cout << "Nacisnij dowolny przycisk by powrocic do Menu Glownego" << endl;
            getch();
            system("cls");
            break;
        case 3:
            system("cls");
            searchBySurname(adressBook);
            cout << "Nacisnij dowolny przycisk by powrocic do Menu Glownego" << endl;
            getch();
            system("cls");
            break;
        case 4:
            system("cls");
            displayWholeAdressBook(adressBook);
            cout << "Nacisnij dowolny przycisk by powrocic do Menu Glownego" << endl;
            getch();
            system("cls");
            break;
        case 5:
            system("cls");
            deletePerson(adressBook);
            cout << "Nacisnij dowolny przycisk by powrocic do Menu Glownego" << endl;
            getch();
            system("cls");
            break;
        case 6:
            system("cls");
            editPersonData(adressBook);
            break;
        case 9:
            exit(0);
        default:
            break;
        }
    }
    return 0;
}
