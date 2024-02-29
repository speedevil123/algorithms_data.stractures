#pragma once
#include <iostream>
#include <string>

using namespace std;

//корень бинарного дерева
template<class T>
class Node
{
private:
	T _value;
	Node* left;
	Node* right;
public:
	Node() : _value(T()), left(nullptr), right(nullptr) {}
	Node(T value)
	{
		_value = value;
		left = nullptr;
		right = nullptr;
	}

	void SetLeft(Node* t) { left = t; }
	void SetRight(Node* t) { right = t; }
	void SetValue(T value) { _value = value; }

	T GetValue() { return _value; }
	Node* GetLeft() { return left; }
	Node* GetRight() { return right; }

};

//бинарное дерево (поисковое)
template<class T>
class Tree
{
private:
	Node<T>* head;

private:
	bool search(T value, Node<T>* node);
	void add(Node<T>* node, T value);
	void delete_tree(Node<T>* t);

	void print_unordered(Node<T>* t, ostream& out);
	ostream& print_ordered(Node<T>* t, ostream& out);
	void print_koncevoe(Node<T>* t, ostream& out);
	Node<T>* RemoveNode(Node<T>* root, T x);
	void copyTree(Node<T>* newNode, Node<T>* otherNode);
	bool compareNodes(Node<T>* node1, Node<T>* node2);
	Node<T>* keyLengthRemoveRec(Node<T>* node, int length);
public:
	Tree();
	Tree(T value);
	Tree(Node<T>* node);
	Tree(const Tree& other);
	~Tree();

	Node<T>* GetHead() { return head; } 
	void SetHead(Node<T>* head_) { head = head_; }
	void print_unordered(ostream& out);
	ostream& print_ordered(ostream& out);
	void print_koncevoe(ostream& out);
	Tree* scan_file(string path);

	Node<T>* RemoveNode(T x);
	void add(T value);
	bool search(T value);
	Tree<T>& operator = (const Tree<T>& other);
	bool operator == (const Tree<T>& other);
	void keyLengthRemove(int length);

};

template<class T>
Tree<T>::Tree()
{
	head = nullptr;
}

template<class T>
Tree<T>::Tree(T value)
{
	Node<T>* node = new Node<T>(value);
	head = node;
}

template<class T>
Tree<T>::Tree(Node<T>* node) { head = node; }

template<class T>
Tree<T>::Tree(const Tree& other)
{
	if (other.head == nullptr)
	{
		head = nullptr;
	}
	else
	{
		head = new Node<T>(other.head->GetValue());
		copyTree(head, other.head);
	}
}

template<class T>
Tree<T>::~Tree()
{
	delete_tree(head);
	head = nullptr;
}

//обратный обход (лево-корень-право)
template<class T>
void Tree<T>::print_unordered(ostream& out)
{
	if(&out == &cout)
		cout << "Обратный обход (лево-корень-право): " << endl;

	print_unordered(head, out);

	if(&out == &cout)
		cout << endl;
}

//прямой обход (корень-лево-право)
template<class T>
ostream& Tree<T>::print_ordered(ostream& out)
{
	if(&out == &cout)	
		cout << "Прямой обход (корень-лево-право): " << endl;

	return print_ordered(head, out);

	if (&out == &cout)
		cout << endl;
}

//концевой обход (лево-право-корень)
template<class T>
void Tree<T>::print_koncevoe(ostream& out)
{
	if (&out == &cout)
		cout << "Концевой обход (лево-право-корень): " << endl;

	print_koncevoe(head, out);

	if (&out == &cout)
		cout << endl;
}

template<class T>
Tree<T>* Tree<T>::scan_file(string path)
{
	ifstream fin(path);
	T value;
	while (fin >> value)
	{
		this->add(value);
	}
	fin.close();
	return this;
}

//рекурсия идет сначала до левого нижнего узла, потом до правого нижнего узла,
//далее поднимается в корень
//и пока поднимается в корень, удаляет все узлы.
template<class T>
void Tree<T>::delete_tree(Node<T>* t)
{
	if (t != NULL)
	{
		delete_tree(t->GetLeft());
		delete_tree(t->GetRight());
		delete t;
	}
}

