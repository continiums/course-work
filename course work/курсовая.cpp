#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <time.h>

using namespace std;

void Crypt();

void Decrypt();

ifstream input;
ofstream output;
int semestr = 0;
string subject[9] = { "матан" , "линал" , "диск.мат." , "Я.П." , "информатика" , "физ-ра" , "история" , "философия" , "ин.яз." };

struct date {
	int day;
	int month;
	int year;
};

bool checkdate(date data)
{
	if (data.day >= 1 and data.day <= 31 and data.month >= 1 and data.month <= 12 and data.year <= 2023 and data.year >= 1000)
		return true;
	else
		return false;
}

class marks
{
public:
	string name;
	int amarks[8];
};

double found_srznach(marks* ocenka)
{
	double sreda = 0;
	for (int i = 0; i < 9; i++)
	{
		sreda += (ocenka[i].amarks[semestr - 1]);
	}
	sreda = sreda / 9;
	return sreda;
}

class node {
public:
	string surname;
	string name;
	string faculty;
	string department;
	string group;
	string recordNurdNumber;
	date birth;
	bool sex;
	int startYear;
	class marks marks[9];
	class node* next;
	double srznach;
	node()
	{
		for (int i = 0; i < 9; i++)
		{
			this->marks[i].name = subject[i];
		}
	}
};

class node* myhead;
class node* myhead2;
int countitem = 0;
int countitem2 = 0;
void printdate(date data)
{
	if (data.day > 9)
	{
		cout << data.day;
	}
	else
	{
		cout << '0' << data.day;
	}
	cout << '.';
	if (data.month > 9)
	{
		cout << data.month;
	}
	else
	{
		cout << '0' << data.month;
	}
	cout << '.';
	cout << data.year << ' ';
}
void printitem()
{
	class node* current = myhead;
	cout << endl;
	int item = 0;
	while (current)
	{
		cout << '\t' << item + 1 << ".\t";
		item++;
		cout << "  " << current->surname << ' ' << current->name << ' ' << current->group << endl;
		current = current->next;
	}
}
void printitem2()
{
	class node* current = myhead2;
	cout << endl;
	system("cls");
	int item = 0;
	while (current)
	{
		cout << '\t' << item + 1 << ".\t";
		item++;
		cout << "  " << current->surname << ' ' << current->name << ' ' << current->group << endl;
		current = current->next;
	}
}

void safe()
{
	output.open("file.txt", ios_base::out);
	class node* current = myhead;
	while (current)
	{
		output << current->surname << ' ' << current->name << ' ' << current->faculty << ' ' << current->department << ' ' << current->group << ' ' << current->recordNurdNumber << ' ';
		output << current->birth.day << ' ' << current->birth.month << ' ' << current->birth.year << ' ' << current->sex << ' ' << current->startYear << ' ';
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				output << current->marks[i].amarks[j] << ' ';
			}
		}
		output << endl;
		current = current->next;
	}
	output.close();
}

void additem(node data, int& Count)
{
	class node* newitem = new node();
	newitem->surname = data.surname;
	newitem->name = data.name;
	newitem->faculty = data.faculty;
	newitem->department = data.department;
	newitem->group = data.group;
	newitem->recordNurdNumber = data.recordNurdNumber;
	newitem->birth.day = data.birth.day;
	newitem->birth.month = data.birth.month;
	newitem->birth.year = data.birth.year;
	newitem->sex = data.sex;
	newitem->startYear = data.startYear;
	for (int i = 0; i < 9; i++)
	{
		newitem->marks[i] = data.marks[i];
	}
	if (Count == 0)
	{
		newitem->next = NULL;
	}
	else
	{
		newitem->next = myhead;
	}
	myhead = newitem;
	countitem++;
	Count++;
}




void deleteitem(int index, int& count)
{
	if (index > 0 and count > 0 and index <= count)
	{

		class node* current = myhead;
		class node* old;
		if (index == 1)
		{
			old = myhead;
			myhead = current->next;
			delete old;
			countitem--;
			count--;
		}
		else {
			int i = 0;
			while (current)
			{
				if (i == index - 2) {
					old = current->next->next;
					delete current->next;
					current->next = old;
					countitem--;
					count--;
					break;
				}
				current = current->next;
				i++;
			}

		}
	}
	safe();
}

