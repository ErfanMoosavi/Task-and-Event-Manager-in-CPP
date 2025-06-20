#include "System.hpp"

System::System(HolidayManager &holiday_manager_)
    : holiday_manager(holiday_manager_), logged_in_user(nullptr)
{
}

Status System::signup(string username, string password)
{
    if (logged_in_user)
        return Status::permission_denied;
    if (findUser(username))
        return Status::bad_request;

    auto user = make_shared<User>(username, password);
    users.push_back(user);
    return login(username, password);
}

Status System::login(string username, string password)
{
    auto user = findUser(username);

    if (logged_in_user)
        return Status::permission_denied;
    else if (!user)
        return Status::not_found;
    else if (user->getPassword() != password)
        return Status::permission_denied;

    logged_in_user = user;
    return Status::ok;
}

Status System::logout()
{
    if (!logged_in_user)
        return Status::permission_denied;

    logged_in_user = nullptr;
    return Status::ok;
}

Status System::addEvent(string date_str, int start_time, int duration, string title, string description)
{
    Date date = date_utilities.stringToDate(date_str);
    Date origin;

    if (!logged_in_user)
        return Status::permission_denied;
    else if (date <= origin)
        return Status::bad_request;
    else if (isOverlap(date, start_time, duration))
        return Status::overlap;
    else if (holiday_manager.isHoliday(date))
        return Status::holiday_found;

    auto event = make_shared<Event>(date, start_time, duration, title, description);
    logged_in_user->addEvent(event);
    return Status::ok;
}

Status System::addWeeklyEvent(string start_date_str, string end_date_str, int start_time, int duration, string week_days, string title, string description)
{
    if (!logged_in_user)
        return Status::permission_denied;

    vector<string> week_days_vec = extractDaysOfWeek(week_days);
    Date start_date = date_utilities.stringToDate(start_date_str);
    Date end_date = date_utilities.stringToDate(end_date_str);
    Date origin;

    if (start_date <= origin || end_date <= start_date || week_days_vec.empty())
        return Status::bad_request;
    for (string &day : week_days_vec)
    {
        if (day != "Saturday" && day != "Sunday" && day != "Monday" && day != "Tuesday" && day != "Wednesday" && day != "Thursday" && day != "Friday")
            return Status::bad_request;
    }
    auto weekly_event = make_shared<WeeklyEvent>(start_date, end_date, start_time, duration, week_days_vec, title, description, holiday_manager);

    for (auto &date : weekly_event->getDates())
    {
        if (isOverlap(date, start_time, duration))
        {
            return Status::overlap;
        }
    }
    int found_holiday = weekly_event->getHasHoliday();
    logged_in_user->addPeriodicEvent(weekly_event);
    if (found_holiday)
        return Status::holiday_found;

    return Status::ok;
}

Status System::addTask(string date_str, int time, string title, string description)
{
    Date date = date_utilities.stringToDate(date_str);
    Date origin;
    if (!logged_in_user)
        return Status::permission_denied;
    else if (date <= origin)
        return Status::bad_request;

    auto task = make_shared<Task>(date, time, title, description);
    logged_in_user->addTask(task);
    return Status::ok;
}

Status System::deleteTask(int id)
{
    if (!logged_in_user)
        return Status::permission_denied;
    else if (!findTask(id))
        return Status::not_found;

    logged_in_user->deleteTask(id);
    return Status::ok;
}

Status System::editTask(int id, string date_str, int time, string title, string description)
{
    Date origin;
    Date date = date_utilities.stringToDate(date_str);

    if (!logged_in_user)
        return Status::permission_denied;
    else if (!findTask(id))
        return Status::not_found;
    else if (date <= origin)
        return Status::bad_request;

    auto task = findTask(id);
    logged_in_user->editTask(task, date, date_str, time, title, description);
    return Status::ok;
}

Status System::generateReportItems(string start_date_str, string end_date_str)
{
    if (!logged_in_user)
        return Status::permission_denied;

    report_items.clear();
    Date start_date = date_utilities.stringToDate(start_date_str);
    Date end_date = date_utilities.stringToDate(end_date_str);

    gatherReportItems(start_date, end_date);

    if (report_items.empty())
        return Status::empty;

    sortReportItems();
    return Status::ok;
}

