#pragma once
#pragma once
#include "Task.h"

class FileTransferTask : public Task
{
private:
	MyString sourcePath;
	MyString destinationPath;
	size_t fileSize;

public:
	FileTransferTask(int id, const MyString& name, int priority, Status status, const MyString& sourcePath, const MyString& destinationPath, size_t size);

	void displayTaskInfo() const override;

	Task* clone() const override;
};