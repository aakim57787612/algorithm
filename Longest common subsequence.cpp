#include <iostream>
#include <string>
#include <vector>
using namespace std;

void print(char **b, vector <char> X,int i,int j) {
	if (i == 0 || j == 0)
		return;
	if (b[i][j] == 'G') {
		print(b, X, i - 1, j - 1);
		cout << X[i - 1]<<",";
	}
	else if (b[i][j] == 'U') {
		print(b, X, i - 1, j);
	}
	else
		print(b, X, i, j-1);
}

int main() {
	//將input整理並分別塞入 X 跟 Y 兩陣列
	string input;
	vector <char> X, Y;
	getline(cin,input); int i;
	for (i = 0; i < input.size(); i++) {
		if (input[i] == '<') {
			i++;
			while (input[i] != '>') {
				if (input[i] != ',' && input[i] != ' ')
				X.push_back(input[i]);
				i++;
			}
			break;
		}
	}
	for (i; i < input.size(); i++) {
		if (input[i] == '<') {i++;
			while (input[i] != '>') {
				if(input[i]!=','&& input[i] != ' ')
				Y.push_back(input[i]);
				i++;
			}
			break;
		}
	}

	//new int 宣告 b 跟 c 二維陣列存方向跟步數
	int m = X.size(), n = Y.size();
	char** b = new char* [m+1];
	for (int i = 0; i <= m; ++i) {
		b[i] = new char[n+1];
	}
	int** c = new int* [m+1];
	for (int i = 0; i <= m; ++i) {
		c[i] = new int[n+1];
	}

	//將c的第一列跟第一列行設為0
	for (int i = 1; i <= m; i++) {
		c[i][0] = 0;
	}
	for (int j = 1; j <= n; j++) {
		c[0][j] = 0;
	}

	//找出b跟c兩陣列的值，設max找出最大步數值
	int Max = 0, maxnum = 0;
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if (X[i - 1] == Y[j - 1]) {
				c[i][j] = c[i - 1][j - 1] + 1;
				b[i][j] = 'G';
				if (c[i][j] > Max)
				Max = c[i][j];
			}
			else if (c[i - 1][j] >= c[i][j - 1]) {
				c[i][j] = c[i - 1][j];
				b[i][j] = 'U';
			}
			else if (c[i - 1][j] < c[i][j - 1]) {
				c[i][j] = c[i][j-1];
				b[i][j] = 'L';
			}
		}
	}

	//存最大步數的位置以及最大步數位置有多少個
	vector<int>maxx, maxy;
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if (c[i][j] == Max && b[i][j] == 'G') {
				maxx.push_back(i);
				maxy.push_back(j);
				maxnum++;
			}	
		}
	}

	//開始print，由各個最大步數的位置開始print它自己的路徑
	for (int k = 0; k < maxnum; k++) {
		cout << "<";
		print(b,X,maxx[k], maxy[k]);
		cout << "\b>\n";
	}
}