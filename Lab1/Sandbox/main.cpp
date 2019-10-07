#include <iostream>

using namespace std;

int main()
{
	int x, y;
	cout << "x=";
	cin >> x;
	cout << "y=";
	cin >> y;
	if (y <= x)
	{
		y = 0;
		cout << "y=" << y;
	}
	if (x <= y)
	{
		x = 0;
		cout << "x=" << x;
	}
	return 0;
}