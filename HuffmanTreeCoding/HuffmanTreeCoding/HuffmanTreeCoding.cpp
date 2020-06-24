//Project 4: HuffmanTreeCoding
//Joseph Bdaro
//CS323

#include <iostream>
#include <fstream>
using namespace std;

//huffman node class
class HtreeNode {
public:
	string chStr;
	int prob;
	string code;
	HtreeNode* left;
	HtreeNode* right;
	HtreeNode* next;

	//constuctor
	HtreeNode(string chStr, int prob, string code, HtreeNode* left, HtreeNode* right, HtreeNode* next) {
		this->chStr = chStr;
		this->prob = prob;
		this->code = code;
		this->left = left;
		this->right = right;
		this->next = next;
	}

	//print node method
	static void printNode(HtreeNode* T, ofstream& outFile) {
		if(T->next != NULL && T->left == NULL && T->right == NULL) {
			outFile << "(" << T->chStr << ", " << T->prob << ", " << T->code << ", " << "NULL, NULL, " << T->next->chStr <<")->";
		}

		else if (T->next != NULL && (T->next->left != NULL || T->next->right != NULL)) {
			outFile << "(" << T->chStr << ", " << T->prob << ", " << T->code << ", " << T->left->chStr << ", " <<T->right->chStr <<", " << T->next->chStr << ")->";
		}
		
		else {
			outFile << "(" << T->chStr << ", " << T->prob << ", " << T->code << ", " << T->left->chStr << ", " << T->right->chStr << ")->";

		}
	}
};

//huffman linked list class
class constructHuffmanLList {

public:
	HtreeNode* listHead = new HtreeNode("dummy", 0, "dummy", NULL, NULL, NULL);
	//contructor
	constructHuffmanLList(ifstream& inFile, ofstream& outFile) {
		if (inFile.is_open()) {
			string chr;
			int prob;
			while (inFile >> chr) {
				inFile >> prob;
				HtreeNode* newNode = new HtreeNode(chr, prob, "", NULL, NULL, NULL);
				listInsert(listHead, newNode);
				printList(listHead, outFile);
			}
			outFile << endl;
		}
	}
	
	//inserts node into LL
	static void listInsert(HtreeNode* listHead, HtreeNode* newNode) {
		HtreeNode* spot = findSpot(listHead, newNode);
		newNode->next = spot->next;
		spot->next = newNode;
	}

	//used by listinsert to find the spot to insert the node in the LL
	static HtreeNode* findSpot(HtreeNode* listHead, HtreeNode* newNode) {
		HtreeNode* spot = listHead;
		while (spot->next != NULL && spot->next->prob < newNode->prob) {
			spot = spot->next;
		}
		return spot;
	}

	//prints the entire list by invoking printnode
	static void printList(HtreeNode* listHead, ofstream& outFile) {
		
		HtreeNode* itterator = listHead;
		while (itterator->next != NULL) {
			HtreeNode::printNode(itterator, outFile);

			itterator = itterator->next;

		}
		outFile << "(" << itterator->chStr << ", " << itterator->prob << ", " << itterator->code << ", " << "NULL, NULL, NULL)-> NULL";
		outFile << endl;
	}

};

//huffman binary tree class
class HuffmanBinaryTree {
public:
	HtreeNode* Root;
	//constructor
	HuffmanBinaryTree(HtreeNode* listHead, ofstream& outFile) {
		while (listHead->next->next != NULL) {
			HtreeNode* newNode = new HtreeNode(listHead->next->chStr + listHead->next->next->chStr, listHead->next->prob + listHead->next->next->prob, "", listHead->next, listHead->next->next, NULL);
			constructHuffmanLList::listInsert(listHead, newNode);
			listHead->next = listHead->next->next->next;
			constructHuffmanLList::printList(listHead, outFile);
		}
		Root = listHead;
	}

	//preorder traversal of tree
	void preOrderTraversal(HtreeNode* T, ofstream& outFile) {
		if (isLeaf(T)) {
			HtreeNode::printNode(T, outFile);
		}
		else {
			HtreeNode::printNode(T, outFile);
			preOrderTraversal(T->left, outFile);
			preOrderTraversal(T->right, outFile);
		}
	}

	//inorder traversal of tree
	void inOrderTraversal(HtreeNode* T, ofstream& outFile) {
		if (isLeaf(T)) {
			HtreeNode::printNode(T, outFile);
		}
		else {
			preOrderTraversal(T->left, outFile);
			HtreeNode::printNode(T, outFile);
			preOrderTraversal(T->right, outFile);
		}
	}

	//postorder traversal of tree
	void postOrderTraversal(HtreeNode* T, ofstream& outFile) {
		if (isLeaf(T)) {
			HtreeNode::printNode(T, outFile);
		}
		else {
			preOrderTraversal(T->left, outFile);
			preOrderTraversal(T->right, outFile);
			HtreeNode::printNode(T, outFile);

		}
	}

	//checks if node is a leaf
	bool isLeaf(HtreeNode* T) {
		if (T->left == NULL && T->right == NULL) {
			return true;
		}
		else {
			return false;
		}
	}

	//constructs the new binary code for the characters
	void constructCharCode(HtreeNode* T, string code, ofstream& outFile) {
		if (isLeaf(T)) {
			T->code = code;
			outFile << T->chStr << " = " << T->code <<endl;
		}
		else {
			constructCharCode(T->left, code + "0", outFile);
			constructCharCode(T->right, code + "1", outFile);
		}

	}
};


int main(int argc, char* argv[])
{
	ifstream inFile;
	inFile.open(argv[1]);
	ofstream outFile1, outFile2, outFile3;
	outFile1.open(argv[2]);
	outFile2.open(argv[3]);
	outFile3.open(argv[4]);

	constructHuffmanLList* listHead = new constructHuffmanLList(inFile, outFile3);
	listHead->printList(listHead->listHead, outFile2);
	outFile2 << endl;
	HuffmanBinaryTree* Root = new HuffmanBinaryTree(listHead->listHead, outFile3);
	Root->preOrderTraversal(Root->Root->next, outFile2);
	outFile2 << endl << endl;
	Root->inOrderTraversal(Root->Root->next, outFile2);
	outFile2 << endl << endl;
	Root->postOrderTraversal(Root->Root->next, outFile2);
	Root->constructCharCode(Root->Root->next, "", outFile1);


}


