#include "Doubly_Linked_List.h"

//definitions of functions declared in Doubly_Linked_List.h

//constuction of the list
DoublyLinkedList::DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

//destruction of the list, we need to free memory for each Node in the List, otherwise we would have a memory leak
DoublyLinkedList::~DoublyLinkedList() {
    Node* current = head;
    while (current) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
}

void DoublyLinkedList::print_array(void){
    Node* temp = head;

    while (temp != nullptr) {
        std::cout << temp->data << " ";
        temp = temp->next;
    }

    std::cout << std::endl;
}

void DoublyLinkedList::get_size(void) const{
    return size;
}

void DoublyLinkedList::get_component(size_t index) {

    if (index >= size) {
        std::cout << "\nIndex=" << index << " is out of bounds.\n";
        return 0;
    }
    

    //to avoid unnecessary iterations we can start from the end of the list that is closer to the index we want to get
    Node* temp;
    if(index >= size/2) {
        temp = tail;
        for(size_t i = size - 1; i > index; i--) {
            temp = temp->prev;
        }
    }
    else {
        temp = head;
        for(size_t i = 0; i < index; i++) {
            temp = temp->next;
        }
    }
    return temp->data;
}

void DoublyLinkedList::search(int value) {
    // 2 "pointers" at both ends of the array moving towards the middle until they "collide" (to ensure they will the size must be odd)
    Node* current = head;
    Node* current_end = tail;
    // if the size is even, we skip 1 step (of course we check if we didn't pass our value) and act as we have size-- therefore odd
    if (size % 2 == 0 && size) {
        if (current->data == value) {
            return true;
        }

        current = current->next;
    }

    if (size == 1) {
        if (current->data == value) {
            return true;
        }

        return false;
    }

    while (current != tail) {
        if (current->data == value) {
            return true;
        }

        else if (current_end->data == value) {
            return true;
        }

        current = current->next;
        current_end = current_end->prev;
    }

}


void DoublyLinkedList::searchAll(int value) {
        Node* left = this->head;
        Node* right = this->tail;

        int leftIndex = 0;
        int rightIndex = getSize() - 1;

        while (left != nullptr && right != nullptr && leftIndex <= rightIndex) {

            // Check left side
            if (left->data == value) {
                std::cout << "Found at index: " << leftIndex << std::endl;
            }

            // Check right side (avoid duplicate if same node)
            if (right != left && right->data == value) {
                std::cout << "Found at index: " << rightIndex << std::endl;
            }

            left = left->next;
            right = right->prev;

            leftIndex++;
            rightIndex--;
        }
 } 



