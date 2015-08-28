#include <iostream>

using namespace std;

class Timer
{
	int value;
	int min;
	int max;
public:
	Timer()
	{
		value = 0;
		min = 0;
		max = 100;
	}
	~Timer()
	{

	}
	void ShowTimer()
	{
		cout << "Timer value = " << value << endl;
	}
	void MaxMin(int m1, int m2)
	{
		min = m1;
		max = m2;
	}
	void ValuePlus()
	{
		value++;
		if (value>max){
			value = min;
		}
	}
}


int main()
{
	Timer t;
	int min, max;
	cout << "Enter min timer value" << endl;
	cin >> min;
	cout << "Enter max timer value" << endl;
	cin >> max;
	t.MaxMin(min, max);
	int des;
	int f = 0;
	do{
		cout << "Enter \n 1, if you ned up timer value,\n 2, for show timer value,\n 3, if you ned to exit.";
			cin >> des;
		system("cls");
		if (des == 1){
			t.ValuePlus;
			t.ShowTimer;
		}
		else if (des == 2){
			t.ShowTimer;
		}
		else if (des == 3){
			f++;
		}
		else{
			cout << "Enter correct number";
		}
	} while (f = 0);
	return 0;
}