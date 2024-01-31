#include <iostream>
#include <string>
#include <cmath>

using namespace std;


int brackets(const char polish[])
{
	int i = 0;
	int open = 0;
	while (polish[i])
	{
		if (polish[i] == 40)
			open = open + 1;
		else
			open = open - 1;

		if (open < 0)
			break;

		i++;
	}
	if (open == 0)
		return 1;
	else
		return 0;
}



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

class Maths
{
	double n1;
	double n2;
public:
	Maths() :n1(0), n2(0) {};
	Maths(char operator_, Stack* nums)
	{
		switch (operator_)
		{
		case 'l':
		case '+':
		case '-':
		case '^':
		case '*':
		case '/':
			n1 = (*nums).pop();
			n2 = (*nums).pop();
		//	cout << "pop:" << n1 << ' ' << n2 << endl;
			break;
		case 's':
		case 'c':
		case 'C':
		case 't':
			n1 = (*nums).pop();
			break;
		}
	}
	int CheckOperands(char operator_)const
	{
		switch (operator_)
		{
		case '/':
			if (n1 == 0)
				return 1;
		case 'l':
			if (n2 <= 0 || n1 <= 0 || n2 == 1)
				return 2;
		case 'C':
			if (tan(n1) == 0)
				return 3;
		case '^':
			if (!n2)
			{
				if (n1 < 0)
					return 4;
			}
			else if (n1 - int(n1) > 0.0000001)
				return 4;
		}
		return 0;
	}
	double Result(char operator_)
	{
		double res = 0;
		switch (operator_)
		{
		case '+':
			res = n1 + n2;
			break;
		case '-':
			res = -(n1 - n2);
			break;
		case '^':
			res = pow(n2, n1);
			break;
		case 's':
			res = sin(n1);
			break;
		case 'c':
			res = cos(n1);
			break;
		case 't':
			res = tan(n1);
			break;
		case 'l':
			res = log(n1) / log(n2); // логарифм по основанию b от числа a == натуральный логарифм (a) / натуральный логарифм (b). 
			//Для вычисления логарифма нужно обработать два числа, log(x) вычисляет натуральный логарифм
			break;
		case '*':
			res = n1 * n2;
			break;
		case '/':
			res = n2 / n1;
			break;
		case 'C': //cot = C
			res = 1 / tan(n1);
			break;
		}
		//cout << "res:" << n1 << ' ' << n2 << ' ' << res << endl;
		return(res);
	}
};

int priority(char sign)
{
	switch (sign)
	{
	case 's':
	case 'c':
	case 't':
	case 'C'://котангенс обозначим как C, в вводе также вместо cot напишем C
		return 4;
	case '^':
	case 'l':
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

			int prior = priority(current_symbol); //		TO DO:  в строке: sin; мы считали s, определили приоритет, 
			while (!signs.is_empty() && priority(signs.get_top()) >= prior && signs.get_top() != '(')
			{
				polish[a++] = signs.pop();
				polish[a++] = ' ';
			}
			if (prior) signs.push(current_symbol); // или priority вернет 0, и если (!priority) то символ не пушим
			if (!flag_ignored) // need to check; if we met "-", we already skipped the symbol
			{
				cin.ignore();
				flag_ignored = 0;
			}
			if (current_symbol == 's' || current_symbol == 'c' || current_symbol == 't' || current_symbol == 'l')
			{
				cin.ignore();
				cin.ignore();
			}
		}
	}

	while (!signs.is_empty())
	{
		polish[a++] = signs.pop();
		polish[a++] = ' ';
	}


	//cout << polish << endl;

	double res = 0;
	Stack nums;
	int i = 0;
	double n1 = 0;
	double n2 = 0;
	int flag_result = 1;
	while (i < a && flag_result)
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

		if (priority(polish[i]))
		{
			Maths Math(polish[i], &nums);
			int errors = Math.CheckOperands(polish[i]);
			if (!errors)
			{
				res = Math.Result(polish[i]);
				nums.push(res);
				//cout << res << endl;
			}
			else
			{
				switch (errors)
				{
				case 1:
					cout << "Error : Division by zero" << endl;
					break;
				case 2:
					cout << "Error : Wrong log data" << endl;
					break;
				case 3:
					cout << "Error : Wrong cot data" << endl;
					break;
				case 4:
					cout << "Error : Wrong ^ data" << endl;
				}
				flag_result = 0;
			}
		}



		++i;
	}
	int flag_brackets = brackets(polish);
	if (!flag_brackets)
		cout << "Error : Wrong Brackets input" << endl;
	if (flag_result && flag_brackets) cout << res << endl;
}
