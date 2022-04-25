#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <windows.h>
#include <conio.h>
#include <algorithm>
#include <cstdio>


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

void displayMainMenu()
{
    cout << "MENU UZYTKOWNIKA" << endl;
    cout << "--------------------" << endl;
    cout << "1. Dodaj osobe" << endl;
    cout << "2. Wyszukaj po imieniu" << endl;
    cout << "3. Wyszukaj po nazwisku" << endl;
    cout << "4. Wyswietl wszystkich adresatow" << endl;
    cout << "5. Usun osobe" << endl;
    cout << "6. Edytuj osobe" << endl;
    cout << "--------------------" << endl;
    cout << "7. Zmien haslo" << endl;
    cout << "8. Wyloguj sie" << endl;
    cout << "--------------------" << endl;
    cout << "Twoj wybor: ";
}

void displayEditMenu()
{
    cout << "WYBIERZ KTORA POZYCJE CHCESZ EDYTOWAC" << endl;
    cout << "1 - name" << endl;
    cout << "2 - surname" << endl;
    cout << "3 - numer telefonu" << endl;
    cout << "4 - email" << endl;
    cout << "5 - adres" << endl;
    cout << "6 - powrot do menu" << endl;
    cout << "--------------------" << endl;
    cout << "Twoj wybor: ";
}

void displayLoginMenu()
{
    cout << "1. Rejestracja " << endl;
    cout << "2. Logowanie " << endl;
    cout << "9. Wyjdz z programu " << endl;
    cout << "--------------------" << endl;
    cout << "Twoj wybor: ";
}

bool checkDecision(char decision)
{
    if(decision == '1' || decision == '2' || decision == '9' ) return true;
    else return false;
}

char getDecision()
{
    char decision;
    cin >> decision;
    if(checkDecision(decision)) return decision;
    else
    {
        cout << "Nie ma takiej opcji w menu! Sprobuj ponownie" << endl;
        getDecision();
    }
    return decision;
}

