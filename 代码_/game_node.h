#pragma once
#include "cards.h"

class game_node {
public:
	cards card;//自己的手牌
	porker_hands own;//自己的出法
	game_node* father;//上一个节点的出法
	deque<game_node*> son;//所对应的下一个节点
	bool color;//判断是哪一方
	char win = -1;//1:此节点必胜,0:此节点必输,-1:不确定
	int th;


	bool operator<(const game_node& b)const {

		re rrr;
		if (color != b.color) { return color < b.color; }
		//是同一种颜色

		rrr = own.compare(b.own);
		if (!rrr.equal) { return rrr.smaller; }
		//是同一种招法

		rrr = card.compare(b.card);
		if (!rrr.equal) { return rrr.smaller; }
		//是同一手牌

		rrr = father->card.compare(b.father->card);
		if (!rrr.equal) { return rrr.smaller; }
		//父亲牌也相同

		return false;
	}
	game_node* get_next_node() {
		game_node* result;
		if (th < son.size()) {
			result = son[th];
			th += 1;
		}
		else { result = 0; }

		return result;
	}

	bool has_next() {
		return th < son.size();
	}
};



