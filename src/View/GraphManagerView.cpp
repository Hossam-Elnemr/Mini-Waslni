#include "GraphManagerView.h"

pair< vector<string> , vector<tuple<string, string, int , bool> > > View::GraphManagerView::getGraphInfo()
{
	int n, m;
	cout << "Enter number of cities: ";
	cin >> n;
	cout << "\nEnter number of edges: ";
	cin >> m;

	vector<string> cities;
	while (n--) {
		cout << "Enter city name (without spaces): " << endl;
		//cin.ignore();
		string city;
		cin >> city;


		//cout << endl;
		/*cin.ignore();
		while (Tools::isContainSpaces(city)) {
			cout << "Don't use spaces.. Try again: ";
			getline(cin, city);
			cin.ignore();
		} */

		cities.push_back(city);
	}


	vector< tuple<string, string, int ,bool> > edges;

	while (m--) {
		string src, dest;
		int length;
		bool isDirected;
		cout << "Enter edge source city (without spaces): "<<endl;
		cin >> src;
		//cin.ignore();
		//getline(cin, src);
		/*while (Tools::isContainSpaces(src)) {
			cout << "Don't use spaces.. Try again: ";
			getline(cin, src);
		}*/


		cout << "\nEnter edge destination city (without spaces): ";
		cin >> dest;
		//cin.ignore();
		//getline(cin, dest);
		
		/*while (Tools::isContainSpaces(dest)) {
			cout << "Don't use spaces.. Try again: ";
			getline(cin, dest);
		}*/

		cout << "\nEnter edge length: ";
		cin >> length;

		cout << "\nIs the edge directed? (1 for yes, 0 for no): ";
		cin >> isDirected;

		edges.push_back({ src , dest , length , isDirected });
	}

	
	return  { cities , edges };
}

pair<string, string> View::GraphManagerView::getPathFindingInfo()
{
	string from, to;
	cout << "Enter from city (without spaces):";
	//getline(cin, from);
	cin >> from;
	
	while (Tools::isContainSpaces(from)) {
		cout << "Don't use spaces.. Try again: ";
		getline(cin, from);
	}

	cout << "\nEnter to city (without spaces):";
	//getline(cin, to);
	cin >> to;
	
	while (Tools::isContainSpaces(to)) {
		cout << "Don't use spaces.. Try again: ";
		getline(cin, to);
	}

	return { from , to };
}

int View::GraphManagerView::showMenu(vector<string> menu)
{
	for (const auto& item : menu) {
		cout << item << endl;
	}
	int choice;
	cout << "Enter your choice: ";
	cin >> choice;
	cout << endl;

	return choice;
}

View::GraphManagerView::~GraphManagerView()
{
}
