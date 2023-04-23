#include <regex>
#include "Processing_Event.h"

pair<int, int> check_time(string s) {
    pair<int, int> res;
    if (s[0] == '0') {
        res.first = stoi(s.substr(1, 2));
    } else {
        res.first = stoi(s.substr(0, 2));
    }
    if (s[3] == '0') {
        res.second = stoi(s.substr(4, 5));
    } else {
        res.second = stoi(s.substr(3, 5));
    }
    return res;
}

string convert_hours(pair<int, int> p) {
    string res = "";
    if (p.first < 10) {
        res += '0';
    }
    res += to_string(p.first);

    res += ':';
    if (p.second < 10) {
        res += '0';
    }
    res += to_string(p.second);
    return res;
}

bool check_format(string str, regex regexPattern) {
    if (!regex_match(str, regexPattern)) {
        return false;
    }
    return true;
}

bool check_id(int n, string s) {
    if (n > 4) {
        cout << "Line error: " << s << endl;
        return false;
    }
    return true;
}

void Processing_Event::parse_file(string filename) {
    string s;
    ifstream file(filename);
    getline(file, s);
    regex tablesRegex("\\d+");
    if (!check_format(s, tablesRegex)) {
        throw string{s};
    }
    information.set_num_tables(stoi(s));

    getline(file, s);
    regex timeRegex("^([01]?[0-9]|2[0-3]):[0-5][0-9]\\s([01]?[0-9]|2[0-3]):[0-5][0-9]$");
    if (!check_format(s, timeRegex)) {
        throw string{s};
    }

    int pos = s.find(' ', 0);

    pair<int, int> p = check_time(s);
    information.set_start_time(p);

    p = check_time(s.substr(pos + 1));
    information.set_finish_time(p);

    getline(file, s);
    regex costRegex("\\d+");
    if (!check_format(s, costRegex)) {
        throw string{s};
    }
    information.set_price(stoi(s));

    Event temp;
    int pos2 = 0;

    std::regex eventRegex(R"(\d{2}:\d{2} \d+ [a-z0-9_-]+|\d{2}:\d{2} \d+ [a-z0-9_-]+ \d+)");

    while (!file.eof()) {
        getline(file, s);
        if (!check_format(s, eventRegex)) {
            throw string{s};
        }

        pos = s.find(' ', 0);
        p = check_time(s.substr(0, pos));
        temp.set_cur_time(p);

        pos2 = s.find(' ', pos + 1);

        if (!check_id(stoi(s.substr(pos + 1, pos2)), s)) {
            throw string{s};
        }
        temp.set_id(stoi(s.substr(pos + 1, pos2)));

        int pos3 = 0;
        if (temp.get_id() == 2) {
            pos = s.find(' ', pos + 1);
            string str = s.substr(pos + 1, pos2);
            if (str.find(' ') != -1) {
                pos3 = str.find(' ');
                str.erase(pos3);
            }
            pos3 = s.find(' ', pos2 + 1);
            temp.set_name_client(str);
            string sss = (s.substr(pos3));
            sss.erase(find(sss.begin(), sss.end(), ' '));
            temp.set_table(stoi(sss));
        } else {
            temp.set_name_client(s.substr(pos2 + 1));
            temp.set_table(0);
        }
        events.push_back(temp);
    }
}

