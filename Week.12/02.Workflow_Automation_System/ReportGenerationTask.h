#pragma once
#pragma once
#include "Task.h"

enum class ReportType
{
	Annual,
	Monthly,
	Technical,
	Suggestion,
	Undefined
};

class ReportGenerationTask : public Task
{
private:
	ReportType reportType = ReportType::Undefined;
	MyString outputFormat;

	MyString getReport() const;
	void setOutputFormat(const MyString& outputFormat);

public:
	ReportGenerationTask(int id, const MyString& name, int priority, Status status, ReportType reportType, const MyString& outputFormat);

	void displayTaskInfo() const override;

	Task* clone() const override;
};