#include <iostream>
#include <cassert>
#include <stack>

template <typename T>
struct IsLess {
	bool operator()(const T& l, const T& r) const
	{
		return l < r;
	}
};

template <class T>
struct print
{
	void operator()(const T& a) const
	{
		std::cout << a << " ";
	}
};

template <class T>
class Vector
{
	T* arr = new T[1];
	int l_array = 1; // [0,l_array)
	void MakeVectorLonger()
	{
		T* arr2 = new T[l_array * 2];
		for (int j = 0; j < l_array; ++j)
			arr2[j] = arr[j];
		T* t = arr;
		arr = arr2;
		delete[] t;
		l_array *= 2;
		for (int j = l_array / 2; j < l_array; ++j)
			arr[j] = 0;
	}
public:
	Vector() { arr[0] = 0; }
	void PopI(int i)
	{
		while (i >= l_array)
			MakeVectorLonger();
		arr[i] ++;
	}
	void GetArray()
	{
		for (int i = 0; i < l_array; ++i)
			std::cout << arr[i] << " ";
	}
	int GetMax()
	{
		T max = 0;
		int maxi;
		for (int i = 0; i < l_array; ++i)
			if (arr[i] > max)
			{
				max = arr[i];
				maxi = i;
			}

		return max;
	}
	~Vector()
	{
		delete[] arr;
	}
};

template <class T, class TLess = IsLess<T>>
class TreeDec
{
	struct node
	{
		T x; 
		T y; 
		node* left;
		node* right;
		node(T x_ = 0, T y_ = 0) { x = x_; y = y_; left = right = nullptr;}
	};
	node* head = nullptr;

	void destruct(node* p)
	{
		if (p == nullptr)
			return;
		if (p->left != nullptr)
			destruct(p->left);
		if (p->right != nullptr)
			destruct(p->right);
		delete p;
		p = nullptr;
	}

	void ConstructCopy(node* source, node* dest)
	{
		if (source->left != nullptr)
		{
			dest->left = new node(*(source->left));
			ConstructCopy(source->left, dest->left);
		}
		if (source->right != nullptr)
		{
			dest->right = new node(*(source->right));
			ConstructCopy(source->right, dest->right);
		}
	}

	static node* Merge(node* left, node* right, const TLess& isLess = TLess())
	{
		if (!left || !right)
			return left ? left : right;
		if (isLess(right->y, left->y))
		{
			left->right = Merge(left->right, right);
			return left;
		}
		else
		{
			right->left = Merge(left, right->left);
			return right;
		}

	}

	static void Split(node* nod, T x, node*& tree1, node*& tree2, const TLess& isLess = TLess())
	{
		if (!nod)
		{
			tree1 = tree2 = nullptr;
			return;
		}
		if (isLess(nod->x, x))
		{
			tree1 = nod;
			Split(nod->right, x, tree1->right, tree2);
		}
		else
		{
			tree2 = nod;
			Split(nod->left, x, tree1, tree2->left);
		}
	}

	node* FindNode(T X, T Y, const TLess& isLess = TLess())
	{
		if (head == nullptr)
			return head;
		node* p = head;
		node* parent = nullptr;
		while (p != nullptr && isLess(Y, p->y))
		{
			if (isLess(p->x, X))
			{	
				parent = p;
				p = p->left;
			}
			else
			{
				parent = p;
				p = p->right;
			}
	
		}
		return parent;
	}

	void GetMaxLevel(Vector<T>& v, node* p, int n = 0)
		{
			if (p != nullptr)
				v.PopI(n);
			if (p != nullptr && p->left != nullptr)
			{
				GetMaxLevel(v,p->left, n + 1);
			}
			if (p != nullptr && p->right != nullptr)
			{
				GetMaxLevel(v, p->right, n + 1);
			}
		}
public:
	TreeDec() {}

	TreeDec(const TreeDec& tree)
	{
		if (tree.head == nullptr)
			return;
		head = new node(*(tree.head));
		ConstructCopy(tree.head, head);
	}

	TreeDec(TreeDec&& tree)
	{
		head = tree.head;
		tree.head = nullptr;
	}

	~TreeDec(){ destruct(head); }

