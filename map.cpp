#include <cstring>
#include <iostream>

using namespace std;

class mapnode {
public:
    mapnode* ascii[75];
    int value;
    bool terminal;

    mapnode() {
        for(int i = 0; i < 75; i++)
            ascii[i] = NULL;

        terminal = false;
        value = 0;
    }
};

class map {
private:
    mapnode* head;

public:
    map() {
        head = NULL;
    }
    int get(string str) {
        if(head == NULL)
            return -1;

        mapnode* temp_node = head;

        for(int i = 0; str[i] != '\0'; i++) {
            if(str[i] < '0' || str[i] > 'z') {
                return -1;
            }
            if(temp_node -> ascii[str[i] - '0'] == NULL)
                return -1;
            temp_node = temp_node -> ascii[str[i] - '0'];
        }
        if(temp_node -> terminal == true)
            return temp_node -> value;
        else
            return -1;
    }

    void insert(string str, int value) {
        if(head == NULL)
            head = new mapnode();

        mapnode* temp_node = head;

        for(int i = 0; str[i] != '\0'; i++) {
            if(str[i] < '0' || str[i] > 'z') {
                cout << "Invalid characters!" << endl;
                return;
            }
            if(temp_node -> ascii[str[i] - '0'] == NULL)
                temp_node -> ascii[str[i] - '0'] = new mapnode();
            temp_node = temp_node -> ascii[str[i] - '0'];
        }
        temp_node -> terminal = true;
        temp_node -> value = value;
    }
    void printmap() {
        if(head == NULL) {
            cout << "Trie is empty!" << endl;
            return;
        }
        printmap_rec(head, NULL, 0);
    }
    void search(string key) {
        int i;
        mapnode* temp_node = head;
        if(head == NULL) {
            cout << "Trie is empty" << endl;
            return;
        }

        for(i = 0; key[i] != '\0'; i++) {
            if(key[i] < '0' || key[i] > 'z') {
                cout << "Invalid characters!" << endl;
                return;
            }
            if(temp_node -> ascii[key[i] - '0'] == NULL) {
                cout << "No results found!" << endl;
                return;
            }
            temp_node = temp_node -> ascii[key[i] - '0'];
        }

        const char* str = key.c_str();

        printmap_rec(temp_node, str, i);
    }

private:
    void printmap_rec(mapnode* node,const char* prefix, size_t length) {
        char newprefix[length + 2];

        memcpy(newprefix, prefix, length);
        newprefix[length + 1] = 0;

        if(node->terminal)
            printf("%s: %d\n", prefix, node->value);

        for(int i = 0; i < 75; i++) {
            if(node -> ascii[i] != NULL) {
                newprefix[length] = i + '0';
                printmap_rec(node -> ascii[i], newprefix, length + 1);
            }
        }
    }
};
