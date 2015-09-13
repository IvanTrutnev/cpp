#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;


enum MODE{ COMPANY, OWNER, PHONE, ADDRESS, TYPE };

struct Node
{
	char m_company[40];
	char m_owner[40];
	char m_phone[40];
	char m_address[40];
	char m_type[40];
	Node* left;
	Node* right;
	Node* parent;

	Node(Node* r, Node* l, char* co = "Company", char* own = "Owner", char* ph = "Phone", char* addr = "Address", char* ty = "Type")
	{
		strcpy(m_company, co);
		strcpy(m_owner, own);
		strcpy(m_phone, ph);
		strcpy(m_address, addr);
		strcpy(m_type, ty);
		left = l;
		right = r;
	}
};

class BinaryTree
{
private:
	Node* root = nullptr;
public:
	BinaryTree() = default;
	BinaryTree(const BinaryTree&) = delete;
	BinaryTree operator=(BinaryTree&) = delete;

	Node* getroot();
	Node* min(Node* current);
	Node* max(Node* current);
	Node* next(Node* current);
	Node* previous(Node* current);
	void insert(char* co, char* own, char* ph, char* addr, char* ty, Node*& cur);
	void insert(char* co, char* own, char* ph, char* addr, char* ty);
	bool search(char* key, MODE m, Node* current);
	bool search(char* key, MODE m);
	char* variant(MODE m, Node* current, int re_mode);
	void print(Node* current);
	void to_file(char* filename);
	void from_file(char* filename);
};

Node* BinaryTree::getroot()
{
	return root;
}

Node* BinaryTree::min(Node* current)
{
	if (current)
	{
		while (current->left)
		{
			current = current->left;
		}
	}

	return current;
}

Node* BinaryTree::max(Node* current)
{
	if (current)
	{
		while (current->right)
		{
			current = current->right;
		}
	}

	return current;
}

Node* BinaryTree::next(Node* current)
{
	Node* temp = nullptr;
	if (current)
	{
		if (current->right)
		{
			return min(current->right);
		}

		temp = current->parent;

		while (temp && current == temp->right)
		{
			current = temp;
			temp = temp->parent;
		}

	}

	return temp;
}

Node* BinaryTree::previous(Node* current)
{
	Node* temp = nullptr;
	if (current)
	{
		if (current->left)
		{
			return max(current->left);
		}

		temp = current->parent;

		while (temp && current == temp->left)
		{
			current = temp;
			temp = temp->parent;
		}
	}

	return temp;
}

void BinaryTree::insert(char* co, char* own, char* ph, char* addr, char* ty, Node*& cur)
{
	if (cur)
	{
		insert(co, own, ph, addr, ty, strcmp(cur->m_company, co) > 0 ? cur->left : cur->right);
		strcmp(cur->m_company, co) > 0 ? cur->left->parent = cur : cur->right->parent = cur;
	}
	else{
		cur = new Node(nullptr, nullptr, co, own, ph, addr, ty);
		cur->parent = nullptr;
	}
}

void BinaryTree::insert(char* co, char* own, char* ph, char* addr, char* ty)
{
	return insert(co, own, ph, addr, ty, root);
}

bool BinaryTree::search(char* key, MODE m, Node* current)
{
	cout << "Searching result for " << key << ":\n";
	current = min(current);
	int is_any = 0;
	while (current)
	{
		if (strcmp(key, variant(m, current, 0)) == 0)
		{
			printf_s("%-20s %-10s ", current->m_company, current->m_owner);
			printf_s("%-12s %-15s ", current->m_phone, current->m_address);
			printf_s("%-12s\n", current->m_type);
			is_any++;
		}
		current = next(current);
	}

	if (is_any == 0)
	{
		cout << "No such " << variant(m, current, 1);
		return false;
	}
	else{
		return true;
	}

}

bool BinaryTree::search(char* key, MODE m)
{
	return search(key, m, root);
}

