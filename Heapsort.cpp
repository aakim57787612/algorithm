#include <iostream>
#include <vector>
#include <string>
#include <math.h>
using namespace std;

void max_heap(vector <int>& data,int i) {
    int l = 2 * i, r = 2 * i + 1, largest, temp;
    if (l <= data.size() && data[l - 1] > data[i - 1]) {
        largest = l;//i為parent，先跟left子節點比，大的為largest
    }
    else
        largest = i;
    if (r <= data.size() && data[r - 1] > data[largest - 1]) {
        largest = r;//largest再跟right子節點比，大的為largest
    }
    if (largest != i) {//當largest != i，則有子節點比parent大，largest跟parent做swap
        temp = data[i - 1];
        data[i - 1] = data[largest - 1];
        data[largest - 1] = temp;
        max_heap(data, largest);//因原本largest的位置有被動到，故largest這位置要重新max_heap()
    }
}
void build_max_heap(vector <int>& data) {
    int heap_size = data.size();
    for (int i = heap_size / 2; i > 0; i--) {
        max_heap(data, i);//把有子節點的放入，範圍是heap_size~1
    }
}

//回傳 root(最大的數)並把最後一位leaf放入root再刪除最後一位leaf，再進 max_heap()整理heapsort
int extract_max(vector <int>& data) {
    int max = data[0];
    data[0] = data[data.size() - 1];
    data.pop_back();
    max_heap(data,1);
    return max;
}

//print 二元樹
void print(vector <int>& data) {
    int h = 0, temp, height = 0;
    temp = pow(2, height);
    while (1 != data.size() / temp) {
        height++;
        temp = pow(2, height);
    }
    for (int i = 0; i < data.size(); i++) {
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
        cout << data[i];    
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

    build_max_heap(data); 
    //開始建heapsort

    vector<int> Sorted_numbers;
    //建vector Sorted_numbers 放大到小的 sorted numbers

    int datasize = data.size();
    cout << "The construction of max-heap tree\n";
    for (int i = 0; i < datasize; i++) {
        print(data);
        //print 出二元樹的 heapsort

        cout<<"\nSorted numbers: ";
        Sorted_numbers.push_back(extract_max(data));
        //做datasize次的extract_max(data)並push_back至Sorted_numbers

        for (int i = 0; i < Sorted_numbers.size(); i++) {//print目前Sorted_numbers中的data
            cout << Sorted_numbers[i];
            if (i < Sorted_numbers.size() - 1)
                cout << ", ";
        }
        cout << endl;
    }
}