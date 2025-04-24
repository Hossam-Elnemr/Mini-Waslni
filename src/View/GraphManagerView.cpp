#include "GraphManagerView.h"

pair<string, string> View::GraphManagerView::getPathFindingInfo()
{
	string from, to;
	cout << "Enter from city (without spaces):";
	getline(cin, from);
	do {
		cout << "Don't use spaces.. Try again: ";
		getline(cin, from);
	} while (Tools::isContainSpaces(from));

	cout << "\nEnter to city (without spaces):";
	getline(cin, to);
	do {
		cout << "Don't use spaces.. Try again: ";
		getline(cin, to);
	} while (Tools::isContainSpaces(to));

	return { from , to };
}

View::GraphManagerView::~GraphManagerView()
{
}
