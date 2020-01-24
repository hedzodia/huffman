#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <iterator>
#include <algorithm>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class Node
{
private:
	int frequency;
	char character;
	Node* nodeRight;
	Node* nodeLeft;

public:
	Node(int p_Frequency, char p_Character);
	Node(Node* p_NodeRight, Node* p_NodeLeft);
	~Node();

	int GetFrequency() const;
	char GetCharacter() const;

	Node* GetLeft() const;
	Node* GetRight() const;

	friend ostream& operator<<(ostream& os, Node const& n);
};