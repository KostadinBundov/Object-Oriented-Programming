#pragma once
#include "Task.h"

class TaskCollection
{
private:
	Task** data = nullptr;
	size_t size = 0;
	size_t actualSize = 0;
	size_t capacity = 0;

	void resize(size_t newCapacity);
	
	void copyFrom(const TaskCollection& other);
	void moveFrom(TaskCollection&& other);
	void free();

	int getIndexToInsert(Task* newTask) const;
	void shiftElementsBeforeAdding(size_t index);
	void shiftElementsAfterFinishingTask(size_t index);
	int getIndexToSetCompletedTask() const;

	int fundTaskById(int id) const;
public:
	TaskCollection();

	TaskCollection(const TaskCollection& other);
	TaskCollection(TaskCollection&& other);

	TaskCollection& operator=(const TaskCollection& other);
	TaskCollection& operator=(TaskCollection&& other);

	~TaskCollection();

	void add(Task* task);
	void add(const Task& task);

	void printUpcomingTasks() const;
	void printCompletedTasks() const;

	void executeTask();
	Task* seeNextTask() const;

	void changePriority(int id, int newPriority);
};