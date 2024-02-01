#include <iostream>
#include <string>
#include <cmath>
#include <fstream>

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

class Correct
{
	string expression;
public:
	Correct() : expression() {};
	Correct(string exp) : expression(exp) {};
	int is_cor_brackets()
	{
		int c = 0;
		for (int i = 0; i < expression.length(); ++i)
		{
			if (expression[i] == '(') ++c;
			else if (expression[i] == ')')
			{
				--c;
				if (c < 0) return 0;
			}
		}
		if (!c) return 1;
		return 0;
	}
	void delete_spaces()
	{
		int start = expression.find(" ");
		while (start != string::npos)
		{
			expression.erase(start, 1);
			start = expression.find(" ");
		}
	}
	void change_ctg()
	{
		int start = expression.find("ctg");
		while (start != string::npos)
		{
			expression.replace(start,3,"C");
			start = expression.find("ctg");
		}
	}
	string get_expr() const
	{
		return expression;
	}
	void set_expr(string value)
	{
		expression = value;
	}
};



struct Variable
{
	string name;
	double value;
};

class ListVariable
{
	Variable* vars;
	int size, max_size;
public:
	ListVariable(int s): vars(nullptr), size(0), max_size(s)
	{
		if (s > 0) vars = new Variable[max_size];
	}
	int is_empty()
	{
		return (size) ? 1 : 0;
	}
	int is_full()
	{
		return max_size == size;
	}
	void add(Variable f)
	{
		if (!is_full()) vars[size++] = f;
	}
	int find(string n)
	{
		for (int i = 0; i < size; ++i)
		{
			if (vars[i].name == n) return i;
		}
		return -1;
	}
	string repl(string expr, string name_var)
	{
		int i = find(name_var);
		if (i != -1)
		{
			int start = expr.find(vars[i].name);
			while (start != string::npos)
			{
				expr.replace(start, vars[i].name.length(), to_string(vars[i].value));
				start = expr.find(vars[i].name);
			}
		}
		return expr;
	}
	int get_size() const
	{
		return size;
	}
	Variable* get_vars() const
	{
		return vars;
	}
};
ListVariable listV(10);
class Function
{
	string name, argument;
	Correct definition;
public:
	Function() : name(), argument(), definition() {};
	Function(string n, string d, string a) : name(n), definition(d), argument(a) {};
	int is_correct()
	{
		if (!definition.is_cor_brackets()) return 0;
		definition.change_ctg();
		definition.delete_spaces();
		return 1;
	}
	string get_name() const
	{
		return name;
	}
	string get_arg() const
	{
		return argument;
	}
	string get_def() const
	{
		return definition.get_expr();
	}
	void set_def(string value)
	{
		definition.set_expr(value);
	}
	void replace_var()
	{
		string changed = definition.get_expr();
		changed = listV.repl(changed, argument);
		set_def(changed);
	}
};

class ListFunction
{
	Function* funcs;
	int size, max_size;
public:
	ListFunction(int s) : funcs(nullptr), size(0), max_size(s)
	{
		if (s > 0) funcs = new Function[max_size];
	}
	int is_empty()
	{
		return (size)? 1: 0;
	}
	int is_full()
	{
		return max_size == size;
	}
	void add(Function f)
	{
		if (!is_full())
		{
			f.is_correct();
			funcs[size++] = f;
		}
	}
	int find(string n)
	{
		for (int i = 0; i < size; ++i)
		{
			if (funcs[i].get_name() == n) return i;
		}
		return -1;
	}
	void replace_variable(string n)
	{
		int i = find(n);
		if (i != -1)
		{
			int j = find(funcs[i].get_arg());
			if (j == -1)
			{
				funcs[i].replace_var();
				return;
			}
			replace_variable(funcs[i].get_arg());
		}
	}
	string replace_function(string expr, string n)
	{
		int i = find(n);
		if (i != -1)
		{
			replace_variable(n);
			int start = expr.find(funcs[i].get_name());
			while (start != string::npos)
			{
				expr.replace(start, funcs[i].get_name().length()+ funcs[i].get_arg().length()+2, "("+funcs[i].get_def()+")");
				start = expr.find(funcs[i].get_name());
			}
		}
		return expr;
	}
	int get_size() const
	{
		return size;
	}
	Function* get_funcs() const
	{
		return funcs;
	}
};
ListFunction listF(10);
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
string re_write_file(ifstream& f)
{
	
	string expr;
		f >> expr;
		Correct expression(expr);
		if (!expression.is_cor_brackets()) return "";
		expression.change_ctg();
		expression.delete_spaces();
		string name, def;
		while (f >> name >> def)
		{
			if (name.find("(") == string::npos)
			{
				Variable item;
				item.name = name;
				item.value = stod(def);
				listV.add(item);
			}
			else
			{
				string arg = name.substr(name.find("(") + 1, name.length() - name.find("(") - 2);
				name = name.substr(0, name.find("("));
				Function item(name, def, arg);
				listF.add(item);
			}
		}
		for (int i = 0; i < listF.get_size(); ++i)
		{
			expression = listF.replace_function(expression.get_expr(), listF.get_funcs()[i].get_name());
		}
		for (int i = 0; i < listV.get_size(); ++i)
		{
			expression = listV.repl(expression.get_expr(), listV.get_vars()[i].name);
		}
		//f << expression.get_expr()<<endl;
		return expression.get_expr();
	
}

int main()
{
	ifstream fs;
	fs.open("input.txt");
	//C:\\Users\\yajul\\source\\repos\\calculator\\calculator
	string r = re_write_file(fs);
	fs.close();
	ofstream fo;
	fo.open("input.txt");
	if (r=="")
	{
		cout << "Неправильный ввод" << endl;
		return 0;
	}
	fo << r << endl;
	fo.close();
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
