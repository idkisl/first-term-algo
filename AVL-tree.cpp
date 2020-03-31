#include <iostream>
#include <cassert>
#include <queue>

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
public:
	struct node // структура для представления узлов дерева
	{
		T key;
		unsigned char height;
		int size;
		node* left;
		node* right;
		node(T k) { key = k; left = right = 0; height = 1; size = 1; }
		node(const node& p) { key = p.key; height = p.height; left = right = nullptr; size = p.size; }
	};
private:
	node* head = nullptr;

	unsigned char height(node* p)
	{
		return p ? p->height : 0;
	}

	int size(node* p)
	{
		return p ? p->size : 0;
	}

	int bfactor(node* p)
	{
		return height(p->right) - height(p->left);
	}

	void fixheight(node* p)
	{
		unsigned char hl = height(p->left);
		unsigned char hr = height(p->right);
		p->height = (hl > hr ? hl : hr) + 1;
	}

	void fixsize(node* p)
	{
		p->size = size(p->left) + size(p->right) + 1;
	}

	node* rotateright(node* p) // правый поворот вокруг p
	{
		node* q = p->left;
		p->left = q->right;
		q->right = p;
		fixheight(p);
		fixheight(q);
		fixsize(p);
		fixsize(q);
		return q;
	}

	node* rotateleft(node* q) // левый поворот вокруг q
	{
		node* p = q->right;
		q->right = p->left;
		p->left = q;
		fixheight(q);
		fixheight(p);
		fixsize(q);
		fixsize(p);
		return p;
	}

	node* balance(node* p) // балансировка узла p
	{
		fixheight(p);
		fixsize(p);
		if (bfactor(p) == 2)
		{
			if (bfactor(p->right) < 0)
				p->right = rotateright(p->right);
			return rotateleft(p);
		}
		if (bfactor(p) == -2)
		{
			if (bfactor(p->left) > 0)
				p->left = rotateleft(p->left);
			return rotateright(p);
		}
		return p; // балансировка не нужна
	}

	node* findmax(node* p) // поиск узла с максимальным ключом в дереве p 
	{
		return p->right ? findmax(p->right) : p;
	}

	node* findmin(node* p) // поиск узла с минимальным ключом в дереве p 
	{
		return p->left ? findmin(p->left) : p;
	}

	node* removemin(node* p) // удаление узла с минимальным ключом из дерева p
	{
		if (p->left == 0)
			return p->right;
		p->left = removemin(p->left);
		return balance(p);
	}

	node* FindAndRemoveMin(node* Node, node*& min)
	{
		if (!Node)
			return nullptr;
		if (!Node->left)
		{
			min = Node;
			return Node;
		}
		if (Node->left->left)
		{
			FindAndRemoveMin(Node->left, min);
		}
		else
		{
			min = Node->left;
			Node->left = Node->left->right;
		}
		return balance(Node->left);
	}

	node* FindAndRemoveMax(node* Node, node*& max)
	{
		if (!Node)
			return nullptr;
		if (!Node->right)
		{
			max = Node;
			return Node;
		}
		if (Node->right->right)
		{
			FindAndRemoveMax(Node->right, max);
		}
		else
		{
			max = Node->right;
			Node->right = Node->right->left;
		}
		return balance(Node->right);
	}

	node* removemax(node* p) // удаление узла с максимальным ключом из дерева p
	{
		if (p->right == 0)
			return p->left;
		p->right = removemax(p->right);
		return balance(p);
	}

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

	node* insert(node* p, T k, const TLess& Isless = TLess()) // вставка ключа k в дерево с корнем p
	{
		if (!p) return new node(k);
		if (Isless(k , p->key))
			p->left = insert(p->left, k);
		else
			p->right = insert(p->right, k);
		return balance(p);
	}

	node* remove(node* p, T k,const TLess& Isless = TLess()) // удаление ключа k из дерева p
	{
		if (!p) return 0;
		if (Isless(k , p->key))
			p->left = remove(p->left, k);
		else if (Isless( p->key , k))
			p->right = remove(p->right, k);
		else //  k == p->key 
		{
			node* q = p->left;
			node* r = p->right;
			delete p;
			if (!r) return q;
			node* min = findmin(r);
			min->right = removemin(r);
			min->left = q;
			return balance(min);
		}
		return balance(p);
	}

	node* removeMinOrMax(node* p, T k,const TLess& Isless = TLess()) // удаление ключа k из дерева p
	{
		if (!p) return 0;
		if (Isless(k , p->key))
			p->left = removeMinOrMax(p->left, k);
		else if (Isless( p->key , k))
			p->right = removeMinOrMax(p->right, k);
		else //  k == p->key 
		{
			node* left = p->left;
			node* right = p->right;
			delete p;
			if (height(left) < height(right))
			{
				if (!right) return left;
				node* min;
				FindAndRemoveMin(right, min);// это новый код
				if (min)
					return balance(min);
				return nullptr;
			}
			else
			{
				if (!left) return right;
				node* max;
				FindAndRemoveMax(left, max);// это новый код
				if (max)
					return balance(max);
				return nullptr;
			}
		}
		return balance(p);
	}

public:
	Tree(){}

	Tree(const Tree& tree)
	{
		if (tree.head == nullptr)
			return;
		head = new node(*(tree.head));
		ConstructCopy(tree.head,head);
	}

	Tree(Tree&& tree) 
	{
		head = tree.head;
		tree.head = nullptr;
	}

	node* operator= (const Tree& tree)
	{
		destruct(head);
		if (tree.head == nullptr)
			return nullptr;
		head = new node(*tree.head);
		ConstructCopy(tree.head, head);
		return head;
	}

	~Tree()
	{
		destruct(head);
	}

	void FindAndRemove(T key)
	{
		head = removeMinOrMax(head, key);
	}

	void Insert(T key)
	{
		if (head == nullptr)
			head = new node(key);
		else
			head = insert(head, key);
		fixsize(head);
	}

	int k_por_stat(int k)
	{
		assert(head != nullptr);
		assert(k >= 0);
		node* p = head;
		while (p && k >= 0)
		{
			if (size(p->left) == k)
			{
				return p->key;
			}
			if (size(p->left) >= k)
			{
				p = p->left;
			}
			else
			{
				k = k - size(p->left) - 1; // -1 тк корень тоже есть
				p = p->right;
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
		int current,k;
		std::cin >> current;
		if (current > 0)
			tree.Insert(current);
		if (current < 0)
			tree.FindAndRemove(current * (-1));
		std::cin >> k;
		std::cout << tree.k_por_stat(k) << std::endl;
	}
	//Tree tree3(std::move(tree2)); // move make from lvalue to rvalue
	return 0;
}