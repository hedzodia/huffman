#include "Node.h"

Node::Node(Node* pNodeG, Node* pNodeD)
{
	frequency = pNodeD->frequency + pNodeG->frequency;
	character = NULL;
	nodeRight = pNodeD;
	nodeLeft = pNodeG;
}

Node::Node(int pFrequence, char pCaractere) {
	frequency = pFrequence;
	character = pCaractere;
	nodeRight = NULL;
	nodeLeft = NULL;
}

Node::~Node()
{
}

int Node::GetFrequency() const
{
	return frequency;
}

char Node::GetCharacter() const
{
	return character;
}

Node * Node::GetLeft() const
{
	return nodeLeft;
}

Node * Node::GetRight() const
{
	return nodeRight;
}

ostream & operator<<(ostream & os, Node const & n)
{
	os << "Node((" << n.GetCharacter() << "," << n.GetFrequency() << ")";
	if (n.nodeRight != nullptr){os << "{" << *n.nodeLeft<<"," << *n.nodeRight << "}";}
	os << ")";
	return os;
}