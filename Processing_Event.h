#ifndef YADRO_PROCESSING_EVENT_H
#define YADRO_PROCESSING_EVENT_H
#include "Event.h"
#include "Time_Table.h"

struct Amount {
    int table;
    int price;
    pair<int,int> sum_time;
};

class Processing_Event {
private:
    int busy_tables = 0;
    multimap<string, int> queue;
    Info_Club information;
    vector<Event> events;
    Event e;
    vector<Time_Table> time_tables;
    set<Amount> result;
public:
    Processing_Event() = default;

    void parse_file(string filename);

    Event outgoing_events(Info_Club information, Event e, multimap<string, int> &queue, int &busy_tables);

    void print();

    string convert_to_string_incoming_event(Event e);

    string convert_to_string_outgoing_event(Event e);

    vector<pair<int,pair<int,int>>> table_occupancy_count();

    void revenue_calculation();
};


#endif //YADRO_PROCESSING_EVENT_H
