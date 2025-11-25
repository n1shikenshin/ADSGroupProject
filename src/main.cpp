#include <iostream>
#include <vector>
#include <limits>
using namespace std;

// =======================================================
//  BASELINE APPROACH — ARRAY
// =======================================================
class PriceTrackerArray {
private:
    vector<double> prices;

public:
    void addPrice(double price) {
        prices.push_back(price);
    }

    double getMinPrice() {
        if (prices.empty()) return numeric_limits<double>::quiet_NaN();

        double minVal = numeric_limits<double>::infinity();
        for (double p : prices) {
            if (p < minVal) minVal = p;
        }
        return minVal;
    }

    double getMaxPrice() {
        if (prices.empty()) return numeric_limits<double>::quiet_NaN();

        double maxVal = -numeric_limits<double>::infinity();
        for (double p : prices) {
            if (p > maxVal) maxVal = p;
        }
        return maxVal;
    }
};


// =======================================================
//  AVL TREE NODE
// =======================================================
struct AVLNode {
    double value;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(double v) : value(v), left(NULL), right(NULL), height(1) {}
};


// =======================================================
//  AVL TREE IMPLEMENTATION
// =======================================================
class AVLTree {
public:
    AVLNode* insert(AVLNode* node, double price) {
        if (!node) return new AVLNode(price);

        if (price < node->value)
            node->left = insert(node->left, price);
        else
            node->right = insert(node->right, price);

        updateHeight(node);

        int balance = getBalance(node);

        // LL Case
        if (balance > 1 && price < node->left->value)
            return rightRotate(node);

        // RR Case
        if (balance < -1 && price > node->right->value)
            return leftRotate(node);

        // LR Case
        if (balance > 1 && price > node->left->value) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // RL Case
        if (balance < -1 && price < node->right->value) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    double getMin(AVLNode* node) {
        if (!node) return numeric_limits<double>::quiet_NaN();
        while (node->left) node = node->left;
        return node->value;
    }

    double getMax(AVLNode* node) {
        if (!node) return numeric_limits<double>::quiet_NaN();
        while (node->right) node = node->right;
        return node->value;
    }

private:
    int height(AVLNode* node) {
        return node ? node->height : 0;
    }

    void updateHeight(AVLNode* node) {
        node->height = 1 + max(height(node->left), height(node->right));
    }

    int getBalance(AVLNode* node) {
        return height(node->left) - height(node->right);
    }

    AVLNode* rightRotate(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    AVLNode* leftRotate(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }
};


// =======================================================
//  OPTIMIZED PRICE TRACKER USING AVL TREE
// =======================================================
class PriceTrackerAVL {
private:
    AVLNode* root = NULL;
    AVLTree tree;

public:
    void addPrice(double price) {
        root = tree.insert(root, price);
    }

    double getMinPrice() {
        return tree.getMin(root);
    }

    double getMaxPrice() {
        return tree.getMax(root);
    }
};


// =======================================================
//  MAIN PROGRAM — ASKS FOR USER INPUT
// =======================================================
int main() {
    PriceTrackerArray arr;
    PriceTrackerAVL avl;

    int n;
    cout << "Enter number of prices: ";
    cin >> n;

    cout << "Enter " << n << " prices:\n";
    for (int i = 0; i < n; i++) {
        double price;
        cin >> price;

        arr.addPrice(price);
        avl.addPrice(price);
    }

    // Output results
    cout << "\n=== RESULTS (ARRAY) ===\n";
    cout << "Min Price: " << arr.getMinPrice() << endl;
    cout << "Max Price: " << arr.getMaxPrice() << endl;

    cout << "\n=== RESULTS (AVL TREE) ===\n";
    cout << "Min Price: " << avl.getMinPrice() << endl;
    cout << "Max Price: " << avl.getMaxPrice() << endl;

    return 0;
}
