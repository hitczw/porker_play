#include "solve_game.h"
#include<sstream>
#include<fstream>

vector<uchar> split(string s,const char flag) {
	vector<uchar> result;
	istringstream iss(s);

	string temp;

	while (getline(iss, temp, flag)) {
		result.push_back(stoi(temp));
	}
	return result;
}

int main() {

	//优化:内存问题:可以删除地主必输的子节点,解决内存管理问题
	//速度:对牌型做一定选择,优先考虑问题//已优化
	//     一次计算只取一个节点

	ifstream file_read;
	file_read.open("斗地主.txt", ios::in);

	if (!file_read) {
		cout << "box.txt dose not exist!" << endl;
		system("pause");
		return 100;
	}

	string x;
	string y;
	getline(file_read, x);
	getline(file_read, y);
	file_read.close();
	

	//cout << "请输入先手牌(用分号隔开):";
	//cin >> x;
	//cout << "请输入后手牌(用分号隔开):";
	//cin >> y;

	vector<uchar>xxx = split(x, ';');
	vector<uchar>yyy = split(y, ';');
	solve_game t(xxx, yyy);
	t.compute();
	t.inter_active();
	system("pause");


}



//先加入重复性判断功能,看功能是否有问题,再进行细节优化