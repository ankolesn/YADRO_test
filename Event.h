#ifndef YADRO_EVENT_H
#define YADRO_EVENT_H
#include "Info_Club.h"

class Event {
private:
    int id;
    int table = 0;
    string name_client; // или сообщение
    pair<int, int> cur_time;

public:
    Event() = default;

    void set_id(int id);

    int get_id();

    void set_table(int table);

    int get_table();

    void set_name_client(string name_client);

    string get_name_client();

    void set_cur_time(pair<int, int> cur_time);

    pair<int, int> get_cur_time();
};


#endif //YADRO_EVENT_H
