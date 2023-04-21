#include "Info_Club.h"

void Info_Club::set_num_tables(int num_tables) {
    this->num_tables = num_tables;
}

int Info_Club::get_num_tables() {
    return num_tables;
}

void Info_Club::set_start_time(pair<int, int> start_time) {
    this->start_time = start_time;
}

pair<int, int> Info_Club::get_start_time() {
    return start_time;
}

void Info_Club::set_finish_time(pair<int, int> finish_time) {
    this->finish_time = finish_time;
}

pair<int, int> Info_Club::get_finish_time() {
    return finish_time;
}

void Info_Club::set_price(int price) {
    this->price = price;
}

int Info_Club::get_price() {
    return price;
}

