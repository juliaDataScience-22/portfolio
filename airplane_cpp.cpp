#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//The number of rows and columns in the seating chart.
const int ROWS = 13;
const int COLUMNS = 6;

//These are all the functions used in the program.
void initializeSeatPlan(char seatPlan[ROWS][COLUMNS], int row, int col);

void showSeatAssignments(char seatPlan[ROWS][COLUMNS], int row);

void assignSeat(char seatPlan[ROWS][COLUMNS], int row, int col, int count, int p);

void showSeatFirstClass(char seatPlan[ROWS][COLUMNS], int row);

void showSeatBusinessClass(char seatPlan[ROWS][COLUMNS], int row);

void showSeatEconomyClass(char seatPlan[ROWS][COLUMNS], int row);

bool isFirstClassFull(char seatPlan[ROWS][COLUMNS], int row, int col, int check);

bool isBusinessClassFull(char seatPlan[ROWS][COLUMNS], int check, int row, int col);

bool isEconomyClassFull(char seatPlan[ROWS][COLUMNS], int check, int row, int col);

int isPlaneFull(char seatPlan[ROWS][COLUMNS], int check, int row, int col, int p);

void undoReservedSeats(char seatPlan[ROWS][COLUMNS], int check, int again);

//This is the normal function. This initializes the matrix and displays the seats to the user. 
//Then, it asks the user if they would like to reserve a seat. Then, the user is prompted to enter their choice. 
//This location on the seating chart is changed from * to X to show which seats are taken. 
//The user can continue to add more seats until the plane is full. 
int main()
{
    char seatPlan[ROWS][COLUMNS];
    char resp;
    int checkFirst = 0;
    char undo = 'n';

    initializeSeatPlan(seatPlan, 0, 0);
    showSeatAssignments(seatPlan, 0);

    cout << "This plane holds 78 passengers. To reserve a seat, enter Y or y (yes), or enter N or n (no) if you do not want to reserve a seat: " << endl;
    cin >> resp;
    cout << endl;

    while (resp == 'y' || resp == 'Y')
    {
        //This will end the program if the seating arrangement is already full and explain why the program ended.
        checkFirst = isPlaneFull(seatPlan, 0, 0, 0, 1);
        if (checkFirst == 2)
        {
            cout << "The plane is booked. I apologize for any inconvenience." << endl;
            return 0;
        }

        assignSeat(seatPlan, 0, 0, 0, 1);
        showSeatAssignments(seatPlan, 0);
        
        //This next section allows a user to remove a seat they already reserved and no longer want.
        cout << "Enter y or Y to undo any reserved seats. Enter n or N if you are content with your selection." << endl;
        cin >> undo;
        cout << endl;
        //Turn into a function.
        while (undo == 'y' || undo == 'Y')
        {
            showSeatAssignments(seatPlan, 0);
            undoReservedSeats(seatPlan, 0, 0);

            cout << "Enter y or Y to undo more reserved seats. Enter n or N if you are content with your selection." << endl;
            cin >> undo;
            cout << endl;
        }

        cout << "To reserve more seats, enter Y or y (yes). If you are done reserving seats, enter N or n (no): ";
        cin >> resp;
        cout << endl;

        if (resp != 'y' && resp != 'Y')
        cout << "Thank you for booking your flight with us! Be sure to wear your mask on the plane. Enjoy your trip." << endl;
    }
    
    return 0;
}

