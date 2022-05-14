#include <iostream>
#include <windows.h>
#include <fstream>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <iomanip>
#include <ctime>

using namespace std;
struct Bus{

    private:
        string  passwd_scheduler = "scheduler", passwd_ticketer = "ticketer"; // default password.
        string bus_name = "93", bus_plate = "A 124141";
        int tariff = 5, price_box = 0; // tariff is 5 birr per km.
        int journey = 0; // total journey of the bus.
        double total_km = 10, left_km = total_km; // total (km) of the bus.
        int sits = 30; // total number of sits.
        int km_travel = 0; // the bus how much it travels.
        string stations[100] = {"megenagna", "abensa_garaj", "emperial", "hayat_hostpital", "bole", "michael", "yoseph", "kadisco", "saris", "abo" }; // stations that the bus are stoped.
        string st_start = "Megenagna" , st_end = "Abo", current_station = stations[0], next_station = stations[1], issue = "Normal";
        const int width = 100;
        const int height = 5;
        int x_pos_bus = 1; int const y_pos_bus = 3;
        int hr=0, mn=0, sec = 0, flag = 1;
        double km_t = 0.6; // initially the bus is goes 1km in a minuet.
        int s = 0; //value if the bus is stopped or not. if x = 0 it is not stopped else it stopped somewhere.
        int st_index = 0; // the index of the station for time changing the current and next station.
        bool ticketer_mode = false;
        void bus_live() {
            x_pos_bus =  x_pos_bus + 90 / (km_t * 100);

            if(s == 0 ) { // if the bus is not stopped move the axis of the x position of the bus.
                if (x_pos_bus >= 90) {
                    x_pos_bus = 0;

                    //station tweek
                    left_km --;
                    st_index++;
                    current_station = stations[st_index];
                    next_station = stations[st_index + 1];

                }
            }else x_pos_bus = s;

            //Tariff
            if (left_km >= 15) {
                tariff = 10;
            }else if(left_km >= 10) {
                tariff = 7;
            }else if (left_km >= 5) {
                tariff = 5;
            } else if (left_km >= 0) {
                tariff = 3;
            }

        }
    public:
        //[u] user mode.
        void uMode () {
            ticketer_mode = false;
        }
        void reserveSits() {
            if (sits > 0){ // we can reserve sits until it's empty.
                sits -= 1;
                price_box += tariff;
            }
        }
        void freeSits() {
            if ( sits < 30) sits +=1; // we can't reserve sits above max level.
        }
        // [c] calling the ambulance.
        void callAmbulance() {
            issue ="calling...";
        }
        // [x] bus stopped.
        void busStop() {
            issue = "bus stropped...";
            s = x_pos_bus;
        }
        //[n] normal. sets to the default.
        void normal() {
            km_t = 0.2;
            issue = "Noramal";

        }
        //[l] low jum.
        void lowJum() {
            km_t += 0.2;
        }
        //[h] high jum.
        void highJum () {
            km_t += 0.4;
        }
        //[q] quit program
        void quitProgram() {
            flag = 0;
        }
        // flag -> control the game loop.
        bool getFlag() {
            return flag;
        }

        void setPlate(string p) {
            bus_plate = p;
        }
        string getBusPlate() {
            return bus_plate;
        }
        void setStaion(int index, string st) {
            stations[index] = st;
        }
        void setStart(string start) {
            st_start = start;
        }
        void setEnd(string e) {
            st_end = e;
        }

        void setBusName(string name) {
            bus_name = name;
        }
        void setPrice(int p) {
            tariff = p;
        }
        void setJourney(int j) {
            journey = j;
        }
        void setTotalKm(int tot_km) {
            total_km = tot_km;
        }
        void setKmTravel(int km_t) {
            km_travel = km_t;
        }
        int getSits() {
            return sits;
        }

