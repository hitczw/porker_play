#pragma once
#include "game_node.h"
#include <unordered_set>
#include <set>

//两种重复性判断方法:1.通过搜索树 2.通过哈希表
//现有方法测试哈希表速度快一倍左右

class repeat_set {
	//根据搜索树建立的查重判断
	class cmp {
	public:
		bool operator()(const game_node*x, const game_node* y)const {
			return *x < *y;
		}
	};
	set<game_node*, cmp> ss;
public:
	game_node* is_repeat(game_node* input) {
		auto result = ss.find(input);
		if (result != ss.end()) {
			//找到重复节点
			return *result;
		}
		//非重复节点
		ss.insert(input);
		return 0;
	}

	int get_node_nums() {
		return ss.size();
	}
};

class repeat_hash {
	//根据哈希表建立的查重判断
	//关键问题之:如何寻找更快的哈希函数
	class get_size_t {
	public:
		size_t operator()(const game_node*x)const {
			static int p = 2;
			size_t hash = 0;
		   
			hash = (hash<<p)-hash+x->color;
			hash = (hash<<p)-hash+x->own.tp;
			hash = (hash<<p)-hash+x->own.main_value;
			hash = (hash<<p)-hash+x->own.value1;
			////hash = (hash<<p)-hash+x->own.value2;
			//result = result*131  + card[i];//BKDR算法
			for (int i = 3; i <= 18; i++) {
				if (i != 15) {
					hash = (hash << p) - hash + x->card.card[i];
				}
			}
			
			for (int i = 3; i <= 18; i++) {
				if (i != 15) {
					hash = (hash << p) - hash + x->father->card.card[i];
				}
			}
			return hash;
		}
	};

	class cmp {
	public:
		bool  operator()(const game_node* x,const game_node* y)const{
			if (x->color != y->color) { return false; }
			if (!(x->own == y->own)) { return false; }
			if (!(x->card == y->card)) { return false; }
			if (!(x->father->card == y->father->card)) { return false; }
			
			return true;
		}
	};
	unordered_set<game_node*, get_size_t,cmp> ss;

public:
	game_node* is_repeat(game_node* input) {
		auto result = ss.find(input);
		if (result != ss.end()) {
			//找到重复节点
			return *result;
		}
		//非重复节点
		ss.insert(input);
		return 0;
	}

	int get_node_nums() {
		return ss.size();
	}
};
