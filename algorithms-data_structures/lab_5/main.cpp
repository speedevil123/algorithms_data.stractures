#include <iostream>
#include <fstream>
#include "header.h"

using namespace std;
enum Menu
{
	insert_elem = 1,
	scan_from_file,
	delete_elem,
	search_elem,
	print_to_display,
	print_to_file,
	comparisons_collisions,
	exit_programm
};
int main()
{
	setlocale(LC_ALL, "Russian");
	HashTable p;
	size_t ans, collisions = 0, comparisons = 0;


	do
	{
		cout << "Выберите пункт меню: " << endl
			<< insert_elem << " - Вставить идентификатор" << endl
			<< scan_from_file << " - Заполнить из файла" << endl
			<< delete_elem << " - Удалить идентификатор" << endl
			<< search_elem << " - Поиск идентификатора" << endl
			<< print_to_display << " - Вывод в консоль" << endl
			<< print_to_file << " - Вывод в файл" << endl
			<< comparisons_collisions << " - Количество сравнений и коллизий" << endl
			<< exit_programm << " - Выход из программы" << endl;

		cin >> ans;

		switch (ans)
		{
		case insert_elem:
		{
			string key_insert;
			cout << "Введите идентификатор для вставки: ";
			cin >> key_insert;
			while (p.search(key_insert, comparisons))
			{
				cout << "Идентификатор уже есть в таблице" << "\nВведите новый идентификатор: ";
				cin >> key_insert;
			}
			p.insert(key_insert, collisions);
			break;
		}
		case scan_from_file:
		{
			p.clear();
			string key_insert_file;
			ifstream fin("input.txt");
			if (!fin)
			{
				cout << "\nСканирование из файла" << "\033[31m" << " провалено\n" << "\033[0m" << endl;
				break;
			}
			while (getline(fin, key_insert_file))
			{
				if (p.search(key_insert_file, comparisons))
				{
					cout << "\nИдентификатор " << " << " << "\033[34m" << key_insert_file << "\033[0m" << " >> " << " уже есть в таблице" << "\nПропуск итерации...\n" << endl;
					continue;
				}
				p.insert(key_insert_file, collisions);
			}
			fin.close();
			cout << "\nСканирование из файла" << "\033[32m" << " завершено\n" << "\033[0m" << endl;
			break;
		}
		case delete_elem:
		{
			string key_delete;
			cout << "Введите идентификатор для удаления: ";
			cin >> key_delete;
			p.remove(key_delete);
			break;
		}
		case search_elem:
		{
			string key_search;
			cout << "Введите идентификатор для поиска: ";
			cin >> key_search;
			bool search_hash = p.search(key_search, comparisons);

			if (search_hash)
			{
				cout << "\nИндентификатор найден\n" << endl;
			}
			else
			{
				cout << "\nИдентификатор не найден\n" << endl;
			}
			break;
		}
		case print_to_display:
		{
			cout << p;
			break;
		}
		case print_to_file:
		{
			ofstream fout("output.txt");
			if (!fout)
			{
				cout << "\nВывод в файл" << "\033[31m" << " провален\n" << "\033[0m" << endl;
			}
			p.print(fout);
			fout.close();
			cout << "\nВывод в файл" << "\033[32m" <<  " завершен\n" << "\033[0m" << endl;
			break;
		}
		case comparisons_collisions:
		{
			cout << "\nКоличество коллизий: " << collisions << "\nКоличество сравнений: " << comparisons << "\n" << endl;
			break;
		}
		}
	} while (ans != exit_programm);
	p.~HashTable();
	return 0;
};