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

size_t DoublyLinkedList::get_size(void) const{
    return size;
}

int DoublyLinkedList::get_component(size_t index) const {

    if (index >= size) {
        std::cout << "\nIndex is out of range.\n";
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

bool DoublyLinkedList::search(int value) {
	// same as in get_component, we can start from the end of the list that is closer to the middle of the list (to avoid unnecessary iterations)
    // and move towards the middle until we "collide" (to ensure they will the size must be odd)
    Node* current = head;
    Node* current_end = tail;

    // if the size is even, we skip 1 step (we check if we didn't pass our value) and act as we have size-- therefore odd
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


//int* DoublyLinkedList::searchAll(int value, int& count) {
//        Node* left = this->head;
//        Node* right = this->tail;
//
//        int leftIndex = 0;
//        int rightIndex = get_size() - 1;
//
//        while (left != nullptr && right != nullptr && leftIndex <= rightIndex) {
//
//            // check left side
//            if (left->data == value) {
//                std::cout << "Found at index: " << leftIndex << std::endl;
//            }
//
//            // check right side (avoid duplicate if same node)
//            if (right != left && right->data == value) {
//                std::cout << "Found at index: " << rightIndex << std::endl;
//            }
//
//            left = left->next;
//            right = right->prev;
//
//            leftIndex++;
//            rightIndex--;
//        }
// } 


void DoublyLinkedList::push_back(int value) {

    Node* newNode = new Node(value);

	//if the dll is empty, the new node becomes both head and tail
    //newly added node should point to old tail

    if (!head) {
        head = tail = newNode;
    }
    else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }

    size++;
}

void DoublyLinkedList::push_front(int value) {

    Node* newNode = new Node(value);

    //if the dll is empty, the new node becomes both head and tail
    //newly added node should point to old head

    if (!head) {
        head = tail = newNode;
    }
    else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    size++;
}

void DoublyLinkedList::push_at(int value, size_t index) {

    //we check if the index is the beginning or the end of the list, if so we can call push_front or push_back respectively, 
    //otherwise we need to insert the node in the middle of the list
    //we check if the index is valid, if not we throw an exception
        if (index == 0) {
            push_front(value);
            return;
        }
        if (index == size) {
            push_back(value);
            return;
        }
        if (index > size)
        {
            std::cout << "\nIndex is out of range.\n";
            return;
        }

        Node* current = head;
        for (size_t i = 0; i < index; i++)
            current = current->next;

        Node* newNode = new Node(value);

        newNode->prev = current->prev;
        newNode->next = current;

        current->prev->next = newNode;
        current->prev = newNode;

        size++;
}

int DoublyLinkedList::pop_at(size_t index) {
    if (index >= size) {
        std::cout << "\nThere is nothing to remove.\n";
        return 0;
    }
    if (index == 0) {
        pop_front();
        return 0;
    }
    if (index == size - 1) {
        pop_back();
        return 0;
    }
    Node* temp = head;
    for (size_t i = 0; i < index; i++) {
        temp = temp->next;
    }
    temp->prev->next = temp->next; // Node before temp now points at Node after temp
    temp->next->prev = temp->prev; // Node after temp now points at Node before temp
    delete temp;
    size--;
    return 0;
}

int DoublyLinkedList::pop_front() {
    if (!head)
    {
        std::cout << "\nThere is nothing to remove.\n";
        return 0;
    }

    Node* temp = head;
    int value = temp->data;

    head = head->next; // head is passed to the next Node
    if (head)
        head->prev = nullptr; // Node after old head now points at nothing instead of the old head
    else
        tail = nullptr;

    delete temp;
    size--;
    return value;
}

int DoublyLinkedList::pop_back() {
    if (!tail)
    {
        std::cout << "\nThere is nothing to remove.\n";
        return 0;
    }

    Node* temp = tail;
    int value = temp->data;

    tail = tail->prev; // tail is passed to the prior Node
    if (tail)
        tail->next = nullptr; // Node before old tail now points at nothing instead of the old tail
    else
        head = nullptr;
   
   
    delete temp;
    size--;
    return value;
}





