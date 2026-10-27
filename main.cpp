#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <random>
#include <cmath>
#include "Coordinate.h"

void add_coordinate(Coordinate *&list_end, float x, float y)  //add_coordinate: add's a coordinate to the end of the linked list
{
    Coordinate *new_node = new Coordinate;  //create a new node in memory for struct Coordinate
    new_node -> x = x;  //assign float x value to the new_node location struct x location
    new_node -> y = y;  //assign float y value to the new_node location struct y location
    new_node -> next = nullptr;  //assign nullptr to indicate no follow on address assignment
    if (list_end == nullptr)  //checks if list_end equals nullptr, which indicates initial struct node
    {
        new_node -> previous = nullptr;  //assigns previous struct location no address, since this is the first node
        new_node -> coord_id = 1;  //assigns coord_id 1 as the first instance
        list_end = new_node;  //assign new_node struct info to list_end
    }
    else  //else, list_end does not equals nullptr, which indicates not initial struct node
    {
        list_end -> next = new_node;  //assign new node value to the struct next location
        new_node -> previous = list_end;  //assigns previous struct location no address, since this is the first node
        new_node -> coord_id = list_end -> coord_id + 1;  //assigns coord_id 1 as the first instance
        list_end = new_node;  //assign new_node struct info to list_end
    }     
}

void forward_display(Coordinate *list_beginning)  //forward_display: displays all coordinates from beginning to end
{
    Coordinate *next_node = list_beginning;  //assign list_beginning address as next_node
    std::cout << "Forward Display Order" << std::endl;  //lists the direction of listing
    while (next_node != nullptr)  //loops while next_node is not nullptr
    {
        std::cout << "Struct ID: " << next_node -> coord_id << ", X: " << next_node -> x <<  ", Y: " << next_node -> y << std::endl;  //display each value of x and y in original order
        next_node = next_node -> next;  // sets current next_node to the next...next_node
    }
}

void backward_display(Coordinate *list_end)  //backwards_display: displays all coordinates from end to beginning
{
    Coordinate *previous_node = list_end;  //assign list_beginning address as previous_node
    std::cout << "\nReverse Display Order" << std::endl;  //lists the direction of listing
    while (previous_node != nullptr)  //loops while previous_node is not nullptr
    {        
        std::cout << "Struct ID: " << previous_node -> coord_id << ", X: " << previous_node -> x <<  ", Y: " << previous_node -> y << std::endl;  //display each value of x and y in reverse order
        previous_node = previous_node -> previous;  // sets current previous_node to the previous...previous_node
    }
}

void delete_coordinate(Coordinate *list_beginning, int coord_id_to_delete)  //delete_coordinate: removes a coordinate from the linked list (free memory!)
{
    Coordinate *next_node = list_beginning;  //assign list_beginning address as next_node
    for (int i = 0; i < coord_id_to_delete; i++)  //loop through nodes to get to node seleted for deletion 
    {
        next_node = next_node -> next;  //set next_node to next address
    }
    (next_node -> next) -> previous = next_node -> previous;  //provides the next struct with the address to the previous struct
    (next_node -> previous) -> next = next_node -> next;  //provides the previous struct with the address to the next struct
    delete next_node;  //deletes struct from the list of coordinates
}

int list_length(Coordinate *list_beginning)  //list_length: return the length of the list
{
    Coordinate *next_node = list_beginning;  //assign list_beginning address as next_node
    int count = 0;  //initialize struct counter to zero
    while (next_node != nullptr)  //loops while next_node is not nullptr
    {
        count = count + 1;  //increment struct count
        next_node = next_node -> next;  //sets current next_node to the next...next_node
    }
    std::cout << "\nThe number of the structs in the list is: " << count << "\n" << std::endl;  //display each value of x and y in original order
    return count;  //return the length of the structs list
}

