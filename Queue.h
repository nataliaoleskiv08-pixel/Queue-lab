#pragma once

class Queue {
private:
    struct Node {
        double data;
        Node* next;
        Node(double val) : data(val), next(nullptr) {}
    };

    Node* frontNode;
    Node* rearNode;
    int count;

public:
    Queue() : frontNode(nullptr), rearNode(nullptr), count(0) {}

    ~Queue() {
        while (!isEmpty()) {
            pop();
        }
    }

    bool isEmpty() const {
        return frontNode == nullptr;
    }

    // Додавання елемента з перевіркою на унікальність
    bool pushUnique(double val) {
        if (contains(val)) return false;
        Node* newNode = new Node(val);
        if (isEmpty()) {
            frontNode = rearNode = newNode;
        }
        else {
            rearNode->next = newNode;
            rearNode = newNode;
        }
        count++;
        return true;
    }

    double pop() {
        if (isEmpty()) return 0.0;
        Node* temp = frontNode;
        double val = temp->data;
        frontNode = frontNode->next;
        if (frontNode == nullptr) {
            rearNode = nullptr;
        }
        delete temp;
        count--;
        return val;
    }

    int getCount() const { return count; }

    bool contains(double val) const {
        Node* current = frontNode;
        while (current != nullptr) {
            if (current->data == val) return true;
            current = current->next;
        }
        return false;
    }

    // Отримання елемента за індексом (0-based)
    bool getAt(int index, double& val) const {
        if (index < 0 || index >= count) return false;
        Node* current = frontNode;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        val = current->data;
        return true;
    }

    // Пошук мінімального та максимального елементів
    bool getMinMax(double& minVal, double& maxVal) const {
        if (isEmpty()) return false;
        minVal = frontNode->data;
        maxVal = frontNode->data;
        Node* current = frontNode->next;
        while (current != nullptr) {
            if (current->data < minVal) minVal = current->data;
            if (current->data > maxVal) maxVal = current->data;
            current = current->next;
        }
        return true;
    }

    // Елемент перед мінімальним та після максимального
    bool getNeighbors(double& beforeMin, double& afterMax, bool& hasBeforeMin, bool& hasAfterMax) const {
        if (count < 1) return false;
        double minVal, maxVal;
        getMinMax(minVal, maxVal);

        hasBeforeMin = false;
        hasAfterMax = false;

        Node* current = frontNode;
        Node* prev = nullptr;

        while (current != nullptr) {
            if (current->data == minVal && prev != nullptr) {
                beforeMin = prev->data;
                hasBeforeMin = true;
            }
            if (prev != nullptr && prev->data == maxVal) {
                afterMax = current->data;
                hasAfterMax = true;
            }
            prev = current;
            current = current->next;
        }
        return true;
    }

    // Позиція елемента (1-based)
    int findPosition(double val) const {
        Node* current = frontNode;
        int pos = 1;
        while (current != nullptr) {
            if (current->data == val) return pos;
            current = current->next;
            pos++;
        }
        return -1;
    }

    // Об'єднання двох черг у нову структуру (без повторів)
    static Queue* merge(const Queue& q1, const Queue& q2) {
        Queue* merged = new Queue();
        Node* curr = q1.frontNode;
        while (curr != nullptr) {
            merged->pushUnique(curr->data);
            curr = curr->next;
        }
        curr = q2.frontNode;
        while (curr != nullptr) {
            merged->pushUnique(curr->data);
            curr = curr->next;
        }
        return merged;
    }

    // Прямий доступ до елемента за індексом для виведення
    double getElementAtDirect(int index) const {
        Node* current = frontNode;
        for (int i = 0; i < index && current != nullptr; i++) {
            current = current->next;
        }
        return current ? current->data : 0.0;
    }
};