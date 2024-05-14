//
// Created by nicoc on 13.05.2024.
//

#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#include <string>
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <algorithm>
#include "2_dimesional_vector.h"

class GameOfLife {
    private:
        const std::string LIVE = "\033[32mX\033[0m";
        const std::string DEAD = "\033[90mO\033[0m";
        const std::string CLEAN = "\033[2J\033[H";

        int height, width;
        std::vector<std::vector<int>> grid;
        std::vector<int> past, present, future; // This definition is completely optional
        bool print_enable = false;
        int print_delay_ms = 200;

        void evolve(std::vector<int>& map, std::vector<int>&next, std::vector<int>& neighbors);
        bool is_stable();
        void print();
        void load(std::string p);
        void save();
        std::vector<int> count_neighbors(const std::vector<int>& vec);
        int get_element_value(const std::vector<int> &col, int x, int y) const;

    public:
        GameOfLife(int h, int w, bool populate = false);
        GameOfLife(const std::string& path);
        void run_simulation(int gens);
        void toggle_display() {print_enable = !print_enable;} // Initial value is always OFF
        void set_delay(int delay_ms) {print_delay_ms = delay_ms;} // Initial delay is 200ms
        void save_game();
        void load_world(std::string path);
        void set_state(int i, int s);
        void set_state(int x, int y, int s);
        void set_states(std::vector<std::tuple<int, int, int>>& states);
        int get_state(int i);
        int get_state(int x, int y);
        void addGlider(int x, int y);
        void addToad(int x, int y);
        void addBeacon(int x, int y);
        void addMethuselah(int x, int y);
        void display(); // For testing porpuse only
};


#endif //GAMEOFLIFE_H
