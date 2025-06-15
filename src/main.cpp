#include "System.hpp"
#include "HolidayManager.hpp"
#include "../server/server.hpp"
#include "handlers.hpp"

void mapServerPaths(Server &server, System *system)
{
    server.setNotFoundErrPage("static/404_login.html");
    server.setNotFoundErrPage("static/404.html");
    
    server.get("/", new ShowPage("static/home.html"));
    server.get("/signup", new ShowPage("static/signup.html"));
    server.post("/signup", new SignupHandler(system));
    server.get("/login", new ShowPage("static/login.html"));
    server.post("/login", new LoginHandler(system));
    server.get("/logout", new ShowPage("static/logout.html"));
    server.post("/logout", new LogoutHandler(system));
    server.get("/dashboard", new DashboardHandler("static/dashboard.html", system));
    server.get("/add_task", new AddTaskHandlerTemp("static/add_task.html", system));
    server.post("/add_task", new AddTaskHandler(system));
    server.get("/edit_task", new EditTaskHandlerTemp("static/edit_task.html", system));
    server.post("/edit_task", new EditTaskHandler(system));
    server.get("/delete_task", new DeleteTaskHandlerTemp("static/delete_task.html", system));
    server.post("/delete_task", new DeleteTaskHandler(system));
    server.get("/add_event", new AddEventHandlerTemp("static/add_event.html", system));
    server.post("/add_event", new AddEventHandler(system));
    server.get("/add_weekly_event", new AddWeeklyEventHandlerTemp("static/add_weekly_event.html", system));
    server.post("/add_weekly_event", new AddWeeklyEventHandler(system));
    server.get("/generate_report", new GenerateReportHandlerTemp("static/generate_report.html", system));
    server.post("/generate_report", new GenerateReportHandler(system));
    server.get("/report", new ReportHandler(system));
    server.post("/report", new ShowPage("static/dashboard.html"));
    server.get("/bad_request", new ShowPage("status/bad_request.html"));
    server.get("/not_found", new ShowPage("status/not_found.html"));
    server.get("/permission_denied", new ShowPage("status/permission_denied.html"));
    server.get("/bad_request_login", new ShowPage("status/bad_request_login.html"));
    server.get("/not_found_login", new ShowPage("status/not_found_login.html"));
    server.get("/permission_denied_login", new ShowPage("status/permission_denied_login.html"));
    server.get("/empty_login", new ShowPage("status/empty_login.html"));
    server.get("/ok_login", new ShowPage("status/ok_login.html"));
    server.get("/holiday_found_login", new ShowPage("status/holiday_found_login.html"));
    server.get("/overlap_login", new ShowPage("status/overlap_login.html"));
}

int main(int argc, char **argv)
{
    try
    {
        HolidayManager hm;
        hm.loadFromCSV(argv[2]);

        System system(hm);

        int port = argc > 1 ? stoi(argv[1]) : 5000;
        Server server(port);
        mapServerPaths(server, &system);
        cout << "Server running on port: " << port << endl;
        server.run();
    }
    catch (const invalid_argument &e)
    {
        cerr << e.what() << endl;
    }
    catch (const Server::Exception &e)
    {
        cerr << e.getMessage() << endl;
    }
    return 0;
}