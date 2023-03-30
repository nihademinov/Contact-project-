#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

#include "table.h"


class Contact
{
	//--------------Class Fields---------------------------------------
public:
	int id;
	string *_name;
	string *_number;

private:
	//-------------------Private function--------------------------------
	bool checkPhoneOperator(string number)
	{
		string operator_;
		for (int i = 0; i < 3; i++)
		{
			operator_ += number[i];
		}

		if (operator_ == "055" || operator_ == "050" || operator_ == "051" || operator_ == "070" || operator_ == "077" || operator_ == "010" || operator_ == "099")
		{
			return true;
		}
		return false;
	}

public:

	//-----------------------Constructors---------------------------------------

	Contact(string number)
	{
		this->id++;
		string defaultMesage = "Unkown name";
		this->_name = new string(defaultMesage);
		setPhone(number);
	}

	Contact(string name, string number)
	{
		this->id++;
		setPhone(number);
		setName(name);
	}


	//----------------------Set function--------------------------------------
	void setName(string name)
	{
		string defaultMessage;
		defaultMessage = "Unkown";

		if (name == " ")
		{
			this->_name = new string( defaultMessage);

		}
		else
		{
			this->_name = new string(name);
		}
	}

	void setPhone(string number)
	{
		bool checkError = false;
		bool checkDigit = true;
		string defaultMessage;
		defaultMessage = "Unknown";

		if (number == "Unknown")
		{
			this->_number = new string(defaultMessage);
			return;
		}

		for (int i = 0; i < (number.length()); i++)
		{
			if (!isdigit(number[i]))
			{
				checkDigit = false;
			}

		}

		if (number.length() == 10)
		{
			checkError = checkPhoneOperator(number);
		}
		
		if (checkError&& checkDigit )
		{
			number = number.insert(3, "-");
			number = number.insert(7, "-");
			number = number.insert(10, "-");
			this->_number = new string (number);
		}
		else
		{
			try
			{
				throw exception("False phone");
			}
			catch (const std::exception& ex)
			{
				this->_number = new string (defaultMessage);
				cout << ex.what() << endl;
			}
		}
	}

	//-----------------------Get function------------------------------------
	string getName()
	{
		return *this->_name;
	}

	string getNumber()
	{
		return *this->_number;
	}

	//------------------Show function-------------------------------------
	void showContact()
	{
		cout << "Name: " << *this->_name << endl;
		cout << "Phone: " << *this->_number << endl;
	}

	//-------------------Destructor------------------------------------
	
};

class DataBase
{
public:
	vector<Contact>* contacts = new vector<Contact>;

	DataBase(){}
	
	

	void searchByName(Contact* other)
	{
		bool checkName = false;
		ifstream file("Contact.txt", ios::in);

		string data;
		vector<string> tempName;
		vector<string> tempName2;
		while (!file.eof())
		{
			getline(file, data, '\n');
			tempName.push_back(data);
			
		}

		for (auto& i : tempName)
		{
			string namedata;
			for (auto j = i.begin(); j < i.end(); j++)
			{
				
				if (*j != '-')
				{
					namedata += *j;
				}
				else
				{
					tempName2.push_back(namedata);
					break;
				}
			}
			
		}

		for (auto& i : tempName2)
		{
			if (i == *other->_name) 
			{
				checkName = true;
			}
		}
		if (checkName)
		{
			cout << "Name was find." << endl;
		}
		else
		{
			cout << "Name was not find" << endl;
		}
		file.close();
	}

