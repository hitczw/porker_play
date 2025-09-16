#pragma once
#include<iostream>
#include<vector>
#include<string>


#define uchar unsigned char
using namespace std;

class re {
public:
    bool equal;
    bool smaller;

    re(bool equal_ = false, bool smaller_ = false) {
        equal = equal_;
        smaller = smaller_;
    }
};

class porker_hands {
    //牌型类
    //飞机暂时没有考虑
private:
    static vector<string>mx;
public:
    enum types{one,
               two,
               three,
               three_one,
               three_two,
               bomb_two,
               bomb_two_pair,
               conti, 
               double_conti,
               bomb, 
               king, 
               none};

    uchar main_value;//主值
    uchar value1;//副值1,三带带值和顺子连对长度
    uchar value2;//副值2,仅四带类型牌
    
    types tp;//牌型:单牌型，带牌型，连续型，炸弹，王炸

    bool operator==(const porker_hands& b)const {
        return tp == b.tp && 
               (main_value == b.main_value) && 
               (value1 == b.value1) && 
               (value2 == b.value2);
    }

    porker_hands(types tp_=none,uchar mv=0,uchar v1=0,uchar v2=0) {
        tp = tp_;
        main_value = mv;
        value1 = v1;
        value2 = v2;
    }

    re compare(const porker_hands& b)const{
        if (tp != b.tp)
            return re(false, tp < b.tp);
        switch (tp)
        {
        case porker_hands::one:
            if (main_value != b.main_value)
                return re(false, main_value < b.main_value);
            break;

        case porker_hands::two:
            if (main_value != b.main_value)
                return re(false, main_value < b.main_value);
            break;

        case porker_hands::three:
            if (main_value != b.main_value)
                return re(false, main_value < b.main_value);
            break;

        case porker_hands::three_one:
            if (main_value != b.main_value)
                return re(false, main_value < b.main_value);
            if(value1!=b.value1)
                return re(false, value1 < b.value1);
            break;

        case porker_hands::three_two:
            if (main_value != b.main_value)
                return re(false, main_value < b.main_value);
            if (value1 != b.value1)
                return re(false, value1 < b.value1);
            break;

        case porker_hands::bomb_two:
            if (main_value != b.main_value)
                return re(false, main_value < b.main_value);
            if (value1 != b.value1)
                return re(false, value1 < b.value1);
            if (value2 != b.value2)
                return re(false,value2<b.value2);
            break;

        case porker_hands::bomb_two_pair:
            if (main_value != b.main_value)
                return re(false, main_value < b.main_value);
            if (value1 != b.value1)
                return re(false, value1 < b.value1);
            if (value2 != b.value2)
                return re(false,value2<b.value2);
            break;

        case porker_hands::conti:
            if (main_value != b.main_value)
                return re(false, main_value < b.main_value);
            if (value1 != b.value1)
                return re(false, value1 < b.value1);
            break;

        case porker_hands::double_conti:
            if (main_value != b.main_value)
                return re(false, main_value < b.main_value);
            if (value1 != b.value1)
                return re(false, value1 < b.value1);
            break;

        case porker_hands::bomb:
            if (main_value != b.main_value)
                return re(false, main_value < b.main_value);
            break;

        case porker_hands::king:
            break;

        case porker_hands::none:
            break;
        default:
            break;
        }
        return re(true, false);
    }


    void copy_print(string m,int nums) {
        for (int i = 0; i < nums; i++) {
            cout << m << " ";
        }
    }

    void cnt_print(int nums) {
        for (int i = 0; i < value1; i++){
            copy_print(mx[main_value + i], nums);
        }
        cout << endl;
    }

    void show_self() {
        string mv = mx[main_value];
        string v1 = mx[value1];
        string v2 = mx[value2];
        switch (tp)
        {
        case porker_hands::one:
            cout << mv << endl;
            break;
        case porker_hands::two:
            copy_print(mv, 2);
            cout << endl;
            break;
        case porker_hands::three:
            copy_print(mv, 3);
            cout <<endl;
            break;
        case porker_hands::three_one:
            copy_print(mv, 3);
            cout << v1 << endl;
            break;
        case porker_hands::three_two:
            copy_print(mv, 3);
            copy_print(v1,2);
            cout << endl;
            break;
        case porker_hands::bomb_two:
            copy_print(mv, 4);
            cout << v1 << " ";
            cout << v2 << endl;
            break;
        case porker_hands::bomb_two_pair:
            copy_print(mv, 4);
            copy_print(v1, 2);
            copy_print(v2,2);
            cout << endl;
            break;
        case porker_hands::conti:
            cnt_print(1);
            break;
        case porker_hands::double_conti:
            cnt_print(2);
            break;
        case porker_hands::bomb:
            copy_print(mv,4);
            cout << endl;
            break;
        case porker_hands::king:
            cout << "王炸"<<endl;
            break;
        case porker_hands::none:
            cout << "不出" << endl;
            break;
        default:
            break;
        }
    }
};
vector<string> porker_hands::mx = { "0","0","0","3","4","5","6","7","8","9","10","J","Q","K","A","??","2","小王","大王" };