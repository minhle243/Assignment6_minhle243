#include "coordinate.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

// returns a random float from 0.00 to 99.99
float random_float()
{
    return (rand() % 10000) / 100.0;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <number_of_coordinates>" << std::endl;
        return 1;
    }

    int count = std::atoi(argv[1]);
    if (count <= 0)
    {
        std::cerr << "Number of coordinates must be a positive number" << std::endl;
        return 1;
    }
    srand(time(NULL)); // seed so we get different numbers each time we run

    // making the first node
    Coordinate *list_beginning = new Coordinate;
    list_beginning->x = random_float();
    list_beginning->y = random_float();
    list_beginning->coord_id = 1;
    list_beginning->next = NULL;
    list_beginning->previous = NULL;

    Coordinate *list_end = list_beginning;

    // add the rest of the coordinates
    for (int i = 1; i < count; i++)
    {
        add_coordinate(list_end, random_float(), random_float());
        list_end = list_end->next;
    }
    std::cout << "List length: " << list_length(list_beginning) << std::endl;
    forward_display(list_beginning);
    backward_display(list_end);

    std::cout << std::endl;
    closest_to(list_beginning, 50.0, 50.0);

    // I start with ID = 3 because it is usually in the middle of the list
    int id_to_delete = 3;
    if (count < 3) // if there are less than 3 coordinates => no ID 3, delete 1 instead
    {
        id_to_delete = 1;
    }
    std::cout << std::endl;
    delete_coordinate(list_beginning, id_to_delete);

    // the deleted node might have been the last one, so find the end again
    list_end = list_beginning;
    while (list_end->next != NULL) // keep going until there is no next node
    {
        list_end = list_end->next;
    }

    // show the list after deleting
    std::cout << "List length after the deletion: " << list_length(list_beginning) << std::endl;
    forward_display(list_beginning);
    backward_display(list_end);

    // free memory
    Coordinate *current = list_beginning;
    while (current != NULL)
    {
        Coordinate *nextnode = current->next;
        delete current;
        current = nextnode;
    }
    return 0;
}
