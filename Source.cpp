#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct PERSON
{
	int ID;
	string name;
	double balance;
};

void DisplayRaf(const char* fname)

{
	PERSON st = { 0,"bbbb", 0.0 };
	fstream f;
	f.open(fname, ios::in | ios::binary);
	cout << "This is the content of " << fname << " File \n";
	f.read((char*)&st, sizeof(st));
	while (true)
	{
		cout << st.ID << '\t' << st.name << '\t' << st.balance << endl;
		f.read((char*)&st, sizeof(st));
		if (f.fail())
		{
			break;
		}
	}
	f.close();
}

int main()

{
	PERSON st = { 0, "bbbb", 0.0 };
	int pos;
	int choice = 0;
	fstream f1;
	f1.open("file.raf", ios::out | ios::binary);
	for (int i = 1; i <= 10; i++)
	{
		f1.write((char*)&st, sizeof(st));
	}
	f1.close();
	DisplayRaf("display.raf");
	PERSON arrays[7];
	ifstream DataIn;
	int id = 0;
	double balance = 0.0;
	string name = {};
	DataIn.open("data.txt");
	int i = 0;
	while (!DataIn.eof())
	{
		DataIn >> id >> name >> balance;
		arrays[i].ID = id;
		arrays[i].name = name;
		arrays[i].balance = balance;
		i++;
	}
	do {
		//Display the Menu Options
		cout << "------Bank of America------" << endl;
		cout << "1. Display all records from the RAf" << endl;
		cout << "2. Display a record when ID is given" << endl;
		cout << "3. Deposit in an account with a given ID" << endl;
		cout << "4. Withdraw from an account with a given ID" << endl;
		cout << "5. Close an account for a given ID" << endl;
		cout << "6. Exit (copy the RAF into a text file)" << endl;
		cout << endl << "Enter an option (1-6): ";
		cin >> choice;

		if (choice == 1)						//Copy date from arrays into RAF. Use ID as a key value
												//Display all records from the RAF

		{
			fstream f2;
			f2.open("file.raf", ios::out | ios::binary);
			for (int i = 0; i < 7; i++)
			{
				pos = (arrays[i].ID / 10 - 1) * sizeof(arrays[i]);
				f2.seekp(pos, ios::beg);
				f2.write((char*)&arrays[i], sizeof(arrays[i]));
			}f2.close();
			DisplayRaf("file.raf");
			cout << endl;
		}
		if (choice == 2)
		{						//Display a record when ID is given
			int record;
			cout << "Enter the ID number of the record you wish to display: ";
			cin >> record;
			cout << "This is the contents of the record with id# " << record << " :" << endl;
			fstream f3;
			f3.open("file.raf", ios::in | ios::binary);
			int r = (record / 10);
			r = r - 1;
			f3.seekg(r * sizeof(st), ios::cur);
			f3.read((char*)&st, sizeof(st));
			cout << st.ID << '\t' << st.name << '\t' << st.balance << endl;
		}
		if (choice == 3)
		{
			fstream f4;
			f4.open("file.raf", ios::in | ios::out | ios::binary);
			int record;
			double amount;
			cout << "Enter the ID number of the account for deposit: ";
			cin >> record;
			cout << "Enter the amount you wish to deposit: ";
			cin >> amount;
			int r = (record / 10);
			r = r - 1;
			f4.seekg(r * sizeof(st), ios::beg);
			pos = f4.tellg();
			f4.read((char*)&st, sizeof(st));
			st.balance += amount;
			f4.seekp(pos, ios::beg);
			f4.write((char*)&st, sizeof(st));
			f4.seekg(r * sizeof(st), ios::beg);
			f4.read((char*)&st, sizeof(st));
			cout << "This is the content of the record with id#: " << record << endl;
			cout << st.ID << '\t' << st.name << '\t' << st.balance << endl << endl;
			f4.close();
		}
		if (choice == 4)							//Withdraw from an account with a given ID
		{
			fstream f5;
			f5.open("file.raf", ios::in | ios::out | ios::binary);
			int record;
			double amount;
			cout << "Enter the ID number of the account for withdraw: ";
			cin >> record;
			cout << "Enter the amount you wish to withdraw: ";
			cin >> amount;
			int r = (record / 10);
			r = r - 1;
			f5.seekg(r * sizeof(st), ios::beg);
			pos = f5.tellg();
			f5.read((char*)&st, sizeof(st));
			st.balance -= amount;
			f5.seekp(pos, ios::beg);
			f5.write((char*)&st, sizeof(st));
			f5.seekg(r * sizeof(st), ios::beg);
			f5.read((char*)&st, sizeof(st));
			cout << "This is the content of the record with id#: " << record << endl;
			cout << st.ID << '\t' << st.name << '\t' << st.balance << endl << endl;
			f5.close();
		}
		if (choice == 5)							//Close an account for a given ID
		{
			fstream f6;
			f6.open("file.raf", ios::in | ios::out | ios::binary);
			int record;
			cout << "Enter the ID number of the account you wish to close: ";
			cin >> record;
			int r = (record / 10);
			r = r - 1;
			f6.seekg(r * sizeof(st), ios::beg);
			pos = f6.tellg();
			f6.read((char*)&st, sizeof(st));
			st.balance = 0.00;
			st.ID = 0;
			st.name = "bbbb";
			f6.seekp(pos, ios::beg);
			f6.write((char*)&st, sizeof(st));
			f6.seekg(r * sizeof(st), ios::beg);
			f6.read((char*)&st, sizeof(st));
			cout << "This is the content of the record with id# " << record << " :" << endl;
			cout << st.ID << '\t' << st.name << '\t' << st.balance << endl << endl;
			f6.close();
		}
		if (choice == 6)
		{
			DisplayRaf("file.raf");
			system("pause");
		}
	} while (choice > 0 && choice < 6);
	system("pause");
}

