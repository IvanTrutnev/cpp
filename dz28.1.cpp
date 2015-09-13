#include <windows.h>
#include <iostream>
#include <io.h>
#include <cstdlib>
#include <sys\locking.h>
#include <cstring>
#include <cctype>
using namespace std;
struct Elem
{
	char phone_number[20];
	char surname[40];

	Elem * left, *right, *parent;
};

class Tree
{
	Elem* root;
public:
	Tree();
	~Tree();
	Elem* GetRoot();
	Elem* Search_number(Elem* Node, char* key_number);
	Elem* Search_surname(Elem* Node, char* key_surname);
	Elem* Min(Elem* Node);
	Elem* Max(Elem* Node);
	Elem* Next(Elem* Node);
	Elem* Previous(Elem* Node);
	void Insert(char* phone, char* sur);
	void Change(Elem* Node, char* new_number, char* new_surname);
	void Del(Elem* z = nullptr);
	void Print(Elem* Node, char* key_1 = nullptr, char* key_2 = nullptr, int mode = 0);
	void from_file(const char* file_name);
	void to_file(const char* file_name);
};
Tree::Tree()
{
	root = nullptr;
}

Tree::~Tree()
{
	Del();
}

Elem* Tree::GetRoot()
{
	return root;
}

Elem* Tree::Search_number(Elem* Node, char* key_number)
{
	while (Node != nullptr && strcmp(key_number, Node->phone_number) != 0)
	{
		if (strcmp(key_number, Node->phone_number) < 0)
		{
			Node = Node->left;
		}
		else{
			Node = Node->right;
		}
	}

	return Node;
}

Elem* Tree::Search_surname(Elem* Node, char* key_surname)
{
	while (Node != nullptr && strcmp(key_surname, Node->surname) != 0)
	{
		if (strcmp(key_surname, Node->surname) < 0)
		{
			Node = Node->left;
		}
		else{
			Node = Node->right;
		}
	}

	return Node;
}

Elem* Tree::Min(Elem* Node)
{
	if (Node != nullptr)
	{
		while (Node->left != nullptr)
		{
			Node = Node->left;
		}
	}

	return Node;
}

Elem* Tree::Max(Elem* Node)
{
	if (Node != nullptr)
	{
		while (Node->right != nullptr)
		{
			Node = Node->right;
		}
	}

	return Node;
}

Elem* Tree::Next(Elem* Node)
{
	Elem* y = nullptr;
	if (Node != nullptr)
	{
		if (Node->right != nullptr)
		{
			return Min(Node->right);
		}

		y = Node->parent;

		while (y != nullptr && Node == y->right)
		{
			Node = y;
			y = y->parent;
		}
	}

	return y;
}

Elem* Tree::Previous(Elem* Node)
{
	Elem* y = nullptr;
	if (Node != nullptr)
	{
		if (Node->left != nullptr)
		{
			return Max(Node->left);
		}

		y = Node->parent;

		while (y != nullptr && Node == y->left)
		{
			Node = y;
			y = y->parent;
		}
	}

	return y;
}

void Tree::Insert(char* phone, char* sur)
{
	Elem* new_person = new Elem;
	strcpy(new_person->phone_number, phone);
	strcpy(new_person->surname, sur);

	if (Search_number(root, new_person->phone_number) == nullptr)
	{
		new_person->left = nullptr;
		new_person->right = nullptr;
		Elem * y = nullptr;
		Elem * Node = root;

		while (Node != nullptr)
		{
			y = Node;
			if (strcmp(new_person->surname, Node->surname) < 0)
			{
				Node = Node->left;
			}
			else{
				Node = Node->right;
			}
		}

		new_person->parent = y;

		if (y == nullptr)
		{
			root = new_person;
		}
		else if (strcmp(new_person->surname, y->surname) < 0)
		{
			y->left = new_person;
		}
		else{
			y->right = new_person;
		}

	}
	else{
		delete new_person;
		cout << "no-no-no\n";
	}
}

void Tree::Change(Elem* Node, char* new_number, char* new_surname)
{
	Del(Node);
	Insert(new_number, new_surname);
}

void Tree::Del(Elem* z)
{
	if (z != nullptr)
	{
		Elem* Node;
		Elem* y;

		if (z->left == nullptr || z->right == nullptr)
		{
			y = z;
		}
		else{
			y = Next(z);
		}


		if (y->left != nullptr)
		{
			Node = y->left;
		}
		else{
			Node = y->right;
		}

		if (Node != nullptr)
		{
			Node->parent = y->parent;
		}


		if (y->parent == nullptr)
		{
			root = Node;
		}
		else if (y == y->parent->left)
		{
			y->parent->left = Node;
		}
		else{
			y->parent->right = Node;
		}

		if (y != z)
		{
			strcpy(z->phone_number, y->phone_number);
			strcpy(z->surname, y->surname);
		}

		delete y;
	}
	else{
		while (root != nullptr)
		{
			Del(root);
		}
	}
}

