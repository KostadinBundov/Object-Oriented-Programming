#include "TaskCollection.h"

void TaskCollection::resize(size_t newCapacity)
{
	Task** temp = new Task * [newCapacity];

	for (int i = 0; i < size; i++)
	{
		temp[i] = data[i];
	}

	delete data;
	data = temp;
	capacity = newCapacity;
}

void TaskCollection::copyFrom(const TaskCollection& other)
{
	data = new Task * [other.capacity];

	for (int i = 0; i < other.size; i++)
	{
		data[i] = other.data[i]->clone();
	}

	size = other.size;
	capacity = other.capacity;
}

void TaskCollection::moveFrom(TaskCollection&& other)
{
	data = new Task * [other.capacity];

	for (int i = 0; i < other.size; i++)
	{
		data[i] = other.data[i];
		other.data[i] = nullptr;
	}

	size = other.size;
	other.size = 0;

	capacity = other.capacity;
	other.capacity = 0;
}

void TaskCollection::free()
{
	for (int i = 0; i < actualSize; i++)
	{
		delete data[i];
	}

	delete[] data;
}

int TaskCollection::getIndexToInsert(Task* newTask) const
{
	int start = 0;
	int end = size - 1;

	int priotity = newTask->getPriority();

	while (start <= end)
	{
		int index = start + end / 2;

		if (priotity == data[index]->getPriority())
		{
			return index;
		}
		else if (priotity < data[index]->getPriority())
		{
			start = index + 1;

		}
		else if (priotity > data[index]->getPriority())
		{
			end = index - 1;
		}
	}

	return end + 1;
}

void TaskCollection::shiftElementsBeforeAdding(size_t index)
{
	for (int i = capacity - 1; i > index; i--)
	{
		data[i] = data[i - 1];
	}

	data[index] = nullptr;
}

void TaskCollection::shiftElementsAfterFinishingTask(size_t index)
{
	for (int i = index; i < capacity; i++)
	{
		data[i] = data[i + 1];
	}

	data[capacity - 1] = nullptr;
}

int TaskCollection::getIndexToSetCompletedTask() const
{
	for (int i = 0; i < capacity; i++)
	{
		if(data[i] == nullptr)
		{
			return i;
		}
	}

	return -1;
}

int TaskCollection::fundTaskById(int id) const
{
	for (int i = 0; i < size; i++)
	{
		if (data[i]->getId() == id)
		{
			return i;
		}
	}

	return -1;
}

TaskCollection::TaskCollection()
{
	size = 0;
	capacity = 8;
	data = new Task * [capacity] {nullptr};
}

TaskCollection::TaskCollection(const TaskCollection& other)
{
	copyFrom(other);
}

TaskCollection::TaskCollection(TaskCollection&& other)
{
	moveFrom(std::move(other));
}

TaskCollection& TaskCollection::operator=(const TaskCollection& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

TaskCollection& TaskCollection::operator=(TaskCollection&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

TaskCollection::~TaskCollection()
{
	free();
}

void TaskCollection::add(Task* task)
{
	if (task->getStatus() == Status::Completed)
	{
		if (actualSize >= capacity)
		{
			resize(capacity * 2);
		}

		int index = getIndexToSetCompletedTask();
		data[index] = task;
		actualSize++;
		return;
	}

	if (size == 0 && actualSize == 0)
	{
		data[0] = task;
		size++;
		actualSize++;
		return;
	}
	else if (size == 0 && actualSize != 0)
	{
		if (actualSize + 1 >= capacity)
		{
			resize(capacity * 2);
		}
		
		shiftElementsBeforeAdding(0);

		data[0] = task;
		size++;
		actualSize++;

		return;
	}

	if (actualSize >= capacity)
	{
		resize(capacity * 2);
	}

	int indexToInsert = getIndexToInsert(task);

	shiftElementsBeforeAdding(indexToInsert);
	data[indexToInsert] = task;
	size++;
	actualSize++;
}

void TaskCollection::add(const Task& task)
{
	Task* temp = task.clone();
	add(temp);
}

void TaskCollection::printUpcomingTasks() const
{
	if (size == 0)
	{
		throw std::length_error("There are no upcomming tasks!");
	}

	for (int i = 0; i < size; i++)
	{
		if (data[i]->getStatus() == Status::Running || data[i]->getStatus() == Status::NotCompleted)
		{
			data[i]->displayTaskInfo();
		}
	}
}

void TaskCollection::printCompletedTasks() const
{
	if (actualSize == 0)
	{
		throw std::length_error("There are no completed tasks!");
	}

	for (int i = 0; i < actualSize; i++)
	{
		if (data[i]->getStatus() == Status::Completed)
		{
			data[i]->displayTaskInfo();
		}
	}
}

void TaskCollection::executeTask()
{
	if (size == 0)
	{
		throw std::length_error("There is no task to be executed!");
	}

	data[0]->execute();
	Task* completedTask = data[0];

	shiftElementsAfterFinishingTask(0);
	int indexToPutCompletedTask = getIndexToSetCompletedTask();
	data[indexToPutCompletedTask] = completedTask;
	size--;
}

Task* TaskCollection::seeNextTask() const
{
	if (size == 0)
	{
		throw std::length_error("There is no task to be executed!");
	}

	return data[0];
}

void TaskCollection::changePriority(int id, int newPriority)
{
	int index = fundTaskById(id);

	if (index == -1)
	{
		throw std::invalid_argument("There is no task with such id!");
	}

	Task* temp = data[index];
	temp->setPriority(newPriority);
	shiftElementsAfterFinishingTask(index);
	size--;
	add(temp);
	actualSize--;
}