/*
This is the content of display.raf File
0       bbbb    0
------Bank of America------
1. Display all records from the RAf
2. Display a record when ID is given
3. Deposit in an account with a given ID
4. Withdraw from an account with a given ID
5. Close an account for a given ID
6. Exit (copy the RAF into a text file)

Enter an option (1-6): 1
This is the content of file.raf File
10      Nixon,Kathy     100.1
20      Reagon,Ron      200.2
30      Clinton,Bill     300.3
40      Bush,Barbara     400.4
50      Carter,Jimmy    500.5
60      Bush,George     600.6
0               0
0               0
90      Obama,Barack    900.9

------Bank of America------
1. Display all records from the RAf
2. Display a record when ID is given
3. Deposit in an account with a given ID
4. Withdraw from an account with a given ID
5. Close an account for a given ID
6. Exit (copy the RAF into a text file)

Enter an option (1-6): 2
Enter the ID number of the record you wish to display: 30
This is the contents of the record with id# 30 :
30      Clinton,Bill     300.3
------Bank of America------
1. Display all records from the RAf
2. Display a record when ID is given
3. Deposit in an account with a given ID
4. Withdraw from an account with a given ID
5. Close an account for a given ID
6. Exit (copy the RAF into a text file)

Enter an option (1-6): 3
Enter the ID number of the account for deposit: 10
Enter the amount you wish to deposit: 99.91
This is the content of the record with id#: 10
10      Nixon,Kathy     200.01

------Bank of America------
1. Display all records from the RAf
2. Display a record when ID is given
3. Deposit in an account with a given ID
4. Withdraw from an account with a given ID
5. Close an account for a given ID
6. Exit (copy the RAF into a text file)

Enter an option (1-6): 4
Enter the ID number of the account for withdraw: 90
Enter the amount you wish to withdraw: 900.89
This is the content of the record with id#: 90
90      Obama,Barack    0.01

------Bank of America------
1. Display all records from the RAf
2. Display a record when ID is given
3. Deposit in an account with a given ID
4. Withdraw from an account with a given ID
5. Close an account for a given ID
6. Exit (copy the RAF into a text file)

Enter an option (1-6): 5
Enter the ID number of the account you wish to close: 50
This is the content of the record with id# 50 :
0       bbbb    0

------Bank of America------
1. Display all records from the RAf
2. Display a record when ID is given
3. Deposit in an account with a given ID
4. Withdraw from an account with a given ID
5. Close an account for a given ID
6. Exit (copy the RAF into a text file)

Enter an option (1-6): 6
This is the content of file.raf File
10      Nixon,Kathy     200.01
20      Reagon,Ron      200.2
30      Clinton,Bill     300.3
40      Bush,Barbara     400.4
0       bbbb    0
60      Bush,George     600.6
0               0
0               0
90      Obama,Barack    0.01
*/
