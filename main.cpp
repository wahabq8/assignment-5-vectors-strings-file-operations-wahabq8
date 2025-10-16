#include <iostream>
#include <cstdlib>
#include <cmath>
#include <iomanip>

#include "coordinate.h"

// Function Prototypes
void add_coordinate(Coordinate*& head, Coordinate*& tail, float x, float y);
void forward_display(Coordinate* list_beginning);
void backward_display(Coordinate* list_end);
void delete_coordinate(Coordinate*& head, Coordinate*& tail, int coord_id_to_delete);
int list_length(Coordinate* list_beginning);
void closest_to(Coordinate* list_beginning, float x, float y);

int main(int argc, char *argv[]) {
    
    int num_coords = atoi(argv[1]);
    if (num_coords <= 0) {
        std::cerr << "Please enter a positive number of coordinates." << std::endl;
        return 1;
    }

    Coordinate *head = nullptr;
    Coordinate *tail = nullptr;

    std::cout << "Adding " << num_coords << " coordinates:" << std::endl;
    for (int i = 0; i < num_coords; ++i) {
        float rand_x = static_cast<float>(rand()) / RAND_MAX * 100.0f;
        float rand_y = static_cast<float>(rand()) / RAND_MAX * 100.0f;
        add_coordinate(head, tail, rand_x, rand_y);
    }
    std::cout << std::endl;
    
    std::cout << "List forward:" << std::endl;
    forward_display(head);
    std::cout << std::endl;

    std::cout << "List backward:" << std::endl;
    backward_display(tail);
    std::cout << std::endl;

    std::cout << "Current list length:" << std::endl;
    std::cout << "Length: " << list_length(head) << std::endl;
    std::cout << std::endl;

    int id_to_delete = 3;
    if (num_coords >= id_to_delete) {
        std::cout << "Deleting coordinate with ID " << id_to_delete << std::endl;
        delete_coordinate(head, tail, id_to_delete);
        std::cout << "List after deletion:" << std::endl;
        forward_display(head);
        std::cout << std::endl;
    }

    float test_x = 50.0f;
    float test_y = 50.0f;
    std::cout << "Finding coordinate closest to (" << test_x << ", " << test_y << "):" << std::endl;
    closest_to(head, test_x, test_y);
    std::cout << std::endl;

    Coordinate* current = head;
    while(current != nullptr) {
        Coordinate* node_to_delete = current;
        current = current->next;
        delete node_to_delete;
    }
    head = nullptr;

    return 0;
}


// Function implement

void add_coordinate(Coordinate*& head, Coordinate*& tail, float x, float y) {
    Coordinate *new_node = new Coordinate;
    new_node -> x = x;
    new_node -> y = y;
    new_node -> next = nullptr;
    
    static int current_id = 1;
    new_node -> coord_id = current_id++;

    if (head == nullptr) {
        new_node -> previous = nullptr;
        head = new_node;
        tail = new_node;
    } else {
        tail -> next = new_node;
        new_node -> previous = tail;
        tail = new_node;
    }
}

void forward_display(Coordinate *list_beginning) {
    Coordinate *current = list_beginning;
    while (current != nullptr) {
        std::cout << "ID: " << current->coord_id 
                  << "\t(x, y) = (" << std::fixed << current->x 
                  << ", " << current->y << ")" << std::endl;
        current = current->next;
    }
}

void backward_display(Coordinate *list_end) {
    Coordinate *current = list_end;
    while (current != nullptr) {
        std::cout << "ID: " << current->coord_id 
                  << "\t(x, y) = (" << std::fixed << current->x 
                  << ", " << current->y << ")" << std::endl;
        current = current->previous;
    }
}

void delete_coordinate(Coordinate*& head, Coordinate*& tail, int coord_id_to_delete) {
    Coordinate* current = head;
    while (current != nullptr && current->coord_id != coord_id_to_delete) {
        current = current->next;
    }
    if (current == nullptr) { 
        std::cout << "Coordinate " << coord_id_to_delete << " not found." << std::endl;
        return;
    }
    if (current == head) { 
        head = current->next;
    } else { 
        current->previous->next = current->next;
    }
    if (current == tail) { 
        tail = current->previous;
    } else { 
        current->next->previous = current->previous;
    }
    delete current;
    std::cout << "Deleted coordinate ID " << coord_id_to_delete << "." << std::endl;
}

int list_length(Coordinate *list_beginning) {
    int count = 0;
    Coordinate *current = list_beginning;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

void closest_to(Coordinate *list_beginning, float x, float y) {
    if (list_beginning == nullptr) {
        std::cout << "List is empty." << std::endl;
        return;
    }

    Coordinate* closest_node = nullptr;
    float min_distance_sq = -1.0f;

    Coordinate* current = list_beginning;
    while (current != nullptr) {
        float dx = current->x - x;
        float dy = current->y - y;
        float distance_sq = dx * dx + dy * dy;

        if (closest_node == nullptr || distance_sq < min_distance_sq) {
            min_distance_sq = distance_sq;
            closest_node = current;
        }
        current = current->next;
    }
    float min_distance = sqrt(min_distance_sq);

    std::cout << "The closest point is ID " << closest_node->coord_id 
              << " at (" << std::fixed << closest_node->x << ", " << closest_node->y << ")." << std::endl;
    std::cout << "Distance: " << min_distance << std::endl;
}
