#include "handlers.hpp"

SignupHandler::SignupHandler(System *system_)
    : system(system_)
{
}

Response *SignupHandler::callback(Request *req)
{
    string username = req->getBodyParam("username");
    string password = req->getBodyParam("password");

    Status status = system->signup(username, password);

    if (status != Status::ok)
        return statusHandler(status, system);
    else
    {
        Response *res = Response::redirect("/dashboard");
        res->setSessionId(username);
        return res;
    }
}

LoginHandler::LoginHandler(System *system_)
    : system(system_)
{
}

Response *LoginHandler::callback(Request *req)
{
    string username = req->getBodyParam("username");
    string password = req->getBodyParam("password");

    Status status = system->login(username, password);

    if (status != Status::ok)
        return statusHandler(status, system);
    else
    {
        Response *res = Response::redirect("/dashboard");
        res->setSessionId(username);
        return res;
    }
}

LogoutHandler::LogoutHandler(System *system_)
    : system(system_)
{
}

Response *LogoutHandler::callback(Request *req)
{
    string confirmation = req->getBodyParam("confirmation");
    if (confirmation == "Yes")
    {
        Status status = system->logout();
        if (status == Status::ok)
        {
            Response *res = Response::redirect("/");
            res->setSessionId("");
            return res;
        }
        else
        {
            return statusHandler(status, system);
        }
    }
    else if (confirmation == "No")
    {
        Response *res = Response::redirect("/dashboard");
        return res;
    }
    else
    {
        Response *res = Response::redirect("/bad_request_login");
        return res;
    }
}

DashboardHandler::DashboardHandler(const string &file_path, System *system_)
    : TemplateHandler(file_path),
      system(system_)
{
}

map<string, string> DashboardHandler::handle(Request *req)
{
    map<string, string> context;
    context["username"] = system->getLoggedInUser()->getUsername();
    return context;
}

AddTaskHandlerTemp::AddTaskHandlerTemp(const string &file_path, System *system_)
    : TemplateHandler(file_path), system(system_)
{
}

map<string, string> AddTaskHandlerTemp::handle(Request *req)
{
    map<string, string> context;
    context["username"] = system->getLoggedInUser()->getUsername();
    return context;
}

AddTaskHandler::AddTaskHandler(System *system_)
    : system(system_)
{
}

Response *AddTaskHandler::callback(Request *req)
{
    string date = req->getBodyParam("date");
    int time = stoi(req->getBodyParam("time"));
    string title = req->getBodyParam("title");
    string description = req->getBodyParam("description");

    Status status = system->addTask(date, time, title, description);
    return statusHandler(status, system);
}

EditTaskHandlerTemp::EditTaskHandlerTemp(const string &file_path, System *system_)
    : TemplateHandler(file_path), system(system_)
{
}

map<string, string> EditTaskHandlerTemp::handle(Request *req)
{
    map<string, string> context;
    context["username"] = system->getLoggedInUser()->getUsername();
    return context;
}

EditTaskHandler::EditTaskHandler(System *system_)
    : system(system_)
{
}

Response *EditTaskHandler::callback(Request *req)
{
    int task_id = stoi(req->getBodyParam("task-id"));
    string new_date = req->getBodyParam("new-date");
    int new_time = stoi(req->getBodyParam("new-time"));
    string new_title = req->getBodyParam("new-title");
    string new_description = req->getBodyParam("new-description");

    Status status = system->editTask(task_id, new_date, new_time, new_title, new_description);
    return statusHandler(status, system);
}

DeleteTaskHandlerTemp::DeleteTaskHandlerTemp(const string &file_path, System *system_)
    : TemplateHandler(file_path), system(system_)
{
}

map<string, string> DeleteTaskHandlerTemp::handle(Request *req)
{
    map<string, string> context;
    context["username"] = system->getLoggedInUser()->getUsername();
    return context;
}

DeleteTaskHandler::DeleteTaskHandler(System *system_)
    : system(system_)
{
}

Response *DeleteTaskHandler::callback(Request *req)
{
    int task_id = stoi(req->getBodyParam("task-id"));

    Status status = system->deleteTask(task_id);
    return statusHandler(status, system);
}

AddEventHandlerTemp::AddEventHandlerTemp(const string &file_path, System *system_)
    : TemplateHandler(file_path), system(system_)
{
}