//This initializes the matrix with * for each row and column.
void initializeSeatPlan(char seatPlan[ROWS][COLUMNS], int row, int col)
{
    for (row = 0; row < ROWS; row++)
    {
        for (col = 0; col < 6; col++)
        {
            seatPlan[row][col] = '*';
        }
    }
}
//This displays the actual matrix as desired in the seating plan output format. Rows are labeled as Row 1 through Row 13.
//Columns are labeled as A through F.
void showSeatAssignments(char seatPlan[ROWS][COLUMNS], int row)
{
    cout << setw(9) << 'A' << setw(3) << 'B' << setw(3) << 'C' << setw(3) << 'D' << setw(3) << 'E' << setw(3) << 'F' << endl;
    for (row = 0; row < ROWS; row++)
    {

        cout << left << setw(4) << "Row " << setw(2) << row + 1 << right << setw(3) << seatPlan[row][0] << setw(3) << seatPlan[row][1] << setw(3) << seatPlan[row][2] << setw(3) << seatPlan[row][3] << setw(3) << seatPlan[row][4] << setw(3) << seatPlan[row][5] << endl;

    }
    cout << endl;

}
//This allows the user to enter the ticket type and then assign seats (X) based on ticket type.
//It calls other functions when sections are full or when the whole plane is full.
void assignSeat(char seatPlan[ROWS][COLUMNS], int row, int col, int count, int p)
{
    string seatingClass = "0 A";
    int noOfSeats = 0;
    p = 1;
    char column = '\n';

    cout << "If you would like a seat in first class, enter \"first\". If you would like a seat in business class, enter \"business\". If you would like a seat in economy class, enter \"economy\"." << endl;
    cin >> seatingClass;
    cout << endl;

    while (p == 1)
    {
        if (seatingClass == "first")
        {
            p = isPlaneFull(seatPlan, 0, 0, 0, 1);
            if (p == 2)
            {
                cout << "The plane is booked. Try a different plane if you still need a flight. I apologize for any inconvenience." << endl;
                return;
            }

            p = isFirstClassFull(seatPlan, 0, 0, 0);
            if (p == 1)
            {
                cout << "Unfortunately, this class is full. You must choose another class. Your options are \"first\", \"business\", or \"economy\"." << endl;
                cin >> seatingClass;
                cout << endl; 
            }

        }
        else if (seatingClass == "business")
        {
            p = isPlaneFull(seatPlan, 0, 0, 0, 1);
            if (p == 2)
            {
                cout << "The plane is booked. Try a different plane if you still need a flight. I apologize for any inconvenience." << endl;
                return;
            }

            p = isBusinessClassFull(seatPlan, 0, 0, 0);
            if (p == 1)
            {
                cout << "Unfortunately, this class is full. You must choose another class. Your options are \"first\", \"business\", or \"economy\"." << endl;
                cin >> seatingClass;
                cout << endl;
            }

        }
        else if (seatingClass == "economy")
        {
            p = isPlaneFull(seatPlan, 0, 0, 0, 1);
            if (p == 2)
            {
                cout << "The plane is booked. Try a different plane if you still need a flight. I apologize for any inconvenience." << endl;
                return;
            }
            p = isEconomyClassFull(seatPlan, 0, 0, 0);
            if (p == 1)
            {
                cout << "Unfortunately, this class is full. You must choose another class. Your options are \"first\", \"business\", or \"economy\"." << endl;
                cin >> seatingClass;
                cout << endl;
            }            
        }
        else
        {
            cout << "Your response was invalid. Please type in a valid option. Your options are \"first\", \"business\", or \"economy\"." << endl;
            cin >> seatingClass;
            cout << endl;

            p = 1;
        }

    }


    cout << "The following chart shows the available seat based on the class you chose:" << endl << endl;


    //To display the chart with available seats for that class on the plane        
    if (seatingClass == "first")
    {
        showSeatFirstClass(seatPlan, 0);
    }
    else if (seatingClass == "business")
    {
        showSeatBusinessClass(seatPlan, 0);
    }
    else
    {
        showSeatEconomyClass(seatPlan, 0);
    }

    //Check the number of seats available in that class and either let the person continue 
    //or ask them to pick a new number of seats.

    int continueProgram = 0;
    int check = 0;
    while (continueProgram == 0)
    {
        check = 0;
        char response = 'y';
        noOfSeats = 0;

        while (noOfSeats < 1)
        {
            cout << "How many seats would you like to reserve in " << seatingClass << " class?" << endl;
            cin >> noOfSeats;
            cout << endl;

            cin.clear();
            cin.ignore(100, '\n');

            if (noOfSeats < 1)
            {
                cout << "You need to reserve 1 or more seats. If you would no longer like to reserve a seat, please enter n or N." << endl;
                cin >> response;
                cout << endl;

                if (response == 'n' || response == 'N')
                    return;
            }
        }
        //This whole next section checks to make sure the number of seats they want in the class are available to take.
        if (seatingClass == "first")
        {
            check = 0;

            for (row = 0; row < 2; row++)
            {
                for (col = 0; col < 6; col++)
                { 
                    if (seatPlan[row][col] == '*')
                        check = check + 1;
                }
            }
        }
        else if (seatingClass == "business")
        {
            check = 0;

            for (row = 2; row < 7; row++)
            {
                for (col = 0; col < 6; col++)
                {
                    if (seatPlan[row][col] == '*')
                        check = check + 1;
                }
            }
        }
        else if (seatingClass == "economy")
        {
            check = 0;

            for (row = 7; row < 13; row++)
            {
                for (col = 0; col < 6; col++)
                {
                    if (seatPlan[row][col] == '*')
                        check = check + 1;
                }
            }
        }
        
        if (noOfSeats > check)   
        {
            cout << "Only " << check << " seats are available in " << seatingClass << " class, so you cannot reserve ";
            cout << noOfSeats << " seats. Please enter a value of " << check << " or less." << endl;
            cout << endl;

            continueProgram = 0;
        }
        else
        {
            continueProgram = 1;
        }
    }

    //This section will automatically reserve the whole section if you would like the number of remaining available seats.
    if ((seatingClass == "first") && (noOfSeats == check))
    {
       for (row = 0; row < 2; row++)
        {
            for (col = 0; col < 6; col++)
            {
                seatPlan[row][col] = 'X';
            }
        }  
        return;        
    }
    else if ((seatingClass == "business") && (noOfSeats == check))
    {
        for (row = 2; row < 7; row++)
        {
            for (col = 0; col < 6; col++)
            {
                seatPlan[row][col] = 'X';
            }
        }
        return;
    }
    else if ((seatingClass == "economy") && (noOfSeats == check))
    {
        for (row = 7; row < 13; row++)
        {
            for (col = 0; col < 6; col++)
            {
                seatPlan[row][col] = 'X';
            }
        }
        return;
    }

    count = 0;

    do
    {
        row = 0;
        column = 0;
        if (seatingClass == "first")
        {
            cout << "Which seat would you like? Please enter your choice in the following format: row column. For example, 1 A and 2 D." << endl;
            cin >> row >> column;
        
            cin.clear();
            cin.ignore(100, '\n');
            cin.clear();
        }
        else if (seatingClass == "business")
        {
            cout << "Which seat would you like? Please enter your choice in the following format: row column. For example, 3 A and 4 E." << endl;
            cin >> row >> column;
        
            cin.clear();
            cin.ignore(100, '\n');
            cin.clear();
        }
        else if (seatingClass == "economy")
        {
            cout << "Which seat would you like? Please enter your choice in the following format: row column. For example, 8 A and 12 F." << endl;
            cin >> row >> column;
        
            cin.clear();
            cin.ignore(100, '\n');
            cin.clear();
        }
        
        //The following statements ensure the person is entering the right information for the class they chose.
        if (seatingClass == "first")
        {
           if (row > 0 && row < 3)
            {
                row = row - 1;
                column = static_cast<int>(column) - 65;
                if (column >= 0 && column < 6)
                {
                    //This if...else section determines if the seat they want is available and asks
                    //the user to pick a new seat if the seat is taken.
                    if (seatPlan[row][column] == '*')
                    {
                        seatPlan[row][column] = 'X';
                        count = count + 1;   

                        showSeatFirstClass(seatPlan, 0);
                    }
                    else
                    {
                        cout << "Your seat is already taken. Try again." << endl << endl;
                        count = 0;
                    }             
                }
                else
                {
                    cout << "Your response was invalid. Your seat was not reserved. Try again." << endl << endl;
                    count = 0;
                }        
            }
            else
            {
                cout << "Your response was invalid. Your seat was not reserved. Try again." << endl << endl;
                count = 0;
            } 
        }
        else if (seatingClass == "business")
        {
            if (row > 2 && row < 8)
            {                
                row = row - 1;
                column = static_cast<int>(column) - 65;
                if (column >= 0 && column < 6)
                {
                    //This if...else section determines if the seat they want is available and asks
                    //the user to pick a new seat if the seat is taken.
                    if (seatPlan[row][column] == '*')
                    {
                        seatPlan[row][column] = 'X';
                        count = count + 1;   
                        showSeatBusinessClass(seatPlan, 0);
                    }
                    else
                    {
                        cout << "Your seat is already taken. Try again." << endl << endl;
                        count = 0;
                    }              
                }
                else
                {
                    cout << "Your response was invalid. Your seat was not reserved. Try again." << endl << endl;
                    count = 0;
                }        
            }
            else
            {
                cout << "Your response was invalid. Your seat was not reserved. Try again." << endl << endl;
                count = 0;
            }
        }
        else if (seatingClass == "economy")
        {
            if (row > 7 && row < 14)
            {
                row = row - 1;
                column = static_cast<int>(column) - 65;
                if (column >= 0 && column < 6)
                {
                    //This if...else section determines if the seat they want is available and asks
                    //the user to pick a new seat if the seat is taken.
                    if (seatPlan[row][column] == '*')
                    {
                        seatPlan[row][column] = 'X';
                        count = count + 1;   
                        showSeatEconomyClass(seatPlan, 0);
                    }
                    else
                    {
                        cout << "Your seat is already taken. Try again." << endl << endl;
                        count = 0;
                    }                
                }
                else
                {
                    cout << "Your response was invalid. Your seat was not reserved. Try again." << endl << endl;
                    count = 0;
                }        
            }
            else
            {
                cout << "Your response was invalid. Your seat was not reserved. Try again." << endl << endl;
                count = 0;
            }
        }
        
    } while (count < noOfSeats);
}

