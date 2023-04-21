#include "Event.h"

void Event::set_id(int id) {
    this->id = id;
}

int Event::get_id() {
    return id;
}

void Event::set_table(int table) {
    this->table = table;
}

int Event::get_table() {
    return table;
}

void Event::set_name_client(string name_client) {
    this->name_client = name_client;
}

string Event::get_name_client() {
    return name_client;
}

void Event::set_cur_time(pair<int, int> cur_time) {
    this->cur_time = cur_time;
}

pair<int, int> Event::get_cur_time() {
    return cur_time;
}
