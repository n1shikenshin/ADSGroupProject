#include <iostream>
#include <string>
#include <chrono>
using namespace std;
using namespace std::chrono;

// =============================
// AVL NODE
// =============================
struct AVLNode {
    string store;
    double price;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(const string& s, double p)
        : store(s), price(p), left(nullptr), right(nullptr), height(1) {}
};

// =============================
// AVL TREE CLASS
// =============================
class AVLTree {
private:
    AVLNode* root;

public:
    AVLTree() : root(nullptr) {}

    // Public insert wrapper
    void insert(const string& store, double price) {
        root = insertRec(root, store, price);
    }

    const AVLNode* getMin() const {
        return getMinNode(root);
    }

    const AVLNode* getMax() const {
        return getMaxNode(root);
    }

    ~AVLTree() {
        destroy(root);
    }

private:
    int height(AVLNode* node) const {
        return node ? node->height : 0;
    }

    int getBalance(AVLNode* node) const {
        return height(node->left) - height(node->right);
    }

    void updateHeight(AVLNode* node) {
        node->height = 1 + max(height(node->left), height(node->right));
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

    AVLNode* insertRec(AVLNode* node, const string& store, double price) {
        if (!node)
            return new AVLNode(store, price);

        if (price < node->price)
            node->left = insertRec(node->left, store, price);
        else
            node->right = insertRec(node->right, store, price);

        updateHeight(node);
        int balance = getBalance(node);

        // LL
        if (balance > 1 && price < node->left->price)
            return rightRotate(node);

        // RR
        if (balance < -1 && price > node->right->price)
            return leftRotate(node);

        // LR
        if (balance > 1 && price > node->left->price) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // RL
        if (balance < -1 && price < node->right->price) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    AVLNode* getMinNode(AVLNode* node) const {
        if (!node) return nullptr;
        while (node->left) node = node->left;
        return node;
    }

    AVLNode* getMaxNode(AVLNode* node) const {
        if (!node) return nullptr;
        while (node->right) node = node->right;
        return node;
    }

    void destroy(AVLNode* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
};

// =============================
// MAIN PROGRAM
// =============================
int main() {
    AVLTree tracker;
    int n;

    cout << "Enter number of entries: ";
    cin >> n;

    cout << "\n=== ENTER STORE INFORMATION ===\n";

    for (int i = 1; i <= n; i++) {
        string store;
        double price;

        cout << "\nEntry " << i << ":\n";
        cout << "Enter Store " << i << ": ";
        cin >> store;
        cout << "Enter Price " << i << ": ";
        cin >> price;

        auto start = high_resolution_clock::now();
        tracker.insert(store, price);
        auto end = high_resolution_clock::now();

        cout << "Inserted (" 
             << duration_cast<microseconds>(end - start).count()
             << " us)\n";
    }

    cout << "\n===== AVL TREE RESULTS =====\n";

    auto startMin = high_resolution_clock::now();
    const AVLNode* minStore = tracker.getMin();
    auto endMin = high_resolution_clock::now();

    auto startMax = high_resolution_clock::now();
    const AVLNode* maxStore = tracker.getMax();
    auto endMax = high_resolution_clock::now();

    cout << "Cheapest Store : " << minStore->store
         << " RM" << minStore->price
         << " (" << duration_cast<microseconds>(endMin - startMin).count()
         << " us)\n";

    cout << "Most Expensive : " << maxStore->store
         << " RM" << maxStore->price
         << " (" << duration_cast<microseconds>(endMax - startMax).count()
         << " us)\n";

    return 0;
}

