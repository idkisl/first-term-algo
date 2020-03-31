// TREE DFS


#include <iostream>
#include <stack>

template <class T>
struct print
{
	void operator()(const T& a) const
	{
		std::cout << a << " ";
	}
};

template <typename T>
struct IsLess {
	bool operator()(const T& l, const T& r) const
	{
		return l < r;
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
	Tree<int> tree;
	int N;
	std::cin >> N;
	for (int i = 0; i < N; ++i)
	{
		int a;
		std::cin >> a;
		tree.Insert(a);
	}
	tree.DFS(print<int>());
}

// Find posiiton const
// убрать шаблон IsLess