#include <deque>
#include <regex>
#include "work.h"
#include "binTree.h"
#include "table_inform.h"

void split(const std::string& str, std::vector<std::string>& out) {
    int start, end = 0;
    while ((start = str.find_first_not_of(' ', end)) != std::string::npos) {
        end = str.find(' ', start);
        out.push_back(str.substr(start, end - start));
    }
}

void work_in_club(const std::string& file_name) {
    std::ifstream input(file_name.c_str());
    std::string out_name("check.txt");
    std::ofstream output(out_name.c_str(), std::ios::out);

    if (!input.good()) {
        std::cerr << "Cannot open the file " << file_name << "\n";
        std::exit(-1);
    }
    std::regex pattern_N("^[1-9]\\d*$"); // Natural number
    std::regex pattern_T("\\d{2}:\\d{2}"); // "XX:XX"
    std::regex pattern_C("^[a-z0-9_-]+$");
    std::string buffer, close_time;
    int num_of_comp, price;
    Time start_time, end_time;

    BinTree<std::string> clients;
    std::deque<std::string> queue;

    std::getline(input, buffer);
    if (std::regex_match(buffer, pattern_N)) {
        num_of_comp = std::stoi(buffer);
    }
    else {
        std::cerr << buffer;
        std::exit(-1);
    }

    std::vector<table_inform> table(num_of_comp);
    std::vector<std::string> actions;
    table_inform::count_free = num_of_comp;

    std::getline(input, buffer);
    split(buffer, actions);
    if (actions.size() == 2 && std::regex_match(actions[0], pattern_T) &&
        std::regex_match(actions[1], pattern_T)) {
        start_time = Time(actions[0]);
        std::cout << actions[0] << "\n";
        output << actions[0] << "\n";

        close_time = actions[1];
        end_time = Time(actions[1]);
    }
    else {
        std::cerr << buffer;
        std::exit(-1);
    }
    actions.clear();

    std::getline(input, buffer);
    if (std::regex_match(buffer, pattern_N)) {
        price = std::stoi(buffer);
    }
    else {
        std::cerr << buffer;
        std::exit(-1);
    }

    while (std::getline(input, buffer)) {
        std::cout << buffer << "\n";
        output << buffer << "\n";

        split(buffer, actions);
        if (!std::regex_match(actions[0], pattern_T) ||
            !std::regex_match(actions[1], pattern_N)) {
            std::cerr << buffer;
            std::exit(-1);
        }
        Time current(actions[0]);
        int id = std::stoi(actions[1]);
        switch (id)
        {
            case 1: {
                if (actions.size() != 3 || !std::regex_match(actions[2], pattern_C)) {
                    std::cerr << buffer;
                    std::exit(-1);
                }

                if (current < start_time || current > end_time) {
                    std::cout << current << " 13 NotOpenYet\n";
                    output << current << " 13 NotOpenYet\n";
                    break;
                }
                if (clients.find(actions[2]) != nullptr) {
                    std::cout << current << " 13 YouShallNotPass\n";
                    output << current << " 13 YouShallNotPass\n";
                    break;
                }

                clients.insert(actions[2]);
                break;
            }
            case 2: {
                if (actions.size() != 4 || !std::regex_match(actions[3], pattern_N)
                    || std::stoi(actions[3]) > num_of_comp
                    || !std::regex_match(actions[2], pattern_C)) {
                    std::cerr << buffer;
                    std::exit(-1);
                }

                int pos = std::stoi(actions[3]);
                if (!table[pos - 1].empty) {
                    std::cout << current << " 13 PlaceIsBusy" << "\n";
                    output << current << " 13 PlaceIsBusy" << "\n";
                    break;
                }

                auto client = clients.find(actions[2]);
                if (client == nullptr) {
                    std::cout << current << " 13 ClientUnknown" << "\n";
                    output<< current << " 13 ClientUnknown" << "\n";
                    break;
                }

                table[pos - 1].name = actions[2];
                table[pos - 1].start = current;
                table[pos - 1].empty = false;

                if (client->table != -1) {
                    table[client->table].count += current - table[client->table].start;
                    table[client->table].income += table[client->table].count.rounding() * price;
                    table[client->table].start.clear();
                    table[client->table].empty = true;
                }
                else {
                    table_inform::count_free--;
                }
                client->table = pos - 1;
                break;
            }
            case 3: {
                if (actions.size() != 3 || !std::regex_match(actions[2], pattern_C)) {
                    std::cerr << buffer;
                    std::exit(-1);
                }
                if (table_inform::count_free > 0) {
                    std::cout << current << " 13 ICanWaitNoLonger!" << "\n";
                    output << current << " 13 ICanWaitNoLonger!" << "\n";
                    break;
                }
                if (queue.size() >= num_of_comp) {
                    std::cout << current << " 11 " << actions[3] << "\n";
                    output << current << " 11 " << actions[3] << "\n";
                    break;
                }
                queue.push_back(actions[2]);
                break;
            }
            case 4: {
                if (actions.size() != 3 || !std::regex_match(actions[2], pattern_C)) {
                    std::cerr << buffer;
                    std::exit(-1);
                }

                auto client = clients.find(actions[2]);
                if (client == nullptr) {
                    std::cout << current << " 13 ClientUnknown\n";
                    output << current << " 13 ClientUnknown\n";
                    break;
                }
                int old_table = client->table;
                if (old_table != -1) {
                    Time new_duration = current - table[old_table].start;
                    table[old_table].count += new_duration;
                    table[old_table].income += new_duration.rounding() * price;
                    if (!queue.empty()) {
                        table[old_table].name = queue.front();
                        queue.pop_front();
                        table[old_table].start = current;
                        clients.find(table[old_table].name)->table = old_table;
                        std::cout << current << " 12 " << table[old_table].name << " " << old_table + 1 << "\n";
                        output << current << " 12 " << table[old_table].name << " " << old_table + 1 << "\n";
                    }
                    else {
                        table[old_table].start.clear();
                        table[old_table].empty = true;
                        table_inform::count_free++;
                    }
                }
                clients.erase(actions[2]);
                break;
            }
            default:
                std::cerr << buffer;
                std::exit(-1);
        }
        actions.clear();
    }
    output.close();

    if (clients.getsize() > 0) {
        clients.print(out_name, close_time);
    }
    output.open(out_name.c_str(), std::ios::app);
    std::cout << close_time << "\n";
    output << close_time << "\n";

    for (int i = 0; i < num_of_comp; ++i) {
        if (!table[i].empty) {
            Time new_duration = end_time - table[i].start;
            table[i].count += new_duration;
            table[i].income += new_duration.rounding() * price;
            table[i].empty = true;
        }
        std::cout << i + 1 << " " << table[i].income << " " << table[i].count << "\n";
        output << i + 1 << " " << table[i].income << " " << table[i].count << "\n";
    }
    output.close();
}
