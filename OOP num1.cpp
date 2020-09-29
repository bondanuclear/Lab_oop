// OOP num1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cstdlib>
#include <map>
#include <fstream>
#define INF 0x3F3F3F3F
#define MAX 110

using namespace std;
template<class T>

class Graph 
{
private: 
	int Size;
	T** adj_matrix;
	//int nmbVrtx = 0;
	
	
public:
	Graph()
	{
		Size = 0;
		adj_matrix = nullptr;
	}
	Graph( int size) // конструктор
	{
		Size = size;
		adj_matrix = new T * [Size];
		for (int i = 0; i < Size; i++)
		{
			adj_matrix[i] = new T[Size];
			for (int j = 0; j < Size; j++)
			{
				//nmbVrtx++;
				adj_matrix[i][j] = 0;
			}
		}
	}
	Graph( T value , int size) // конструктор для DaT
	{
		Size = size;
		adj_matrix = new T * [Size];
		for (int i = 0; i < Size; i++)
		{
			adj_matrix[i] = new T[Size];
			for (int j = 0; j < Size; j++)
			{
				//nmbVrtx++;
				adj_matrix[i][j] = value;
			}
		}
	}
	Graph(const Graph& other)// конструктор копіювання
	{
		Size = other.Size;
		adj_matrix = new T * [Size];
		for (int i = 0; i < Size; i++)
		{
			adj_matrix[i] = new T[Size];
			for (int j = 0; j < Size; j++)
			{
				adj_matrix[i][j] = other.adj_matrix[i][j];
			}
		}
	}
	T GetM(int i, int j) // геттер
	{
		if (Size > 0) return adj_matrix[i][j];
		//else return 0;
	}
	void SetM(int i, int j, T value) // сеттер
	{
		adj_matrix[i][j] = value;
	}
	void PrintGraph(string Graph_Name) // Надрукувати граф
	{
		cout << "Graph: " << Graph_Name << endl;
		for (int i = 0; i < Size; i++)
		{
			for (int j = 0; j < Size; j++)
				cout << adj_matrix[i][j] << " ";
			cout << endl;
		}
		cout << "================================ " << endl;
	}
	
	Graph operator=(const Graph& other) // перевантажений оператор =
	{
		if (Size > 0)
		{
			for (int i = 0; i < Size; i++)
			{
				delete[] adj_matrix[i];
			}
			delete[] adj_matrix;
		}
		Size = other.Size;
		adj_matrix = new T * [Size];
		for (int i = 0; i < Size; i++)
		{
			adj_matrix[i] = new T[Size];
			for (int j = 0; j < Size; j++)
			{
				adj_matrix[i][j] = other.adj_matrix[i][j];
			}
		}
		return *this;
	}
	Graph add_edge(int n, int m, T value) // додавання ребра
	{
		
		for (int i = 0; i < Size; i++)
		{
			for (int j = 0; j < Size; j++)
			{
				if (adj_matrix[i][j] == adj_matrix[n][m])
					adj_matrix[i][j] = value;
				
				
			}
		}
		return *this;
	}

