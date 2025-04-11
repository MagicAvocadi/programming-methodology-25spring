#include "todo.h"
#include <stdexcept>

void TodoList::init() {
    size = 0;
    for (int i = 0; i < MAX_TASKS; i++) {
        tasks[i] = nullptr;
    }
}

void TodoList::destroy() {
    for (int i = 0; i < size; i++) {
        delete[] tasks[i];
        tasks[i] = nullptr;
    }
    size = 0;
}

int TodoList::string_length(const char* str) const {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

void TodoList::string_copy(char* dest, const char* src) const {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

void TodoList::add_task(const char* task) {
    if (size >= MAX_TASKS) {
        throw std::runtime_error("TodoList is full");
    }

    int length = string_length(task);
    tasks[size] = new char[length + 1];
    string_copy(tasks[size], task);
    size++;
}

void TodoList::remove_task(int index) {
    if (index < 0 || index >= size) {
        throw std::runtime_error("Invalid task index");
    }

    delete[] tasks[index];
    
    // Shift remaining tasks left
    for (int i = index; i < size - 1; i++) {
        tasks[i] = tasks[i + 1];
    }
    
    tasks[size - 1] = nullptr;
    size--;
}

const char** TodoList::get_pending_tasks(int& count) const {
    count = size;
    return const_cast<const char**>(tasks);
}