void pauseProgram()
{
    cout << "Nacisnij dowolny przycisk by powrocic do Menu Glownego" << endl;
    getch();
    system("cls");
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

bool checkIfUserAlreadyExists(vector <User> &users,string checkedUserLogin)
{
    for(auto it1 = users.begin(); it1 != users.end() ; it1++ )
    {
        if(it1->login == checkedUserLogin) return true;
    }
    return false;
}

bool checkIfPersonExistsInAdressBook(vector<Person> adressBook,int checkedID)
{
    for(auto it1 = adressBook.begin(); it1 != adressBook.end(); it1++ )
    {
        if (it1 -> ID == checkedID)  return true;
    }
    return false;
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

int loadPersonDataFromTextFileToVector(vector<Person> &adressBook,int loggedInUserID)
{
    fstream textFile;
    textFile.open("KsiazkaAdresowa.txt",fstream::in | fstream::out | fstream::app);

    string textLine;
    int startPosition;
    int lastID = 0;

    while(getline(textFile,textLine))
    {
        Person person;

        startPosition = 0;
        person.ID = stoi(textLine.substr(startPosition,textLine.find("|",startPosition) - startPosition));
        lastID = person.ID;

        startPosition = textLine.find("|",startPosition)+1;
        person.userID = stoi(textLine.substr(startPosition,textLine.find("|",startPosition) - startPosition));

        if(person.userID != loggedInUserID) continue;

        startPosition = textLine.find("|",startPosition)+1;
        person.name = textLine.substr(startPosition,textLine.find("|",startPosition) - startPosition);

        startPosition = textLine.find("|",startPosition)+1;
        person.surname = textLine.substr(startPosition,textLine.find("|",startPosition) - startPosition);

        startPosition = textLine.find("|",startPosition)+1;
        person.phoneNumber = textLine.substr(startPosition,textLine.find("|",startPosition) - startPosition);

        startPosition = textLine.find("|",startPosition)+1;
        person.emailAdress = textLine.substr(startPosition,textLine.find("|",startPosition) - startPosition);

        startPosition = textLine.find("|",startPosition)+1;
        person.adress = textLine.substr(startPosition,textLine.find("|",startPosition) - startPosition);

        adressBook.push_back(person);
    }
    textFile.close();
    return lastID;
}

int personCounter(vector<Person> adressBook)
{
    int counter;
    counter = adressBook.size();
    return counter;
}

void printPersonData(Person person)
{

    cout << "ID Adresata:      " << person.ID << endl;
    cout << "Imie:            " << person.name << endl;
    cout << "Nazwisko:        " << person.surname << endl;
    cout << "Numer telefonu:  " << person.phoneNumber << endl;
    cout << "Ares Email:      " << person.emailAdress << endl;
    cout << "Adres:           " << person.adress << endl;
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
        cout<<"Wyswietlono "<<personCounter(adressBook)<<" kontaktow"<<endl;
    }
}

void searchByName (vector<Person> adressBook)
{
    bool exist = false;
    string searchedName;

    cout << "Podaj wyszukiwane imie: " ;
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
    bool exist = false;
    string searchedSurname;

    cout << "Podaj wyszukiwane nazwisko: " ;
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

Person searchForPositionInVector(vector<Person> adressBook,int checkedID)
{
    for(auto it1 = adressBook.begin(); it1 != adressBook.end(); it1++ )
    {
        if (it1 -> ID == checkedID)  return *it1;
    }
}

// true - deleted
// false - edited

void rewriteTextFileAfterDeletionOrEdition(vector<Person> &addressBook,int recentEditedID,bool deletedOrEdited)
{
    fstream addressBookTextFile;
    addressBookTextFile.open("KsiazkaAdresowa.txt",fstream::in);

    if (!addressBookTextFile.good())
    {
        cout << "Problem z plikiem ksiazka adresowa!";
        exit(0);
    }

    fstream temporaryTextFile;
    temporaryTextFile.open("tymczasowy.txt",fstream::out);

    if (!temporaryTextFile.good())
    {
        cout << "Problem z plikiem ksiazka adresowa!";
        exit(0);
    }

    string textFileLine;
    int startPosition;
    int currentPersonID;

    while(getline(addressBookTextFile,textFileLine))
    {
        startPosition = 0;
        currentPersonID = stoi(textFileLine.substr(startPosition,textFileLine.find("|",startPosition) - startPosition));
        if((currentPersonID == recentEditedID) && deletedOrEdited == true ) continue;
        else if((currentPersonID == recentEditedID) && deletedOrEdited == false )
        {
            auto it1 = searchForPositionInVector(addressBook,currentPersonID);
            temporaryTextFile << it1.ID << "|" << it1.userID <<"|"<< it1.name <<"|"<< it1.surname << "|" << it1.phoneNumber << "|";
            temporaryTextFile << it1.emailAdress << "|" << it1.adress << "|" << endl;
        }
        else
        {
            temporaryTextFile << textFileLine << endl;
        }
    }
    addressBookTextFile.close();
    remove("KsiazkaAdresowa.txt");
    temporaryTextFile.close();
    rename("tymczasowy.txt","KsiazkaAdresowa.txt");
}

void deletePerson(vector<Person> &addressBook)
{
    int personID;
    char prove;
    char repeat;

    cout << "Podaj ID osoby do usuniecia: " << endl;
    cin >> personID;
    if(checkIfPersonExistsInAdressBook(addressBook,personID))
    {
        for(auto it1 = addressBook.begin(); it1 <= addressBook.end(); it1++)
        {
            if (it1 -> ID == personID)
            {
                cout<<"Czy na pewno usunac osobe z ksiazki adresowej t/n: ";
                cin>> prove;

                if(prove == 't')
                {
                    addressBook.erase(it1);

                    cout<<"Osoba zostala pomyslnie usunieta z ksiazki adresowej!" << endl;

                    rewriteTextFileAfterDeletionOrEdition(addressBook, personID, true);
                    break;
                }
                else  break;
            }
        }
    }
    else
    {
        cout << "Nie ma osoby o podanym ID w ksiazce adresowej" << endl;
        cout << "Wybierz m jesli chcesz powrocic do menu, d jesli chcesz sprobowac ponownie: " << endl;
        cin >> repeat;

        if(repeat == 'm') cout << "Powrot do MENU" << endl;
        else deletePerson(addressBook);
    }
}

void editPersonData(vector<Person> &addressBook)
{
    int editingPersonID;
    int userChoice;
    string editedData;

    cout << "Wprowadz ID adresata ktorego chcesz edytowac " << endl;
    cin >> editingPersonID;

    if(checkIfPersonExistsInAdressBook(addressBook,editingPersonID))
    {
        displayEditMenu();

        cin >> userChoice;
        cin.sync();

        if(userChoice < 6)
        {
            for(auto it1 = addressBook.begin(); it1 != addressBook.end(); it1++)
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
                    rewriteTextFileAfterDeletionOrEdition(addressBook, editingPersonID, false);

                    cout<<"Kontakt po edycji: "<<endl;
                    cout <<"-----------------------------------------------" << endl;

                    printPersonData(*it1);
                    pauseProgram();
                }
            }
        }
    }
    else {
            cout<<"Nie ma osoby o podanym ID w ksiazce adresowej"<<endl;
            pauseProgram();
    }
}

