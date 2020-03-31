#include <iostream>
/*5_1. Скобочная последовательность.
Дан фрагмент последовательности скобок, состоящей из символов (){}[].
Требуется определить, возможно ли продолжить фрагмент в обе стороны, получив корректную последовательность.
Длина исходной последовательности ≤ 800000.
Формат входных данных. Строка, содержащая символы (){}[] и, возможно, перевод строки.
Формат выходных данных. Если возможно - вывести минимальную корректную последовательность, иначе - напечатать "IMPOSSIBLE".*/

class Stack
{
public:
	void push_stack(char element);
	char pop_stack();
	char GetLast();
	int ReturnSize() const { return size; }
	~Stack();
private:
	char* grow();
	int size = 0;
	int size_array = 1;
	char* array = new char[1];

};
void PrintAnswerTrue(char* str, char* pref, char* suf, int SizeStr, int SizePref, int SizeSuf)
{
	for (int i = 0; i < SizePref; ++i)
	{
		std::cout << pref[i];
	}
	for (int i = 0; i < SizeStr; ++i)
	{
		std::cout << str[i];
	}
	for (int i = 0; i < SizeSuf; ++i)
	{
		std::cout << suf[i];
	}
}
bool OpenBreacket(char bracket)
{
	if ((bracket == '[') || (bracket == '{') || (bracket == '('))
		return true;
	return false;
}
char Mirror(char c)
{
	if (c == '(') return ')';
	if (c == ')') return '(';
	if (c == '[') return ']';
	if (c == ']') return '[';
	if (c == '{') return '}';
	if (c == '}') return '{';
}
void PSP(char* str, int N)
{
	Stack a;
	char current;
	bool answer = true;

	for (int i = 0; i < N; ++i)
	{
		current = str[i];
		if (a.ReturnSize() == 0)
		{
			a.push_stack(current);
			continue;
		}
		if (OpenBreacket(a.GetLast()) && (Mirror(current) != a.GetLast()))
			//((current == ']' && a.GetLast() != '[' || current == '}' && a.GetLast() != '{' || current == ')' && a.GetLast() != '(')))
		{
			answer = false;
			break;
		}
		if (a.ReturnSize() != 0 && (current == ']' && a.GetLast() == '[' || current == '}' && a.GetLast() == '{' || current == ')' && a.GetLast() == '('))
		{
			a.pop_stack();
			continue;
		}
		a.push_stack(current);
	}
	//пока встречаются открывающие, их нужно отразить и в конец в правильном порядке

	char* pref = new char[a.ReturnSize()];
	char* suf = new char[a.ReturnSize()];
	int LongOfSuf = 0, LongOfPref = 0;

	if (answer)
	{
		while (a.GetLast() == '[' || a.GetLast() == '(' || a.GetLast() == '{')
		{
			suf[LongOfSuf] = Mirror(a.pop_stack());
			++LongOfSuf;
		}
		while (a.GetLast() == ']' || a.GetLast() == ')' || a.GetLast() == '}')
		{
			pref[LongOfPref] = Mirror(a.pop_stack());
			++LongOfPref;
		}
		PrintAnswerTrue(str, pref, suf, N, LongOfPref, LongOfSuf);
	}
	else
		std::cout << "IMPOSSIBLE";
	/*for (int i = a.ReturnSize(); i > 0; --i)
		std::cout << a.pop_stack() << "  ";
	*/
	delete[] suf;
	delete[] pref;
}
int long_of_string(char* str)
{
	int n = 0;
	while (str[n] != '\0')
		++n;
	return n;
}

int main()
{
	char* str = new char[800001];
	std::cin >> str;
	PSP(str, long_of_string(str));

	return 0;
}

void Stack::push_stack(char element)
{
	if (size < size_array)
	{
		array[size] = element;
	}
	else
	{
		array = grow();
		array[size] = element;
	}
	++size;
}

char Stack::pop_stack()
{
	if (size > 0)
	{
		return array[--size];
	}
	else
		return -1;
}

char Stack::GetLast()
{
	return array[size - 1];
}

Stack::~Stack()
{
	delete[] array;
}

char* Stack::grow()
{
	char* new_array = new char[size_array * 2];
	for (int i = 0; i <= size; ++i)
	{
		new_array[i] = array[i];
	}
	size_array *= 2;
	delete[] array;
	return new_array;
}
