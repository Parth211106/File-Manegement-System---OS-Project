#include <iostream>
#include <string>
#include <vector>
#include <dirent.h>
using namespace std;

class cBaseNode {
public:
    string data;
    cBaseNode* left;
    cBaseNode* right;
    cBaseNode(string data) {
        this->data = data;
        this->left = NULL;
        this->right = NULL;
    }
};

class Indexer{
public:
    cBaseNode* root;
    Indexer(){
        this->root = NULL;
    }

    void vAddfile(string filename) {
        if (root == NULL) {
            root = new cBaseNode(filename);
        } else {
            _vAddfile(filename, root);
        }
    }

    void _vAddfile(string filename, cBaseNode* node) {
        if (filename < node->data) {
            if (node->left == NULL) {
                node->left = new cBaseNode(filename);
            } else {
                _vAddfile(filename, node->left);
            }
        } else {
            if (node->right == NULL) {
                node->right = new cBaseNode(filename);
            } else {
                _vAddfile(filename, node->right);
            }
        }
    }

    void Indexing(string directory_path) {
        DIR* dir;
        struct dirent* ent;
        if ((dir = opendir(directory_path.c_str())) != NULL) {
            while ((ent = readdir(dir)) != NULL) {
                string filename = ent->d_name;
                if (filename != "." && filename != "..") {
                    vAddfile(filename);
                }
            }
            closedir(dir);
        } else {
            cout << "Error opening directory" << endl;
        }
    }

    void Inorder(cBaseNode* node) {
        if (node != NULL) {
            Inorder(node->left);
            cout << node->data << endl;
            Inorder(node->right);
        }
    }

    void Index() {
        cout << "File in Directory are :" << endl;
        Inorder(root);
    }

    bool Searchfile(string filename) {
        return _Searchfile(filename, root);
    }

    bool _Searchfile(string filename, cBaseNode* node) {
        if (node == NULL) {
            return false;
        }
        if (node->data == filename) {
            return true;
        } else if (filename < node->data) {
            return _Searchfile(filename, node->left);
        } else {
            return _Searchfile(filename, node->right);
        }
    }
};
class cManager {
public:
    Indexer indexer;

    cManager() {}

    void vAddfile(string filename) {
        indexer.vAddfile(filename);
    }

    void Indexing(string directory_path) {
        indexer.Indexing(directory_path);
    }

    bool Searchfile(string filename) {
        return indexer.Searchfile(filename);
    }

    void Index() {
        indexer.Index();
    }
};

/*
int main() {
    cManager managerObj;
    // Index all files in directory
    managerObj.Indexing("C:\\Users\\ipart\\OneDrive\\Desktop\\");
    // Search for a file
    if (managerObj.Searchfile("test.txt")) {
        cout << "File found!" << endl;
    } else {
        cout << "File not found." << endl;
    }
    // Print the file index
    managerObj.Index();
    return 0;
}
*/
