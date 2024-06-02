#pragma once
#include "Task.h"

class EmailTask : public Task
{
private:
	MyString recipient;
	MyString subject;
	MyString body;

public:
	EmailTask(int id, const MyString& name, int priority, Status status, const MyString& recipient, const MyString& subject, const MyString& body);

	void displayTaskInfo() const override;

	Task* clone() const override;
};