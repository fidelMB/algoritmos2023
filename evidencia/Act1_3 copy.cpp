#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

struct message {
	int year;
	int month;
	int day;
	int time;
	long long ip;
	string info;
};

/*
Se combinan dos vectores ordenados en uno solo
@param un vector con n valores enteros
@return se modifica el vector dado directamente, no se regresa ningun valor
Tiempo: O(n)
Espacio: O(n)
*/
void merge(vector<message>& v, int l, int r) {
	if (l == r)
		return;

	int mid = l + (r - l) / 2;
	int rIndex = 0, lIndex = 0, lSize = mid - l + 1, rSize = r - mid;
	int vIndex = l;
	vector<message> leftV(lSize);
	vector<message> rightV(rSize);

	for (int i = l; i <= mid; i++)
	{
		leftV[i - l] = v[i];
	}
	for (int i = mid + 1; i <= r; i++)
	{
		rightV[i - mid - 1] = v[i];
	}


	while (lIndex < lSize && rIndex < rSize)
	{
		if (leftV[lIndex].ip < rightV[rIndex].ip) {
			v[vIndex] = leftV[lIndex];
			lIndex++;
		}
		else
		{
			v[vIndex] = rightV[rIndex];
			rIndex++;
		}
		vIndex++;
	}

	while (lIndex < lSize)
	{
		v[vIndex] = leftV[lIndex];
		lIndex++;
		vIndex++;
	}

	while (rIndex < rSize)
	{
		v[vIndex] = rightV[rIndex];
		rIndex++;
		vIndex++;
	}

}

/*
Se ordena una seccion de un vector de n valores con el metodo de merge
@param un vector con n valores enteros
@return se modifica el vector dado directamente, no se regresa ningun valor
Tiempo: O(n*log(n))
Espacio: O(n)
*/
void mergeS(vector<message>& v, int l, int r) {
	if (l >= r)
		return;

	int mid = l + (r - l) / 2;
	mergeS(v, l, mid);
	mergeS(v, mid + 1, r);
	merge(v, l, r);

	return;
}

/*
Ordenamiento de un vector mediante el metodo de merge
@param un vector con n valores enteros
@return se modifica el vector dado directamente, no se regresa ningun valor
Tiempo: O(n*log(n))
Espacio: O(n)
*/
void mergeSortByIp(vector<message>& v) {
	mergeS(v, 0, v.size() - 1);
}

long long ipToLong(string ip1, string ip2, string ip3, string ip4) {
	string current, ip = "";
	vector<string> ips = { ip1, ip2, ip3, ip4 };

	if (ips[0][0] == ' ')
		ips[0].erase(0, 1);

	for (int i = 0; i < 4; i++)
	{
		current = ips[i];

		if (current.length() == 1) {
			ip += "00" + current;
		}
		else if (current.length() == 2) {
			ip += "0" + current;
		}
		else {
			ip += current;
		}
	}
	
	return stoll(ip);
}

void fileToVector(vector<message>& v, string fileName) {
	fstream bitacora;
	message temp;
	string line, time, ip1, ip2, ip3, ip4;
	map<string, int> months = { {"Jan", 1}, {"Feb", 2}, {"Mar", 3}, {"Apr", 4}, {"May", 5}, {"Jun", 6}, {"Jul", 7}, {"Aug", 8}, {"Sep", 9}, {"Oct", 10}, {"Nov", 11}, {"Dec", 12} };

	bitacora.open(fileName, ios::in);

	while (getline(bitacora, line, ' ')) {
		temp.year = stoi(line);
		getline(bitacora, line, ' ');
		temp.month = months[line];
		getline(bitacora, line, ' ');
		temp.day = stoi(line);

		time = "";
		getline(bitacora, line, ':');
		time += line;
		getline(bitacora, line, ':');
		time += line;
		getline(bitacora, line, ':');
		time += line;
		temp.time = stoi(time);

		getline(bitacora, ip1, '.');
		getline(bitacora, ip2, '.');
		getline(bitacora, ip3, '.');
		getline(bitacora, ip4, ' ');
		temp.ip = ipToLong(ip1, ip2, ip3, ip4);
		
		getline(bitacora, line, ':');
		getline(bitacora, line);
		line.erase(0, 1);
		temp.info = line;
		
		v.push_back(temp);	
	}

}

