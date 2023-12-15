#include "Stack.h"

int main()
{
	string expr;
	cout << "\n\t ***------------Welcome to the program------------***";
	cout << "\n\n\tEnter:  ";
	getline(cin, expr);

	Infix* infix = new Infix();
	vector<string> M;
	ParseExpression(expr, M);

	cout << "\n\tEqual: " << infix->calculateExpr(M) << endl << endl;

	return 0;
}