        string getBusName() {
            return bus_name;
        }
        string getBus_plate() {
            return bus_plate;
        }
        void bus_animation() {
            bus_live();

            cout << "now: " << current_station << setw(65) << " " << "next: "<<next_station << endl;
             for (int i = 0; i < width + 1; i++) {
        cout << '-';
    }
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j  = 0; j < width; j++) {
                int r_w = 2; // right wall of animation board.
            if (j == 0) {
                cout << '|';
            }
            if (i == y_pos_bus && j == x_pos_bus) {
                cout << "0^0^0^0";

            }else {
                cout << " ";
            }
            if (j == (width - r_w)) {
                cout << ' ';
            }
        }
        cout << endl;
    }
    for (int i = 0; i < width + 1; i++) {
        cout << '-';
    }
    cout << endl;
        }

    void startTime() {
        Sleep(1000);
        system("cls" );

        cout << "======================================================================================================"<<endl;
        cout << "                                             hr / min / sec /                                         "<<endl;
        cout << "                                            -----------------                                         "<<endl;
        cout << "                                              " << hr << "  /  " << mn << "  /  " << sec << "              "<<endl;
        cout << "======================================================================================================" << endl;


        //left_km = left_km - km_t / 2;// when it goes one min 200m are traveles.
        if (left_km <= 0) {
            left_km = total_km; // it reaches it's destination.
            journey++;
        }
        sec++;
        if (sec == 60) {
            mn++;
            sec=0;
            if(mn == 60) {
                hr++;
                mn=0;
            }
        }

    }
    void printData() {
        cout << left;
        cout << setw(100) << setfill('-') << " " << setfill(' ') << endl; // 50
        cout << "| " << setw(11) << "Bus Name: " << setw(10) << bus_name << setw(11) << "Bus plate:" << setw(10) << bus_plate << setw(24) << " " << "| " << setw(18) << "    Ticketer   " << "  |" << endl;
        cout << "| " << setw(10) << "st start: " << setw(13) << st_start << " --> " << setw(10) << "st End: " << setw(28) << st_end << "| " << setw(19) << "[u] User mode " << " |" << endl;
        cout << "| " << setw(18) << "current station: " << setw(15) << current_station << " " << setw(15) << "next station: " << setw(16) << next_station << " | " << setw(20) << "[s] +1 sits  " << "|" << endl;
        cout << "| " << setw(17) << "Avaliabel sites: " << setw(45) << sits << "    | " << setw(20) << "[f] free sits" << "|" << endl;
        cout << "| " << setw(9) << "tariff: " << setw(57) << tariff << "| " << setw(20) << "[h] jum " << "| " << endl;
        cout << "| " << setw(66) << " " << "| " << setw(15) << "[l] Low jum " << setw(13) << "     |" << endl;
        cout << "| " << setw(66) << " " << "| " << setw(15) << "[h] high jum " << setw(14) <<"     |" << endl;
        cout << "| " << setw(7) << "Issue: " << setw(19) << issue << setw(40) << " " <<  "| " << setw(15) << "[n] normal" << setw(11) << "     |" << endl;
        cout << "| " << setw(9) << "Rmain(km): " << setw(55)<< left_km << "| " << setw(19) << "[x] problem  " << setw(3) << " |" << endl;
        cout << "| " << setw(66) << " " << "| " << setw(19) << "[c] call Ambulance " << setw(3) << " |" << endl;
        cout << "| " << setw(66) << " " << "| " << setw(15) << "[q] quit Program " << setw(7) << "   |" << endl;
        cout << setw(100) << setfill('-') << " " << setfill(' ') << endl;
}

    void start_T() {
        string passwd;
        cout << "enter the password: ";
        cin >> passwd;
        ticketer_mode = true;
        if (passwd_ticketer == passwd) {

            while (flag) {
                    if (ticketer_mode) {
            if (_kbhit()) { // return the positive value if the key is hitted.
                switch (_getch()) { // _getch() return what was the key touched from the keyboard.
                    case 's':
                        reserveSits();
                        break;
                    case 'f':
                        freeSits();
                        break;
                    case 'j':
                        lowJum();
                        break;
                    case 'h':
                        highJum();
                        break;
                    case 'n':
                        normal();
                        break;
                    case 'x':
                        busStop();
                        break;
                    case 'c':
                        callAmbulance();
                        break;
                    case 'q':
                        quitProgram();
                        break;
                }
            }
        }
            startTime();
            printData();
            bus_animation();
            }
        }else cerr << "error (Ticketer) password login!" << endl;
    }
    void start_U() {


        while (flag) {

        if (_kbhit()) {
            if (_getch() == 'q') {
                quitProgram();
            }
        }

        startTime();
        printData();
        bus_live();
        bus_animation();
    }
    }

    void report() {
        string passwd;
        cout << "Enter The password(scheduler): ";
        cin >> passwd;

        if (passwd == passwd_scheduler) {

            time_t tt; // arg of a time.
            struct  tm * ti; // return values are stored in structure.
            time(&tt); // applying a time.
            ti = localtime(&tt); // store local time on ti.

            fstream file;
            file.open("C:/Users/joy/Desktop/Bus_Service/Report.txt", ios::app | ios::in);

            if (file.is_open()) {

                file << "------------------------------------Report-----------------------------------" << endl;
                file << "bus name: " << bus_name << endl;
                file << "bus plate: " << bus_plate << endl;
                file << "total journey: " << journey << endl;
                file << "Colected money: " << price_box << endl;
                file << "bus Status " << issue << endl;
                file << "Date: " << asctime(ti);
                file << "------------------------------------------------------------------------------" << endl;

                cout << "Reports are generated....." << endl;

            }else {
                cerr << "File can't be opened" << endl;
                cerr << "report failed! Exitting....." << endl;
            }
        } else cerr << "INVALID! password (scheduler) login" << endl;
    }

    void setpasswd(string passwd) {
        int chose = 0;
        if (passwd == passwd_scheduler) {
            do {
                cout << "[1] set scheduler password" << endl;
                cout << "[2] set Tiketer password" << endl;
                cout << "[3] exit set password" << endl;
                cin >> chose;
                if (chose == 3) {
                    cout << "Exiting set password...." << endl;
                    break;
                }
                if (chose < 0 | chose > 4) {
                    cerr << "ERROR! selection. please select appropriately." << endl;
                }
            }while (chose < 0 | chose > 4);
            if (chose == 1) {
                cout << "new Password (scheduler): ";
                cin >> passwd;
                passwd_scheduler = passwd;
            } else if (chose == 2) {
                cout << "new Password (Ticketer): ";
                cin >> passwd;
                passwd_ticketer = passwd;
            }
        }
    }

    void addBus() {
        string passwd;
        cout << "password (scheduler): ";
        cin >> passwd;

        if (passwd == passwd_scheduler) {
            int dist = 0, price = 0;
            string name, s_st, e_st, plate;
            cout << "Bus Name: ";
            cin>> bus_name;
            cout << "Plate: ";
            cin >> bus_plate;
            cout << "Start Station: ";
            cin >> st_start;
            cout << "Terminal (end): ";
            cin >> st_end;
            cout << "distance (km): ";
            cin >> total_km;
            cout << "supply " << total_km << " stations respective: ";
            for (int i =0; i < total_km; i++) {
                cin >> e_st;
                stations[i] = e_st;
            }
        }else cerr << "INVALID! password (secheduler) login" << endl;
}


