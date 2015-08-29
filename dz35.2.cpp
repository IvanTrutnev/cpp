#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
	int n = 11;
	vector< vector <int> > a(n);
	int i, j;

	for (i = 0; i < n; i++)
		a[i].resize(n);

	for (i = 1; i < n; i++){
		for (j = 1; j < n; j++){
			a[i][j] = i * j;
		}
	}
	for (i = 1; i < n; i++)
	{
		for (int j = 1; j < n; j++)
		{
			cout << setw(5) << a[i][j];
		}
		cout << endl << endl;
	}
	return 0;
}