	Graph del_edge(int n, int m) // видалення ребра
	{

		for (int i = 0; i < Size; i++)
		{
			for (int j = 0; j < Size; j++)
			{
				if (adj_matrix[i][j] == adj_matrix[n][m])
					adj_matrix[i][j] = 0;

				
			}
		}
		return *this;
	}
	Graph add_vertex(int vertex) // Додавання вершини
	{
		this->Size = vertex;
		//
		for (int i = 0; i < Size - 1; i++)
		{
			
			for (int j = Size - 1; j < Size; j++)
			{
				adj_matrix[i][j] = 0;


			}
		}
	
		for (int i = (Size - 1); i < Size; i++)
		{
			adj_matrix[i] = new T[Size];
			for (int j = 0; j < Size;j++)
				cin >> adj_matrix[i][j];
		}
		return *this;
	}
	Graph del_vertex(int vertex) // видалення вершини 
	{
		for (int i = vertex; i <= vertex; i++)
		{
			for (int j = 0; j < Size; j++)
			{
				adj_matrix[i][j] = 0;
			}
		}
		for (int i = 0; i < Size; i++)
		{
			for (int j = vertex; j <= vertex; j++)
			{
				adj_matrix[i][j] = 0;
			}
		}


			return *this;
	}
	void isConnected() // Перевірка на зв'язність
	{
		int k= 0;
		int amount=0;
		for (int i = 0; i < Size; i++)
		{
			for (int j = 0; j < Size; j++)
			{
				amount++; // Загальна кількість
				if (i == j) continue; // пропускаємо елементи головної матриці
				
				if (adj_matrix[i][j] == 0) k++; // кількість ребер, що = 0
			}
		}
		//cout <<" 0 elements " << k << " " << endl;
		//cout << " amount: " << amount << endl;
		if (amount - k == Size) cout << " Not connected \n"; // Якщо false , то не зв'язний
		else cout << "Connected \n" ;
	}
	int Radius() // радіус графа
	{
		int Rad = INF;
		for (int i = 0; i < Size; i++)
		{
			int max = 0;
			for (int j = 0; j < Size; j++)
			{
				if (adj_matrix[i][j] > max) max = adj_matrix[i][j];
				if (max < Rad) Rad = max;

			}
		}
		return Rad;
	}
	int Diameter() // діаметр графа
	{
		int diam = 0;
		for (int i = 0; i < Size; i++)
		{
			int max = 0;
			for (int j = 0; j < Size; j++)
			{
				if (adj_matrix[i][j] > max) max = adj_matrix[i][j];

				if (max > diam) diam = max;
			}
		}
		return diam;
	}
	void DFS(int st) // алгоритм пошуку в глибину
	{
		int r;
		bool* visited;
		visited = new bool [Size];
		cout << st + 1 << " "; // стартовий вузол
		visited[st] = true;
		for (r = 0; r <= Size; r++)
			if ((adj_matrix[st][r] != 0) && (!visited[r]))
				DFS(r);
		delete[]visited;
	}
	void Dijkstra(int st) // Алгоритм Дійкстри пошуку найкоротшого шляху
	{
		bool *visited = new bool[Size];
		int *distance = new int[Size];
		int count, index, i, u;
		int m = st++;
		for (int i = 0;i < Size; i++)
		{
			distance[i] = INT_MAX;
			visited[i] = false;
		}
		distance[st] = 0;
		for (count = 0; count < Size - 1; count++)
		{
			int min = INT_MAX;
			for (int i = 0; i < Size; i++)
				if (!visited[i] && distance[i] <= min)
				{
					min = distance[i]; index = i;
				}
			u = index;
			visited[u] = true;
			for (i = 0; i < Size; i++)
				if (!visited[i] && adj_matrix[u][i] && distance[u] != INT_MAX && distance[u] + adj_matrix[u][i] < distance[i])
					distance[i] = distance[u] + adj_matrix[u][i];
		}
		cout << "Вартість шляху від з початкової вершини до решти вершин:\t\n";
		for (i = 0; i < Size; i++) if (distance[i] != INT_MAX)
			cout << m << " > " << i + 1 << " = " << distance[i] << endl;
		else cout << m << " > " << i + 1 << " = " << "маршрут недоступний" << endl;
		delete[] visited;
		delete[] distance;
	}

