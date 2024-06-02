#include "FileTransferTask.h"

FileTransferTask::FileTransferTask(int id, const MyString& name, int priority, Status status, const MyString& sourcePath, const MyString& destinationPath, size_t size)
	:Task(id, name, priority, status), sourcePath(sourcePath), destinationPath(destinationPath), fileSize(size) { }

void FileTransferTask::displayTaskInfo() const
{

	Task::displayTaskInfo();
	std::cout << "Source path: " << sourcePath << std::endl;
	std::cout << "Destination path: " << destinationPath << std::endl;
	std::cout << "File size: " << fileSize << std::endl;
}

Task* FileTransferTask::clone() const
{
	return new FileTransferTask(*this);
}