void toTxtFile(vector<message> v, string fileName) {
	fstream bitacora;
	map<int, string> months = { {1, "Jan"}, {2, "Feb"}, {3, "Mar"}, {4, "Apr"}, {5, "May"}, {6, "Jun"}, {7, "Jul"}, {8, "Aug"}, {9, "Sep"}, {10, "Oct"}, {11, "Nov"}, {12, "Dec"} };
	int hour, min, sec;
	string ipString;
	
	bitacora.open(fileName, ios::out);

	for (int i = 0; i < v.size(); i++)
	{
		bitacora << v[i].year << " " << months[v[i].month] << " ";
		if (v[i].day < 10)
			bitacora << '0';

		bitacora << v[i].day << " ";
			
		hour = v[i].time / 10000;
		min = (v[i].time / 100) % 100;
		sec = v[i].time % 100;
		
		if (hour < 10)
			bitacora << "0";
		bitacora << hour << ":";
		if (min < 10)
			bitacora << "0";
		bitacora << min << ":";
		if (sec < 10)
			bitacora << "0";
		
		bitacora << sec << " | IP: ";
		
		ipString = to_string(v[i].ip);
		while (ipString.length() != 12)
			ipString = "0" + ipString;
		
		bitacora << stoi(ipString.substr(0, 3)) << '.' << stoi(ipString.substr(3, 3)) << '.' << stoi(ipString.substr(6, 3)) << '.' << stoi(ipString.substr(9, 3));
		bitacora << " | INFO: " << v[i].info << endl;
	}

	bitacora.close();
}

int binarySearchNextBiggest(vector<message> v, long long target)
{
	int start = 0, end = v.size()-1;
	int ans = end+1;
	
	while (start <= end)
	{
		int mid = (start + end) / 2;

		if (v[mid].ip <= target)
			start = mid + 1;
		else
		{
			ans = mid;
			end = mid - 1;
		}
	}

	return ans;
}

void printFormattedInfo(message m) {
	map<int, string> months = { {1, "Jan"}, {2, "Feb"}, {3, "Mar"}, {4, "Apr"}, {5, "May"}, {6, "Jun"}, {7, "Jul"}, {8, "Aug"}, {9, "Sep"}, {10, "Oct"}, {11, "Nov"}, {12, "Dec"} };
	int hour, min, sec;
	string ipString;
	cout << m.year << " " << months[m.month] << " ";
	if (m.day < 10)
		cout << '0';

	cout << m.day << " ";

	hour = m.time / 10000;
	min = (m.time / 100) % 100;
	sec = m.time % 100;

	if (hour < 10)
		cout << "0";
	cout << hour << ":";
	if (min < 10)
		cout << "0";
	cout << min << ":";
	if (sec < 10)
		cout << "0";

	cout << sec << " | IP: ";

	ipString = to_string(m.ip);
	while (ipString.length() != 12)
		ipString = "0" + ipString;

	cout << stoi(ipString.substr(0, 3)) << '.' << stoi(ipString.substr(3, 3)) << '.' << stoi(ipString.substr(6, 3)) << '.' << stoi(ipString.substr(9, 3));
	cout << " | INFO: " << m.info << endl;
}


int main()
{
	vector<message> messages;
	string ipStart, ipEnd;
	long long ipS, ipE;
	int ip, endIndex, startIndex;
	string ipString;
	vector<string> ipDivided;
	
	fileToVector(messages, "bitacoraelb.txt");
	mergeSortByIp(messages);
	
	cout << "Introduzca IP de inicio: ";
	cin >> ipStart;
	cout << "Introduzca IP de fin: ";
	cin >> ipEnd;
	
	ipString = "";
	for (int i = 0; i < ipStart.length(); i++)
	{
		if (ipStart.at(i) == '.')
		{
			ipDivided.push_back(ipString);
			ipString = "";
		}
		else
		{
			ipString += ipStart.at(i);
		}
	}
	ipDivided.push_back(ipString);
	ipString = "";

	ipS = ipToLong(ipDivided[0], ipDivided[1], ipDivided[2], ipDivided[3]);
	ipDivided.clear();

	for (int i = 0; i < ipEnd.length(); i++)
	{
		if (ipEnd.at(i) == '.')
		{
			ipDivided.push_back(ipString);
			ipString = "";
		}
		else
		{
			ipString += ipEnd.at(i);
		}
	}
	ipDivided.push_back(ipString);

	ipE = ipToLong(ipDivided[0], ipDivided[1], ipDivided[2], ipDivided[3]);

	endIndex = binarySearchNextBiggest(messages, ipE);
	startIndex = binarySearchNextBiggest(messages, ipS-1);

	for (int i = startIndex; i < endIndex; i++)
	{
		printFormattedInfo(messages[i]);
	}

	
	toTxtFile(messages, "bitacoraelbSorted.txt");
}