void closest_to(Coordinate *list_beginning, float x, float y)  //closest_to: find the coordinate that is closest to the given x, y and output the distance between the 2
{
    float minDist = 100000.0; //set initial min distance to a large number
    float xMin = 0; //initialize xMin to 0
    float yMin = 0;  //initialize xMin to 0  
    Coordinate *next_node = list_beginning;  //assign list_beginning address as next_node
    while (next_node != nullptr)  //loops while next_node is not nullptr
    {
        float dx = next_node->x - x;  //finds the x delta
        float dy = next_node->y - y;  //finds the y delta
        float dist = sqrt((dx * dx) + (dy * dy));  //calculate sqrt(dx^2 + dy^2)
        if (dist < minDist)  //check to see if the current distance is less thant the previous minimum distance
        {
            minDist = dist;  //sets minimum distance to the current distance calculation
            xMin = next_node -> x;  //sets new minimum x value to the next node x value
            yMin = next_node -> y;  //sets new minimum y value to the next node y value              
        }
        next_node = next_node -> next;  //select the address of the next node in the chain
    }
    std::cout << "Smallest distance between x/y values is: " << minDist << " from x coordinate " << xMin << " and y coordinate " << yMin << "\n" << std::endl;  //display the smallest distance with corresponding x and y values
}

int main(int argc, char *argv[])  //main function intaking user input via argc and argv
{
    std::cout << "\n\n" << std::endl;  //printing spaces
    if (argc < 2) //checks to see if user entered a value.  If not aborts...
    {
        std::cout << "No no random number generator value entered by user.\n\nThis task is aborted!\n\n" << std::endl;  //Notifies the user that there was no number entered for the random number generator
        return 1;  //return 1 to exit the program execution
    }
    int rndNums = atoi(argv[1]); //gathers the size of the array provided by user
     if (rndNums <= 0)  //checks to see if user entered number greater than 0.  If not, aborts...
    {
        std::cout << "Value entered by user must be > zero to complete calculations.\n\nThis task is aborted!\n\n" << std::endl;  //Notifies the user that the number provided is not greater than 0
        return 1;  //return 1 to exit the program execution
    }
    std::random_device rd;  //locates random_device from the library
    std::mt19937 generator(rd());  //establishes the random generator function
    std::uniform_real_distribution<float> distribution(1.0,100.0);  //forces the list of randomly generated number to fall between 1 and 100
    Coordinate* list_beginning = nullptr;  //initialize list_beginning to nullptr
    Coordinate* list_end = nullptr;  //initialize list_end to nullptr
    for (int i = 0; i < rndNums; i++)  //for loop for the size provided by the user for the length of random numbers generated
    {
        float rand_x = distribution(generator);  //generates random x values the length of the user provided number
        float rand_y = distribution(generator);  //generates random y values the length of the user provided number
        add_coordinate(list_end, rand_x, rand_y);  //call add_coordinate function: add's a coordinate to the end of the linked list
        if (list_beginning == nullptr)  //check to see if list_beginning currently equals nullptr
        {
            list_beginning = list_end;  //initial assignmnet to the beginning of list_beginning after first list_end value is assigned
        }
    }
    forward_display(list_beginning);  //call forward_display function: displays all coordinates from beginning to end
    backward_display(list_end);  //call backwards_display function: displays all coordinates from end to beginning
    int coord_id_to_delete = 3;  //assign an x/y value to delete from the chain
    delete_coordinate(list_beginning, coord_id_to_delete);  //call delete_coordinate function: removes a coordinate from the linked list (free memory!)
    int listLength = list_length(list_beginning);  //call list_length function: return the length of the list
    float x = 100.0;  //assign an x value to pass into closest_to function
    float y = 100.0;  //assign an x value to pass into closest_to function
    closest_to(list_beginning, x, y);  //call closest_to function: find the coordinate that is closest to the given x, y and output the distance between the 2
    Coordinate *currentList = list_beginning;  //start at the beginning of the list
    while (currentList != nullptr)             //loop until there are no more nodes
    {
        Coordinate *next_node = currentList->next; //save the next node's address
        delete currentList;                        //delete the current node
        currentList = next_node;                   //move to next address
    }
    return 0;  //return zero to exit main function
}