//This shows the seats available and taken for first class.
void showSeatFirstClass(char seatPlan[ROWS][COLUMNS], int row)
{
    row = 0;
    cout << setw(9) << 'A' << setw(3) << 'B' << setw(3) << 'C' << setw(3) << 'D' << setw(3) << 'E' << setw(3) << 'F' << endl;
    for (row = 0; row < 2; row++)
    {

        cout << left << setw(4) << "Row " << setw(2) << row + 1 << right << setw(3) << seatPlan[row][0] << setw(3) << seatPlan[row][1] << setw(3) << seatPlan[row][2] << setw(3) << seatPlan[row][3] << setw(3) << seatPlan[row][4] << setw(3) << seatPlan[row][5] << endl;

    }
    cout << endl;
}

//This shows the seats available and taken for business class.
void showSeatBusinessClass(char seatPlan[ROWS][COLUMNS], int row)
{
    row = 0;

    cout << setw(9) << 'A' << setw(3) << 'B' << setw(3) << 'C' << setw(3) << 'D' << setw(3) << 'E' << setw(3) << 'F' << endl;
    for (row = 2; row < 7; row++)
    {

        cout << left << setw(4) << "Row " << setw(2) << row + 1 << right << setw(3) << seatPlan[row][0] << setw(3) << seatPlan[row][1] << setw(3) << seatPlan[row][2] << setw(3) << seatPlan[row][3] << setw(3) << seatPlan[row][4] << setw(3) << seatPlan[row][5] << endl;

    }
    cout << endl;
}
//this shows the seats available and taken for economy class.
void showSeatEconomyClass(char seatPlan[ROWS][COLUMNS], int row)
{
    row = 0;

    cout << setw(9) << 'A' << setw(3) << 'B' << setw(3) << 'C' << setw(3) << 'D' << setw(3) << 'E' << setw(3) << 'F' << endl;
    for (row = 7; row < ROWS; row++)
    {

        cout << left << setw(4) << "Row " << setw(2) << row + 1 << right << setw(3) << seatPlan[row][0] << setw(3) << seatPlan[row][1] << setw(3) << seatPlan[row][2] << setw(3) << seatPlan[row][3] << setw(3) << seatPlan[row][4] << setw(3) << seatPlan[row][5] << endl;

    }
    cout << endl;
}