//structure ends here.
};



int main () {
    Bus bus;
    string passwd;
    int chose = 0;

    while(true) {
        do {
            cout << "                           [1] Scheduler " << endl;
            cout << "                           [2] Ticketer " << endl;
            cout << "                           [3] User " << endl;
            cout << "                           [4] exit " << endl;
            cout << "                          >>> ";
            cin >> chose;
                if (chose < 0 | chose > 5) {
                    cerr << "ERROR! selection. please select appropriately." << endl;
                }


            if (chose == 1) {
                while(true){

                    do {
                        cout << "                                [1] add bus " << endl;
                        cout << "                                [2] report " << endl;
                        cout << "                                [3] set password " << endl;
                        cout << "                                [4] exit " << endl;
                        cout << "                               >> ";
                        cin >> chose;
                         if (chose < 0 | chose > 5) {
                            cerr << "ERROR! selection. please select appropriately." << endl;
                        }
                    } while (chose < 0 | chose > 4);

                    if ( chose == 1 ) {
                         bus.addBus();
                    } else if (chose == 2) {
                        bus.report();
                    } else if (chose == 3) {
                        cout << "enter the password: ";
                        cin >> passwd;
                        bus.setpasswd(passwd);
                    }
                    if (chose == 4) {
                                cout <<  "Admin Exiting ....." << endl;
                                break;
                            }

                }
            } else if (chose == 2) {
                bus.start_T();
            } else if (chose == 3) {
                bus.start_U();
            }
        }while( chose < 0 | chose > 5);



        if (chose == 4) {
                    cout << "APP exiting ......";
                    break;
                }

    }
    return 0;
}
