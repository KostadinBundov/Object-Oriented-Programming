#include "EmailTask.h"

EmailTask::EmailTask(int id, const MyString& name, int priority, Status status, const MyString& recipient, const MyString& subject, const MyString& body)
	:Task(id, name, priority, status)
{
	this->recipient = recipient;
	this->body = body;
	this->subject = subject;
}

void EmailTask::displayTaskInfo() const
{
	Task::displayTaskInfo();
	std::cout << "Recipient: " << recipient << std::endl;
	std::cout << "Subject: " << subject << std::endl;
	std::cout << "Body: " << body << std::endl;
}

Task* EmailTask::clone() const
{
	return new EmailTask(*this);
}