char* BinaryTree::variant(MODE m, Node* current, int re_mode)
{
	if (re_mode == 0)
	{
		char* variants[5] = { current->m_company, current->m_owner, current->m_phone, current->m_address, current->m_type };
		return variants[m];
	}
	else if (re_mode == 1){
		char* variants[5] = { "company!\n", "owner!\n", "phone!\n", "address!\n", "type!\n" };
		return variants[m];
	}

}

void BinaryTree::print(Node* current)
{
	if (current)
	{
		print(current->left);
		printf_s("%-20s %-10s ", current->m_company, current->m_owner);
		printf_s("%-12s %-15s ", current->m_phone, current->m_address);
		printf_s("%-12s\n", current->m_type);
		print(current->right);
	}

}

void BinaryTree::to_file(char* filename)
{
	fstream f(filename, ios::out | ios::binary);
	if (!f)
	{
		cout << "ooops! Can not open file.\n";
		return;
	}

	Node* current = root;
	current = min(current);

	while (current)
	{
		f.write((char*)current->m_company, sizeof(current->m_company));
		f.write((char*)current->m_owner, sizeof(current->m_owner));
		f.write((char*)current->m_phone, sizeof(current->m_phone));
		f.write((char*)current->m_address, sizeof(current->m_address));
		f.write((char*)current->m_type, sizeof(current->m_type));

		current = next(current);
	}

	f.close();
}

void BinaryTree::from_file(char* filename)
{
	fstream f(filename, ios::in | ios::binary);
	if (!f)
	{
		cout << "oops! Can not open file.\n";
		return;
	}

	Node* current = root;
	char *co, *own, *ph, *addr, *ty;
	int a;
	int temp;
	char ch;

	while ((ch = f.peek()) != EOF)
	{
		temp = sizeof(current->m_company);
		co = new char[temp + 1];
		f.read((char*)co, temp);
		co[temp] = '\0';
		printf_s("%-20s ", co);

		temp = sizeof(current->m_owner);
		own = new char[temp + 1];
		f.read((char*)own, temp);
		own[temp] = '\0';
		printf_s("%-10s ", own);

		temp = sizeof(current->m_phone);
		ph = new char[temp + 1];
		f.read((char*)ph, temp);
		ph[temp] = '\0';
		printf_s("%-12s ", ph);

		temp = sizeof(current->m_address);
		addr = new char[temp + 1];
		f.read((char*)addr, temp);
		addr[temp] = '\0';
		printf_s("%-15s ", addr);

		temp = sizeof(current->m_type);
		ty = new char[temp + 1];
		f.read((char*)ty, temp);
		ty[temp] = '\0';
		printf_s("%-12s\n", ty);

		insert(co, own, ph, addr, ty);

		delete[] co;
		delete[] own;
		delete[] ph;
		delete[] addr;
		delete[] ty;
	}
}
int main()
{
	BinaryTree tree_1;

	tree_1.from_file("dz.dat");
	cout << endl;
	tree_1.search("\"The anaconda\"", COMPANY);
	tree_1.insert("\"The anaconda\"", "Laurence", "345-23-20", "33th st., 43", "Escort");
	tree_1.to_file("dz.dat");
	cout << endl;
	tree_1.print(tree_1.getroot());
	cout << endl;
	tree_1.search("\"The anaconda\"", COMPANY);

	/*
	tree_1.insert("\"Hello\"", "oleg", "322-22-22", "29th st., 21-4", "student");
	tree_1.insert("\"hi\"", "jora", "756-23-92", "38th st., 41-3", "player");
	tree_1.insert("\"hi\"", "vasja", "865-23-78", "19th st., 122", "tourist");
	tree_1.insert("\"Worn\"", "ivan", "294-34-59", "56th st., 12-1", "it");
	tree_1.insert("\"qwe\"", "katja", "865-33-93", "43th st., 23", "player");
	
	tree_1.to_file("dz.dat");
	*/
	return 0;
}