template<class T>
void Tree<T>::print_unordered(Node<T>* t, ostream& out)
{
	if (t != nullptr)
	{
		print_unordered(t->GetLeft(), out);
		out << t->GetValue() << " ";
		print_unordered(t->GetRight(), out);
	}
}

template<class T>
ostream& Tree<T>::print_ordered(Node<T>* t, ostream& out)
{
	if (t != nullptr)
	{
		out << t->GetValue() << " ";
		print_ordered(t->GetLeft(), out);
		print_ordered(t->GetRight(), out);
	}
	return out;
}

template<class T>
void Tree<T>::print_koncevoe(Node<T>* t, ostream& out)
{
	if (t != nullptr)
	{
		print_koncevoe(t->GetLeft(), out);
		print_koncevoe(t->GetRight(), out);
		out << t->GetValue() << " ";
	}
}

template<class T>
void Tree<T>::copyTree(Node<T>* newNode, Node<T>* otherNode)
{
	if (otherNode->GetLeft() != nullptr)
	{
		newNode->SetLeft(new Node<T>(otherNode->GetLeft()->GetValue()));
		copyTree(newNode->GetLeft(), otherNode->GetLeft());
	}

	if (otherNode->GetRight() != nullptr)
	{
		newNode->SetRight(new Node<T>(otherNode->GetRight()->GetValue()));
		copyTree(newNode->GetRight(), otherNode->GetRight());
	}
}

template<class T>
bool Tree<T>::compareNodes(Node<T>* node1, Node<T>* node2)
{
	if (node1 == nullptr && node2 == nullptr)
		return true;
	else if (node1 == nullptr || node2 == nullptr)
		return false;
	else if (node1->GetValue() != node2->GetValue())
		return false;
	else
		return ((compareNodes(node1->GetLeft(), node2->GetLeft())) && (compareNodes(node1->GetRight(), node2->GetRight())));
}

template<class T>
Node<T>* Tree<T>::RemoveNode(Node<T>* root, T x)
{
	if (root == NULL)
		return NULL;
	if (x == root->GetValue())
	{
		Node<T>* t;
		if (root->GetLeft() == NULL)
		{
			t = root->GetRight();
			delete root;
			return t;
		}
		t = root->GetLeft();
		while (t->GetRight())
		{
			t = t->GetRight();
		}
		t->SetRight(root->GetRight());
		t = root;
		root = root->GetLeft();
		delete t;
		return root;
	}
	if (x < root->GetValue())
		root->SetLeft(RemoveNode(root->GetLeft(), x));
	else
		root->SetRight(RemoveNode(root->GetRight(), x));
	return root;
}

template<class T>
void Tree<T>::add(Node<T>* node, T value)
{
	if (head == nullptr)
	{
		Node<T>* newNode = new Node<T>(value);
		head = newNode;
	}
	else if (value >= node->GetValue())
	{
		if (node->GetRight() != nullptr)
			add(node->GetRight(), value);
		else
		{
			Node<T>* newNode = new Node<T>(value);
			node->SetRight(newNode);
		}
	}
	else
	{
		if (node->GetLeft() != nullptr)
			add(node->GetLeft(), value);
		else
		{
			Node<T>* newNode = new Node<T>(value);
			node->SetLeft(newNode);
		}
	}
}

template<class T>
Node<T>* Tree<T>::RemoveNode(T x)
{
	head = RemoveNode(head,x);
	return head;
}


template<class T>
void Tree<T>::add(T value)
{
	if (head == nullptr)
	{
		Node<T>* newNode = new Node<T>(value);
		head = newNode;
	}
	else if (value >= head->GetValue())
	{
		if (head->GetRight() != nullptr)
			add(head->GetRight(), value);
		else
		{
			Node<T>* newNode = new Node<T>(value);
			head->SetRight(newNode);
		}
	}
	else
	{
		if (head->GetLeft() != nullptr)
			add(head->GetLeft(), value);
		else
		{
			Node<T>* newNode = new Node<T>(value);
			head->SetLeft(newNode);
		}
	}
}

