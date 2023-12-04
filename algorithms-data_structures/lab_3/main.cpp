#include <iostream>
#include "List1.h"

using namespace std;

enum Menu
{
	scan_from_keyboard,
	build_polojitelny_array,
	print_to_display_1arr,
	print_to_display_2arrs,
	insert_proizv_index,
	delete_proizv_index,
	find_index_po_znach,
	find_elem_po_index,
	exit_program
};
int main()
{
	system("chcp 1251");
	int ans;
	List1<int> L1;
	List1<int> L2;

	do
	{
		cout << "Выберите пункт меню: " << endl
			<< scan_from_keyboard << " - Заполнить список" << endl
			<< build_polojitelny_array << " - Создать такой же список, использовав положительные числа" << endl
			<< print_to_display_1arr << " - Вывести на экран первый список" << endl
			<< print_to_display_2arrs << " - Вывести на экран оба списка" << endl
			<< insert_proizv_index << " - Вставить элемент в произвольную позицию" << endl
			<< delete_proizv_index << " - Удалить элемент из произвольной позиции" << endl
			<< find_index_po_znach << " - Найти индекс элемента по значению" << endl
			<< find_elem_po_index << " - Найти элемент по его расположению ( индексу )" << endl;

		cin >> ans;

		switch (ans)
		{
		case scan_from_keyboard:
		{
			L1.Clear();
			int size, value;
			cout << "\nВведите количество элементов: ";
			cin >> size;

			for (int i = 0; i < size; i++)
			{
				cout << "Введите " << i + 1 << " элемент: ";
				cin >> value;
				L1.Insert_end(value);
			}
			break;
		}
		case build_polojitelny_array:
		{
			L2.Clear();
			for (int i = 0; i < L1.size(); i++)
			{
				if (L1.GetValue(i) > 0)
					L2.Insert_end(L1.GetValue(i));
			}
			break;
		}
		case print_to_display_1arr:
		{
			cout << "\nИсходный список: \n" << endl;
			L1.Print();
			cout << "\n";
			break;
		}
		case print_to_display_2arrs:
		{
			cout << "\nИсходный список: \n" << endl;
			L1.Print();

			cout << "\nОбновлённый список из положительных значений: \n" << endl;
			L2.Print();
			cout << "\n";
			break;
		}
		case insert_proizv_index:
		{
			int index, value;

			cout << "Введите индекс, под которым хотите расположить элемент: ";
			cin >> index;
			cout << "Введите значение, которое хотите поместить под заданным индексом: ";
			cin >> value;

			L1.Insert_proizv(index, value);
			break;
		}
		case delete_proizv_index:
		{
			int index;
			
			cout << "Введите индекс, под которым хотите удалить элемент: ";
			cin >> index;

			L1.Delete_proizv(index);
			break;
		}
		case find_index_po_znach:
		{
			int value;
			
			cout << "Введите значение, для которого ищете индекс: ";
			cin >> value;

			Node<int>* root = L1.Move_znach(value);
			cout << root->Value();
			break;
		}
		case find_elem_po_index:
		{
			int index;

			cout << "Введите индекс, по которому хотите найти элемент: ";
			cin >> index;

			Node<int>* root = L1.Move(index);
			cout << "Найденное значение: " << root->Value() << endl;
			break;
		}
		} 
	} while (ans != exit_program);

	L1.~List1();
	L2.~List1();
	return 0;
}