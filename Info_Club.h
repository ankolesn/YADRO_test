#ifndef YADRO_INFO_CLUB_H
#define YADRO_INFO_CLUB_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;

class Info_Club {
private:
    int num_tables;
    pair<int, int> start_time;
    pair<int, int> finish_time;
    int price;

public:
    Info_Club() = default;

    void set_num_tables(int num_tables);

    int get_num_tables();

    void set_start_time(pair<int, int> start_time);

    pair<int, int> get_start_time();

    void set_finish_time(pair<int, int> finish_time);

    pair<int, int> get_finish_time();

    void set_price(int price);

    int get_price();
};


#endif //YADRO_INFO_CLUB_H
