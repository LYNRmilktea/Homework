#include <iostream>
#include <utility>
#include <stack>
#include <random>
#include <cmath>
#include <iomanip>
using namespace std;

template <class K, class E>
class Dictionary {
public:
	virtual bool IsEmpty() const = 0;
	virtual pair<K, E>* Get(const K&) = 0;
	virtual void Insert(const pair<K, E>&) = 0;
	virtual void Delete(const K&) = 0;
};

template <class K, class E>
class BST : public Dictionary<K, E> {
private:
	struct TreeNode {
		pair<K, E> data;
		TreeNode* leftChild;
		TreeNode* rightChild;
		int leftSize;
		TreeNode(const pair<K, E>& thePair)
			: data(thePair), leftChild(nullptr), rightChild(nullptr), leftSize(0) {
		}
	};

	TreeNode* root;
	pair<K, E>* Get(TreeNode*, const K&) const;
	void Insert(TreeNode*&, const pair<K, E>&);
	int calculateHeight(TreeNode* root) const;
	TreeNode* Delete(TreeNode*&, const K&, bool& deletedLeft);

public:
	BST() : root(nullptr) {}
	~BST();
	bool IsEmpty() const { return root == nullptr; }
	pair<K, E>* Get(const K&);
	pair<K, E>* RankGet(int);
	void Insert(const pair<K, E>&);
	void Delete(const K&);
	int Height() const { return calculateHeight(root); }
	int Size(TreeNode*) const;
	TreeNode* GetRoot() const { return root; }
};

template <class K, class E>
BST<K, E>::~BST() {
	stack<TreeNode*> s;
	TreeNode* current = root;
	while (current || !s.empty()) {
		while (current) {
			s.push(current);
			current = current->leftChild;
		}
		current = s.top(); s.pop();
		TreeNode* temp = current;
		current = current->rightChild;
		delete temp;
	}
}

template <class K, class E>
pair<K, E>* BST<K, E>::Get(const K& k) {
	return Get(root, k);
}

template <class K, class E>
pair<K, E>* BST<K, E>::Get(TreeNode* p, const K& k) const {
	if (!p) return nullptr;
	if (k < p->data.first) return Get(p->leftChild, k);
	if (k > p->data.first) return Get(p->rightChild, k);
	return &p->data;
}

template <class K, class E>
pair<K, E>* BST<K, E>::RankGet(int r) {
	TreeNode* currentNode = root;
	while (currentNode) {
		if (r < currentNode->leftSize) {
			currentNode = currentNode->leftChild;
		}
		else if (r > currentNode->leftSize) {
			r -= currentNode->leftSize + 1;
			currentNode = currentNode->rightChild;
		}
		else {
			return &(currentNode->data);
		}
	}
	return nullptr;
}

template <class K, class E>
void BST<K, E>::Insert(const pair<K, E>& thePair) {
	TreeNode* p = root;
	TreeNode* pp = nullptr;
	while (p) {
		pp = p;
		if (thePair.first < p->data.first) {
			p->leftSize++;
			p = p->leftChild;
		}
		else if (thePair.first > p->data.first) {
			p = p->rightChild;
		}
		else {
			p->data.second = thePair.second;
			return;
		}
	}
	TreeNode* newNode = new TreeNode(thePair);
	if (!root) root = newNode;
	else if (thePair.first < pp->data.first) pp->leftChild = newNode;
	else pp->rightChild = newNode;
}

template <class K, class E>
void BST<K, E>::Delete(const K& k) {
	bool deletedLeft = false;
	root = Delete(root, k, deletedLeft);
}

template <class K, class E>
typename BST<K, E>::TreeNode* BST<K, E>::Delete(TreeNode*& node, const K& k, bool& deletedLeft) {
	if (!node) return nullptr;

	if (k < node->data.first) {
		node->leftChild = Delete(node->leftChild, k, deletedLeft);
		if (deletedLeft) node->leftSize--;
	}
	else if (k > node->data.first) {
		node->rightChild = Delete(node->rightChild, k, deletedLeft);
	}
	else {
		deletedLeft = true;
		if (!node->leftChild) {
			TreeNode* temp = node->rightChild;
			delete node;
			return temp;
		}
		else if (!node->rightChild) {
			TreeNode* temp = node->leftChild;
			delete node;
			return temp;
		}
		else {
			TreeNode* s = node->leftChild;
			TreeNode* sp = node;
			while (s->rightChild) {
				sp = s;
				s = s->rightChild;
			}
			node->data = s->data;
			bool dummy = false;
			node->leftChild = Delete(node->leftChild, s->data.first, dummy);
			node->leftSize--;
		}
	}
	return node;
}

template <class K, class E>
int BST<K, E>::Size(TreeNode* node) const {
	if (!node) return 0;
	return Size(node->leftChild) + Size(node->rightChild) + 1;
}

template <class K, class E>
int BST<K, E>::calculateHeight(TreeNode* root) const {
	if (!root) return 0;
	int leftHeight = calculateHeight(root->leftChild);
	int rightHeight = calculateHeight(root->rightChild);
	return max(leftHeight, rightHeight) + 1;
}

int main() {
	const int testSizes[] = { 100, 500, 1000, 2000, 3000, 4000, 5000, 10000 };
	const int numTests = sizeof(testSizes) / sizeof(testSizes[0]);

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dist(1, 1000000);

	cout << left << setw(10) << "n" << setw(15) << "height" << setw(20) << "log2(n)" << setw(20) << "height / log2(n)" << endl;
	cout << fixed << setprecision(4);

	for (int i = 0; i < numTests; ++i) {
		int n = testSizes[i];
		BST<int, int> bst;
		for (int j = 0; j < n; ++j) {
			int key = dist(gen);
			bst.Insert(make_pair(key, 0));
		}
		int height = bst.Height();
		double log2n = log2(n);
		double ratio = height / log2n;
		cout << setw(10) << n << setw(15) << height << setw(20) << log2n << setw(20) << ratio << endl;
	}

	return 0;
}