void printmarks(node* otm)
{
	for (int i = 0; i < 9; i++)
	{
		cout << otm->marks[i].name << ' ';
	}
	cout << endl;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (j == 5) cout << "  ";
			cout << otm->marks[j].amarks[i] << "       ";
		}
		cout << endl;
	}
	cout << endl;
}

void editmarks(node* stud, int index)
{
	system("cls");
	class node* current = myhead;
	for (int i = 0; i < index - 1; i++)
	{
		current = current->next;
	}
	printmarks(current);
	cout << "введите, какой предмет хотите отредактировать\n 1 - матан \n 2 - линал \n 3 - диск.мат. \n 4 - Я.П. \n 5 - информатика \n 6 - физ-ра \n 7 - история \n 8 - фмлософия \n 9 - ин.яз \n";
	int ch;
	cin >> ch;
	switch (ch)
	{
	case 0:
		break;
	default:
		cout << "корректировка предмета: " << current->marks[ch - 1].name << endl;
		int sem;
		cout << "введите семестр для изменения : от 1 до 8\n";
		cin >> sem;
		switch (sem)
		{
		case 0:
			break;
		default:
		a9:			int mark;
			cout << "введите отметку: от 2 до 5\n";
			cin >> mark;
			if (mark < 2 or mark > 5)
			{
				cout << "ошибка ввода отметки: отметка вне диапазона от 2 до 5\n";
				goto a9;
			}
			current->marks[ch - 1].amarks[sem - 1] = mark;
			break;
		}
		break;
	}

}

void edititem(int index, int& Count)
{
	string a1, b1, c1, a, b;
	class node* current = myhead;
	if (index >= 0 and index <= countitem and countitem > 0)
	{
		for (int i = 0; i < index - 1; i++)
		{
			current = current->next;
		}
		int st;
c1:		system("cls");
		cout << "  " << current->surname << ' ' << current->name << ' ' << current->faculty << ' ' << current->department << ' ' << current->group << ' ' << current->recordNurdNumber << ' ';
		printdate(current->birth);
		if (current->sex == 1)
		{
			cout << "мужчина" << ' ';
		}
		else
		{
			cout << "woman" << ' ';
		}
		cout << current->startYear;
		cout << endl;
		cout << endl;

		printmarks(current);
		cout << "\n\nвведите, что хотите изменить в студенте: \n 0 - удалить студента\n 1 - фамилию \n 2 - имя";
		cout << "\n 3 - факультет \n 4 - институт \n 5 - группу \n 6 - номер зачетной книжки \n 7 - дату рождения \n 8 - пол \n 9 - год поступления \n 10 - корректировка отметок \n 11 - вернуться в главное меню\n";
		cin >> st;
		switch (st)
		{
		case 0:
			deleteitem(index, Count);
			break;
		case 1:
		y1:			cout << "\n введите новую фамилию\t";
			cin >> a;
			if (size(a) > 20)
			{
				cout << "фамилия не может быть длиннее 20 символов\n";
				goto y1;
			}
			for (int i = 0; i < size(a); i++)
				if (a[i] >= '\0' && a[i] <= '@' or a[i] >= '[' && a[i] <= '`' or a[i] >= '{' && a[i] <= 191)
				{
					cout << "ошибка ввода. Фамилия должна содержать только буквы латинского или русского алфавита\n";
					goto y1;
				}
			current->surname = a;
			break;
		case 2:
		y2:			cout << "\n введите новое имя\t";
			cin >> b;
			if (size(b) > 20)
			{
				cout << "имя не может быть длиннее 20 символов\n";
				goto y2;
			}
			for (int i = 0; i < size(b); i++)
				if (b[i] >= '\0' && b[i] <= '@' or b[i] >= '[' && b[i] <= '`' or b[i] >= '{' && b[i] <= 191)
				{
					cout << "ошибка ввода. имя должно содержать только буквы латинского или русского алфавита\n";
					goto y2;
				}
			current->name = b;
			break;
		case 3:
			cout << "\n введите новый факультет\t";
			cin >> current->faculty;
			break;
		case 4:
			cout << "\nвведите новый институт\t";
			cin >> current->department;
			break;
		case 6:
			cout << "\n введите новый номер зачетной книжки\t";
			cin >> current->recordNurdNumber;
			break;
		case 5:
			cout << "\n введите нлвую группу\t";
			cin >> current->group;
			break;
		case 7:
		p1:			cout << "\n введите новую дату рождения\t";
			date tempdata;
			cin >> a1 >> b1 >> c1;
			for (int i = 0; i < size(a1); i++) if (!(a1[i] > '/' and a1[i] < ':')) { cout << "в дате нужно использовать только цифры\n"; goto p1; }
			tempdata.day = stoi(a1);
			for (int i = 0; i < size(b1); i++) if (!(b1[i] > '/' and b1[i] < ':')) { cout << "в дате нужно использовать только цифры\n"; goto p1; }
			tempdata.month = stoi(b1);
			for (int i = 0; i < size(c1); i++) if (!(c1[i] > '/' and c1[i] < ':')) { cout << "в дате нужно использовать только цифры\n"; goto p1; }
			tempdata.year = stoi(c1);
			if (checkdate(tempdata)) current->birth = tempdata;
			else
			{
				cout << " что-то не так с датой\n";
				goto p1;
			}
			break;
		case 8:
			cout << "\n ведите новый пол : 1 - мужчина 0 - вумен\t";
			cin >> current->sex;
			break;
		case 9:
			cout << "\n введите новый год поступления\t";
			cin >> current->startYear;
			break;
		case 10:
			editmarks(current, index);
			break;
		case 11:
			break;
		default:
			goto c1;
		}
		safe();
	}
	else
	{
		cout << "ошибка ввода индекса";
	}
}