	~Graph() // деструктор
	{
		//Size = nmbVrtx;
		if (Size > 0)
		{
			for (int i = 0; i < Size; i++)
			{
				//cout << "destructor i " << this << endl;
				delete[] adj_matrix[i];
			}
			//cout << "destructor[] " << endl;
			delete[] adj_matrix;
		}
	}
};
class DaT
{
private:
	string date;
	int day;
	int year;
	int month;
	int hours;
	int minutes;
	int seconds;
	
public:
	DaT()
	{
		date = "";
		day = 0;
		year = 0;
		month = 0;
		hours = 0;
		minutes = 0;
		seconds = 0;
	}
	DaT(string date,int day, int month, int year, int hours, int minutes, int seconds )
	{
		this->date = date;
		this->day = day;
				this->year = year;
				this->month = month;
				this->hours = hours;
				this->minutes = minutes;

				this->seconds = seconds;
			}
	DaT(long int n, long int n1, long int n2, string h, string m, string s) // альтернативний ввід дати через бінарний вигляд та часу через римську систему числення :)
	{

		//cout << "Введіть дату в бінарному вигляді: " << endl;
		//cout << "Введіть день:  " << endl;
		//cin >> n;
		cout << n << " in decimal = " << convertBinaryToDecimal(n) << endl;
		this->day = convertBinaryToDecimal(n);
		cout << "Введіть місяць:  " << endl;
		//cin >> n1;
		cout << n1 << " in decimal = " << convertBinaryToDecimal(n1) << endl;
		this->month = convertBinaryToDecimal(n1);
		cout << "Введіть рік:  " << endl;
		//cin >> n2;
		cout << n2 << " in decimal = " << convertBinaryToDecimal(n2) << endl;
		this->year = convertBinaryToDecimal(n2);

		this->hours = romanToInt(h);
		this->minutes = romanToInt(m);
		this->seconds = romanToInt(s);
	}
	void printDate() // друк
	{
		cout <<"Day: " << date << " "  << day << "." << month << "." << year << endl;
		cout << hours << " Hours " << minutes << " Minutes " << seconds << " Seconds " << endl;
	}
	bool isCorrect()// перевірка на правильність введення дати,...
	{
		if ((day > 31) || (month > 12) || (hours > 24) || (minutes > 60) || (seconds > 60)) return 0;
		else return 1;
	}
void Date() // День тижня заданої дати
	{
	int total = 0;
		cout << "Today is " << this->date;
		cout << " the ";
		if ((this->day == 1) || (this->day == 21) || (this->day == 31)) cout << day << "st" << endl;
		else if ((this->day == 2) || (this->day == 22)) cout << day << "nd" << endl;
		else if ((this->day == 3) || (this->day == 23))cout << day << "rd" << endl;
		else cout << day << "th" << endl;
	}
/*void date_difference(int day, int month, int year, int hours, int minutes, int seconds) //  різниця між датами - не працює
{
	int r_day, r_month, r_year, r_hours, r_minutes, r_seconds; // результати
	
	if ( (this->month >= month) && (this->day > day))
		cout << " year: " << endl;
	else
	{
		r_year = year - this->year;
		cout << "r_year" << r_year << endl;
	}
	if (month >= this->month && day >= this->day) r_month = month - this->month;
	else r_month = 12 - (this->month - month);
	//
	cout << "month" << r_month;

}*/
int number_of_week_m() // номер тижня в місяці
{
	cout << "Number of week in a month" << endl;
	return this->day / 7;
	
}
int number_of_week_y() // номер тижня в році
{
	int total = 0;
	const int m[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
	for (int i = 0; i < (this->month-1); i++)
	{
		total += m[i];
	}

	if (((this->year % 4 == 0 && this->year % 100 != 0) || this->year % 400 == 0) && this->month > 2 )
	{
		++total;
	}
	
	return (total / 7)+(this->day / 7);
}
int convertBinaryToDecimal(long long n) // binary to decimal
{
	int decimalNumber = 0, i = 0, remainder;
	while (n != 0)
	{
		remainder = n % 10;
		n /= 10;
		decimalNumber += remainder * pow(2, i);
		++i;
	}
	return decimalNumber;
}
int romanToInt(string s) // Перевід з римської в арабську систему числення
{
	int sum = 0;

	map<char, int> container = { {'I', 1}, {'V', 5},{'X', 10},{'L', 50},
	{'C', 100},{'D', 500},{'M', 1000} };
	for (int i = 0; i < s.length(); i++)
	{
		if (container[s[i + 1]] > container[s[i]])
		{
			sum = sum - container[s[i]];
		}
		else sum = container[s[i]] + sum;



	}
	return sum;
}
void HoursSubtraction(int n) // віднімання годин
{
	if (this->hours < n) cout << 24 - (n - this->hours);
	else
	this->hours -= n;
	if (this->hours == 0) this->hours = 24;
	
}
void HoursAdd(int n) // додавання годин
{
	if ((this->hours + n) > 24) this->hours = 0 + (n - (24 - this->hours));
	else  this->hours + n;
	//if (this->hours == 24) this->hours = 0;
}
DaT time_zone() // підтримка різних часових поясів
{
	cout << "Зараз ви знаходитесь у східноєвропейському часовому поясі " << endl;
	cout << "На який часовий пояс бажаєте перейти? " << endl;
	cout << "[1] - Центральноєвропейський (-1 година)\n [2] -  Західноєвропейський час (-2 години)\n [3] - Московський час (+1 година)" << endl;
	string time_zone;
	cin >> time_zone;
	if (time_zone == "1") HoursSubtraction(1);
	else
		if (time_zone == "2") HoursSubtraction(2);
		else if (time_zone == "3") HoursAdd(1);
	return *this;
}
DaT JulianDate() // Юліанський календар
{
	const int m[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	int n = 13;
	if (this->day < 14 && this->month != 1)
	{
		n = (13 - this->day);
		this->day = m[this->month - 2] - n;
		this->month--;
	}
	else 
	if (this->day < 14 && this->month == 1)
	{
		n = (13 - this->day);
		this->day = m[11] - n;
		this->month = 12;
		this->year--;
	}
	else
	this->day -= 13;
	cout << "Юліанівський календар" << endl;
	return *this;
}
void Julian_day() // номер юліанського дня за григоріанським календарем
{
	int a;
	a = (14 - this->month) / 12;
	int y;
	y = this->year + 4800 - a;
	int m;
	m = this->month + (12 * a) - 3;
	int JDN;
	JDN = this->day + (153 * m + 2) / 5 + 365 * y + (y / 4) - (y / 100) + (y / 400) - 32045; //Вычисление номера юлианского дня (JDN) по дате григорианского календаря - 
	cout << "JDN: " << JDN << endl; // я сам не дуже зрозумів, що це, але чому б ні))
}
friend void read_from_file(const DaT& a);
};


void Add_to_file(const DaT& a) // запис до файлу
{
	string path = "Text.txt";
	ofstream fout;
	fout.open(path, ofstream::app);
	if (!fout.is_open())
	{
		cout << "Error" << endl;

	}
	else
	{
		cout << "File is opened" << endl;
		fout.write((char*)&a, sizeof(DaT));
	}
	fout.close();
}
void read_from_file(const DaT & a) // зчитування з файлу
{
	string path = "Text.txt";

	ifstream fin;
	fin.open(path);
	if (!fin.is_open())
	{
		cout << "Error" << endl;
	}
	else
	{
		while (fin.read((char*)&a, sizeof(DaT)))
		{
			cout << "Day: " << a.date << " " << a.day << "." << a.month << "." << a.year << endl;
			cout << a.hours << " Hours " << a.minutes << " Minutes " <<a.seconds << " Seconds " << endl;
		}
	}
}
void graph()
{
	Graph<int> a(3);
	int v;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cin >> v;
			a.SetM(i, j, v);
		}
	}
	a.DFS(1);
	cout << endl;
	a.add_edge(0, 0, 5);
	a.del_edge(2, 1);
	cout << a.Diameter() << endl;
	cout << a.Radius() << endl;
	a.Dijkstra(1);
	cout << endl;
	a.isConnected();
    a.del_vertex(2);
	a.PrintGraph("Graph A");
	Graph<int> b(3);
	b = a;
	b.PrintGraph("Graph B:");
}
void dat()
{
	DaT a("Tuesday", 15, 4, 2020, 13, 45, 54);
	a.printDate();
	cout << a.isCorrect();
	cout << endl;
	cout << a.number_of_week_m();
	cout << endl;

	cout << a.number_of_week_y();
	cout << endl;
	a.time_zone();
	a.Date();
	a.printDate();
	cout << endl;
	a.JulianDate();
	a.Julian_day();
	a.printDate();
	a.number_of_week_y();
}
int main()
{
	setlocale(LC_CTYPE, "ukr");
	graph();
	dat();
	
	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
