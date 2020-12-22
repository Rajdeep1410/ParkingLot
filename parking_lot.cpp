#include <bits/stdc++.h>
// #include <queue>
// #include <unordered_map>

using namespace std;

class Car
{
// as of now declaring all the data members as public

public:
    string registration_number;
    string color;

    Car(string reg_no, string clr)
    {
        registration_number = reg_no;
        color = clr;
    }
};

class ParkingLot //: public Car
{

    // as of now declaring all the data members as public
public:
    // registration_slot_mapping is an unordered map that will have key as registration_no(string) and value as slot(int)
    unordered_map<string, int> registration_slot_mapping;

    // color_registration_mapping is an unordered map that will have key as color(string) and value as registration_no(string)
    unordered_map<string, string> color_registration_mapping;

    // slot_car_mapping is a map(ordered by default) to maintain the orders of cars while showing status
    // it will have key as slot(int) and value as car(Car object)
    map<int, Car> slot_car_mapping;

    // we will initialize all slots as free
    //vector<int> available_parking_lots = {0};

    // below is a priority queue to store the available parking lots.
    priority_queue<int, vector<int>, greater<int>> available_parking_lots;

    /* Below constructor to modify and implement

    ParkingLot()
    {

        // registration_slot_mapping is an unordered map that will have key as registration_no(string) and value as slot(int) 
        unordered_map<string, int> registration_slot_mapping;

        // color_registration_mapping is an unordered map that will have key as color(string) and value as registration_no(string) 
        unordered_map<string, string> color_registration_mapping;

        // slot_car_mapping is a map(ordered by default) to maintain the orders of cars while showing status
        // it will have key as slot(int) and value as car(Car object) 
        map <int, Car> slot_car_mapping;

        // we will initialize all slots as free
        vector<int> available_parking_lots = {0};
    }

    */

    // The below function takes total slots as param input and creates a parking lot accordingly

    bool create_parking_lot(int total_slots)
    {
        // Using min-heap(priority queue) as this will always give minimum slot number in O(1) time
        cout << "Created a parking lot with " << total_slots << " slots" << endl;
        for (int i = 1; i <= total_slots; i++)
        {
            available_parking_lots.push(i);
        }
        return true;
    }

    // the below function returns the status of the parking lot

    bool status()
    {
        cout << "Slot No. \t Registration No \t Colour " << endl;
        map<int, Car>::iterator itr;
        for (itr = slot_car_mapping.begin(); itr != slot_car_mapping.end(); ++itr)
        {
            cout << itr->first << '\t' << itr->second.registration_number << '\t' << itr->second.color << endl;
        }

        cout << endl;
        return true;
    }

    // This function will be needed to get the nearest available slot

    int get_nearest_slot()
    {
        if (available_parking_lots.size())
        {
            int slot_val; // to store the nearest available slot value 
            slot_val = available_parking_lots.top();
            available_parking_lots.pop();
            return slot_val;
        }
        else
            return 0;
    }

    // The below function will take the slot number to be made free

    bool leave(int slot_to_be_freed)
    {
        string found = "";
        for (auto itr : registration_slot_mapping)
        {
            if (itr.second == slot_to_be_freed)
            {
                found = itr.first;
            }
        }

        if (found != "")
        {
            available_parking_lots.push(slot_to_be_freed);
            registration_slot_mapping.erase(found);
            Car car_to_leave = slot_car_mapping.at(slot_to_be_freed);
            car_to_leave.registration_number = found;
            color_registration_mapping[car_to_leave.color] = "";
            slot_car_mapping.erase(slot_to_be_freed); 
            cout << "Slot number" << slot_to_be_freed << " is free" << endl;
            return true;
        }

        else
        {
            cout << "Slot is not in use" << endl;
            return false;
        }
    }

    // The below function will park a car in an empty available slot and return the slot number

    int park(Car car)
    {
        int slot_no;
        slot_no = get_nearest_slot();
        if (slot_no == 0)
        {
            cout << "Sorry, parking lot is full" << endl;
            return 0;
        }

        cout << " Allocated slot number is: " << slot_no << endl;
        slot_car_mapping.insert({slot_no, car});
        registration_slot_mapping.insert({car.registration_number, slot_no});
        color_registration_mapping.insert({car.color, car.registration_number});
        return slot_no;
    }

    // The below function will give the Registration numbers of all cars of a particular colour

    vector<string> registration_numbers_for_cars_with_colour(string color)
    {
        vector<string> registration_numbers;
        for (auto it = color_registration_mapping.begin(); it != color_registration_mapping.end(); it++)
        {
            if (it->first == color)
            {
                registration_numbers.push_back(it->second);
            }
        }

        return registration_numbers;
    }

    // The below function will give the Slot numbers of all slots where a car of a particular colour is parked
    vector<int> slot_numbers_for_cars_with_colour(string color)
    {
        vector<string> registration_numbers;
        for (auto it = color_registration_mapping.begin(); it != color_registration_mapping.end(); it++)
        {
            if (it->first == color)
            {
                registration_numbers.push_back(it->second);
            }
        }

        vector<int> slots;
        /*
        
        for (auto it1 = registration_slot_mapping.begin(); it1!= registration_slot_mapping.end(); it1++)
        {
            // it->first = regis no     it->second = slot  
            for (auto it2 = registration_numbers.begin(); it2 != registration_numbers.end(); it2++)
            {
                if(it1->first == *it2)
                    slots.push_back(it1->second);
            }
        }
        */

        for (int i = 0; i < registration_numbers.size(); i++)
        {
            slots.push_back(registration_slot_mapping[registration_numbers[i]]);
        }
        return slots;
    }

    int slot_number_for_registration_number(string registration_number)
    {
        int slot_number = 0;
        if (auto itr = registration_slot_mapping.find(registration_number); itr != registration_slot_mapping.end()) // itr -> iterator
        {
            slot_number = itr->second; // itr->second = slot
            cout << slot_number << endl;
            return slot_number;
        }
        else
        {
            cout << "Slot not found" << endl;
            return slot_number;
        }
    }
};