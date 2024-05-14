//
// Created by nicoc on 13.05.2024.
//

#include <fstream>
#include <utility>
#include "GameOfLife.h"

GameOfLife::GameOfLife(int h, int w, bool p) : height(h), width(w){
    grid.resize(height, std::vector<int>(width));

    // Populate the world at random
    if (p) {
        srand(time(0));
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                grid[i][j] = rand() % 2;
            }
        }
    }

    // Assign memory
    present = collapse(grid);
    past = present;
    future = present;
}


GameOfLife::GameOfLife(const std::string &path) {
    load(path);
}

void GameOfLife::run_simulation(int gens) {

    for (int i = 0; i < gens; ++i) {

        if (print_enable){
            print();
            std::this_thread::sleep_for(std::chrono::milliseconds(print_delay_ms));
        }

        std::vector<int> neighbors = count_neighbors(present);
        evolve(present, future, neighbors);

        if (is_stable()) {
            std::cout << "The system is stable and the simulation has been stopped" << std::endl;
            break;
        }
        // Assign new values to compare later
        past = present;
        present = future;
    }
}

void GameOfLife::evolve(std::vector<int>& map, std::vector<int>&next, std::vector<int>& neighbors) {
    std::transform(map.begin(), map.end(), neighbors.begin(), next.begin(), [](int live, int n) {
        if (live == 1){
            if (n < 2) return 0;
            if (n == 2 || n == 3) return 1;
            if (n > 3) return 0;
        }
        return (n == 3) ? 1 : 0;
    });
}


std::vector<int> GameOfLife::count_neighbors(const std::vector<int>& vec) {
    std::vector<int> result;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {

            int count = 0;

            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {

                    if (dx == 0 && dy == 0) continue;

                    if (get_element_value(vec, j + dx, i + dy) == 1) {
                        count++;
                    }
                }
            }
            result.push_back(count);
        }
    }
    return result;
}

int GameOfLife::get_element_value(const std::vector<int>& col, int x, int y) const {
    x = (x + width) % width;
    y = (y + height) % height;
    return col[y * width + x];
}

bool GameOfLife::is_stable() {
    return (std::equal(present.begin(), present.end(), future.begin())
    || std::equal(past.begin(), past.end(), future.begin()));
}

void GameOfLife::print() {
    int l = 0;
    std::cout << CLEAN;
    std::for_each(present.begin(), present.end(), [this, &l](int live){
        //std::cout << (live ? LIVE : DEAD) << " ";
        std::cout << live << " ";
        l++;
        if (l%width == 0){std::cout << "\n";
        }
    });
}

void GameOfLife::load(std::string p) {
    std::ifstream file(p);
    if (file.is_open()) {
        file >> height >> width;
        present = std::vector<int> (height * width);

        for (int & pre : present) {
            file >> pre;
        }
    }
}

void GameOfLife::save() {
    std::ofstream file("world.txt");
    if (file.is_open()) {
        file << height << " " << width << "\n";
        for (const int& num : present) {
            file << num << "\n";
        }
    }
}

void GameOfLife::save_game(){
    save();
}

void GameOfLife::load_world(std::string path) {
    load(path);
}

void GameOfLife::set_state(int i, int s) {
    if (i > present.size()) {
        std::cout << "Invalid index";
        return;
    }
    present[i] = s;
}

void GameOfLife::set_state(int x, int y, int s) {
    x = (x + width) % width;
    y = (y + height) % width;
    present[y * width + x] = s;
}

void GameOfLife::set_states(std::vector<std::tuple<int, int, int>>& states) {

    for (std::tuple<int, int, int> c: states){
        auto [x, y, s] = c;
        set_state(x, y, s);
    }
}

int GameOfLife::get_state(int i) {
    if (i > present.size()) {
        std::cout << "Invalid index";
        return -1;
    }
    return present[i];
}

int GameOfLife::get_state(int x, int y) {
    x = (x + width) % width;
    y = (y + height) % width;
    return present[x * width + y];
}

void GameOfLife::addGlider(int x, int y) {
    set_state(x, y, 1);
    set_state(x+1, y-1, 1);
    set_state(x-1, y, 1);
    set_state(x-1, y-1, 1);
    set_state(x-1, y-2, 1);

}

void GameOfLife::addToad(int x, int y) {
    set_state(x, y, 1);
    set_state(x+1, y+1, 1);
    set_state(x+1, y-1, 1);
    set_state(x+1, y, 1);
    set_state(x, y-1, 1);
    set_state(x, y-2, 1);
}

void GameOfLife::addBeacon(int x, int y) {
    set_state(x, y, 1);
    set_state(x-1, y, 1);
    set_state(x, y+1, 1);
    set_state(x-3, y+3, 1);
    set_state(x-3, y+2, 1);
    set_state(x-2, y+3, 1);
}

void GameOfLife::addMethuselah(int x, int y) {
    set_state(x, y, 1);
    set_state(x, y-1, 1);
    set_state(x, y+1, 1);
    set_state(x+3, y, 1);
    set_state(x+2, y-1, 1);
    set_state(x+2, y+1, 1);
    set_state(x+1, y-4, 1);
    set_state(x+2, y-4, 1);
    set_state(x+1, y-5, 1);
    set_state(x+2, y-5, 1);
}

void GameOfLife::display(){
    print();
}


int main(){
    GameOfLife gof = GameOfLife(20,20);
    //gof.set_state(0,2,1);

    gof.addToad(9, 9);
    gof.display();

    //gof.toggle_display();
    //gof.set_delay(1000);
    //gof.run_simulation(20);
    //gof.save_game();
    //gof.load_world("world.txt");
    return 0;
}