//This determines if first class is full. A value of true means it is full.
bool isFirstClassFull(char seatPlan[ROWS][COLUMNS], int row, int col, int check)
{

    for (row = 0; row < 2; row++)
    {
        for (col = 0; col < 6; col++)
        {
            if (seatPlan[row][col] == 'X')
                check = check + 1;
            else
                check = 0;
        }
    }
    if (check == 12)
        return true;
    else
        return false;
}

//This determines if business class if full. A value of true means it is full.
bool isBusinessClassFull(char seatPlan[ROWS][COLUMNS], int check, int row, int col)
{
    for (row = 2; row < 7; row++)
    {
        for (col = 0; col < 6; col++)
        {
            if (seatPlan[row][col] == 'X')
                check = check + 1;
            else
                check = 0;
        }
    }
    if (check == 30)
        return true;
    else
        return false;
}

//This determines if economy class is full. A value of true means it is full.
bool isEconomyClassFull(char seatPlan[ROWS][COLUMNS], int check, int row, int col)
{
    for (row = 7; row < 13; row++)
    {
        for (col = 0; col < 6; col++)
        {
            if (seatPlan[row][col] == 'X')
                check = check + 1;
            else
                check = 0;
        }
    }
    if (check == 36)
        return true;
    else
        return false;
}