void creatingfile()
{
	output.open("file.txt", ios_base::app);
	output.close();
}

int countofrows()
{
	int count = 0;
	input.open("file.txt", ios_base::in);
	while (!input.eof())
	{
		if (input.get() == '\n')
		{
			count++;
		}
	}
	input.close();
	return count;
}

void set_srznach()
{
	class node* current = myhead;
	while (current)
	{
		current->srznach = found_srznach(current->marks);
		current = current->next;
	}
}



void copy_list2(int count)
{
	class node* temp2 = nullptr;
	class node* arr[100];
	class node* current = myhead;
	int c = 0;
	while (current)
	{
		arr[c] = current;
		current = current->next;
		c++;
	}
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < count-1; j++)
		{
			if (arr[j]->srznach < arr[j + 1]->srznach)
			{
				temp2 = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp2;
			}
		}
	}
	system("cls");
	cout << "ученики в порядке убывания " << semestr << "-ого семестра\n";
	for (int i = 0; i < count; i++)
	{
		cout << i + 1 <<'.' << arr[i]->name  << ": " << arr[i]->srznach << endl;
	}
}
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	node temp;
	setlocale(LC_ALL, "ru");
	string a1, b1, c1;
	int ch;
	int count = 0;
	creatingfile();
	count = countofrows();
	int& Count = count;
	int max = count;
	string a, b;

	input.open("file.txt", ios_base::in);
	for (int i = 0; i < max; i++)
	{
		input >> temp.surname >> temp.name >> temp.faculty >> temp.department >> temp.group >> temp.recordNurdNumber >> temp.birth.day >> temp.birth.month >> temp.birth.year >> temp.sex >> temp.startYear;
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				input >> temp.marks[i].amarks[j];
			}
		}
		additem(temp, Count);
	}
	input.close();
	cout << '\t' << "0.\t  добавить нового студента" << endl << endl;
	system("cls");
