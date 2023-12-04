
template<class T>
class arraychik
{
private:
	T* arr_;
	int size_;

public:
	arraychik()
	{
		arr_ = nullptr;
		size_ = 0;
	}

	arraychik(int size)
	{
		arr_ = new T[size];
		size_ = size;
	}

	arraychik(const arraychik& other)
	{
		arr_ = new T[other.size_];
		size_ = other.size_;

		for (int i = 0; i < size_; i++)
		{
			arr_[i] = other.arr_[i];
		}
	}

	arraychik& operator = (arraychik other)
	{
		std::swap(arr_, other.arr_);
		std::swap(size_, other.size_);
		return *this;
	}

	~arraychik()
	{
		delete[] arr_;
	}

	T* get_arr() const { return arr_; }
	int get_size() const { return size_; }

	void fill_ordered(int size, T start)
	{
		size_ = size;
		T value = start;
		arr_ = new T[size_];

		for (int i = 0;i < size_; i++)
		{
			arr_[i] = value;
			value++;
		}
	}

	void fill_unordered(int size, T end)
	{
		size_ = size;
		T value = end;
		arr_ = new T[size_];

		for (int i = 0;i < size_; i++)
		{
			arr_[i] = value;
			value--;
		}
	}

	void fill_random(int size, T start, T end)
	{
		srand(time(0));

		size_ = size;
		arr_ = new T[size];
		if constexpr (std::is_same<T, int>::value)
		{
			for (int i = 0; i < size; i++)
			{
				arr_[i] = rand() % (end - start + 1) + start;
			}
		}
		else if constexpr (std::is_same<T, double>::value)
		{
			for (int i = 0; i < size; i++)
			{
				arr_[i] = start + (rand()) / (RAND_MAX / (end - start));
			}
		}
		else
		{
			std::cout << "Данный тип не поддерживается для рандомного заполнения!";
		}
	}


	std::ostream& print(std::ostream& out) const
	{
		out << size_ << std::endl;
		for (int i = 0; i < size_; i++)
		{
			out << arr_[i] << std::endl;
		}
		return out;
	}

	std::istream& scan(std::istream& in)
	{
		if (&in == &std::cin)
			std::cout << "Введите размер массива: ";

		in >> size_;

		delete[] arr_;
		arr_ = new T[size_];

		if (&in == &std::cin)
			std::cout << "Введите " << size_ << " элементов: ";

		for (int i = 0; i < size_; i++)
		{
			in >> arr_[i];
		}

		return in;
	}

	void quickSortR(T* a, long N, int& comparisons, int& swaps);
	void insertSortR(T* a, long size);
	void insertSort();
	void quickSort();

};

template<class T>
void arraychik<T>::quickSortR(T* a, long N, int& comparisons, int& swaps)
{
	// На входе - массив a[], a[N] - его последний элемент.

	long i = 0, j = N - 1;       // поставить указатели на исходные места
	T temp, p;

	p = a[N >> 1];      // центральный элемент побитовый сдвиг вправо означающий деление на два

	// процедура разделения
	do {
		while (a[i] < p) {
			i++;
			comparisons++;
		}

		while (a[j] > p) {
			j--;
			comparisons++;
		}

		if (i <= j) {
			temp = a[i];
			a[i] = a[j];
			a[j] = temp;
			swaps++;
			i++;
			j--;
		}
	} while (i <= j);

	// рекурсивные вызовы, если есть, что сортировать
	if (j > 0) {
		quickSortR(a, j + 1, comparisons, swaps);
	}
	if (N - 1 > i) {
		quickSortR(a + i, N - i, comparisons, swaps);
	}
}


template<class T>
void arraychik<T>::insertSortR(T* a, long size)
{
	T x;
	long i, j;

	int comparisons = 0, swaps = 0;

	for (i = 0; i < size; i++) {  // цикл проходов, i - номер прохода
		x = a[i];

		// поиск места элемента в готовой последовательности 
		for (j = i - 1; j >= 0 && a[j] > x; j--)
		{
			a[j + 1] = a[j];   // сдвигаем элемент направо, пока не дошли
			comparisons++;
			swaps++;
		}

		// место найдено, вставить элемент
		a[j + 1] = x;
		swaps++;
	}
	std::cout << "Количество сравнений: " << comparisons << std::endl;
	std::cout << "Количество перестановок: " << swaps << std::endl;
}

template<class T>
void arraychik<T>::insertSort()
{
	insertSortR(arr_, size_);
}

template<class T>
void arraychik<T>::quickSort()
{
	int comparisons = 0, swaps = 0;
	quickSortR(arr_, size_, comparisons, swaps);
	std::cout << "Количество сравнений: " << comparisons << std::endl;
	std::cout << "Количество перестановок: " << swaps << std::endl;
}