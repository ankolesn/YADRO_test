//
// Created by 79531 on 18.04.2023.
//

#include "Time_Table.h"

void Time_Table::set_name_client(string name_client) {
    this->name_client = name_client;
}

void Time_Table::set_start_time(pair<int, int> start_time) {
    this->start_time = start_time;
}

void Time_Table::set_finish_time(pair<int, int> finish_time) {
    this->finish_time = finish_time;
}

void Time_Table::set_table(int table) {
    this->table = table;
}

string Time_Table::get_name_client() {
    return name_client;
}

pair<int, int> Time_Table::get_start_time() {
    return start_time;
}

pair<int, int> Time_Table::get_finish_time() {
    return finish_time;
}

int Time_Table::get_table() {
    return table;
}
