#include <iostream>
#include <fstream>
#include "header.h"
#include<string>

enum Menu
{
	scan_tree_from_keyboard = 1,
	scan_tree_from_file,
	print_to_console,
	print_to_file,
	add_node,
	delete_node,
	poisk_node_key,
	excersise,
	comparison_trees,
	AVL_tree,
	add_AVL_tree,
	cout_AVL_tree,
	exit_program
	
};

enum Menu2
{
	ordered_print = 1,
	unordered_print,
	koncevoe_print
};

int main()
{
	setlocale(LC_ALL, "Russian");
	Tree<string> p;
	Tree<string> p1;
	BalancedTree<int> p3;
	int ans;
	do
	{
		cout << scan_tree_from_keyboard << " - Ввести дерево с клавиатуры" << endl
			<< scan_tree_from_file << " - Считать дерево из файла" << endl
			<< print_to_console << " - Вывод дерева в консоль" << endl
			<< print_to_file << " - Вывод дерева в файл" << endl
			<< add_node << " - Добавить узел" << endl
			<< delete_node << " - Удалить узел" << endl
			<< poisk_node_key << " - Поиск узла с заданным значнием ключа" << endl
			<< excersise << " - Искомое задание" << endl
			<< comparison_trees << " - Сравнение двух деревьев" << endl
			<< AVL_tree << " - Сбалансированное бинарное дерево" << endl
			<< add_AVL_tree << " - Добавить элемент в сбалансированное дерево" << endl
			<< cout_AVL_tree << " - Вывести сбалансированное дерево на экран" << endl
			<< exit_program << " - Выход из программы" << endl;
		cin >> ans;
		
		switch (ans)
		{
		case scan_tree_from_keyboard:
		{
			if (p.GetHead() != nullptr)
				p.~Tree();

			int size;
			string value;

			cout << "Введите искомое дерево (первый элемент считается корнем): ";
			/*перегрузка потока ввода*/
			cin >> p;
			break;
		}
		case scan_tree_from_file:
		{
			if (p.GetHead() != nullptr)
				p.~Tree();

			p.scan_file("derevo_ordered_scan.txt");
			break;
		}
		case print_to_console:
		{
			/*перегрузка потока вывода*/
			cout << "\n" << p << "\n" << endl;
			break;
		}
		case print_to_file:
		{
			int ans2;
			cout << "Выберите вариант вывода в файл: " << endl
				/*ordered_print - единственный вариант вывода, при котором правильно
				сканируется из этого же файла, так как при выводе корень дерева идет первый, а
				метод scan берет первый элемент за корень*/
				<< ordered_print << " - Прямой вывод в файл" << endl
				<< unordered_print << " - Обратный вывод в файл" << endl
				<< koncevoe_print << " - Концевой вывод в файл" << endl;
				cin >> ans2;

				switch (ans2)
				{
				case ordered_print:
				{
					ofstream fout("derevo_ordered_scan.txt");
					p.print_ordered(fout);
					fout.close();
					break;
				}
				case unordered_print:
				{
					ofstream fout("derevo_unordered.txt");
					p.print_unordered(fout);
					fout.close();
					break;
				}
				case koncevoe_print:
				{
					ofstream fout("derevo_koncevoe.txt");
					p.print_koncevoe(fout);
					fout.close();
					break;
				}
				}
				break;
		}
		case add_node:
		{
			string value;
			cout << "Введите ключ для добавления узла: ";
			cin >> value;
			p.add(value);
			break;
		}
		case delete_node:
		{
			string value;
			cout << "Введите ключ для удаления узла: ";
			cin >> value;
			p.RemoveNode(value);
			break;
		}
		case poisk_node_key:
		{
			string value;
			cout << "Введите ключ для поиска узла: ";
			cin >> value;
			if (p.search(value))
				cout << "\nЭлемент найден и находится в дереве.\n" << endl;
			else
				cout << "\nЭлемент не находится в дереве.\n" << endl;
			break;
		}
		case excersise:
		{
			int length;
			cout << "Введите число для задания: " << endl;
			cin >> length;
			p.keyLengthRemove(length);
			break;
		}
		case comparison_trees:
		{
			bool check = false;
			/*показываем с помощью перегрузки операции "==",
			что при присвоении одного дерева другому(p = p1)
			деревья получаются одинаковые*/
			p = p1;
			cout << "\nСравнение деревьев p и p1: ";
			if (p == p1)
			{
				cout << "Деревья одинаковые" << endl;
				check = true;
			}
			else
			{
				cout << "Деревья различные" << endl;
			}
			cout << endl;


			/*создаем дерево p3 отличное от p, чтобы показать,
			что перегрузка "==" работает верно*/
			Tree<string> p3;
			cin >> p3;

			cout << "\nСравнение деревьев p и p3: ";
			if (p1 == p3)
			{
				cout << "Деревья одинаковые" << endl;
				check = true;
			}
			else
			{
				cout << "Деревья различные" << endl;
			}
			cout << endl;
			break;
		}
		case AVL_tree:
		{
			int size;
			int value;
			cout << "Введите количество узлов в дереве: " << endl;
			cin >> size;
			for (int i = 0; i < size; i++)
			{
				cout << "Введите значение узла: ";
				cin >> value;
				p3.Add(value);
			}
			break;
		}
		case add_AVL_tree:
		{
			int value;
			cout << "Введите элемент, который хотите добавить в дерево: ";
			cin >> value;
			p3.Add(value);
			break;
		}
		case cout_AVL_tree:
		{
			cout << "Дерево, выведенное обратным обходом (лево-корень-право)" << endl;
			p3.PrintTree();
			cout << endl;
			break;
		}
		}
	} while (ans != exit_program);
	return 0;
}