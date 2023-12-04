#pragma once
#include <iostream>
#include <exception>
#include <string>

template<class T>
class Node
{
	T value_;
	Node<T>* next_;
	Node<T>* prev_;
public:
	T Value() { return value_; }
	void SetValue(T value) { value_ = value; }

	Node<T>* Next() { return next_; }
	void SetNext(Node<T>* next) { next_ = next; }

	Node<T>* Prev() { return prev_; }
	void SetPrev(Node<T>* prev) { prev_ = prev; }
};

template<class T>
class List1
{
	Node<T>* begin_;
	Node<T>* end_;
	int size_;
public:
	List1()
	{
		begin_ = end_ = nullptr;
		size_ = 0;
	}
	List1(const List1& obj) { Copy(obj); }
	List1<T>& operator = (const List1& obj) { Copy(obj); return *this; }
	~List1() { Clear(); }

	void Insert_start(T _value)
	{
		try
		{
			Node<T>* t = new Node<T>;
			t->SetValue(_value);
			t->SetPrev(nullptr);
			t->SetNext(begin_);

			if (size_ > 0)
			{
				begin_->SetPrev(t);
				begin_ = t;
			}

			else
			{
				begin_ = end_ = t;
			}
			size_++;

		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	void Insert_end(T _value)
	{
		try
		{
			Node<T>* t = new Node<T>;
			t->SetValue(_value);
			t->SetPrev(end_);
			t->SetNext(nullptr);

			if (end_ != nullptr)
				end_->SetNext(t);

			if (size_ == 0)
				begin_ = end_ = t;
			else
			{
				end_ = t;
			}

			size_++;
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	void Insert_proizv(int index, T _value)
	{
		if (!CorrectIndex(index))
			return;

		if (index == size_)
		{
			Insert_end(_value);
			return;
		}

		if (index == 0)
		{
			Insert_start(_value);
			return;
		}

		try
		{
			Node<T>* itemPrev = Move(index - 1);

			Node<T>* item = Move(index);

			Node<T>* t = new Node<T>;
			t->SetValue(_value);
			t->SetNext(item);
			t->SetPrev(itemPrev);
			itemPrev->SetNext(t);
			item->SetPrev(t);

			size_++;
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}


	Node<T>* Move(int index)
	{
		Node<T>* t = begin_;

		for (int i = 0; i < index; i++)
			t = t->Next();

		return t;
	}

	Node<T>* Move_znach(T other)
	{
		int index = 0;
		Node<T>* t = begin_;

		while (t != nullptr)
		{
			if (t->Value() == other)
				std::cout << "Индекс элемента: " << index << std::endl;
				return t;

			t = t->Next();
			index++;
		}

		return nullptr;
	}

	T GetValue(int index)
	{
		if (!CorrectIndex(index))
			std::cerr << "Неверный индекс." << std::endl;
		Node<T>* t = Move(index);
		return t->Value();
	}

	void Delete_start() { return Delete_proizv(0); }
	void Delete_end() { return Delete_proizv(size_ - 1); }
	void Delete_proizv(int index)
	{
		if (size_ == 0)
			return;

		if (!CorrectIndex(index))
			return;

		Node<T>* item = Move(index);
		Node<T>* itemPrev = item->Prev();
		Node<T>* itemNext = item->Next();

		if ((size_ > 1) && (itemPrev != nullptr))
			itemPrev->SetNext(itemNext);

		if ((itemNext != nullptr) && (size_ > 1))
			itemNext->SetPrev(itemPrev);

		if (index == 0)
			begin_ = itemNext;

		if (index == size_ - 1)
			end_ = itemPrev;

		delete item;

		size_--;
	}
	
	bool CorrectIndex(int index) { return ((index >= 0) && (index < size_)); }
	void Clear()
	{
		int n = size_;
		for (int i = 0; i < n; i++)
			Delete_proizv(0);
	}
	void Copy(const List1<T>& obj)
	{
		Clear();

		Node<T>* t = obj.begin;

		while (t != nullptr)
		{
			Insert_start(t->Value());
			t = t->Next();
		}
	}

	int size() { return size_; }

	void Print()
	{
		Node<T>* t = begin_;

		for (int i = 0; i < size_; i++)
		{
			std::cout << t->Value() << " ";
			t = t->Next();
		}
		std::cout << std::endl;
	}

};