//This determines if the plane is full.
int isPlaneFull(char seatPlan[ROWS][COLUMNS], int check, int row, int col, int p)
{
    p = 1;

    for (row = 0; row < 13; row++)
    {
        for (col = 0; col < 6; col++)
        {
            if (seatPlan[row][col] == 'X')
                check = check + 1;
            else
                break;
        }
    }

    if (check == 78)
        p = 2;

    return p;
}

//This function removes a seat from the reservation. There are a few checks to make sure the person enters proper input.
void undoReservedSeats(char seatPlan[ROWS][COLUMNS], int check, int again)
{
    int noOfSeats = 0;
    char response = 'y';
    char column = 'A';
    int row = 0;
    int col = 0;
    int count;
    int undo;

    do
    {
        cout << "How many seats would you like to undo?" << endl;
        cin >> noOfSeats;
        cout << endl;
        
        again = 0;

        if (noOfSeats < 1)
        {
            cout << "You need to undo 1 or more seats. If you would like to keep your seats, please enter n or N.";
            cout << " If you would like to undo 1 or more seats, please enter y or Y." << endl;
            cin >> response;
            cout << endl;

            if (response == 'n' || response == 'N')
                return;
            else
                again = 1;
        }

        check = 0;

        for (row = 0; row < 13; row++)
        {
            for (col = 0; col < 6; col++)
            {    
                if (seatPlan[row][col] == 'X')
                    check = check + 1;
            }
                
        }
        if (noOfSeats > check)   
        {
            cout << "You only reserved " << check << " seats, so you cannot undo ";
            cout << noOfSeats << " seats. Please enter a value of " << check << " or less." << endl;
            cout << endl;

            count = 0;
            undo = 'y';
            again = 1;
        }
    } while (again == 1);
        
    count = 0;

    while (noOfSeats > count)
    {
        cout << "Which seat would you like to undo? Please enter your choice in the following format: row ";
        cout << "column. For example, 1 A or 10 B." << endl;
        cin >> row >> column;
        
        cin.clear();
        cin.ignore(100, '\n');
        cin.clear();
        
        if (row > 0 && row < 14)
        {
            row = row - 1;
            column = static_cast<int>(column) - 65;
            if (column >= 0 && column < 6)
            {
                //This if...else section determines if the seat they want is available and asks
                //the user to pick a new seat if the seat is taken.
                if (seatPlan[row][column] == 'X')
                {
                    seatPlan[row][column] = '*';
                    count = count + 1;   

                    showSeatAssignments(seatPlan, 0);
                }
                else
                {
                    cout << "You did not yet reserve this seat. Try again." << endl << endl;
                }             
            }
            else
            {
                cout << "Your response was invalid. You did not undo a seat in your reservation. Try again." << endl << endl;
            }        
        }            
        else
        {
            cout << "Your response was invalid. You did not undo a seat in your reservation. Try again." << endl << endl;
        }       
    }
}
