#pragma once
#include "MyString.h"

enum class Status
{
	NotCompleted,
	Running,
	Completed,
	NotSet
};

class Task
{
protected:
	int id = -1;
	MyString name;
	unsigned priority = 0;
	Status status = Status::NotSet;

	MyString getStatusText() const;

public:
	Task(int taskID, const MyString& name, int priority, Status status);

	void execute();
	Status getStatus() const;
	void setPriority(int newPriority);
	unsigned getPriority() const;
	virtual void displayTaskInfo() const;

	int getId() const;

	virtual Task* clone() const = 0;

	virtual ~Task() = default;
};