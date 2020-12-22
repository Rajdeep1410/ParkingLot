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
        cout << "Slot No. \tRegistration No \tColour " << endl;
        map<int, Car>::iterator itr;
        for (itr = slot_car_mapping.begin(); itr != slot_car_mapping.end(); ++itr)
        {
            cout << "  " << itr->first << "\t\t" << itr->second.registration_number << "\t\t" << itr->second.color << endl;
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
            cout << "Slot number " << slot_to_be_freed << " is free" << endl;
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
        cout << "Size of vector registration_numbers: " << registration_numbers.size() << endl;
        for (auto x : registration_numbers)
        {
            cout << x << ", ";
        }
        cout << endl;

        return registration_numbers;
    }

    // The below function will give the Slot numbers of all slots where a car of a particular colour is parked
    vector<int> slot_numbers_for_cars_with_colour(string color)
    {
        vector<string> registration_numbers;
        int c=0; //added
        for (auto it = color_registration_mapping.begin(); it != color_registration_mapping.end(); it++)
        {
            cout<<"Loop number "<<c++; //added
            cout<<"Registration Number = "<<it->second<<"color = "<<color<<endl; //added
            if (it->first == color)
            {
                cout<<"Registration Number "<<(it->second)<<" pushed with color = "<<(it->first)<<endl;//added
                registration_numbers.push_back(it->second);
            }
        }

        vector<int> slots;

        for (int i = 0; i < registration_numbers.size(); i++)
        {
            slots.push_back(registration_slot_mapping[registration_numbers[i]]);
        }

        cout << "The size of slot vector is: " << slots.size() << endl;
        cout << "The slot numbers matching the given color are: " << endl;
        for (int i = 0; i < slots.size(); i++)
        {
            cout << slots[i] << ", ";
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

// *********************************************************************************************************************************
// ADDED TO TEST
// *********************************************************************************************************************************

int main()
{
    ParkingLot parking_lot;
    int choice, slot;
    string reg_no = "", color = "";

    do
    {
        cout << "\n**************MENU**************" << endl;
        cout << "1. To create parking lot" << endl;
        cout << "2. To park cars" << endl;
        cout << "3. To leave" << endl;
        cout << "4. To display status" << endl;
        cout << "5. To display registration_numbers_for_cars_with_colour" << endl;
        cout << "6. To display slot_numbers_for_cars_with_colour " << endl;
        cout << "7. To display slot_number_for_registration_number" << endl;
        cout << "8. To EXIT" << endl;
        cout << "\nEnter your choice: ";

        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << " To create_parking_lot" << endl;
            cout << "Enter no of slots: " << endl;
            cin >> slot;
            parking_lot.create_parking_lot(slot);
            break;

        case 2:
        {
            cout << " To park" << endl;
            cout << "Enter reg_no and color: " << endl;
            cin >> reg_no >> color;
            Car car(reg_no, color);
            parking_lot.park(car);
            break;
        }

        case 3:
            cout << " To leave" << endl;
            cout << "Enter slot: " << endl;
            cin >> slot;
            parking_lot.leave(slot);
            break;

        case 4:
            cout << "To display status: " << endl;
            parking_lot.status();
            break;

        case 5:
            cout << "To display registration_numbers_for_cars_with_colour" << endl;
            cout << "Enter car color: " << endl;
            cin >> color;
            parking_lot.registration_numbers_for_cars_with_colour(color);
            break;

        case 6:
            cout << " To display slot_numbers_for_cars_with_colour " << endl;
            cout << "Enter color: " << endl;
            cin >> color;
            cout << "Slot numbers are: " << endl;
            parking_lot.slot_numbers_for_cars_with_colour(color);
            break;

        case 7:
            cout << " To display slot_number_for_registration_number " << endl;
            cout << "Enter registration_number: " << endl;
            cin >> reg_no;
            cout << "Slot numbers are: " << endl;
            parking_lot.slot_number_for_registration_number(reg_no);
            break;

        case 8:
            cout << "Exiting!.." << endl;
            exit(0);

        default:
            cout << "Wrong Command! Please enter 1 to 8" << endl;
            break;
        }
    } while (choice <= 8);

    return 0;
}