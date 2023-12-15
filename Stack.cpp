
#include "Stack.h"

// Hàm khỏi tạo Stack
Stack::Stack()
{
	pHead = NULL;
}

// Hàm hủy Stack
Stack::~Stack()
{
	while (!IsEmpty())
	{
		Node* p = pHead;
		pHead = p->pNext;
		delete p;
	}
}

// Hmà kiểm tra Stack rỗng
int Stack::IsEmpty()
{
	return (pHead == NULL ? 1 : 0);
}

// Hàm tạo Node
Node* Stack::CreateNode(Data x)
{
	Node* p = new Node();
	p->Info = x;
	p->pNext = NULL;
	return p;
}

// Hàm thêm dữ liệu Stack
void Stack::Push(Data x)
{
	Node* p = CreateNode(x);
	if (IsEmpty())
	{
		pHead = p;
	}
	else
	{
		p->pNext = pHead;
		pHead = p;
	}
}

// Hàm lấy dữ liệu trong Stack
int Stack::Pop(Data& x)
{
	if (IsEmpty())
	{
		return 0;
	}
	else
	{
		Node* p = pHead;
		x = p->Info;
		pHead = p->pNext;
		delete p;
	}
	return 1;
}

// Hàm lấy phần tử đầu Stack
Node* Stack::GetHead()
{
	return pHead;
}

int FindSpace(string str)
{
	for (int i = 0; i < str.length(); i++)
		if (str[i] == ' ')
			return i;
	return -1;
}

void RemoveSpace(string& str)
{
	int spacePos;

	while ((spacePos = FindSpace(str)) != -1)
		str.erase(spacePos, 1);
}

 //Hàm tách chuỗi 
void ParseExpression(string expr, vector<string>& M)
{
	int n = expr.length();
	int count = 0;
	int k1 = 0;
	int k2 = 0;

	for (int i = 0; i < n; i++) {
		if ((expr[i] >= 'a' && expr[i] <= 'z') || (expr[i] >= '0' && expr[i] <= '9')) {
			if (i < n - 1) {

				for (int j = i + 1; j < n; j++) {
					if (expr[i] >= 'a' && expr[i] <= 'z') {
						if ((expr[i] >= '0' && expr[i] <= '9') && (expr[j] >= '0' && expr[j] <= '9')) {
							count++;
						}
						else
							k2 = 1;
					}

					if (
						expr[j] == ')' || 
						expr[j] == '*' || 
						expr[j] == '/' ||
						expr[j] == '+' || 
						expr[j] <= '-' || 
						expr[j] == '%' ||
						expr[j] == '^') {
						M.push_back(expr.substr(i, j - i));
						k1 = j + 1;
						i = j - 1;
						count = 0;
						break;
					}
				}
			}
			else {
				if (count >= 1) {
					
					if (k2 == 1) { 
						M.push_back(expr.substr(k1 + 1, n - 1));
					}
					else { 
						M.push_back(expr.substr(k1, n - 1));
					}
				}
				else {
					M.push_back(expr.substr(i, n - 1));
				}
			}
		}

		else if ( expr[i] == '(' || 
			expr[i] == ')' || 
			expr[i] == '*' ||
			expr[i] == '/' ||
			expr[i] == '+' || 
			expr[i] == '-' || 
			expr[i] == '%' || 
			expr[i] == '^') {
			string temp(1, expr[i]);
			M.push_back(temp);
		}
	}
}

// Khởi tạo và hủy biểu thức
Infix::Infix(){}
Infix::~Infix(){}

// Hàm xét mức độ ưu tiên của các toán tử
int Infix::precedence(string x)
{
	if (x == "sqrt" || x == "^" || x == "cos" || x == "sin" || x == "log" || x == "tan")
		return 3;

	if (x == "*" || x == "/" || x == "%")
		return 2;

	else if (x == "+" || x == "-")
		return 1;

	else if (x == "(")
		return 0;

	return -1;
}