template<class T>
bool Tree<T>::search(T value, Node<T>* node)
{
	while (node != NULL)
	{
		if (value == node->GetValue())
			return true;
		else
		{
			if (value <= node->GetValue())
				return search(value, node->GetLeft());
			else
				return search(value, node->GetRight());

		}
	}
	return false;
}

template<class T>
bool Tree<T>::search(T value)
{
	while (head != NULL)
	{
		if (value == head->GetValue())
			return true;
		else
		{
			if (value <= head->GetValue())
				return search(value, head->GetLeft());
			else
				return search(value, head->GetRight());
		}
	}
	return false;
}

template<class T>
Tree<T>& Tree<T>::operator=(const Tree<T>& other)
{
	if (this != &other)
	{
		delete_tree(head);
		if (other.head == nullptr)
			head = nullptr;
		else
		{
			head = new Node<T>(other.head->GetValue());
			copyTree(head, other.head);
		}
	}
	/*возвращаем разыменованынй объект*/
	return *this;
}

template<class T>
bool Tree<T>::operator==(const Tree<T>& other)
{
	return compareNodes(head, other.head);
}

template<class T>
void Tree<T>::keyLengthRemove(int length)
{
	head = keyLengthRemoveRec(head, length);
}

template<class T>
ostream& operator << (ostream& out, Tree<T>& obj)
{
	obj.print_ordered(out);
	return out;
}

template<class T>
istream& operator >> (istream& in, Tree<T>& obj)
{
	T value;
	bool continueInput = true;
	while (continueInput && in >> value)
	{
		obj.add(value);

		cout << "Хотите ли вы продолжить вводить элементы? (1 - Да, 0 - Нет): ";
		cin >> continueInput;
	}
	return in;
}

template<class T>
Node<T>* Tree<T>::keyLengthRemoveRec(Node<T>* node, int length)
{
	if (node == nullptr)
		return nullptr;

	node->SetLeft(keyLengthRemoveRec(node->GetLeft(), length));
	node->SetRight(keyLengthRemoveRec(node->GetRight(), length));

	if (node->GetValue().length() > length)
	{
		return RemoveNode(node, node->GetValue());
	}

	return node;
}



//сбалансированный корень с коэфом выравнивания

template<class T>
class BalancedNode : public Node<T>
{
private:
	int balance_factor; // коэффициент балансировки
public:
	BalancedNode() : Node<T>(), balance_factor(0) {}
	BalancedNode(T value) : Node<T>(value), balance_factor(0) {}

	void SetBalanceFactor(int bf) { balance_factor = bf; }
	int GetBalanceFactor() { return balance_factor; }

	void SetLeft(BalancedNode* t) { Node<T>::SetLeft(t); }
	void SetRight(BalancedNode* t) { Node<T>::SetRight(t); }
	void SetValue(T value) { Node<T>::SetValue(value); }

	BalancedNode* GetLeft() { return static_cast<BalancedNode*>(Node<T>::GetLeft()); }
	BalancedNode* GetRight() { return static_cast<BalancedNode*>(Node<T>::GetRight()); }
};

//сбалансированное дерево

template<class T>
class BalancedTree : public Tree<BalancedNode<T>>
{
private:
	BalancedNode<T>* balancedHead;

	BalancedNode<T>* LeftRotation(BalancedNode<T>* node);
	BalancedNode<T>* RightRotation(BalancedNode<T>* node);
	BalancedNode<T>* LeftRightRotation(BalancedNode<T>* node);
	BalancedNode<T>* RightLeftRotation(BalancedNode<T>* node);
	void UpdateBalanceFactor(BalancedNode<T>* node);
	BalancedNode<T>* BalanceTree(BalancedNode<T>* node);

	void Add(BalancedNode<T>* node, T value);
	void PrintTree(BalancedNode<T>* node);
	int GetHeight(BalancedNode<T>* node);

public:
	BalancedTree() : Tree<BalancedNode<T>>() {}
	BalancedTree(BalancedNode<T>* node) : Tree<BalancedNode<T>>(node) {}
	BalancedTree(const BalancedTree& other) : Tree<BalancedNode<T>>(other) {}
	~BalancedTree() {}


