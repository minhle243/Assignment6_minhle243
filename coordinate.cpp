#include "coordinate.h"
#include <iostream>
#include <cmath>

// counts how many nodes are in the list
int list_length(Coordinate *list_beginning) {
    int length = 0;
    Coordinate *current = list_beginning;

    while (current != nullptr) {
        length++;
        current = current->next;
    }
    return length;
}

// adds a new coordinate to the end of the list
void add_coordinate(Coordinate *list_end, float x, float y) {
    if (list_end == nullptr) return;

    Coordinate *new_node = new Coordinate;
    new_node->x = x;
    new_node->y = y;
    new_node->next = nullptr;
    new_node->previous = list_end;

    // back to beginning so we can count the list
    Coordinate *head = list_end;
    while (head->previous != nullptr) {
        head = head->previous;
    }

    //add 1 to get the next id to link the new node
    new_node->coord_id = list_length(head) + 1;

    list_end->next = new_node;
}

// prints the list from beginning to end
void forward_display(Coordinate *list_beginning) {
    Coordinate *current = list_beginning;
    std::cout << "\n| Forward Display \n";
    while (current != nullptr) {
        std::cout << "ID: " << current->coord_id
                  << " | (" << current->x << ", " << current->y << ")\n";
        current = current->next;
    }
}

// prints the list from end to beginning
void backward_display(Coordinate *list_end) {
    Coordinate *current = list_end;
    std::cout << "\n| Backward Display \n";
    while (current != nullptr) {
        std::cout << "ID: " << current->coord_id
                  << " | (" << current->x << ", " << current->y << ")\n";
        current = current->previous;
    }
}

// removes the coordinate with the matching id and frees its memory
void delete_coordinate(Coordinate *list_beginning, int coord_id_to_delete) {
    Coordinate *current = list_beginning;

    while (current != nullptr) {
        if (current->coord_id == coord_id_to_delete) {

            // special case: deleting the first node
            // main's pointer can't change so I copy node 2 into node 1
            
            if (current == list_beginning) {
                Coordinate *second = current->next;
                if (second == nullptr) {
                    std::cout << "\nCan't delete the only coordinate in the list.\n";
                    return;
                }
                current->x = second->x;
                current->y = second->y;
                current->coord_id = second->coord_id;
                current->next = second->next;
                if (second->next != nullptr) {
                    second->next->previous = current;
                }
                delete second;
                std::cout << "\nDeleted coordinate ID: " << coord_id_to_delete << "\n";
                return;
            }

            
            current->previous->next = current->next;
            if (current->next != nullptr) {
                current->next->previous = current->previous;
            }

            // clean up memory
            delete current;
            std::cout << "\nDeleted coordinate ID: " << coord_id_to_delete << "\n";
            return;
        }
        current = current->next;
    }
    std::cout << "\nCoordinate ID " << coord_id_to_delete << " not found.\n";
}

// finds the coordinate closest to (x, y)
void closest_to(Coordinate *list_beginning, float x, float y) {
    if (list_beginning == nullptr) return;

    Coordinate *current = list_beginning;
    Coordinate *closest = nullptr;
    float min_distance = -1.0; // -1 means "nothing found yet"

    while (current != nullptr) {
        // distance formula
        float distance = std::sqrt(std::pow(current->x - x, 2) + std::pow(current->y - y, 2));

        if (min_distance < 0 || distance < min_distance) {
            min_distance = distance;
            closest = current;
        }
        current = current->next;
    }

    if (closest != nullptr) {
        std::cout << "\nThe closest point to (" << x << ", " << y << ") is ID "
                  << closest->coord_id << " at (" << closest->x << ", " << closest->y
                  << ") with a distance of " << min_distance << "\n";
    }
}
