#include <iostream>
#include "EmailTask.h"
#include "FileTransferTask.h"
#include "ReportGenerationTask.h"
#include "TaskCollection.h"

int main() 
{
    // This part of the code is our factory in this case - the only place where we know what type exactly is every single task
    Task* firstTask = new EmailTask(1, "Email Task", 3, Status::NotCompleted, "recipient@example.com", "Subject of the email", "Body of the email");
    Task* secondTask = new FileTransferTask(2, "File Transfer Task", 5, Status::Running, "/path/to/source", "/path/to/destination", 1024);
    Task* thirdTask = new ReportGenerationTask(3, "Report Generation Task", 4, Status::Completed, ReportType::Annual, ".pdf");

    TaskCollection taskCollection;
    taskCollection.add(firstTask);
    taskCollection.add(secondTask);
    taskCollection.add(thirdTask);

    std::cout << "Upcoming Tasks:" << std::endl;
    taskCollection.printUpcomingTasks();

    std::cout << "\nCompleted Tasks:" << std::endl;
    taskCollection.printCompletedTasks();

    taskCollection.changePriority(1, 10);

    std::cout << "\nExecuting Next Task:" << std::endl;
    taskCollection.executeTask();

    std::cout << "\nUpdated Upcoming Tasks:" << std::endl;
    taskCollection.printUpcomingTasks();

    std::cout << "\nUpdated Completed Tasks:" << std::endl;
    taskCollection.printCompletedTasks();
}
