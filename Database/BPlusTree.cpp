#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Node {
public:
    int totalKeys;
    Node *parentNode, *nextNode;
    Node **nodePointers;
    bool isLeaf;
    string *english, *meaning;

    Node(int numPointers, int keySize) {
        totalKeys = 0;
        parentNode = nullptr;
        nextNode = nullptr;
        nodePointers = new Node *[numPointers + 1];
        for (int i = 0; i <= numPointers; i++) {
            nodePointers[i] = nullptr;
        }
        isLeaf = true;
        english = new string[keySize + 1];
        meaning = new string[keySize + 1];
    }

    ~Node() {
        delete[] nodePointers;
        delete[] english;
        delete[] meaning;
    }
};

class BPlusTree {
private:
    Node *root;
    int numberOfPointer;
    int key;
    int hopsize;

    Node *createNewNode() {
        return new Node(numberOfPointer, key);
    }

    void createRoot(string value, Node *leftChild, Node *rightChild) {
        Node *node = createNewNode();
        node->isLeaf = false;
        node->english[0] = value;
        node->totalKeys++;
        node->nodePointers[0] = leftChild;
        node->nodePointers[1] = rightChild;
        leftChild->parentNode = node;
        rightChild->parentNode = node;
        root = node;
    }

    Node *searchPosition(Node *node, string english) {
        while (!node->isLeaf) {
            int i;
            for (i = 0; i < node->totalKeys; i++) {
                if (english < node->english[i]) {
                    break;
                }
            }
            node = node->nodePointers[i];
            hopsize++;
        }
        return node;
    }

    void mergeWithParent(Node *parent, string value, Node *rightChild) {
        int track = parent->totalKeys;
        track--;

        if (track > -1) {
            for (; track > -1; track--) {
                if (parent->english[track] <= value)
                    break;
                else {
                    parent->english[track + 1] = parent->english[track];
                    parent->nodePointers[track + 2] = parent->nodePointers[track + 1];
                }
            }
        }
        parent->english[track + 1] = value;
        parent->nodePointers[track + 2] = rightChild;
        parent->totalKeys++;
    }

    void parentRecreation(Node *parent, string value, Node *leftChild, Node *rightChild) {
        if (parent == nullptr) {
            createRoot(value, leftChild, rightChild);
            return;
        }
        rightChild->parentNode = parent;
        mergeWithParent(parent, value, rightChild);
        if (parent->totalKeys == numberOfPointer) {
            Node *secondNode = createNewNode(); // second node
            secondNode->isLeaf = false;
            int mark = parent->totalKeys, j = 0;
            for (int i = mark - (numberOfPointer / 2); i < numberOfPointer; i++) {
                secondNode->english[j] = parent->english[i];
                if (j == 0) {
                    secondNode->nodePointers[0] = parent->nodePointers[i]; // look up later
                    secondNode->nodePointers[0]->parentNode = secondNode;
                }
                secondNode->nodePointers[j + 1] = parent->nodePointers[i + 1];
                secondNode->nodePointers[j + 1]->parentNode = secondNode;
                j++;
            }
            parent->totalKeys -= (mark / 2 + 1);
            secondNode->totalKeys = (mark / 2);
            parentRecreation(parent->parentNode, parent->english[parent->totalKeys], parent, secondNode);
        }
    }

    void addToLeaf(string english, string meaning) {
        // searching for an appropriate place
        Node *leaf = searchPosition(root, english);

        // sorting and insertion
        int track = leaf->totalKeys;
        track--;

        if (track > -1) {
            for (; track > -1; track--) {
                if (english < leaf->english[track]) {
                    leaf->english[track + 1] = leaf->english[track];
                    leaf->meaning[track + 1] = leaf->meaning[track];
                } else break;
            }
        }
        leaf->english[track + 1] = english;
        leaf->meaning[track + 1] = meaning;
        leaf->totalKeys++;

        // balancing
        if (leaf->totalKeys == numberOfPointer) {
            Node *secondNode = createNewNode();    // second node

            int mark = leaf->totalKeys, j = 0;
            for (int i = mark - (numberOfPointer / 2); i < numberOfPointer; i++) {
                secondNode->english[j] = leaf->english[i];
                secondNode->meaning[j] = leaf->meaning[i];
                j++;
            }

            //int v=leaf->totalKeys;
            leaf->totalKeys -= (numberOfPointer / 2);
            secondNode->totalKeys = (numberOfPointer / 2);
            secondNode->nextNode = leaf->nextNode;
            leaf->nextNode = secondNode;

            // move up
            parentRecreation(leaf->parentNode, secondNode->english[0], leaf, secondNode);
        }
    }

    void searchMeaning() {
        int i;
        cout << "Enter the word: ";
        string word;
        cin >> word;

        hopsize = 0;
        Node *leaf = searchPosition(root, word);
        for (i = 0; i < leaf->totalKeys; i++) {
            if (leaf->english[i] == word) break;
        }
        // freopen("ans.txt", "w", stdout);
        if (i == leaf->totalKeys) cout << "Sorry. No word found." << endl;
        else {
            cout << "Word: " << word << endl << "Meaning: " << leaf->meaning[i] << endl;
        }
        // cout << "Hop Size: " << hopsize << endl;
    }

    bool buildBPlusTree() {
        string english, meaning;
        root = createNewNode();

        ifstream filePtr;
        filePtr.open("english_dictionary1.txt");

        if (!filePtr) {
            cout << "File couldn't be opened." << endl;
            return false;
        } else {
            while (filePtr >> english) {
                getline(filePtr, meaning);
                addToLeaf(english, meaning);
            }
            filePtr.close();
        }

        return true;
    }

public:
    BPlusTree(int numPointers) {
        numberOfPointer = numPointers;
        key = numberOfPointer - 1;
        hopsize = 0;
        root = nullptr;
    }

    ~BPlusTree() {
        delete root;
    }

    void buildAndSearch() {
        if (buildBPlusTree())
            cout << "Congratulations! Tree has been built." << endl;
        else
            cout << "Sorry. Tree couldn't be built." << endl;
        searchMeaning();
    }
};

int main() {
    int numPointers;
    cout << "Enter the number of pointers: ";
    cin >> numPointers;

    BPlusTree tree(numPointers);
    tree.buildAndSearch();

    return 0;
}
