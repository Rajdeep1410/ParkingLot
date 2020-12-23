#include <bits/stdc++.h>
#include "parking_lot.cpp"

using namespace std;

// from parking_lot import ParkingLot, Car

ParkingLot parking_lot;

void process(string command_params)
{

    vector<string> command_with_params;
    string word;                      // word variable to store word
    stringstream iss(command_params); // making a string stream

    while (iss >> word) // Read each word and insert it into a vector
        command_with_params.push_back(word);

    // for(int i=0; i<command_with_params.size(); i++)
    //     cout<<"Command with param ["<<i<<"] is: "<<command_with_params[i]<<endl;

    vector<string> command;
    command = command_with_params;

    // for(int i=0; i<command.size(); i++)
    //     cout<<"Command ["<<i<<"] is: "<<command[i]<<endl;

    if (command[0] == "create_parking_lot")
    {
        if (command.size() != 2)
        {
            cout << "create_parking_lot needs no of slots as well" << endl;
        }
        // else if (isdigit(stoi(command[1])) == 0)
        // {
        //     cout << "param should be 'integer type'" << endl;
        // }
        else
        {
            parking_lot.create_parking_lot(stoi(command[1]));
        }
    }

    else if (command[0] == "park")
    {
        if (command.size() != 3)
        {
            cout << "park needs registration number and color as well" << endl;
        }

        else
        {
            Car car(command[1], command[2]);
            parking_lot.park(car);
        }
    }

    else if (command[0] == "leave")
    {
        if (command.size() != 2)
        {
            cout << "leave needs slot number as well" << endl;
        }
        // else if (isdigit(stoi(command[1])) == 0)
        // {
        //     cout << "slot number should be 'integer type'" << endl;
        // }

        else
        {
            parking_lot.leave(stoi(command[1]));
        }
    }

    else if (command[0] == "status")
        parking_lot.status();

    else if (command[0] == "registration_numbers_for_cars_with_colour")
    {
        if (command.size() != 2)
            cout << "registration_numbers_for_cars_with_colour needs color as well" << endl;
        else
            parking_lot.registration_numbers_for_cars_with_colour(command[1]);
    }

    else if (command[0] == "slot_numbers_for_cars_with_colour")
    {
        if (command.size() != 2)
            cout << "slot_numbers_for_cars_with_colour needs color as well" << endl;
        else
            parking_lot.slot_numbers_for_cars_with_colour(command[1]);
    }

    else if (command[0] == "slot_number_for_registration_number")
    {
        if (command.size() != 2)
            cout << "slot_number_for_registration_number needs registration_number as well" << endl;
        else
            parking_lot.slot_number_for_registration_number(command[1]);
    }

    else if (command[0] == "exit")
        exit(0);

    else
        cout << "Wrong Command" << endl;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    { // argc should be 2 for correct execution
        // We print argv[0] assuming it is the program name
        // cout << "usage: " << argv[0] << " <filename>\n";

        // if len(sys.argv) == 1:
        //     while True:
        //         line = input()
        //         process(line)

        while (true)
        {
            string line;
            getline(cin, line);
            process(line);
        }
    }
    else
        cout << "Wrong Command!" << endl;

    return 0;
}

//     else
//     {
//         // We assume argv[1] is a filename to open
//         ifstream the_file(argv[1]);
//         // Always check to see if file opening succeeded
//         if (!the_file.is_open())
//             cout << "Could not open file\n";
//         else
//         {
//             // char x;
//             // // the_file.get ( x ) returns false if the end of the file
//             // //  is reached or an error occurs
//             // while (the_file.get(x))
//             //     cout << x;

//             std::string line;
//             while (getline(the_file, line))
//             {
//                 process(line);
//             }
//         }
//     }
//     // the_file is closed implicitly here
// }