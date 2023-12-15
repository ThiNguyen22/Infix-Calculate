#pragma once
#include <iostream>
#include <stdio.h>
#include <vector>
#include <sstream>
#include <cmath>
#include <string>
#include <cstring>
using namespace std;

typedef string Data;

class Node
{
public:
	Data Info;
	Node* pNext = NULL;
};

class Stack
{
private:
	Node* pHead;

public:
	Stack();
	~Stack();
	int IsEmpty();
	Node* CreateNode(Data x);
	void Push(Data x);
	int Pop(Data& x);
	Node* GetHead();
};

class Infix
{
public:
	Infix();
	~Infix();
	int precedence(string x);
	int checkOper(string x);
	string calculateValueInfix(string b, string x, string a);
	string calculateValueFunc(string x, string a);
	double calculateExpr(vector<string> M);

};

void ParseExpression(string expr, vector<string>& M);
