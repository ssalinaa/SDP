#include <iostream>
#include <cmath>

/*
Реализирайте фунцкия Box* toTree(const int* sortedData, 
std::size_t size), която получава сортиран в нарастващ ред масив 
sortedData, съдържащ size на брой числа. Създава балансирано по тегло 
(перфектно балансирано) двоично наредено дърво, в което са записани 
елементите на масива. Елементите на дървото да се заделят с new. 
Връща като резултат корена на дървото. Ако на функцията се подаде 
празен масив, да връща като резултат nullptr. Сложността да бъде не 
повече от O(size).
*/

struct Box
{
    int data;
    Box* left;
    Box* right;

    Box(int data, Box* left = nullptr, Box* right = nullptr)
        : data(data), left(left), right(right) {}
};

Box* toTree(const int* sortedArray, std::size_t size) {

    if (sortedArray == 0 || size == 0) {

        return nullptr;
    }
    if (size == 1) {

        return new Box(sortedArray[0], nullptr, nullptr);
    }
    if (size % 2 == 1)
    {
        return new Box(sortedArray[size / 2], toTree(sortedArray, size / 2), toTree(sortedArray + (size / 2 + 1), size / 2));
    }
    else
    {
        return new Box(sortedArray[size / 2], toTree(sortedArray, size / 2), toTree(sortedArray + (size / 2 + 1), size / 2 - 1));
    }
}

int weight(Box* root) {

    if (root == nullptr) {

        return 0;
    }

    return 1 + weight(root->left) + weight(root->right);
}

bool isPerfectlyBalanced(Box* root)
{
    if (!root)
    {
        return true;
    }

    return isPerfectlyBalanced(root->left) &&
        isPerfectlyBalanced(root->right) &&
        std::abs(weight(root->left) - weight(root->right)) < 2;
}

void deallocate(Box* root) {

    if (root == nullptr) {

        return;
    }

    deallocate(root->left);
    deallocate(root->right);
    delete root;
}

int main() {

    int arr1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int arr2[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };

    Box* tree1 = toTree(arr1, 10);
    Box* tree2 = toTree(arr2, 11);

    std::cout << std::boolalpha << isPerfectlyBalanced(tree1) << std::endl;
    std::cout << std::boolalpha << isPerfectlyBalanced(tree2) << std::endl;

    deallocate(tree1);
    deallocate(tree2);

    return 0;
}