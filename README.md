# Task and Schedule Management System

This is a C++ web-based task and schedule management system designed to help users efficiently plan, organize, and review their personal schedules. It includes support for one-time and weekly events, task management, and a custom-built HTML-based reporting system.

## Features

- **User Authentication**
  - Sign up, login, and logout functionality
  - Secure session management per user

- **Task Management**
  - Add, edit, and delete personal tasks
  - Tasks are time-stamped and include titles and descriptions

- **Event Management**
  - Create one-time events with specific dates and durations
  - Create recurring weekly events by selecting weekdays within a date range
  - Conflict detection for overlapping events and national holidays

- **Holiday Awareness**
  - Integrated holiday manager to avoid scheduling events on holidays

- **Reporting System**
  - Generate filtered reports between two date ranges
  - Events and tasks are displayed chronologically with type, date, time, and descriptions
  - Reports are rendered in a modern HTML format using a consistent glassmorphism UI theme

## Technologies Used

- **C++** — Core logic, custom HTTP server, and dynamic HTML generation
- **HTML/CSS** — User interface with a focus on modern, minimal design
- **Custom Templating & Routing** — No external frameworks; all routing and rendering are handled internally

## System Architecture

- `System` class: Manages all user operations including authentication, task/event creation, and reporting
- `User` class: Stores user-specific data including tasks, events, and periodic events
- `HolidayManager`: Prevents scheduling on predefined holidays
- `ReportItem`: A unified abstraction for rendering different types of activities in the report
- `DateUtilities`: Responsible for date parsing, formatting, and comparison
- `TemplateHandler` (if used): Converts backend report data into styled HTML

## Usage Overview

1. **Signup / Login**
   - Users must sign up and log in to begin managing their schedule.

2. **Create Tasks and Events**
   - Add individual tasks and one-time or weekly events.
   - The system validates dates and avoids overlaps or holiday conflicts.

3. **Generate Reports**
   - Reports provide a complete view of scheduled tasks and events between two dates.
   - HTML output is styled for clarity and easy navigation.

## Output Design

- Glassmorphism UI: Blurred, semi-transparent containers with soft colored backgrounds
- Dynamic elements: Task, Event, and Weekly Event sections use unique badges and layouts
- Mobile responsive: Design adapts to various screen sizes for accessibility

## Acknowledgments

This project uses the [APHTTP](https://github.com/username/APHTTP) library for HTTP server handling.

### License Notice

The APHTTP library is licensed under the MIT License:

> MIT License  
> Copyright (c)  
>  
> Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:  
>  
> The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.  
>  
> THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