void Tree::Print(Elem* Node, char* key_1, char* key_2, int mode)
{

	FILE* output;
	if (!(output = fopen("choice.txt", "wb")))
	{
		cout << "File not open!\n";
	}

	
	//fout.open("t.txt");
	if (key_1 != nullptr && key_2 != nullptr)
	{

		switch (mode)
		{
		case 1:
			if (Node != nullptr)
			{

				if (strcmp(key_1, key_2) > 0)
				{
					char* temp = key_1;
					key_1 = key_2;
					key_2 = temp;
				}

				Elem* current = Search_surname(root, key_1);
				if (current != nullptr)
				{
					while (current != nullptr && strcmp(current->surname, key_2) <= 0)
					{
						printf("%-15s: ", current->surname);
						printf("\t%-12s\n", current->phone_number);
						fputs(current->phone_number, output);
						fputs(current->surname, output);
						fputs("\r\n", output);
						
						current = Next(current);
					}
				}
				else{
					Elem* maximum = Max(Node);
					Elem* minimum = Min(Node);
					if (strcmp(maximum->surname, key_1) < 0 || strcmp(minimum->surname, key_2) > 0)
					{
						cout << "Wrong range.\n";
					}
					else{
						current = minimum;
						while (current != nullptr && strcmp(current->surname, key_2) <= 0)
						{
							printf("%-15s: ", current->surname);
							printf("\t%-12s\n", current->phone_number);
							fputs(current->phone_number, output);
							fputs(current->surname, output);
							fputs("\r\n", output);
							
							current = Next(current);
						}
					}
				}

			}
			break;
		case 2:
			if (Node != nullptr)
			{

				if (strcmp(key_1, key_2) > 0)
				{
					char* temp = key_1;
					key_1 = key_2;
					key_2 = temp;
				}

				Elem* current = Min(Node);
				if (current != nullptr)
				{
					while (current != nullptr)
					{
						if (strcmp(current->phone_number, key_1) >= 0 && strcmp(current->phone_number, key_2) <= 0)
						{
							printf("%-15s: ", current->surname);
							printf("\t%-12s\n", current->phone_number);
							fputs(current->phone_number, output);
							fputs(current->surname, output);
							fputs("\r\n", output);
							
						}
						current = Next(current);
					}
				}
				else{
					Elem* maximum = Max(Node);
					Elem* minimum = Min(Node);
					if (strcmp(maximum->phone_number, key_1) < 0 || strcmp(minimum->phone_number, key_2) > 0)
					{
						cout << "Wrong range.\n";
					}
					else{
						current = minimum;
						while (current != nullptr && strcmp(current->surname, key_2) <= 0)
						{
							if (strcmp(current->phone_number, key_1) >= 0 && strcmp(current->phone_number, key_2) <= 0)
							{
								printf("%-15s: ", current->surname);
								printf("\t%-12s\n", current->phone_number);
								fputs(current->phone_number, output);
								fputs(current->surname, output);
								fputs("\r\n", output);
								
							}
							current = Next(current);
						}
					}
				}

			}
			break;
		default:
			cout << "Wrong mode!\n";
			break;
		}

	}
	else if (key_1 == nullptr && key_2 == nullptr && mode == 0 && Node != nullptr)
	{
		printf("%-15s: ", Node->surname);
		printf("\t%-12s\n", Node->phone_number);
		fputs(Node->phone_number, output);
		fputs(Node->surname, output);
		fputs("\r\n", output);
		
	}
	else{
		cout << "No record!\n";
	}

	fclose(output);
}

void Tree::from_file(const char* file_name)
{
	FILE* input;
	if (!(input = fopen(file_name, "rb")))
	{
		cout << "File not open!\n";
	}
	else{
		static int count = -1;
		char number[20] = { 0 };
		char surname[20] = { 0 };
		int count_bites = 0;
		int position = 0;
		char correct_surname[20] = { 0 };

		if (count == -1)
		{
			while (!feof(input))
			{
				fgets(number, 10, input);
				fgets(surname, 40, input);
				strncpy(correct_surname, surname, (strlen(surname) - 2));
				Insert(number, correct_surname);
				count++;
			}

			if (count == 0)
			{
				cout << "Error!\n";
			}

			fseek(input, 0, 0);
		}
		fclose(input);
	}
}

void Tree::to_file(const char* file_name)
{
	FILE* output;
	Elem* current = Min(GetRoot());

	if (!(output = fopen(file_name, "wb")))
	{
		cout << "File not open!\n";
	}
	else{

		while (current != nullptr)
		{
			fputs(current->phone_number, output);
			fputs(current->surname, output);
			fputs("\r\n", output);
			current = Next(current);
		}
		fclose(output);
	}
}
int main()
{
	Tree test;

	test.from_file("t.txt");
	test.Print(test.GetRoot(), "A", "Z", 1);

	test.Insert("773-80-31", "qew");
	test.Insert("221-90-21", "Opes");
	test.Insert("123-45-67", "Petrova");
	test.Insert("322-68-88", "Ivanova");
	cout << endl;
	test.Print(test.GetRoot(), "A", "Z", 1);

	test.Del(test.Search_number(test.GetRoot(), "221-90-21"));
	test.Change(test.Search_number(test.GetRoot(), "227-29-19"), "344-29-19", "Petrova");
	cout << endl;
	test.Print(test.GetRoot(), "322-68-88", "123-45-67", 2);
	test.to_file("qwe.txt");

	return 0;
}