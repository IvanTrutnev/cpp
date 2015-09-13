#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	char figures[10];
	char ch;
	int i = 0;

	while ((ch = cin.get()) != '\n')
	{
		figures[i] = ch;
		++i;
	}

	try{
		if (i - 1 > 10)
		{
			throw "Your number is bigger !\n";
		}
	}

	catch (const char* s)
	{
		cout << s << endl;
		exit(0);
	}

	int number = 0;
	int power = pow(10, i - 1);
	char max_int[10] = { '3', '1', '2', '1', '4', '8', '9', '1', '4', '5' };

	for (int j = 0; j < i; ++j)
	{
		try{
			if (i == 10 && (figures[j] - 48) >(max_int[j] - 48))
			{
				throw "Your number is still bigger t!\n";
			}
			else{
				number += (figures[j] - 48) * power;
				power /= 10;
			}
		}

		catch (const char* s)
		{
			cout << s << endl;
			exit(0);
		}
	}


	cout << "\nYour integer is: " << number << endl;


	return 0;
}