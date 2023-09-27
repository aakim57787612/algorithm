#include <iostream>
#include <vector>
#include <string>
#include <math.h>
using namespace std;
int datasize;//input data的size
struct data_info{//每個node的資訊
    int num = -1;
    int position = -1;
    int parent = -1;
    int left = -1;
    int right = -1;
    int successor = -1;
    int predecessor = -1;
};
data_info start[100];//設最大為100個nodes
void build_tree(vector <int>& data) {//建構樹
    start[0].num = data[0];
    start[0].position = 1;
    start[0].left = 2;
    start[0].right = 3;
    for (int i = 1; i < datasize; i++) {
        data_info path = start[0];
        while (1) {
            if (path.num > data[i] && start[path.left -1].num == -1) {//往左且為空
                start[path.position * 2 - 1].num = data[i];
                start[path.position * 2 - 1].position = path.position * 2;
                start[path.position - 1].left = path.position * 2;
                start[path.position * 2-1].parent = path.position;
                start[path.position * 2-1].left = path.position * 2 * 2;
                start[path.position * 2-1].right = path.position * 2 * 2 + 1;
                break;
            }
            else if (path.num < data[i] && start[path.right-1].num == -1) {//往右且為空
                start[path.position * 2].num = data[i];
                start[path.position * 2].position = path.position * 2 + 1;
                start[path.position - 1].right = path.position * 2 + 1;
                start[path.position * 2].parent = path.position;
                start[path.position * 2].left = (path.position * 2+1) * 2;
                start[path.position * 2].right = (path.position * 2+1) * 2 + 1;
                break;
            }
            else if (path.num > data[i] && path.left != -1) {//往左
                path = start[start[path.position - 1].left - 1];
            }
            else if (path.num < data[i] && path.right != -1) {//往右
                path = start[start[path.position - 1].right - 1];
            }  
        }
    }
}
void tree_insert(int data) {//insert為再input一個數字，所以搬build_tree建構函式做一遍即可
    data_info path = start[0]; 
    while (1) {
        if (path.num > data && start[path.left - 1].num == -1) {//往左且為空
            start[path.position * 2 - 1].num = data;
            start[path.position * 2 - 1].position = path.position * 2;
            start[path.position - 1].left = path.position * 2;
            start[path.position * 2 - 1].parent = path.position;
            start[path.position * 2 - 1].left = path.position * 2 * 2;
            start[path.position * 2 - 1].right = path.position * 2 * 2 + 1;
            break;
        }
        else if (path.num < data && start[path.right - 1].num == -1) {//往右且為空
            start[path.position * 2].num = data;
            start[path.position * 2].position = path.position * 2 + 1;
            start[path.position - 1].right = path.position * 2 + 1;
            start[path.position * 2].parent = path.position;
            start[path.position * 2].left = (path.position * 2 + 1) * 2;
            start[path.position * 2].right = (path.position * 2 + 1) * 2 + 1;
            break;
        }
        else if (path.num > data && path.left != -1) {//往左
            path = start[start[path.position - 1].left - 1];
        }
        else if (path.num < data && path.right != -1) {//往右
            path = start[start[path.position - 1].right - 1];
        }
    }
}
void tree_delete(int data) {
    data_info x, y, z;
    for (int i = 0; i < 100; i++) {//找到z
        if (start[i].num == data) {
            z = start[i];
            break;
        }
    }
    if (start[z.left-1].num == -1 || start[z.right - 1].num == -1) {
        y = z;
    }
    else {
        data_info successor = z;//successor為z的right方向再走left方向到底
        if (start[successor.right - 1].num != -1) {
            successor = start[successor.right - 1];
        }
        while (start[successor.left - 1].num != -1) {
            successor = start[successor.left - 1];
        }
        y = successor;
    }
    if (start[y.left - 1].num != -1) {
        x = start[y.left - 1];
    }
    else
        x = start[y.right - 1];
    if (x.num != -1) {
        x.parent = y.parent;
    }
    if (start[y.parent - 1].num == -1) {
        start[0] = x;
    }
    else if (y.position == start[y.parent - 1].left) {
        start[start[y.parent - 1].left - 1] = x;
    }
    else {
        start[start[y.parent - 1].right - 1] = x;
        start[x.position - 1].num = -1;
    }
    if (y.position != z.position) {
        start[z.position - 1] = y;//z改成successor
    }
}
//print 二元樹
void print() {
    int h = 0, temp, height = 0;
    temp = pow(2, height);
    while (1 != 100 / temp) {
        height++;
        temp = pow(2, height);
    }
    for (int i = 0; i < 100; i++) {
        temp = pow(2, h);
        while (1 != (i + 1) / temp) {
            h++;
            temp = pow(2, h);
        }
        if ((i + 1) % temp == 0) {
            for (int j = pow(2,height-h); j >= 0; j--) {
                cout << " ";
            }
        }
        if (start[i].num == -1)
            cout << "  ";
        else
            cout << start[i].num;
        for (int j = pow(2, height - h + 1) - 2; j >= 0; j--) {
            cout << " ";
        }      
        temp = pow(2, h + 1);
        if (i == 0) {
            cout << endl;
        }
        else if ((i+1) % (temp - 1) == 0) {
            cout << endl;
        }
    }
}

int main() {
    string input; vector<int> data;
    cout << "Input: ";
    getline(cin, input);
    int i = 0;
    for (int i = 0; i < input.size(); i++) {//讀input 並放入vector data 中
        string s;
        while (input[i] != ',') {
            s += input[i];
            i++;
            if (i > input.size())
                break;
        }
        data.push_back(stoi(s));
    }
    datasize = data.size();
    build_tree(data);
    //開始建tree

    cout << "The construction of binary search tree\n";
    print();

    cout << "\nInsertion of 12\n";
    tree_insert(12);
    print();

    cout << "\nDeletion of 9\n";
    tree_delete(9);
    print();
}