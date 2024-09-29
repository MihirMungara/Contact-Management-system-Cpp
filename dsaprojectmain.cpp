#include <bits/stdc++.h>
using namespace std;

class Contact
{
private:
    string name;
    string phoneNumber;
    string email;

public:
    Contact(const string &n, const string &phone, const string &mail)
        : name(n), phoneNumber(phone), email(mail) {}

    const string &getName() const
    {
        return name;
    }

    const string &getPhoneNumber() const
    {
        return phoneNumber;
    }

    const string &getEmail() const
    {
        return email;
    }

    void setPhoneNumber(const string &phone)
    {
        phoneNumber = phone;
    }

    void setEmail(const string &mail)
    {
        email = mail;
    }
};

class ContactManager
{
private:
    vector<Contact> contacts;
    map<string, int> nameToIndex;
    map<string, int> phoneToIndex;
    bool isValidEmail(const string &email)
    {
        return email.find('@') != string::npos;
    }

    bool isValidPhoneNumber(const string &phone)
    {
        return phone.length() == 10 && all_of(phone.begin(), phone.end(), ::isdigit);
    }

public:
    void addContactFromUserInput()
    {
        string name, phone, email;

        cout << "Enter name: ";
        getline(cin, name);

        while (true)
        {
            cout << "Enter phone number (10 digits only): ";
            getline(cin, phone);
            if (isValidPhoneNumber(phone))
            {
                break;
            }
            cout << "Invalid phone number format. Please try again." << endl;
        }

        while (true)
        {
            cout << "Enter email: ";
            getline(cin, email);
            if (isValidEmail(email))
            {
                break;
            }
            cout << "Invalid email format. Please try again." << endl;
        }

        addContact(Contact(name, phone, email));
    }

    void updatePhoneNumberFromUserInput()
    {
        string name, newPhone;

        cout << "Enter name of the contact: ";
        getline(cin, name);

        cout << "Enter new phone number: ";
        getline(cin, newPhone);

        updatePhoneNumber(name, newPhone);
    }

    void updateEmailFromUserInput()
    {
        string name, newEmail;

        cout << "Enter name of the contact: ";
        getline(cin, name);

        cout << "Enter new email: ";
        getline(cin, newEmail);

        updateEmail(name, newEmail);
    }

    void findContactByNameFromUserInput()
    {
        string name;

        cout << "Enter name of the contact to find: ";
        getline(cin, name);

        const Contact *found = findContactByName(name);

        if (found)
        {
            cout << "Phone number of " << found->getName() << endl;
            cout << "Phone number : " << found->getPhoneNumber() << endl;
            cout << "Email id : " << found->getEmail() << endl;
        }
        else
        {
            cout << "Contact not found by name." << endl;
        }
    }

    void findContactByPhoneFromUserInput()
    {
        string phone;

        cout << "Enter phone number of the contact to find: ";
        getline(cin, phone);

        const Contact *found = findContactByPhone(phone);

        if (found)
        {
            cout << "Phone number of : " << found->getName() << endl;
            cout << "Email id : " << found->getEmail() << endl;
        }
        else
        {
            cout << "Contact not found by phone." << endl;
        }
    }

    void addContact(const Contact &contact)
    {
        contacts.push_back(contact);
        int index = contacts.size() - 1;
        nameToIndex[contact.getName()] = index;
        phoneToIndex[contact.getPhoneNumber()] = index;
        sortContacts();
    }

    void updatePhoneNumber(const string &name, const string &newPhone)
    {
        if (nameToIndex.find(name) != nameToIndex.end())
        {
            int index = nameToIndex[name];
            contacts[index].setPhoneNumber(newPhone);
            phoneToIndex[newPhone] = index;
            phoneToIndex.erase(contacts[index].getPhoneNumber());
            sortContacts();
        }
    }

    void updateEmail(const string &name, const string &newEmail)
    {
        if (nameToIndex.find(name) != nameToIndex.end())
        {
            int index = nameToIndex[name];
            contacts[index].setEmail(newEmail);
            sortContacts();
        }
    }

    const Contact *findContactByName(const string &name) const
    {
        if (nameToIndex.find(name) != nameToIndex.end())
        {
            int index = nameToIndex.at(name);
            return &contacts[index];
        }
        return nullptr;
    }

    const Contact *findContactByPhone(const string &phone) const
    {
        if (phoneToIndex.find(phone) != phoneToIndex.end())
        {
            int index = phoneToIndex.at(phone);
            return &contacts[index];
        }
        return nullptr;
    }

    void sortContacts()
    {
        sort(contacts.begin(), contacts.end(), [](const Contact &a, const Contact &b)
             { return a.getName() < b.getName(); });
        nameToIndex.clear();
        phoneToIndex.clear();
        for (int i = 0; i < contacts.size(); ++i)
        {
            nameToIndex[contacts[i].getName()] = i;
            phoneToIndex[contacts[i].getPhoneNumber()] = i;
        }
    }

    void displayAllContacts() const
    {
        for (const Contact &contact : contacts)
        {
            cout << "Name: " << contact.getName() << ", Phone: " << contact.getPhoneNumber()
                 << ", Email: " << contact.getEmail() << endl;
        }
    }

    void saveContactsToFile(const string &filename)
    {
        ofstream outputFile(filename);

        if (!outputFile)
        {
            cerr << "Error opening file for writing." << endl;
            return;
        }

        for (const Contact &contact : contacts)
        {
            outputFile << contact.getName() << ","
                       << contact.getPhoneNumber() << ","
                       << contact.getEmail() << endl;
        }

        outputFile.close();

        cout << "Contacts saved to file: " << filename << endl;
    }

    // Function to load contacts from a file
    void loadContactsFromFile(const string &filename)
    {
        ifstream inputFile(filename);

        if (!inputFile)
        {
            cerr << "Error opening file for reading." << endl;
            return;
        }

        contacts.clear();
        nameToIndex.clear();
        phoneToIndex.clear();

        string line;
        while (getline(inputFile, line))
        {
            stringstream ss(line);
            string name, phone, email;

            if (getline(ss, name, ',') && getline(ss, phone, ',') && getline(ss, email, ','))
            {
                addContact(Contact(name, phone, email));
            }
        }

        inputFile.close();

        cout << "Contacts loaded from file: " << filename << endl;
    }
};

int main()
{
    ContactManager manager;

    int choice;
    while (true)
    {
        cout << "\nMenu:\n";
        cout << "1. Add Contact\n";
        cout << "2. Update Phone Number\n";
        cout << "3. Update Email\n";
        cout << "4. Find Contact by Name\n";
        cout << "5. Find Contact by Phone Number\n";
        cout << "6. Display All Contacts\n";
        cout << "7. Save Contacts to File\n";
        cout << "8. Load Contacts from File\n";
        cout << "9. Quit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
            manager.addContactFromUserInput();
            break;
        case 2:
            manager.updatePhoneNumberFromUserInput();
            break;
        case 3:
            manager.updateEmailFromUserInput();
            break;
        case 4:
            manager.findContactByNameFromUserInput();
            break;
        case 5:
            manager.findContactByPhoneFromUserInput();
            break;
        case 6:
            manager.displayAllContacts();
            break;
        case 7:
        {
            string filename;
            cout << "Enter filename: ";
            cin >> filename;
            manager.saveContactsToFile(filename);
            break;
        }
        case 8:
        {
            string filename;
            cout << "Enter filename: ";
            cin >> filename;
            manager.loadContactsFromFile(filename);
            break;
        }
        case 9:
            cout << "Goodbye!" << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }

    return 0;
}