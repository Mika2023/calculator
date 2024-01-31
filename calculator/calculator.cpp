#include <iostream>
#include <string>
#include <cmath>

using namespace std;


class Stack
{
	double arr[1000];
	int head, maxsize;
public:
	Stack() : head(0), arr(), maxsize(1000) {};
	void push(double val)
	{
		if (head != maxsize) arr[head++] = val;
	}
	double get_top()
	{
		if (head)
			return (arr[head - 1]);
		else
			return -1000000000;
	}
	double pop()
	{
		double val = get_top();
		if (val != -1000000000) arr[head--] = 0;
		return val;
	}
	int is_empty()
	{
		return (head) ? 0 : 1;
	}
};

int priority(char sign)
{
	switch (sign)
	{
	case 's':
	case 'c':
	case 't':
	case 'l':
	case 'C'://котангенс обозначим как C, в вводе также вместо cot напишем C
		return 4;
	case '^':
		return 3;
	case '*':
	case '/':
		return 2;
	case '-':
	case '+':
		return 1;
	}
	return 0;
}

int main()
{
	char polish[1000] = { 0 };
	int a = 0;
	int f = 1;
	int flag_ignored = 0;
	Stack signs;
	char current_symbol;
	current_symbol = cin.peek();
	double number = 0;
	//cout << current_symbol;    print current symbol
	// для стеков создадим свой заголовочный файл?

	while (cin.peek() != '\n')
	{
		current_symbol = cin.peek();
		if (current_symbol >= '0' && current_symbol <= '9') // read a number
		{
			cin >> number; //		TO DO: reading from the file
			string stNumber = to_string(number); // convert to string; need to work with polish notation
			int number_length = stNumber.length(); 
			int number_iterator = 0;
			while (number_length)
			{
				polish[a++] = stNumber[number_iterator++];
				number_length--;
			}
			polish[a++] = ' '; // separate from the next number
			f = 0;
			continue;
		}

		if (current_symbol == '(')
		{
			f = 1;
			signs.push('(');
			cin.ignore();
		}
		else if (current_symbol == ')')
		{
			f = 0;
			while (signs.get_top() != -1000000000 && signs.get_top() != '(')
			{
				polish[a++] = signs.pop();
				polish[a++] = ' ';
			}
			if (signs.get_top() == '(')
			{
				signs.pop();
			}
			cin.ignore();
		}
		else
		{
			if (current_symbol == '-' && f) // унарный минус
			{
				cin.ignore();
				cin >> number; //		TO DO: reading from the file
				number = -1 * number;
				string stNumber = to_string(number); // convert to string; need to work with polish notation
				int number_length = stNumber.length();
				int number_iterator = 0;
				while (number_length)
				{
					polish[a++] = stNumber[number_iterator++];
					number_length--;
				}
				polish[a++] = ' '; // separate from the next number
				f = 0;
				continue;
			}
			if (current_symbol == 'l')
			{
				cin.ignore(); cin.ignore(); cin.ignore(); cin.ignore(); //skip l,o,g,(
				double osn, ch = 0;
				cin >> osn;

				string stNumber = to_string(osn); // convert to string; need to work with polish notation
				int number_length = stNumber.length();
				int number_iterator = 0;
				while (number_length)
				{
					polish[a++] = stNumber[number_iterator++];
					number_length--;
				}
				polish[a++] = ' '; // separate from the next number


				cin.ignore(); //skip ,
				cin >> ch;

				stNumber = to_string(ch); // convert to string; need to work with polish notation
				number_length = stNumber.length();
				number_iterator = 0;
				while (number_length)
				{
					polish[a++] = stNumber[number_iterator++];
					number_length--;
				}
				polish[a++] = ' '; // separate from the next number
				f = 0;
				cin.ignore();

			}
			int prior = priority(current_symbol); //		TO DO:  в строке: sin; мы считали s, определили приоритет, 
			while (!signs.is_empty() && priority(signs.get_top()) >= prior && signs.get_top() != '(')
			{
				polish[a++] = signs.pop();
				polish[a++] = ' ';
			}
			signs.push(current_symbol); // или priority вернет 0, и если (!priority) то символ не пушим
			if (!flag_ignored) // need to check; if we met "-", we already skipped the symbol
			{
				cin.ignore();
				flag_ignored = 0;
			}
			if (current_symbol == 's' || current_symbol == 'c' || current_symbol == 't')
			{
				cin.ignore();
				cin.ignore();
			}
		}
	}


	double res = 0;
	Stack nums;
	int i = 0;
	double n1 = 0;
	double n2 = 0;
	while (i < a)
	{
		if (polish[i] == ' ')
		{
			++i;
			continue;
		}
		if (polish[i] >= '0' && polish[i] <= '9') // positive number
		{
			string numberPolish = "";
			while (polish[i] >= '0' && polish[i] <= '9' || polish[i] == '.')
			{
				numberPolish += polish[i++];
			}
			double num = 0;
			num = stod(numberPolish); // convert from string to double
			nums.push(num);
			continue;
		}
		else if (i + 1 < a && polish[i] == '-' && polish[i + 1] >= '0' && polish[i] <= '9') // negative number
		{
			i++; // skip the current "-". case "-" will be ignored
			string numberPolish = "";
			while (polish[i] >= '0' && polish[i] <= '9' || polish[i] == '.')
			{
				numberPolish += polish[i++];
			}
			double num = 0;
			num = stod(numberPolish);
			num = -1 * num; // make the number negative
			nums.push(num);
			continue;
		}
		switch (polish[i])
		{
		case '+':
			res = nums.pop() + nums.pop();
			break;
		case '-':
			res = -(nums.pop() - nums.pop());
			break;
		case '^':
			res = pow(nums.pop(), nums.pop());
			break;
		case 's':
			res = sin(nums.pop());
			break;
		case 'c':
			res = cos(nums.pop());
			break;
		case 't':
			res = tan(nums.pop());
			break;
		case 'l':
			n1 = nums.pop();
			n2 = nums.pop(); // n2 - основание, n1 - число 
			res = log(n1) / log(n2); // логарифм по основанию b от числа a == натуральный логарифм (a) / натуральный логарифм (b). 
			//Для вычисления логарифма нужно обработать два числа, log(x) вычисляет натуральный логарифм
			break;
		case '*':
			res = nums.pop() * nums.pop();
			break;
		case '/':
			n1 = nums.pop();
			n2 = nums.pop();
			res = n2 / n1;
			break;
		case 'C': //cot = C
			res = 1 / tan(nums.pop());
			break;

		}
		nums.push(res);
		++i;
	}


	cout << res << endl;
}
