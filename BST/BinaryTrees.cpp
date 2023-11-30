#pragma once
#include <iostream>
#include <functional>
#include <vector>

class BST {

private:
	struct Box {

		int data;
		Box* left;
		Box* right;

		Box(int data, Box* left, Box *right) :
			data(data), left(left), right(right) { }
	};

	Box* root;

	bool find(Box* root, int element) const {

		if (root == nullptr) {

			return false;
		}
		if (root->data == element) {

			return true;
		}
		else if (root->data < element) {

			return find(root->right, element);
		}

		return find(root->left, element);
	}

	void insert(Box*& root, int element) {

		if (root == nullptr) {

			root = new Box(element, nullptr, nullptr);
		}
		else if (element >= root->data) {

			insert(root->right, element);
		}
		else {

			insert(root->left, element);
		}
	}

	void deallocate(Box* root) {

		if (root == nullptr) {

			return;
		}

		deallocate(root->left);
		deallocate(root->right);
		delete root;
	}

	Box* copy(Box* root) {

		if (root == nullptr) {

			return root;
		}

		return new Box(root->data, copy(root->left), copy(root->right));
	}

	void erase(Box*& root, int element) {

		if (root == nullptr) {

			return;
		}
		else if (root->data < element) {
			
			erase(root->right, element);
			return;
		}
		else if (root->data > element) {

			erase(root->left, element);
			return;
		}

		Box* toDelete = root;
		if (root->left == nullptr && root->right == nullptr) {

			root = nullptr;
		}
		else if (root->left != nullptr && root->right == nullptr) {

			root = root->left;
		}
		else if (root->left == nullptr && root->right != nullptr) {

			root = root->right;
		}
		else {

			Box* maxLeaf = extractMax(root->left);
			maxLeaf->left = root->left;
			maxLeaf->right = root->right;
			root = maxLeaf;
		}
		delete toDelete;
	}

	Box* extractMax(Box*& root) {

		if (root->right != nullptr) {

			return extractMax(root->right);
		}

		Box* result = root;
		root = root->left;
		return result;
	}

	void inorder(Box* root, std::vector<int>& current) const {

		if (root == nullptr) {

			return;
		}
		inorder(root->left, current);
		current.push_back(root->data);
		inorder(root->right, current);
	}

	void preorder(Box* root, std::vector<int>& current) const {

		if (root == nullptr) {

			return;
		}

		current.push_back(root->data);
		preorder(root->left, current);
		preorder(root->right, current);
	}

	void anyorder(Box* root, std::vector<int>& current) const {

		if (root == nullptr) {

			return;
		}

		anyorder(root->right, current);
		current.push_back(root->data);
		anyorder(root->left, current);
	}

	void postorder(Box* root, std::vector<int>& current) const {

		if (root == nullptr) {

			return;
		}

		postorder(root->left, current);
		postorder(root->right, current);
		current.push_back(root->data);
	}

	int size(Box* root) const {

		if (root == nullptr) {

			return 0;
		}

		return 1 + size(root->left) + size(root->right);
	}

	int height(Box* root) const {

		if (root == nullptr) {

			return 0;
		}

		return 1 + std::max(this->height(root->left), this->height(root->right));
	}

	bool isBalanced(Box* root) const {

		if (root == nullptr) {

			return true;
		}

		return isBalanced(root->left) && isBalanced(root->right) &&
			(std::abs(this->height(root->left) - this->height(root->right)) < 2);
	}

	bool isPerfectlyBalanced(Box* root) const {

		if (root == nullptr) {

			return true;
		}

		return isPerfectlyBalanced(root->left) && isPerfectlyBalanced(root->right) &&
			(std::abs(this->height(root->left) - this->height(root->right)) < 2);
	}

	void leaves(Box* root, std::vector<int>& current) const {

		if (root == nullptr) {

			return;
		}

		if (root->left == nullptr && root->right == nullptr) {

			current.push_back(root->data);
		}

		leaves(root->left, current);
		leaves(root->right, current);
	}

