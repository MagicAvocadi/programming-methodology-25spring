#include <gtest/gtest.h>
#include "todo.h"

TEST(TodoListTest, AddSingleTask) {
    TodoList todo;
    todo.init();
    todo.add_task("Write code");

    int count;
    const char** tasks = todo.get_pending_tasks(count);

    ASSERT_EQ(count, 1);
    EXPECT_STREQ(tasks[0], "Write code");

    todo.destroy();
}

TEST(TodoListTest, AddMultipleTasks) {
    TodoList todo;
    todo.init();
    todo.add_task("A");
    todo.add_task("B");
    todo.add_task("C");

    int count;
    const char** tasks = todo.get_pending_tasks(count);
    ASSERT_EQ(count, 3);
    EXPECT_STREQ(tasks[0], "A");
    EXPECT_STREQ(tasks[1], "B");
    EXPECT_STREQ(tasks[2], "C");

    todo.destroy();
}

TEST(TodoListTest, RemoveTask) {
    TodoList todo;
    todo.init();
    todo.add_task("A");
    todo.add_task("B");
    todo.add_task("C");

    todo.remove_task(1);  // Remove "B"

    int count;
    const char** tasks = todo.get_pending_tasks(count);
    ASSERT_EQ(count, 2);
    EXPECT_STREQ(tasks[0], "A");
    EXPECT_STREQ(tasks[1], "C");

    todo.destroy();
}

TEST(TodoListTest, RemoveInvalidIndexThrows) {
    TodoList todo;
    todo.init();
    todo.add_task("Sample Task");

    // Test negative index
    EXPECT_THROW(todo.remove_task(-1), std::runtime_error);
    
    // Test out-of-bounds index
    EXPECT_THROW(todo.remove_task(1), std::runtime_error);
    
    // Test empty list
    todo.remove_task(0);
    EXPECT_THROW(todo.remove_task(0), std::runtime_error);

    todo.destroy();
}

TEST(TodoListTest, AddTooManyTasksThrows) {
    TodoList todo;
    todo.init();

    // Add exactly 32 tasks
    for (int i = 0; i < 32; i++) {
        char task[10];
        sprintf(task, "Task %d", i);
        todo.add_task(task);
    }

    // Try adding a 33rd task
    EXPECT_THROW(todo.add_task("Extra Task"), std::runtime_error);

    todo.destroy();
}