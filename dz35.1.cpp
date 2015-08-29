#include <vector>
#include <iostream>

using namespace std;

int main()
{
	const int n = 10;
	vector<int> a(n);

	for (vector<int>::size_type i =0 ; i != a.size(); ++i)
	{
		a[i] = i*i;
		cout << a[i] << " ";
	}
	cout << endl;

	return 0;
}