void savePersonToTextFile(Person person)
{
    fstream textFile;
    textFile.open("KsiazkaAdresowa.txt",fstream::app);

    textFile << person.ID <<"|" << person.userID << "|" << person.name <<"|"<< person.surname << "|" << person.phoneNumber << "|";
    textFile << person.emailAdress << "|" << person.adress << "|" << endl;

    textFile.close();
}

int addPersonToBook(vector<Person> &addressBook,int userID,int lastID)
{
    Person person;
    person.userID = userID;
    person.ID = lastID + 1;

    cout << "DODAWANIE NOWEGO ADRESATA" << endl;

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

    addressBook.push_back(person);
    savePersonToTextFile(person);

    cout << "Dodawanie przebieglo pomyslnie" << endl;

    return person.ID;
}

int main()
{
    vector<User> users;
    vector<Person> addressBook;
    int userID = 0;
    int lastID;
    char decision;
    loadUserDataFromTextFileToVector(users);

    while(userID == 0)
    {
        displayLoginMenu();
        decision = getDecision();
        switch(decision)
        {
        case '1':
            registration(users);
            system("pause");
            system("cls");
            break;
        case '2':
            userID = loggingIn(users);
            system("pause");
            system("cls");
            break;
        case '9':
            exit(0);
        default:
            cout << "Cos poszlo nie tak!" << endl;
            exit(0);
        }

        lastID = loadPersonDataFromTextFileToVector(addressBook,userID);

        while(userID !=0)
        {
            system("cls");
            displayMainMenu();
            cin >> decision;

            switch(decision)
            {
            case '1':
                system("cls");
                lastID = addPersonToBook(addressBook,userID,lastID);
                pauseProgram();
                break;
            case '2':
                system("cls");
                searchByName(addressBook);
                pauseProgram();
                break;
            case '3':
                system("cls");
                searchBySurname(addressBook);
                pauseProgram();
                break;
            case '4':
                system("cls");
                displayWholeAdressBook(addressBook);
                pauseProgram();
                break;
            case '5':
                system("cls");
                deletePerson(addressBook);
                addressBook.clear();
                lastID = loadPersonDataFromTextFileToVector(addressBook,userID);
                pauseProgram();
                break;
            case '6':
                system("cls");
                editPersonData(addressBook);
                break;
            case '7':
                system("cls");
                changePassword(users,userID);
                pauseProgram();
                break;
            case '8':
                userID = 0;
                addressBook.clear();
                system("cls");
                break;
            default:
                cout << "Cos poszlo nie tak!" << endl;
                break;
            }
        }
    }
    return 0;
}
