// Student name: 
// Studnet ID  : 

// Submission deadline: Thursday, 28 March 2019, 2 pm

// Implement the functions evaluate_postfix() and evaluate_infix()

// Binary operators in the expression are delimited by white-space char.
// Operand with negative value (preceded with the minus sign) is allowed.
// Operands are delimited by white-space char or bracket (in the case of infix expression).

#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <cmath>  // pow(double x, double y), compute the value of x to power y

using namespace std;
bool isOperator(const string& expr, int i);
double evaluateOperator(char opr, const double& d1, const double& d2);
int precNum(char opr);
double nextOperand(const string& expr, int& i);

//------------------- function to evaluate postfix expression

double evaluate_postfix(const string& postfix_expr)
{
	stack<double> S;

	int i = 0;
	while (i < postfix_expr.length())
	{
		if (isspace(postfix_expr[i])) 
			i++;
		else if (isOperator(postfix_expr, i))
		{
			char opr = postfix_expr[i++];

			double operand2 = S.top();
			S.pop();
			double operand1 = S.top();
			S.pop();
			
			S.push(evaluateOperator(opr, operand1, operand2));
		}
		else							
			S.push(nextOperand(postfix_expr, i));		
	}

	return S.top();
}

//------------------- function to evaluate infix expression

void process_opr(stack<char>& oprStack, stack<double>& dataStack)
{
	// process the operator at top of oprStack
	// operands are retrieved from dataStack, result pushed onto dataStack

	char opr = oprStack.top();
	oprStack.pop();

	double operand2 = dataStack.top(); 
	dataStack.pop();

	double operand1 = dataStack.top();
	dataStack.pop();

	dataStack.push(evaluateOperator(opr, operand1, operand2));
}

double evaluate_infix(const string& infix_expr)
{
	stack<double> dataStack;
	stack<char> oprStack;

	oprStack.push('@');  // bottom of stack symbol, with lowest precedence number

	int i = 0;
	while (i < infix_expr.length())
	{
		if (isspace(infix_expr[i]))  
			i++;
		else if (infix_expr[i] == '(')
			oprStack.push(infix_expr[i++]);
		else if (infix_expr[i] == ')')
		{
			// evaluate operators in oprStack until oprStack.top() == '('
			while (oprStack.top() != '(')
				process_opr(oprStack, dataStack);
			
			oprStack.pop(); // discard the '('
			i++;            // consume the ')' in infix_expr
		}
		else if (isOperator(infix_expr, i))
		{
			// evaluate operator at top of oprStack with precedence number >= precedence number of current opr
			char opr = infix_expr[i++];
			int pn = precNum(opr);
			while (precNum(oprStack.top()) >= pn)
				process_opr(oprStack, dataStack);
			
			oprStack.push(opr);
		}
		else  // operand		
			dataStack.push(nextOperand(infix_expr, i));		
	}

	// evaluate remaining operators in oprStack, final result is in dataStack
	while (oprStack.top() != '@')
		process_opr(oprStack, dataStack);
	
	return dataStack.top();
}

// ---------------------------------------- functions given to you

bool isOperator(const string& expr, int i)
{
	// return true if the symbol (char) at index i of expr is an operator

	char c = expr[i];
	if (c == '+' || c == '*' || c == '/' || c == '$')
		return true;

	// not the minus sign of an operand
	if (c == '-' && (i+1 >= expr.length() || isspace(expr[i+1])))
		return true;

	return false;
}

double evaluateOperator(char opr, const double& d1, const double& d2)
{
	//This output statement is for debugging purpose.
	//cout << "evaluate " << d1 << " " << opr << " " << d2 << endl;

	switch (opr) 
	{
		case '+' : return d1 + d2;
		case '-' : return d1 - d2;
		case '*' : return d1 * d2;
		case '/' : return d1 / d2;
		case '$' : return pow(d1, d2);
		default : return 0;
	}
}

int precNum(char opr)
{
	if (opr == '+' || opr == '-')
		return 1;
	if (opr == '*' || opr == '/')
		return 2;
	if (opr == '$')
		return 3;

	return 0; // default precedence number for '(' and '@'
}

double nextOperand(const string& expr, int& i)
{
	// return the value of the operand at index i of the expression
	// index i is advanced to the char that follows the extracted operand

	int j = i;
	while (j < expr.length() && !isspace(expr[j]) && expr[j] != ')' && expr[j] != '(')
		j++;

	string number = expr.substr(i, j-i);
	i = j;

	return stod(number);  // string to double conversion
}

int main()
{	
	cout << "----- Evaluate Postfix Expression -----" << endl << endl;

	ifstream infile("postfix_expr.txt");
	if (!infile.is_open())
	{
		cout << "Error: cannot open postfix_expr.txt" << endl;
		system("pause");
		exit(0);
	}

	string postfix_expr;
	while (getline(infile, postfix_expr))
	{
		double value = evaluate_postfix(postfix_expr);

		cout << "postfix expression: " << postfix_expr << " = " << value << endl << endl;
	}
	infile.close();

	cout << endl;
	cout << "----- Evaluate Infix Expression -----" << endl << endl;

	infile.open("infix_expr.txt");
	if (!infile.is_open())
	{
		cout << "Error: cannot open prefix_expr.txt" << endl;
		system("pause");
		exit(0);
	}

	string infix_expr;
	while (getline(infile, infix_expr))
	{		
		double value = evaluate_infix(infix_expr);
		cout << "infix expression: " << infix_expr << " = " << value << endl << endl;
	}	
	infile.close();

	system("pause");
	exit(0);
}