map<string, string> AddEventHandlerTemp::handle(Request *req)
{
    map<string, string> context;
    context["username"] = system->getLoggedInUser()->getUsername();
    return context;
}

AddEventHandler::AddEventHandler(System *system_)
    : system(system_)
{
}

Response *AddEventHandler::callback(Request *req)
{
    string date = req->getBodyParam("date");
    int start_time = stoi(req->getBodyParam("start-time"));
    int duration = stoi(req->getBodyParam("duration"));
    string title = req->getBodyParam("title");
    string description = req->getBodyParam("description");

    Status status = system->addEvent(date, start_time, duration, title, description);
    return statusHandler(status, system);
}

AddWeeklyEventHandlerTemp::AddWeeklyEventHandlerTemp(const string &file_path, System *system_)
    : TemplateHandler(file_path), system(system_)
{
}

map<string, string> AddWeeklyEventHandlerTemp::handle(Request *req)
{
    map<string, string> context;
    context["username"] = system->getLoggedInUser()->getUsername();
    return context;
}

AddWeeklyEventHandler::AddWeeklyEventHandler(System *system_)
    : system(system_)
{
}

Response *AddWeeklyEventHandler::callback(Request *req)
{
    string start_date = req->getBodyParam("start-date");
    string end_date = req->getBodyParam("end-date");
    int start_time = stoi(req->getBodyParam("start-time"));
    int duration = stoi(req->getBodyParam("duration"));
    string days = req->getBodyParam("days");
    string title = req->getBodyParam("title");
    string description = req->getBodyParam("description");

    Status status = system->addWeeklyEvent(start_date, end_date, start_time, duration, days, title, description);
    cout << "BEFORE RETURN\n\n\n\n\n";
    return statusHandler(status, system);
}

GenerateReportHandlerTemp::GenerateReportHandlerTemp(const string &file_path, System *system_)
    : TemplateHandler(file_path), system(system_)
{
}

map<string, string> GenerateReportHandlerTemp::handle(Request *req)
{
    map<string, string> context;
    context["username"] = system->getLoggedInUser()->getUsername();
    return context;
}

GenerateReportHandler::GenerateReportHandler(System *system_)
    : system(system_)
{
}

Response *GenerateReportHandler::callback(Request *req)
{
    string start_date = req->getBodyParam("start-date");
    string end_date = req->getBodyParam("end-date");

    Status status = system->generateReportItems(start_date, end_date);
    if (status != Status::ok)
    {
        return statusHandler(status, system);
    }
    else
    {
        Response *res = Response::redirect("/report");
        return res;
    }
}

ReportHandler::ReportHandler(System *system_)
    : system(system_)
{
}

Response *ReportHandler::callback(Request *req)
{
    string username = system->getLoggedInUser()->getUsername();
    string html = system->getReportHTML(username);

    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    res->setBody(html);
    return res;
}

Response *statusHandler(Status status, System *system)
{
    if (system->getLoggedInUser())
    {
        if (status == Status::permission_denied)
        {
            Response *res = Response::redirect("/permission_denied_login");
            return res;
        }
        else if (status == Status::bad_request)
        {
            Response *res = Response::redirect("/bad_request_login");
            return res;
        }
        else if (status == Status::empty)
        {
            Response *res = Response::redirect("/empty_login");
            return res;
        }
        else if (status == Status::not_found)
        {
            Response *res = Response::redirect("/not_found_login");
            return res;
        }
        else if (status == Status::holiday_found)
        {
            Response *res = Response::redirect("/holiday_found_login");
            return res;
        }
        else if (status == Status::overlap)
        {
            Response *res = Response::redirect("/overlap_login");
            return res;
        }
        else if (status == Status::ok)
        {
            Response *res = Response::redirect("/ok_login");
            return res;
        }
        else
        {
            Response *res = Response::redirect("/404");
            return res;
        }
    }
    else
    {
        if (status == Status::permission_denied)
        {
            Response *res = Response::redirect("/permission_denied");
            return res;
        }
        else if (status == Status::bad_request)
        {
            Response *res = Response::redirect("/bad_request");
            return res;
        }
        else if (status == Status::not_found)
        {
            Response *res = Response::redirect("/not_found");
            return res;
        }
        else
        {
            Response *res = Response::redirect("/404");
            return res;
        }
    }
}