	int MaxLevel()
	{
		Vector<T> v;
		node* p = head;
		int n = 0;
		GetMaxLevel(v, p, n);
		return v.GetMax();
	}

	void Insert2(T X, T Y)
	{
		if (head == nullptr)
		{
			head = new node(X, Y);
			return;
		}
		node* p = FindNode(X, Y);
		node* Node = new node(X, Y);
		node* T1 = nullptr, * T2 = nullptr;
		Split(p, X, T1, T2);
		head = Merge(Merge(T1, Node), T2);
	}

	// первый способ вставки
	void Insert1(T X, T Y)
	{
		node* T1 = nullptr, * T2 = nullptr;
		node* Node = new node(X, Y);
		Split(head, X, T1, T2);
		T1 = Merge(T1, Node);
		head = Merge(T1, T2);
	}

	void Remove(T X, T Y) 
	{
		node* parent = FindNode(X, Y);
		if (!parent)
			return;
		node* p = nullptr;
		if (parent->left && parent->left->x == X && parent->left->y == Y)
		{
			p = parent->left;
		}
		else if (parent->right && parent->right->x == X && parent->right->y == Y)
		{
			p = parent->right;
		}
		if (!p)
			return;
		p = Merge(p->left, p->right);
	}
};

template <class T, class TLess = IsLess<T>>
class Tree
{
	struct Node
	{
		T data;
		Node* left;
		Node* right;
		Node(T a)
		{
			data = a;
			left = nullptr;
			right = nullptr;
		}
	};
	Node* head;

	Node* FindPosition(T a, const TLess& isLess = TLess()) const
	{
		if (head == nullptr)
			return head;
		Node* current = head;
		while (true)
		{
			if (isLess(a, current->data))
			{
				if (current->left != nullptr)
					current = current->left;
				else
					return current;
			}
			else
			{
				if (current->right != nullptr)
					current = current->right;
				else
					return current;
			}
		}
	}

	void GetMaxLevel(Vector<T>& v)
	{
		if (head == nullptr)
			return;
		int N = 0;
		std::stack<Node*> s;
		Node* current = head;
		while (!s.empty() || current != nullptr)
		{
			if (current == nullptr)
				--N;
			while (current != nullptr)
			{
				s.push(current);
				current = current->left;
				++N;
			}
			current = s.top();
			s.pop();
			--N;
			v.PopI(N);
			//std::cout << current->data << "  ";
			current = current->right;
			++N;
		}
	}

public:
	Tree() : head(nullptr) {}

	void Insert(T a, const TLess& isLess = TLess())
	{
		if (FindPosition(a) == nullptr)
		{
			head = new Node(a);
		}
		else
		{
			Node* parent = FindPosition(a);
			if (isLess(a, parent->data))
				parent->left = new Node(a);
			else
				parent->right = new Node(a);
		}
	}

	template <class OUT>
	void DFS(const OUT& out) const
	{
		if (head == nullptr)
			return;
		std::stack<Node*> s;
		Node* current = head;
		while (!s.empty() || current != nullptr)
		{
			while (current != nullptr)
			{
				s.push(current);
				current = current->left;
			}
			current = s.top();
			s.pop();
			out(current->data);
			current = current->right;
		}
	}

	int MaxLevel()
	{
		Vector<T> v;
		Node* p = head;
		int n = 0;
		GetMaxLevel(v);
		return v.GetMax();
	}

	~Tree()
	{
		Node* p = head;
		std::stack <Node*> s;
		while (!s.empty() || p != nullptr)
		{
			if (p != nullptr && p->left == nullptr && p->right == nullptr)
			{
				delete p;
				p = nullptr;
				if (!s.empty())
				{
					p = s.top();
					s.pop();
					p->left = p->right = nullptr;
				}
			}
			else
			{
				if (p != nullptr && p->left != nullptr)
				{
					s.push(p);
					p = p->left;
				}
				else if (p != nullptr && p->right != nullptr)
				{
					s.push(p);
					p = p->right;
				}
			}
		}
	}
};

int main()
{
	TreeDec<int> tree;
	Tree <int> tree2;
	int N, X, Y;
	std::cin >> N;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> X >> Y;
		tree.Insert(X, Y);
		tree2.Insert(X);
	}
	std::cout << tree.MaxLevel() - tree2.MaxLevel();
	return 0;
}