a1:	printitem();
	cout << "\nвведите, кого хотите изменить  или 0 для ввода нового студента \n\n";
	cout << "введите -1 для выполенения задания\n";
	cin >> ch;
	if (ch > countitem or ch < -1) { cout << "введен неверный индекс\n"; goto a1; }
	switch (ch)
	{
	case 0:
	b1:		cout << "введите фамилию\n";
		cin >> a;
		if (size(a) > 20)
		{
			cout << "фамилия не может быть длиннее 20 символов\n";
			goto b1;
		}
		for (int i = 0; i < size(a); i++)
			if (a[i] >= '\0' && a[i] <= '@' or a[i] >= '[' && a[i] <= '`' or a[i] >= '{' && a[i] <= 191)
			{
				cout << "ошибка ввода. Фамилия должна содержать только буквы латинского или русского алфавита\n";
				goto b1;
			}
		temp.surname = a;
	b2:		cout << "введите  имя\n";
		cin >> b;
		if (size(b) > 20)
		{
			cout << "имя не может быть длиннее 20 символов\n";
			goto b2;
		}
		for (int i = 0; i < size(b); i++)
			if (b[i] >= '\0' && b[i] <= '@' or b[i] >= '[' && b[i] <= '`' or b[i] >= '{' && b[i] <= 191)
			{
				cout << "ошибка ввода. имя должно содержать только буквы латинского или русского алфавита\n";
				goto b2;
			}
		temp.name = b;
		cout << "введите  факультет\n";
		cin >> temp.faculty;
		cout << "введите  институт\n";
		cin >> temp.department;
		cout << "введите  группу\n";
		cin >> temp.group;
		cout << "введите  номер зачетной книжки\n";
		cin >> temp.recordNurdNumber;
	z1:		cout << "введите  дату рождения\n";
		date tempdata;
		cin >> a1 >> b1 >> c1;
		for (int i = 0; i < size(a1); i++) if (!(a1[i] > '/' and a1[i] < ':')) { cout << "в дате нужно использовать только цифры\n"; goto z1; }
		tempdata.day = stoi(a1);
		for (int i = 0; i < size(b1); i++) if (!(b1[i] > '/' and b1[i] < ':')) { cout << "в дате нужно использовать только цифры\n"; goto z1; }
		tempdata.month = stoi(b1);
		for (int i = 0; i < size(c1); i++) if (!(c1[i] > '/' and c1[i] < ':')) { cout << "в дате нужно использовать только цифры\n"; goto z1; }
		tempdata.year = stoi(c1);
		if (checkdate(tempdata)) temp.birth = tempdata;
		else
		{
			cout << " что-то не так с датой\n";
			goto z1;
		}
		cout << "введите  пол: 1- мужчина 0- вумен\n";
		cin >> temp.sex;
		cout << "введите год поступления\n";
		cin >> temp.startYear;
		cout << "введите отметки по предметам\n";
		for (int i = 0; i < 9; i++)
		{
			cout << "посеместровые отметки по предмету: " << temp.marks[i].name << endl;
			for (int j = 0; j < 8; j++)
			{
			x3:				int test;
				cin >> test;
				if (test < 2 or test > 5)
				{
					cout << "\n отметка не может быть меньше 2 или больше 5\n";
					goto x3;
				}
				temp.marks[i].amarks[j] = test;

			}
		}
		additem(temp, Count);
		safe();
		goto a1;

	case -1:
		system("cls");
z10:	cout << "\nвведите семестр для сортировки от 1 до 8\n";
		cin >> semestr;
		if (semestr > 8 or semestr < 1)
		{
			cout << "неправильное значение семестра. допустимо > 1 или < 9";
			goto z10;
		}
		set_srznach();
		copy_list2(countitem);
		goto a1;
		break;
	default:
		edititem(ch, Count);
		goto a1;
	}
}

void Crypt()
{
	srand(time(NULL));
	char* pass = new char[64];
	for (int i = 0; i < 64; ++i) {
		switch (rand() % 3) {
		case 0:
			pass[i] = rand() % 10 + '0';
			break;
		case 1:
			pass[i] = rand() % 26 + 'A';
			break;
		case 2:
			pass[i] = rand() % 26 + 'a';
		}
	}
	string command = "openssl\\bin\\openssl.exe enc -aes-256-cbc -salt -in file.txt -out file.txt.enc -pass pass:";
	command += pass;
	system(command.c_str());
	if (remove("file.txt") != 0) {
		cout << "[ERROR] - deleting file" << endl;
	}
	ofstream file;
	file.open("key.txt", ios::binary);
	file.write(pass, 65);
	file.close();
	command = "openssl\\bin\\openssl.exe rsautl -encrypt -inkey rsa.public -pubin -in key.txt -out key.txt.enc";
	system(command.c_str());
	if (remove("key.txt") != 0) {
		cout << "[ERROR] - deleting file" << endl;
	}
}

void Decrypt()
{
	string command = "openssl\\bin\\openssl.exe rsautl -decrypt -in keyrsa.private - in key.txt.enc - out key.txt";
		system(command.c_str());
	if (remove("key.txt.enc") != 0) {
		cout << "[ERROR] - deleting file" << endl;
	}
	char* pass = new char[64];
	ifstream file;
	file.open("key.txt", ios::binary);
	file.read(pass, 65);
	file.close();
	if (remove("key.txt") != 0) {
		cout << "[ERROR] - deleting file" << endl;
	}
	command = "openssl\\bin\\openssl.exe enc -aes-256-cbc -d -in file.txt.enc - out file.txt - pass pass : ";
		command += pass;
	system(command.c_str());
	if (remove("file.txt.enc") != 0) {
		cout << "[ERROR] - deleting file" << endl;
	}
}