#ifndef YADRO_TIME_TABLE_H
#define YADRO_TIME_TABLE_H

#include <string>

using namespace std;

class Time_Table {
    string name_client;
    pair<int, int> start_time = pair<int, int>(0, 0);
    pair<int, int> finish_time = pair<int, int>(0, 0);
    int table;

public:
    Time_Table() = default;

    void set_name_client(string name_client);

    void set_start_time(pair<int, int> start_time);

    void set_finish_time(pair<int, int> finish_time);

    void set_table(int table);

    string get_name_client();

    pair<int, int> get_start_time();

    pair<int, int> get_finish_time();

    int get_table();
};


#endif //YADRO_TIME_TABLE_H
