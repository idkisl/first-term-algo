#include "List.h"

void List::Swap(List::Node* a, List::Node* b)
{
	int t = a->data;
	a->data = b->data;
	b->data = t;;
}

void List::PushBack(int a)
{
	if (head == nullptr)
	{
		head = new Node(a);
		return;
	}
	Node* p = head;
	while (p->next != nullptr)
	{
		p = p->next;
	}
	p->next = new Node(a);
}

int List::PopBack()
{
	if (head == nullptr)
		throw "Can not Pop because of non-elements";
	if (head->next == nullptr)
	{
		int t = head->data;
		delete head;
		head = nullptr;
		return t;
	}
	Node* current = head->next;
	Node* prev = head;
	while (current->next != nullptr)
	{
		prev = current;
		current = current->next;
	}
	prev->next = nullptr;
	int t = current->data;
	delete current;
	return t;

}

int List::PopFront()
{
	if (head == nullptr)
		throw "Can not Pop because of non-elements";
	int t = head->data;
	Node* It = head->next;
	delete head;
	head = It;
	return t;
}

void List::PushFront(int a)
{
	Node* p = head;
	head = new Node(a);
	head->next = p;
}

int List::VisitBegin()
{
	return head->data;
}

int List::VisitEnd()
{
	Node* current = head;
	while (current->next != nullptr)
	{
		current = current->next;
	}
	return current->data;
}

void List::Clear()
{
	Node* current = head;
	Node* next;

	while (current != nullptr)
	{
		next = current->next;
		delete current;
		current = next;
	}
	head = nullptr;
}

bool List::Empty()
{
	return head == nullptr;
}

int List::Size()
{
	int i = 0;
	Node* current = head;
	while (current != nullptr)
	{
		++i;
		current = current->next;
	}
	return i;
}

void List::Insert(List::Iterator it, int a)
{
	Node* new_node = new Node(a);
	new_node->next = it.node->next;
	it.node->next = new_node;
}

List::Iterator List::Erase(List::Iterator it)
{
	if (head == nullptr)
		throw "Can not Erase because of non-elements";
	Node* current = head->next;
	Node* parent = head;
	if (parent == it.node)
	{
		delete head;
		head = current;
		return Iterator(current);
	}
	while (current != it.node)
	{
		parent = current;
		current = current->next;
	}
	parent->next = current->next;
	delete current;
	return Iterator(parent->next);
}

List::Iterator List::FindFirstEqualElement(int a)
{
	for (List::Iterator it = Begin(); it != End(); ++it)
	{
		if (*it == a)
		{
			return it;
		}
	}
	return End();
}

void List::Sort()
{
	for (Node* i = head; i != nullptr; i = i->next)
	{
		for (Node* j = head; j->next != nullptr; j = j->next)
		{
			if (j->data > j->next->data)
			{
				Swap(j, j->next);

			}
		}
	}

}

std::ostream& operator<<(std::ostream& out, const List& list)
{
	List::Node* p = list.head;
	while (p != nullptr)
	{
		out << p->data << " ";
		p = p->next;
	}
	out << std::endl;
	return out;
}