Event
Processing_Event::outgoing_events(Info_Club information, Event e, multimap<string, int> &queue, int &busy_tables) {
    Event out_event;
    out_event.set_cur_time(e.get_cur_time());
    if (e.get_cur_time().first < information.get_start_time().first) {
        out_event.set_id(13);
        out_event.set_name_client("NotOpenYet");
        return out_event;
    }
    bool contain_name = false;
    for (auto &pos: queue) {
        if (pos.first == e.get_name_client()) {
            contain_name = true;
        }
    }

    if (e.get_id() == 1 && contain_name) {
        out_event.set_id(13);
        out_event.set_name_client("YouShallNotPass");
        return out_event;
    }

    if (e.get_id() == 1) {
        queue.insert(make_pair<string, int>(e.get_name_client(), e.get_table()));
    }

    if (!queue.count(e.get_name_client()) && e.get_id() != 1) {
        out_event.set_id(13);
        out_event.set_name_client("ClientUnknown");
        out_event.set_table(0);
        return out_event;
    }
    bool check_queue = false;
    for (auto &pos: queue) {
//        if (pos.second == -1 || pos.second == 0) {
        if (pos.second == -1) {
            check_queue = true;
        }
    }

    if (e.get_id() == 4) {
        for (auto it = time_tables.begin(); it < time_tables.end(); ++it) {
            if (it->get_name_client() == e.get_name_client() && it->get_finish_time() == pair<int, int>(0, 0)) {
                it->set_finish_time(e.get_cur_time());
            }
        }
    }

    //if (e.get_id() == 4 && busy_tables == information.get_num_tables() && check_queue)
    if (e.get_id() == 4 && check_queue) {
        out_event.set_id(12);
        int outgoing_client_table;
        string outgoing_client_name;
        for (auto pos = queue.begin(); pos != queue.end(); pos++) {
            if (pos->second == -1 || pos->second == 0) {
                outgoing_client_table = queue.find(e.get_name_client())->second;
                out_event.set_table(outgoing_client_table);
                queue.erase(queue.find(e.get_name_client()));
                pos->second = outgoing_client_table;
                out_event.set_name_client(pos->first);
                for (auto &pos2: queue) {
                    if (pos2.first == e.get_name_client()) {
                        pos2.second = e.get_table();
                        busy_tables++;
                    }
                }
                Time_Table tmp;
                tmp.set_name_client(pos->first);
                tmp.set_start_time(e.get_cur_time());
                tmp.set_table(outgoing_client_table);
                time_tables.push_back(tmp);
                return out_event;
            }
        }
        return out_event;
    }

    if (e.get_id() == 4 && busy_tables <= information.get_num_tables() && !check_queue) {
        queue.erase(queue.find(e.get_name_client()));
        busy_tables--;
    }

    bool contain_table = false;
    string contain_table_name = "";
    if (e.get_table() != 0) {
        for (auto &pos: queue) {
            if (pos.second == e.get_table()) {
                contain_table = true;
                contain_table_name = pos.first;
            }
        }
    }

    if (contain_table) {
        out_event.set_id(13);
        out_event.set_name_client("PlaceIsBusy");
        if (contain_table_name != e.get_name_client()) {
            for (auto &pos: queue) {
                if (pos.first == e.get_name_client()) {
                    pos.second = -1;
                }

            }
        }
        return out_event;
    }


    if (e.get_id() == 3) {
        if (contain_table_name != e.get_name_client()) {
            for (auto &pos: queue) {
                if (pos.first == e.get_name_client()) {
                    pos.second = -1;
                }

            }
        }
    }
    int count_client_wait = 0;
    for (auto &pos: queue) {
        if (pos.second == -1) {
            pos.second = -1;
            count_client_wait++;
        }
    }
    if (e.get_id() == 3 && busy_tables == information.get_num_tables() && count_client_wait > busy_tables) {
        out_event.set_id(11);
        out_event.set_name_client(e.get_name_client());
        queue.erase(queue.find(e.get_name_client()));
        return out_event;
    }

    if (e.get_id() == 2) {
        int size = time_tables.size();
        for (auto &pos: queue) {
            if (pos.first == e.get_name_client()) {
                if (pos.second > 0) {
                    for (int i = 0; i < size; i++) {
                        //&& time_tables[i].get_finish_time() == pair<int, int>(0, 0)
                        if (time_tables[i].get_name_client() == e.get_name_client() ) {
                            Time_Table tmp;
                            tmp.set_name_client(e.get_name_client());
                            tmp.set_start_time(e.get_cur_time());
                            tmp.set_table(e.get_table());
                            time_tables[i].set_finish_time(e.get_cur_time());
                            time_tables.push_back(tmp);
                            pos.second = e.get_table();
                        }
                    }
                } else {
                    pos.second = e.get_table();
                    busy_tables++;
                    Time_Table tmp;
                    tmp.set_name_client(e.get_name_client());
                    tmp.set_start_time(e.get_cur_time());
                    tmp.set_table(e.get_table());
                    time_tables.push_back(tmp);
                }
            }
        }
    }

    if (e.get_id() == 3 && busy_tables < information.get_num_tables()) {
        out_event.set_id(11);
        out_event.set_name_client("ICanWaitNoLonger!");
        return out_event;
    }
    out_event.set_id(14);
    return out_event;
}

