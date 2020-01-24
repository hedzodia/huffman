#include "Node.h"
using namespace std;

#pragma region variables
ifstream fs;
vector<Node*> tree;
string temp;
string tempDecode;
string arrayEncode;

#pragma endregion

#pragma region Encode
void CreateTree(vector<pair<int, char>> tabFreq) {
	bool rootCreated = false;
	int sumFreq = 0;
	int j = 0;

	for (int i = 0; i < tabFreq.size(); i++){
		Node* n = new Node(tabFreq[i].first, tabFreq[i].second);
		tree.push_back(n);
		sumFreq += tabFreq[i].first;
	}

	while (!rootCreated){
		Node* newNode = new Node(tree[j], tree[j + 1]);
		for (int i = 0; i < tree.size(); i++){
			if (tree[i]->GetFrequency() >= newNode->GetFrequency()){
				tree.insert(tree.begin() + i, newNode);
				break;
			}
			else if (i == tree.size()-1){
				tree.push_back(newNode);
				break;
			}
		}
		if (newNode->GetFrequency() >= sumFreq){
			rootCreated = true;
		}
		j += 2;	
	}
}

vector<pair<int, char>> CalculateFrequency(string str) {
	map<char, int> tabTemp;
	vector<pair<int, char>> tabFreq;
	for (int i = 0; i < str.size(); i++) {tabTemp[str[i]]++;}	
	for (map<char, int>::iterator it = tabTemp.begin(); it != tabTemp.end(); ++it) {tabFreq.push_back(pair<int, char>(it->second, it->first));}
	sort(tabFreq.begin(), tabFreq.end());
	return tabFreq;
} 

void EncodeRec(char c, Node *root, string result) {
	if (root->GetCharacter() == c){
		temp += result;
		bool alreadyIn = false;
		for (int i = 0; i < arrayEncode.size(); i++){
			while (i != 0 && arrayEncode[i] != ';') {i++;}
			if (arrayEncode[i] == ';'){i++;}
			if (arrayEncode[i] == c){
				alreadyIn = true;
				break;
			}
		}
		if (!alreadyIn){arrayEncode += c + result + ";";}
	}		
	else if (root->GetRight() != nullptr){
		EncodeRec(c, root->GetLeft(), result + '0');
		EncodeRec(c, root->GetRight(), result + '1');
	}
}

void Encode(string s) {
	string result = "";
	for (int i = 0; i < s.size(); i++){EncodeRec(s[i], tree[tree.size() - 1], result);}
}

void Code(string text) {
	fs.open(text);
	stringstream strStream;
	strStream << fs.rdbuf();
	string str = strStream.str();
	string result;
	if (fs.is_open()){
		vector<pair<int, char>> tabFreq = CalculateFrequency(str);
		CreateTree(tabFreq);
		Encode(str);
	}
	cout << temp;
	fs.close();
	ofstream ofsCode("code.txt", ios::out | ios::trunc);
	if (ofsCode){
		ofsCode << arrayEncode; // encoded array
		ofsCode << endl; 
		ofsCode << endl;
		ofsCode << temp; // coded text
		ofsCode.close();
	}
}
#pragma endregion

#pragma region Decode
string Decode(string str) {
	map<string, char> decodeArray;
	string result;
	string temp;
	int i = 0;
	for (i = 0; i < str.size(); i++){
		temp = "";
		if (str[i] == '\n' && str[i + 1] == '\n'){
			i += 2;
			break;
		}
		char c = str[i];
		i++;
		while (str[i] != ';') {
			temp += str[i];
			i++;
		}
		decodeArray[temp] = c;
		temp = "";
	}
	temp = "";
	for (i; i < str.size(); i++){
		map <string, char>::iterator it;
		temp += str[i];
		it = decodeArray.find(temp);
		if (it != decodeArray.end()){
			result += decodeArray.find(temp)->second;
			temp = "";
		}
	}
	return result;
}

void DecodeRec() {
	fs.open("code.txt", fstream::in);
	stringstream strStream;
	strStream << fs.rdbuf();
	string str = strStream.str();
	string result;
	if (fs.is_open()){result = Decode(str);}
	ofstream ofsDecode("decode.txt", ios::out | ios::trunc);
	if (ofsDecode){
		ofsDecode << result;
		ofsDecode.close();
	}
}
#pragma endregion

int main() {
	string choix = "0";
	string text;
	while (true){
		cout << "Please choose 0 to code and 1 to decode (2 to exit the program) : ";
		cin >> choix;
		system("cls");
		if (choix == "0"){
			cout << "Name of your text file to code (without the extension): ";
			cin >> text;
			Code(text + ".txt");
			cout << endl;			
		}
		else if (choix == "1"){
			DecodeRec(); 
			cout << "Decode done";
			cout << endl;
		}
		else if (choix == "2"){
			break;
		}
		else cout << "error: choose between 0 and 2 \n" <<endl;
	}
}