	void searchByPhone(Contact* other)
	{
		ifstream file("Contact.txt", ios::in);
		vector<string> tempNumber;
		vector<string> tempNumber2;
		string tempPhone;
		string tempName;
		string data;
		bool check = false;
		bool checkPhone = false;

		while (!file.eof())
		{
			getline(file, data, '\n');
			tempNumber.push_back(data);

		}


		for (auto& i : tempNumber)
		{
			int count = 0;
			string phonedata;
			for (auto j = i.begin(); j < i.end(); j++)
			{
				

				if (*j == '0')
				{
					check = true;
				}
				
				if (check)
				{
					count++;
					phonedata += *(j);
				}
				if (count == 13)
				{
					tempNumber2.push_back(phonedata);

				}
				
			}

		}

		for (auto& i : tempNumber2)
		{
			if (i == *other->_number)
			{
				checkPhone = true;
			}
		}

		
		if (checkPhone)
		{
			cout << "Number was find." << endl;
		}
		else
		{
			cout << "Number was not founded" << endl;
		}
		file.close();
	}

	

	void deleteContact(Contact* other)
	{
		bool check = false;
		int count = -1;
		string tempData;
		string data;
		for (auto& i : *contacts)
		{
			count++;
			if (*(i._name) == *(other->_name) && *(i._number) == *(other->_number)) 
			{
				delete i._name;
				delete i._number;
				(*contacts).erase((*contacts).begin() + count);

				check = true;
			}
		}
		ofstream file2("Contact.txt", ios::out);
		file2.close();

		ofstream file("Contact.txt", ios::app);
		file.seekp(0);
		for (auto& i : *contacts)
		{
			file << *i._name << "-->" << *i._number << endl;
		}
			file.close();


		
		
		if (check)
		{
			cout << "Contact was delete" << endl;
		}
		else 
		{
			cout << "Contact could not find" << endl;
		}
			
	}


	void saveNumber(Contact * contact)
	{
		contacts->push_back(*contact);
		ofstream file("Contact.txt", ios::app);
		file << *contact->_name << "-->" << *contact->_number <<  endl;
		file.close();
		cout << "Contact created succesfully" << endl;

	}

	void showNumber()
	{
		ifstream file("Contact.txt", ios::in);
		file.seekg(0);
		int count = 0;
		string data;
		
		while (file >> data)
		{
			cout << ++count<<".";
			int lastId = 0;
			cout << data << endl;
			
		}
		file.close();
	}

	

	~DataBase()
	{
		for (auto& i : *contacts)
		{
			

				delete i._name;
				delete i._number;
			
		}
		delete contacts;
	}

};

int main()
{
	DataBase dataBase;
	while (true)
	{
	
		AskToPlayer();

		if (chechCreate)
		{
			string name;
			string phone;
			cout << "Enter name: ";
			cin >> name;
			cout << "Enter phone: ";
			cin >> phone;
			Contact *newContact = new Contact (name, phone);
			dataBase.saveNumber(newContact);
			cout << endl;
			chechCreate = false;
		}

		else if (checkShowContact)
		{
			dataBase.showNumber();
			cout << endl;
			
			checkShowContact = false;
		}

		else if (checkDelete)
		{
			string name;
			string phone;

			cout << "Enter remove name: ";
			cin >> name;
			cout << "Enter remove phone: ";
			cin >> phone;
			Contact* newContact = new Contact(name, phone);

			dataBase.deleteContact(newContact);
			cout << endl;
			
			checkDelete = false;
		}

		else if (checkSearchName)
		{
			string name;
			string phone;
			phone = "Unknown";
			cout << "Enter name: ";
			cin >> name;
			Contact* newContact = new Contact(name,phone);
			dataBase.searchByName(newContact);
			cout << endl;
			
			checkSearchName = false;
		}

		else if (checkSearchPhone)
		{
			string name;
			name = "Unknown";
			string phone;
			cout << "Enter phone: ";
			cin >> phone;
			Contact* newContact = new Contact(name,phone);
			dataBase.searchByPhone(newContact);
			cout << endl;
			
			checkSearchPhone = false;
		}
		int keyPressed = 0;
		cout << "Press Enter for continue";
		while (keyPressed != 13)
		{
			keyPressed = _getch();

		}
	}
}