void System::gatherReportItems(Date start_date, Date end_date)
{
    for (const auto &event : logged_in_user->getEvents())
    {
        if (event->getDate() <= end_date && start_date <= event->getDate())
        {

            report_items.push_back(ReportItem(event->getDate(), event->getStartTime(), 1, event->getId(), "event", event->getTitle(), event->getDescription(), event->getDuration()));
        }
    }

    for (const auto &periodic_event : logged_in_user->getPeriodicEvents())
    {
        for (const auto &date : periodic_event->getDates())
        {
            if (date <= end_date && start_date <= date)
            {
                report_items.push_back(ReportItem(date, periodic_event->getStartTime(), 0, periodic_event->getId(), "weekly_event", periodic_event->getTitle(), periodic_event->getDescription(), periodic_event->getDuration()));
            }
        }
    }

    for (const auto &task : logged_in_user->getTasks())
    {
        if (task->getDate() <= end_date && start_date <= task->getDate())
            report_items.push_back(ReportItem(task->getDate(), task->getTime(), 2, task->getId(), "task", task->getTitle(), task->getDescription(), 0));
    }
}

void System::sortReportItems()
{
    sort(report_items.begin(), report_items.end(), [](const ReportItem &a, const ReportItem &b)
         {
        if (a.date.getYear() != b.date.getYear()) {
            return a.date.getYear() < b.date.getYear();
        }
        if (a.date.getMonth() != b.date.getMonth()) {
            return a.date.getMonth() < b.date.getMonth();
        }
        if (a.date.getDay() != b.date.getDay()) {
            return a.date.getDay() < b.date.getDay();
        }
        if (a.time != b.time) {
            return a.time < b.time;
        }
        if (a.priority != b.priority) {
            return a.priority < b.priority;
        }
        return a.id < b.id; });
}

