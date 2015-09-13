#include <iostream>
#include <string>

using namespace std;

int main()
{
	string inf;
	string post;

	cout << "Infix: \t";
	getline(cin, inf);
	inf.append(1u, '!');

	char* stack_1 = new char[inf.length()];
	int idx_top = -1;

	int i = 0;
	while (inf[i] != '\0'){
		switch (inf[i])
		{
		case '!':
			if (idx_top == -1)
			{
				cout << "OK!\n";
				++i;
			}
			else if (stack_1[idx_top] == '+' || stack_1[idx_top] == '-' || stack_1[idx_top] == '*' || stack_1[idx_top] == '/'){
				post.append(1u, stack_1[idx_top--]);
			}
			else if (stack_1[idx_top] == '('){
				cout << "Error!\n";
				exit(0);
			}
			break;
		case '+':
		case '-':
			if (idx_top == -1 || stack_1[idx_top] == '(')
			{
				stack_1[++idx_top] = inf[i++];
			}
			else if (stack_1[idx_top] == '+' || stack_1[idx_top] == '-' || stack_1[idx_top] == '*' || stack_1[idx_top] == '/'){
				post.append(1u, stack_1[idx_top--]);
			}
			break;

		case '*':
		case '/':
			if (stack_1[idx_top] == '+' || stack_1[idx_top] == '-' || idx_top == -1 || stack_1[idx_top] == '(')
			{
				stack_1[++idx_top] = inf[i++];
			}
			else if (stack_1[idx_top] == '*' || stack_1[idx_top] == '/'){
				post.append(1u, stack_1[idx_top--]);
			}
			break;
		case '(':
			stack_1[++idx_top] = inf[i++];
			break;
		case ')':
			if (idx_top == -1)
			{
				cout << "wtf!\n";
				exit(0);
			}
			else if (stack_1[idx_top] == '+' || stack_1[idx_top] == '-' || stack_1[idx_top] == '*' || stack_1[idx_top] == '/'){
				post.append(1u, stack_1[idx_top--]);
			}
			else if (stack_1[idx_top--] == '('){
				++i;
			}
			break;
		default:
			post.append(1u, inf[i++]);
			break;
		}

	}

	inf.erase(inf.find('!'));
	cout << "postfix: " << post << endl;
	delete[] stack_1;

	double* stack_2 = new double[post.length()];
	idx_top = -1;
	int j = 0;

	while (post[j] != '\0')
	{
		if ((int)post[j] > 47 && (int)post[j] < 58)
		{
			stack_2[++idx_top] = (double)post[j] - 48;
		}
		else{
			double second = stack_2[idx_top];
			double first = stack_2[idx_top - 1];
			switch (post[j])
			{
			case '+':
				stack_2[--idx_top] = first + second;
				break;
			case '-':
				stack_2[--idx_top] = first - second;
				break;
			case '*':
				stack_2[--idx_top] = first * second;
				break;
			case '/':
				stack_2[--idx_top] = first / second;
				break;
			default:
				break;
			}
		}
		++j;
	}

	cout << endl << inf << " = " << stack_2[0] << endl;
	delete[] stack_2;

	return 0;
}