	void atLevel(Box* root, std::size_t n, std::vector<int>& current) const {

		if (root == nullptr) {

			return;
		}

		if (n == 0) {

			current.push_back(root->data);
			return;
		}

		atLevel(root->left, n - 1, current);
		atLevel(root->right, n - 1, current);
	}

	void anyMap(Box* root, std::function<int(int)> f) {

		if (root == nullptr) {

			return;
		}

		anyMap(root->left, f);
		root->data = f(root->data);
		anyMap(root->left, f);
	}

	public:
		BST() : root(nullptr) { }

		BST(const BST& other) : root(this->copy(other.root)) { }

		BST& operator=(const BST& other) {

			if (this != &other) {

				this->deallocate(this->root);
				this->root = this->copy(other.root);
			}

			return *this;
		}

		~BST() {

			this->deallocate(this->root);
		}

		bool find(int element) const {

			return this->find(this->root, element);
		}

		void insert(int element) {

			insert(this->root, element);
		}

		void erase(int element) {

			this->erase(this->root, element);
		}

		std::vector<int> inorder() const {

			std::vector<int> result;
			inorder(this->root, result);

			return result;
		}

		std::vector<int> preorder() const {

			std::vector<int> result;
			preorder(this->root, result);

			return result;
		}

		std::vector<int> anyorder() const {

			std::vector<int> result;
			anyorder(this->root, result);
			
			return result;
		}

		std::vector<int> posorder() const {

			std::vector<int> result;
			postorder(this->root, result);

			return result;
		}

		int size() const {

			return this->size(this->root);
		}

		int height() const {

			return this->height(this->root);
		}

		bool isBalanced() const {

			return this->isBalanced(this->root);
		}

		bool isPerfectlyBalanced() const {

			return this->isPerfectlyBalanced(this->root);
		}

		int min() const {

			if (root == nullptr) {

				throw std::logic_error("Empty BST");
			}

			Box* temp = this->root;
			while (temp->left != nullptr) {

				temp = temp->left;
			}

			return temp->data;

		}

		int max() const {

			if (root == nullptr) {

				throw std::logic_error("Empty BST");
			}

			Box* temp = this->root;
			while (temp->right != nullptr) {

				temp = temp->right;
			}

			return temp->data;
		}

		std::vector<int> leaves() const {

			std::vector<int> result;
			this->leaves(this->root, result);

			return result;
		}

		std::vector<int> atLevel(std::size_t n) const {

			std::vector<int> result;
			this->atLevel(this->root,n, result);

			return result;
		}

		void map(std::function<int(int)> f)
		{

			anyMap(this->root, f);
		}
};

void print(const std::vector<int>& v) {

	for (auto e1 : v) {

		std::cout << e1 << " ";
	}
	std::cout << std::endl;
}

int main() {

	BST bst;
	bst.insert(18);
	bst.insert(14);
	bst.insert(23);
	bst.insert(10);
	bst.insert(15);
	bst.insert(19);
	bst.insert(50);
	bst.insert(6);
	bst.insert(11);
	bst.insert(17);
	bst.insert(18);
	bst.insert(20);
	bst.insert(63);

	std::vector<int> inorder = bst.inorder();
	print(inorder);

	std::vector<int> preorder = bst.preorder();
	print(preorder);

	std::vector<int> anyorder = bst.anyorder();
	print(anyorder);

	std::vector<int> postorder = bst.posorder();
	print(postorder);

	std::cout << "Size: " << bst.size() << std::endl;
	std::cout << "Height : " << bst.height() << std::endl;
	std::cout << std::boolalpha << "Is balanced?: " << bst.isBalanced() << std::endl;
	std::cout << std::boolalpha << "Is perfectly balanced?: " << bst.isPerfectlyBalanced() << std::endl;
	std::cout << "min: " << bst.min() << std::endl;
	std::cout << "max: " << bst.max() << std::endl;

	std::vector<int> leaves = bst.leaves();
	print(leaves);

	std::vector<int> levelN = bst.atLevel(2);
	print(levelN);

	bst.map([](int x) -> int {return 2 * x; });
	std::vector<int> afterMap = bst.anyorder();
	print(afterMap);

	return 0;
}