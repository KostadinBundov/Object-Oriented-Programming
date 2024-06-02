#include "Task.h"

Task::Task(int taskID, const MyString& name, int priority, Status status)
{
    this->id = taskID;
    this->name = name;
    setPriority(priority);
    this->status = status;
}

void Task::execute()
{
	status = Status::Completed;
}

Status Task::getStatus() const
{
	return status;
}

void Task::setPriority(int newPriority)
{
	if (status == Status::Completed)
	{
        throw std::invalid_argument("Task is already completed!");
	}

	if (newPriority <= 0 || newPriority > 10)
	{
		throw std::invalid_argument("Priority must be between 1 and 10!");
	}

	priority = newPriority;
}

void Task::displayTaskInfo() const
{
	std::cout << "Id: " << id << std::endl;
	std::cout << "Task: " << name << std::endl;
	std::cout << "Status: " << getStatusText() << std::endl;
    std::cout << "Priority: " << priority << std::endl;
}

unsigned Task::getPriority() const
{
    return priority;
}

int Task::getId() const
{
    return id;
}

MyString Task::getStatusText() const
{
    MyString result;

    switch (status)
    {
    case Status::NotCompleted:
        result = "Not completed";
        break;

    case Status::Running:
        result = "Running";
        break;

    case Status::Completed:
        result = "Completed";
        break;

    case Status::NotSet:
        result = "Not set";
        break;
    }

    return result;
}