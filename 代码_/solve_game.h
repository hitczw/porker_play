#pragma once

#include "repeat.h"
#include <time.h>

class solve_game {
public:
	cards first;
	cards second;
	game_node* root;
	repeat_hash repeat_test;
	solve_game(vector<uchar>& first_, vector<uchar>& second_) {
		first.init2(first_);
		second.init2(second_);
		root = new game_node;
	}

	void generate_next(game_node* node) {
		//根据此节点生成下一个节点信息
		//即对方应对此节点的所有招法
		//输入为对方手牌,即是上一节点信息
		//即父亲节点要找到应对此节点的招法
		deque<porker_hands> x = node->father->card.what_to_deal(node->own);//得到所有的应对招法
		node->th = 0;
		for (int i = 0; i < x.size(); i++) {
			game_node* gn = new game_node;
			gn->own = x[i];//赋值招法
						   //x[i].show_self();
			gn->card = node->father->card.play_cards(x[i]);//计算出完牌后的牌
			gn->father = node;
			gn->color = !node->color;//顺序取反
			auto repeat_node = repeat_test.is_repeat(gn);

			if (repeat_node) {
				//如果这个点是重复的点,之前已经计算过
				*gn = *repeat_node;
				gn->father = node;
				node->son.push_front(gn);
			}

			else if (gn->card.nums == 0) {
				gn->win = 1;//此节点应该优先考虑
				node->son.push_front(gn);
			}

			else {
				node->son.push_back(gn);
			}
		}
	}

	void compute() {
		//进一步速度提升:改进为哈希表,难点在于找到高效哈希函数
		//加入内存管理
		cout <<"计算中..." << endl;
		root->father = new game_node;
		root->father->card = first;
		root->card = second;
		root->own = porker_hands(porker_hands::none);
		generate_next(root);//由根节点生成初始游戏信息
		root->color = 1;

		game_node* temp_node = root;
		int layer = 0;
		auto t1 = clock();

		while (root->win == -1) {
			if (!temp_node->has_next()) {
				//当前节点的孩子已经遍历完成
				//代表当前节点所有孩子节点是必输的
				//当前节点是必胜的
				temp_node->win = 1;
				temp_node = temp_node->father;

				temp_node->win = 0;
				temp_node = temp_node->father;
				layer -= 2;

			}

			else {
				temp_node = temp_node->get_next_node();
				layer += 1;

				if (layer == 1) {
					cout << "地主尝试招法:";
					temp_node->own.show_self();
				}

				switch (temp_node->win)
				{
				case 1:
					//当前节点是必胜的
					temp_node = temp_node->father;//返回到上一个节点
					temp_node->win = 0;//上一个节点必输
					temp_node = temp_node->father;//返回到上一个节点
					layer -= 2;
					break;

				case 0:
					//当前节点是必输的

					temp_node = temp_node->father;//转到上一个节点
					layer -= 1;
					break;
				default:
					//无法确定当前节点的胜负性	

					generate_next(temp_node);//根据上一节点信息计算temp_node的孩子

					break;
				}
			}
		}
		auto t2 = clock();
		cout << "计算完成.." << endl;
		cout << "花费时间:" << t2 - t1 << "ms" << endl;
		//cout << "总节点:" << repeat_test.get_node_nums() << endl;
	}

	void inter_active() {

		auto temp = root;
		int choose;
		if (!temp->win) {
			while (true) {
				cout << endl<<"地主出:";
				for (int i = 0; i < temp->son.size(); i++) {
					if (temp->son[i]->win == 1) {
						temp = temp->son[i];
						temp->own.show_self();//找到必胜招法
						break;
					}
				}
				cout << endl;

				if (temp->son.empty()) {
					cout << "你输了" << endl;
					break;
				}
				cout << "你准备出什么,请选择一下序号:" << endl;

				for (int i = 0; i < temp->son.size(); i++) {
					cout << i << ":    ";
					temp->son[i]->own.show_self();
				}


				while (true) {
					cout << "请选择:";
					cin >> choose;
					if (choose < temp->son.size() && choose >= 0) {
						break;
					}
					else {
						cout << "选择错误,需要重新选择" << endl;
					}
				}
				temp = temp->son[choose];
			}
		}

		else {
			cout << "地主必输" << endl;
		}
	}
};
