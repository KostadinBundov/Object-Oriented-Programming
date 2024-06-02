#include "ReportGenerationTask.h"

MyString ReportGenerationTask::getReport() const
{
	MyString result;

	switch (reportType)
	{
	case ReportType::Annual:
		result = "Annual";
		break;

	case ReportType::Monthly:
		result = "Monthly";
		break;

	case ReportType::Technical:
		result = "Technical";
		break;

	case ReportType::Suggestion:
		result = "Suggestion";
		break;

	case ReportType::Undefined:
		result = "Undefined";
		break;
	}

	return result;
}

void ReportGenerationTask::setOutputFormat(const MyString& outputFormat)
{
	if (outputFormat == ".docx" || outputFormat == ".xlsx" || outputFormat == ".pdf" || outputFormat == ".pptx")
	{
		this->outputFormat = outputFormat;
	}
	else
	{
		throw std::invalid_argument("Invalid file type!");
	}
}

ReportGenerationTask::ReportGenerationTask(int id, const MyString& name, int priority, Status status, ReportType reportType, const MyString& outputFormat)
	: Task(id, name, priority, status), reportType(reportType)
{
	setOutputFormat(outputFormat);
}

void ReportGenerationTask::displayTaskInfo() const
{
	Task::displayTaskInfo();
	std::cout << "ReportType: " << getReport() << std::endl;
	std::cout << "Output format: " << outputFormat << std::endl;
}

Task* ReportGenerationTask::clone() const
{
	return new ReportGenerationTask(*this);
}