bool operator<(const Amount &dot1, const Amount &dot2) {
    return dot1.table < dot2.table;
}

void Processing_Event::print() {
    cout << convert_hours(information.get_start_time()) << endl;

    Event temp;
    for (int i = 0; i < events.size(); ++i) {
        temp = outgoing_events(information, events[i], queue, busy_tables);

        cout << convert_to_string_incoming_event(events[i]) << endl;
        if (temp.get_id() != 14) {
            cout << convert_to_string_outgoing_event(temp) << endl;
        }
    }
    for (auto &it: queue) {
        temp.set_name_client(it.first);
        temp.set_id(11);
        temp.set_table(0);
        temp.set_cur_time(pair<int, int>(information.get_finish_time().first, information.get_finish_time().second));
        for (auto &it2: time_tables) {
            if (it2.get_finish_time() == pair<int, int>(0, 0)) {
                it2.set_finish_time(pair<int, int>(information.get_finish_time().first, information.get_finish_time().second));
            }
        }
        cout << convert_to_string_outgoing_event(temp) << endl;
    }
    Event leave_clients;
    cout << convert_hours(information.get_finish_time()) << endl;

    table_occupancy_count();
    revenue_calculation();

    for (auto &i: result) {
        cout << i.table << ' ' << i.price << ' ' << convert_hours(i.sum_time) << endl;
    }
}

string Processing_Event::convert_to_string_incoming_event(Event e) {
    string res = "";
    res += convert_hours(e.get_cur_time()) + ' ' + to_string(e.get_id()) + ' ' + e.get_name_client();
    if (e.get_table() != 0) {
        res += ' ' + to_string(e.get_table());
    }
    return res;
}

string Processing_Event::convert_to_string_outgoing_event(Event e) {
    string res = "";
    res += convert_hours(e.get_cur_time()) + ' ' + to_string(e.get_id()) + ' ' + e.get_name_client();
    if (e.get_table() != 0) {
        res += ' ' + to_string(e.get_table());
    }
    return res;
}

int hours_to_minutes(pair<int, int> p) {
    return p.second + (p.first * 60);
}

pair<int, int> minutes_to_hours(int m) {
    pair<int, int> p;
    int hours = m / 60;
    int minutes = m - (hours * 60);
    p.first = hours;
    p.second = minutes;
    return p;
}

vector<pair<int, pair<int, int>>> Processing_Event::table_occupancy_count() {
    int sum = 0;
    vector<pair<int, pair<int, int>>> res;
    pair<int, pair<int, int>> tmp;
    for (auto &i: time_tables) {
        sum = hours_to_minutes(i.get_finish_time()) - hours_to_minutes(i.get_start_time());
        tmp.first = i.get_table();
        tmp.second = minutes_to_hours(sum);
        res.push_back(tmp);
    }
    return res;
}

void Processing_Event::revenue_calculation() {
    vector<pair<int, pair<int, int>>> t_o_c = table_occupancy_count();
    int sum_minutes;
    int cur_minutes;
    Amount a;
    pair<int, int> p;
    for (int i = 0; i < information.get_num_tables(); i++) {
        sum_minutes = 0;
        cur_minutes = 0;
        a.price = 0;
        a.table = i + 1;
        if (a.table > information.get_num_tables() || a.table < 0) {
            break;
        }
        for (int j = 0; j < time_tables.size(); ++j) {
            if (a.table == t_o_c[j].first) {
                sum_minutes = hours_to_minutes(t_o_c[j].second);
                cur_minutes += sum_minutes;
                p = minutes_to_hours(sum_minutes);
                if (p.second > 0) {
                    a.price += p.first * information.get_price() + information.get_price();
                } else {
                    a.price += p.first * information.get_price();
                }
            }
        }
        a.sum_time = minutes_to_hours(cur_minutes);
        result.insert(a);
    }
}
