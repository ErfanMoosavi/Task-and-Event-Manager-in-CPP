#ifndef HANDLERS
#define HANDLERS

#include "../server/server.hpp"
#include "System.hpp"
#include <map>
#include <string>
#include <cstdlib>
#include <iostream>

using namespace std;

class SignupHandler : public RequestHandler
{
    System *system;

public:
    SignupHandler(System *system_);
    Response *callback(Request *req) override;
};

class LoginHandler : public RequestHandler
{
    System *system;

public:
    LoginHandler(System *system_);
    Response *callback(Request *req) override;
};

class LogoutHandler : public RequestHandler
{
    System *system;

public:
    LogoutHandler(System *system_);
    Response *callback(Request *req) override;
};

class DashboardHandler : public TemplateHandler
{
    System *system;

public:
    DashboardHandler(const string &file_path, System *system_);
    map<string, string> handle(Request *req) override;
};

class AddTaskHandlerTemp : public TemplateHandler
{
    System *system;

public:
    AddTaskHandlerTemp(const string &file_path, System *system_);
    map<string, string> handle(Request *req) override;
};

class AddTaskHandler : public RequestHandler
{
    System *system;

public:
    AddTaskHandler(System *system_);
    Response *callback(Request *req) override;
};

class EditTaskHandlerTemp : public TemplateHandler
{
    System *system;

public:
    EditTaskHandlerTemp(const string &file_path, System *system_);
    map<string, string> handle(Request *req) override;
};

class EditTaskHandler : public RequestHandler
{
    System *system;

public:
    EditTaskHandler(System *system_);
    Response *callback(Request *req) override;
};

class DeleteTaskHandlerTemp : public TemplateHandler
{
    System *system;

public:
    DeleteTaskHandlerTemp(const string &file_path, System *system_);
    map<string, string> handle(Request *req) override;
};

class DeleteTaskHandler : public RequestHandler
{
    System *system;

public:
    DeleteTaskHandler(System *system_);
    Response *callback(Request *req) override;
};

class AddEventHandlerTemp : public TemplateHandler
{
    System *system;

public:
    AddEventHandlerTemp(const string &file_path, System *system_);
    map<string, string> handle(Request *req) override;
};

class AddEventHandler : public RequestHandler
{
    System *system;

public:
    AddEventHandler(System *system_);
    Response *callback(Request *req) override;
};

class AddWeeklyEventHandlerTemp : public TemplateHandler
{
    System *system;

public:
    AddWeeklyEventHandlerTemp(const string &file_path, System *system_);
    map<string, string> handle(Request *req) override;
};

class AddWeeklyEventHandler : public RequestHandler
{
    System *system;

public:
    AddWeeklyEventHandler(System *system_);
    Response *callback(Request *req) override;
};

class GenerateReportHandlerTemp : public TemplateHandler
{
    System *system;

public:
    GenerateReportHandlerTemp(const string &file_path, System *system_);
    map<string, string> handle(Request *req) override;
};

class GenerateReportHandler : public RequestHandler
{
    System *system;

public:
    GenerateReportHandler(System *system_);
    Response *callback(Request *req) override;
};

class ReportHandler : public RequestHandler
{
    System *system;

public:
    ReportHandler(System *system_);
    Response *callback(Request *req) override;
};

Response *statusHandler(Status status, System *system);

#endif