	void SetHead(BalancedNode<T>* node) { balancedHead = node; }
	BalancedNode<T>* GetHead() { return balancedHead; }
	void Add(T value);
	void PrintTree();

};

//малый левый поворот
template<class T>
BalancedNode<T>* BalancedTree<T>::LeftRotation(BalancedNode<T>* node)
{
	BalancedNode<T>* temp = node->GetRight();
	node->SetRight(temp->GetLeft());
	temp->SetLeft(node);
	return temp;
}


//малый правый поворот
template<class T>
BalancedNode<T>* BalancedTree<T>::RightRotation(BalancedNode<T>* node)
{
	BalancedNode<T>* temp = node->GetLeft();
	node->SetLeft(temp->GetRight());
	temp->SetRight(node);
	return temp;
}

template<class T>
BalancedNode<T>* BalancedTree<T>::LeftRightRotation(BalancedNode<T>* node)
{
	if (node == nullptr || node->GetLeft() == nullptr)
	{
		return node;
	}

	node->SetLeft(LeftRotation(node->GetLeft()));
	return RightRotation(node);
}

template<class T>
BalancedNode<T>* BalancedTree<T>::RightLeftRotation(BalancedNode<T>* node)
{
	if (node == nullptr || node->GetRight() == nullptr)
	{
		return node;
	}

	node->SetRight(RightRotation(node->GetRight()));
	return LeftRotation(node);
}

template<class T>
void BalancedTree<T>::UpdateBalanceFactor(BalancedNode<T>* node)
{
	int leftHeight = GetHeight(node->GetLeft());
	int rightHeight = GetHeight(node->GetRight());
	node->SetBalanceFactor(rightHeight - leftHeight);
}

template<class T>
BalancedNode<T>* BalancedTree<T>::BalanceTree(BalancedNode<T>* node)
{
	UpdateBalanceFactor(node);
	int balanceFactor = node->GetBalanceFactor();

	if (balanceFactor > 1)
	{
		if (node->GetRight()->GetBalanceFactor() < 0)
		{
			return RightLeftRotation(node);
		}
		else
		{
			return LeftRotation(node);
		}
	}
	else if (balanceFactor < -1)
	{
		if (node->GetLeft()->GetBalanceFactor() > 0)
		{
			return LeftRightRotation(node);
		}
		else
		{
			return RightRotation(node);
		}
	}

	return node;
}





template<class T>
void BalancedTree<T>::Add(BalancedNode<T>* node, T value)
{
	if (node == nullptr)
	{
		BalancedNode<T>* t = new BalancedNode<T>(value);
		node = t;
	}
	if (value < node->GetValue())
	{
		if (node->GetLeft() == nullptr)
		{
			node->SetLeft(new BalancedNode<T>(value));
		}
		else
		{
			Add(node->GetLeft(), value);
			node->SetLeft(BalanceTree(node->GetLeft()));
		}
	}
	else if (value > node->GetValue())
	{
		if (node->GetRight() == nullptr)
		{
			node->SetRight(new BalancedNode<T>(value));
		}
		else
		{
			Add(node->GetRight(), value);
			node->SetRight(BalanceTree(node->GetRight()));
		}
	}
}

template<class T>
void BalancedTree<T>::PrintTree(BalancedNode<T>* node)
{
	if (node != nullptr)
	{
		cout << node->GetValue() << " ";
		PrintTree(node->GetLeft());
		PrintTree(node->GetRight());
	}
}

template<class T>
int BalancedTree<T>::GetHeight(BalancedNode<T>* node)
{
	if(node == nullptr)
		return 0;

	int leftHeight = GetHeight(node->GetLeft());
	int rightHeight = GetHeight(node->GetRight());

	return max(leftHeight, rightHeight) + 1;
}

template<class T>
void BalancedTree<T>::Add(T value)
{
	if (balancedHead == nullptr)
	{
		balancedHead = new BalancedNode<T>(value);
	}
	else
	{
		Add(balancedHead, value);
		balancedHead = BalanceTree(balancedHead);
	}
}

template<class T>
void BalancedTree<T>::PrintTree()
{
	return PrintTree(balancedHead);
}
