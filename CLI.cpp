//
// Created by nicoc on 14.05.2024.
//
#include "GameOfLife.h"

class CLI{
    GameOfLife* gof;

    void create_world(){
        int height, width, populate;
        std::cout << "Enter world height: ";
        std::cin >> height;
        std::cout << "Enter world width: ";
        std::cin >> width;
        std::cout << "Should the world be populated at random (1=yes, 0=No)? ";
        std::cin >> populate;
        gof = new GameOfLife(height, width, populate);
    }

    void load_world(){
        std::string path;
        std::cout << "Please enter the name/path to the file you want to load: ";
        std::cin >> path;
        gof = new GameOfLife(path);
    }

    void save_world(){
        if (!gof) {
            std::cout << "No world has been started, please start one before trying to save it.\n";
            return;
        }
        std::cout << "The world has been saved into world.txt ";
        gof->save_game();
    }

    void toggle_display(){
        gof->toggle_display();
        std::cout << "The display of the world has been changed (standard is OFF)";
    }

    void set_delay_time_in_ms(){
        int t;
        std::cout << "Please enter the amount of ms between evolutions (default 200ms)";
        std::cin >> t;
        gof->set_delay(t);
    }

    void run_evolution(){
        int n;
        std::cout << "Please enter the number of generation that should be simulated: ";
        std::cin >> n;
        std::cout << "The simulation is starting... " << n << " generations will be simulated";
        gof->run_simulation(n);
    }

    void add_figure() {
        if (!gof) {
            std::cout << "No world created or loaded.\n";
            return;
        }
        int x, y;
        std::string figure;
        std::cout << "Enter figure (Glider, Toad, Beacon, Methuselah) and position (x, y): ";
        std::cin >> figure >> x >> y;
        // Assuming World class has these methods to add specific figures
        if (figure == "Glider") {
            gof->addGlider(x, y);
        } else if (figure == "Toad") {
            gof->addToad(x, y);
        } else if (figure == "Beacon") {
            gof->addBeacon(x, y);
        } else if (figure == "Methuselah") {
            gof->addMethuselah(x, y);
        } else {
            std::cout << "Invalid figure name.\n";
        }
    }

    void set_cell(){
        int x, y, s;
        std::cout << "Please enter the x,y coordinates and the state (0 or 1)";
        gof->set_state(x,y,s);
    }

    void get_cell(){
        int x, y, s;
        std::cout << "Please enter the x,y coordinates of the cell";
        gof->get_state(x,y);
    }

public:
    void start() {
        int choice = 0;
        do {
            std::cout << "\033[2J\033[H";
            std::cout << "1. Create world\n"
                      << "2. Load world\n"
                      << "3. Save world\n"
                      << "4. Toggle printing\n"
                      << "5. Set delay\n"
                      << "6. Run simulation\n"
                      << "7. Set cell state\n"
                      << "8. Get cell state\n"
                      << "9. Add figure\n"
                      << "0. Exit\n"
                      << "Enter choice: ";
            std::cin >> choice;
            switch (choice) {
                case 1: create_world(); break;
                case 2: load_world(); break;
                case 3: save_world(); break;
                case 4: toggle_display(); break;
                case 5: set_delay_time_in_ms(); break;
                case 6: run_evolution(); break;
                case 7: set_cell(); break;
                case 8: get_cell(); break;
                case 9: add_figure(); break;
                case 0: break;
                default: std::cout << "Invalid choice, try again.\n";
            }
        } while (choice != 0);
        delete gof;
    }
};
    int main(){

    }
};