// Hàm kiểm tra toán hạng hay toán tử
int Infix::checkOper(string x)
{
	if (x == "sqrt" || x == "cos" ||  x == "sin" || x == "tan" || x == "log" || x == "exp")
		return 3;

	if (x == "*" || x == "/" || x == "%" || x == "+" || x == "-" || x == "^")
		return 2;

	else 
		return 1;
	
}

// Hàm tính giá trị của hàm toán học
string Infix::calculateValueFunc( string a, string x)
{
	double result = 0;

	if (x == "sqrt")
		result = double(sqrt(atof(a.c_str())));

	if (x == "cos")
		result = double(cos(atof(a.c_str())));

	if (x == "sin")
		result = double(sin(atof(a.c_str())));

	if (x == "tan")
		result = double(tan(atof(a.c_str())));

	if (x == "log")
		result = double(log(atof(a.c_str())));
	
	if(x == "exp")
		result = double(exp(atof(a.c_str())));

	string strResult = to_string(result);
	return strResult;
}

// Hàm tính giá trị các phép toán hai ngôi
string Infix::calculateValueInfix(string b, string x, string a)
{
	double result = 0;

	if (x == "^") {
		result = 1;
		for (int i = 1; i <= int(atof(a.c_str())); i++)
			result = result * atof(b.c_str());
	}

	if (x == "%")
		result = int(atof(b.c_str())) % int(atof(a.c_str()));

	if (x == "*")
		result = atof(b.c_str()) * atof(a.c_str());

	else if (x == "/")
		result = atof(b.c_str()) / atof(a.c_str());

	else if (x == "+")
		result = atof(b.c_str()) + atof(a.c_str());

	else if (x == "-")
		result = atof(b.c_str()) - atof(a.c_str());

	string strResult = to_string(result);
	return strResult;
}

// Hàm tính toán biểu thức trung tố
double Infix::calculateExpr(vector<string> M)
{
	Stack* StOperand = new Stack(); // Stack lưu các toán hạng
	Stack* StOperator = new Stack(); // Stack lưu các toán tử 
	double result = 0;
	int n = M.size();

	for (int i = 0; i < n; i++) {

		// kiểm tra toán tử hay toán hạng đẩy vào Stack và 
		//xét mức độ ưu tiên để tính giá trị biểu thức
		if (checkOper(M[i]) == 1) {

			if (M[i] != "(" && M[i] != ")") {
				StOperand->Push(M[i]);
			}
			else if (M[i] == "(") {
				StOperator->Push(M[i]);
			}
			else if (M[i] == ")") {
				if (result == 1) {
					string a = "";
					StOperand->Pop(a);
					string b = "";
					StOperator->Pop(b);
					string c = "";
					StOperator->Pop(c);
					StOperand->Push(calculateValueFunc(a, c));
					result = 0;
				}
				else {
					while (StOperator->GetHead()->Info != "(")
					{
						string a = "";
						StOperand->Pop(a);
						string x = "";
						StOperator->Pop(x);
						string b = "";
						StOperand->Pop(b);
						StOperand->Push(calculateValueInfix(b, x, a));
					}
					string t = "";
					StOperator->Pop(t);
				}
			}
		}

		else if (checkOper(M[i]) == 2) {

			while (!StOperator->IsEmpty() && (precedence(M[i]) <= precedence(StOperator->GetHead()->Info))) {
				string a = "";
				StOperand->Pop(a);
				string x = "";
				StOperator->Pop(x);
				string b = "";
				StOperand->Pop(b);
				StOperand->Push(calculateValueInfix(b, x, a));
			}
			StOperator->Push(M[i]);
		}

		else if (checkOper(M[i]) == 3) {

			result = 1;
			StOperator->Push(M[i]);
		}
	}
	while (!StOperator->IsEmpty()) {
		string a = "";
		StOperand->Pop(a);
		string x = "";
		StOperator->Pop(x);
		string b = "";
		StOperand->Pop(b);
		StOperand->Push(calculateValueInfix(b, x, a));
	}

	string strResult = "";
	StOperand->Pop(strResult);
	result = atof(strResult.c_str());
	return result;
}
