// ex4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <vector>
using namespace std;
bool IsPalindrom(string word);
void PalindromFilter(vector<string> words, int minLength)
{
	for (auto c : words)
	{
		if (c.size() >= minLength && (IsPalindrom(c) == 1))
		{
			cout << c << " ";
		}
	}
}
bool IsPalindrom(string word)
{
	for (int i = 0; i < word.size()/2; i++)
	{
		if (word[i] != word[word.size() - i - 1]) return false;
	}
	return true;
}
int main()
{
	vector<string> words;
	int minLength;
	//cin >> minLength;
	PalindromFilter({ "abacaba", "aba", "a" }, 5);
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