string System::getReportHTML(const string &username) const
{
    string html;

    html += R"(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1.0" />
  <title>Report</title>
  <style>
    * { margin: 0; padding: 0; box-sizing: border-box; }
    body {
      height: 100vh; background: #141e30; font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
      color: #ffffff; overflow-y: auto; position: relative; padding: 2rem;
    }
    .background-circle {
      position: absolute; border-radius: 50%; filter: blur(120px);
      opacity: 0.4; z-index: 0;
    }
    .circle1 { width: 400px; height: 400px; background: #ffb347; top: -100px; left: -150px; }
    .circle2 { width: 300px; height: 300px; background: #87f5fb; bottom: -150px; right: -100px; }
    .circle3 {
      width: 300px; height: 300px; background: #d18fff;
      top: 60%; left: 75%; transform: translate(-50%, -50%);
    }
    .container {
      position: relative; z-index: 1; max-width: 900px; margin: auto;
      background: rgba(255, 255, 255, 0.1); border-radius: 20px;
      backdrop-filter: blur(20px); -webkit-backdrop-filter: blur(20px);
      border: 1px solid rgba(255, 255, 255, 0.2);
      box-shadow: 0 0 40px rgba(255, 255, 255, 0.1); padding: 2.5rem;
    }
    .logout-button, .username-button {
      position: absolute; top: 1rem; padding: 0.45rem 1rem;
      font-weight: 600; font-size: 0.9rem; border: none;
      border-radius: 16px; backdrop-filter: blur(10px);
      -webkit-backdrop-filter: blur(10px); cursor: pointer;
      transition: background 0.3s ease, color 0.3s ease;
    }
    .logout-button {
      left: 1rem; background: rgba(255, 100, 100, 0.15); color: #ffb3b3;
    }
    .logout-button:hover {
      background: rgba(255, 100, 100, 0.3); color: #ffffff;
    }
    .username-button {
      right: 1rem; background: rgba(100, 255, 100, 0.15); color: #b3ffb3;
    }
    .username-button:hover {
      background: rgba(100, 255, 100, 0.3); color: #ffffff;
    }
    .report-section-bar {
      width: 140px;
      height: 5px;
      margin: 0.3rem auto 0.4rem;
      border-radius: 2px;
      background: linear-gradient(to right, #ffb347, #d18fff);
    }
    h2 {
      text-align: center; margin-bottom: 2rem; font-size: 2.5rem;
      background: linear-gradient(to right, #ffb347, #d18fff);
      background-clip: text; -webkit-background-clip: text;
      color: transparent; -webkit-text-fill-color: transparent;
    }
    .report-item {
      background: rgba(255, 255, 255, 0.07); border-radius: 15px;
      padding: 1.5rem; margin-bottom: 2rem;
      box-shadow: 0 2px 10px rgba(0, 0, 0, 0.1);
    }
    .type-label {
      display: inline-block; padding: 0.3rem 0.8rem;
      font-size: 0.85rem; font-weight: 600; border-radius: 20px;
      margin-bottom: 1rem; text-transform: uppercase;
      letter-spacing: 1px;
    }
    .type-label.task { background: rgba(255, 100, 150, 0.2); color: #ff709a; }
    .type-label.event { background: rgba(100, 200, 255, 0.2); color: #71cfff; }
    .type-label.weekly_event { background: rgba(150, 100, 255, 0.2); color: #b07aff; }

    .details-grid {
      display: grid;
      grid-template-columns: repeat(3, 1fr);
      gap: 1rem;
    }

    .detail-card {
      flex: 1 1 calc(25% - 1rem);
      background: rgba(255, 255, 255, 0.1);
      border-radius: 15px;
      padding: 1rem;
      text-align: center;
      box-shadow: 0 2px 10px rgba(0, 0, 0, 0.05);
      backdrop-filter: blur(10px);
      transition: transform 0.3s ease, box-shadow 0.3s ease;
    }

    .detail-card:hover {
      transform: translateY(-8px);
      box-shadow: 0 12px 30px rgba(255, 255, 255, 0.15), 0 6px 20px rgba(0, 0, 0, 0.1);
    }

    .detail-card .label {
      font-size: 0.88rem;
      font-weight: 500;
      text-transform: uppercase;
      color: rgb(255, 255, 255);
      padding: 0.3rem 0.7rem;
      border-radius: 12px;
      display: inline-block;
      width: fit-content;
      margin-bottom: 0.3rem;
      box-shadow: 0 2px 6px rgba(0,0,0,0.1);
    }

    .detail-card .value {
      font-size: 1.1rem;
      font-weight: 700;
      color: rgb(255, 255, 255);
    }

    .dashboard-btn {
      display: block; margin: 2rem auto 0; padding: 0.9rem 2rem;
      border: none; border-radius: 30px; font-size: 1.1rem;
      font-weight: 600; background: linear-gradient(to right, #ffb347, #d18fff);
      color: white; cursor: pointer;
      transition: background 0.3s ease, box-shadow 0.3s ease;
    }
    .dashboard-btn:hover {
      background: linear-gradient(to right, #ffb347, #d18fff);
      box-shadow: 0 4px 15px rgba(135, 245, 251, 0.4);
    }

    @media (max-width: 700px) {
      .details-grid { grid-template-columns: repeat(2, 1fr); }
    }
    @media (max-width: 400px) {
      .details-grid { grid-template-columns: 1fr; }
    }
  </style>
</head>
<body>
<div class='background-circle circle1'></div>
<div class='background-circle circle2'></div>
<div class='background-circle circle3'></div>
<div class='container'>
)";

    html += "<button class='logout-button' onclick=\"location.href='/logout'\">Logout</button>";
    html += "<button class='username-button'>" + username + "<span id='clock' style='margin-left: 0.5rem; font-weight: 600;'></span></button>";
    html += "<h2>Report Results</h2>";

    for (const auto &item : report_items)
    {
        html += "<div class='report-item'>";
        html += "<span class='type-label " + item.type + "'>" + item.type + "</span>";
        html += "<div class='details-grid'>";

        html += "<div class='detail-card'><div class='label'>Title</div><div class='section-bar report-section-bar'></div><div class='value'>" + item.title + "</div></div>";
        html += "<div class='detail-card'><div class='label'>ID</div><div class='section-bar report-section-bar'></div><div class='value'>" + to_string(item.id) + "</div></div>";
        html += "<div class='detail-card'><div class='label'>Date</div><div class='section-bar report-section-bar'></div><div class='value'>" + date_utilities.dateToString(item.date) + "</div></div>";
        html += "<div class='detail-card'><div class='label'>Time</div><div class='section-bar report-section-bar'></div><div class='value'>" + to_string(item.time) + ":00</div></div>";
        if (item.duration != 0)
            html += "<div class='detail-card'><div class='label'>Duration</div><div class='section-bar report-section-bar'></div><div class='value'>" + to_string(item.duration) + " Hours</div></div>";
        if (!item.description.empty())
            html += "<div class='detail-card'><div class='label'>Description</div><div class='section-bar report-section-bar'></div><div class='value'>" + item.description + "</div></div>";

        html += "</div></div>";
    }

    html += "<button class='dashboard-btn' onclick=\"location.href='/dashboard'\">Go to Dashboard</button>";
    html += R"(</div>

<script>
  const clock = document.getElementById("clock");
  function updateClock() {
    const now = new Date();
    clock.textContent = now.toLocaleTimeString();
  }
  setInterval(updateClock, 1000);
  updateClock();

  const AudioCtx = window.AudioContext || window.webkitAudioContext;
  const audioCtx = new AudioCtx();

  function playHoverSound() {
    const oscillator = audioCtx.createOscillator();
    const gainNode = audioCtx.createGain();

    oscillator.type = 'sine';
    oscillator.frequency.setValueAtTime(650, audioCtx.currentTime);
    gainNode.gain.setValueAtTime(0.12, audioCtx.currentTime);

    oscillator.connect(gainNode);
    gainNode.connect(audioCtx.destination);

    oscillator.start();
    oscillator.frequency.exponentialRampToValueAtTime(850, audioCtx.currentTime + 0.15);
    gainNode.gain.exponentialRampToValueAtTime(0.0001, audioCtx.currentTime + 0.15);
    oscillator.stop(audioCtx.currentTime + 0.15);
  }

  const hoverElements = document.querySelectorAll('.logout-button, .username-button, .dashboard-btn');
  hoverElements.forEach(elem => {
    elem.addEventListener('mouseenter', () => {
      if (audioCtx.state === 'suspended') audioCtx.resume();
      playHoverSound();
    });
  });
</script>

</body>
</html>
)";

    return html;
}

vector<string> System::extractDaysOfWeek(string week_days_str)
{
    vector<string> week_days;
    stringstream ss(week_days_str);
    string day;

    while (getline(ss, day, ','))
    {
        day.erase(day.begin(), find_if(day.begin(), day.end(), [](unsigned char ch)
                                       { return !isspace(ch); }));
        day.erase(find_if(day.rbegin(), day.rend(), [](unsigned char ch)
                          { return !isspace(ch); })
                      .base(),
                  day.end());

        if (day == "Saturday" || day == "Sunday" || day == "Monday" ||
            day == "Tuesday" || day == "Wednesday" || day == "Thursday" || day == "Friday")
        {
            week_days.push_back(day);
        }
    }
    return week_days;
}

bool System::isOverlap(Date &date, int start_time, int duration) const
{
    for (const auto &event : logged_in_user->getEvents())
    {
        if (date_utilities.isSameDate(date, event->getDate()) &&
            ((start_time >= event->getStartTime() &&
              start_time < event->getStartTime() + event->getDuration()) ||
             (start_time + duration > event->getStartTime() &&
              start_time < event->getStartTime() + event->getDuration())))
        {
            return true;
        }
    }

    for (const auto &periodic_event : logged_in_user->getPeriodicEvents())
    {
        for (const auto &perdiodic_event_date : periodic_event->getDates())
        {
            if (date_utilities.isSameDate(date, perdiodic_event_date) &&
                ((start_time >= periodic_event->getStartTime() &&
                  start_time < periodic_event->getStartTime() + periodic_event->getDuration()) ||
                 (start_time + duration > periodic_event->getStartTime() &&
                  start_time < periodic_event->getStartTime() + periodic_event->getDuration())))
                return true;
        }
    }
    return false;
}

shared_ptr<User> System::findUser(string username)
    const
{
    for (const auto &user : users)
    {
        if (user->getUsername() == username)
            return user;
    }

    return nullptr;
}

shared_ptr<Task> System::findTask(int id)
    const
{
    for (const auto &task : logged_in_user->getTasks())
    {
        if (task->getId() == id)
            return task;
    }

    return nullptr;
}

shared_ptr<User> System::getLoggedInUser() const { return logged_in_user; }