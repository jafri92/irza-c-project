---

# Weather Monitoring and Anomaly Detection Project

## Overview

This project consists of a weather monitoring application written in C, along with associated scripts for generating weather reports and detecting anomalies. The C application fetches weather data and can be used in conjunction with Bash scripts to send daily weather reports and perform anomaly detection.

## Components

1. **Weather App (C):** A C program that interacts with a weather API to fetch and process weather data.
2. **Report Script (Bash):** A script that runs the weather app and sends a daily weather report via email.
3. **Anomaly Detection Script (Bash):** A script that periodically checks for weather anomalies and sends an alert if any are detected.
4. **Cron Jobs:** Scheduled tasks to automate the running of the above scripts.

## Setup and Usage

### Weather App in C

- **Description:** This is a C program that fetches weather data from an API.
- **Compilation:** Use `gcc` to compile the program:
  ```bash
  gcc -o weather_app weather_app.c -lcurl -ljson-c
  ```
- **Usage:** Run the compiled program to fetch and display weather data.

### Daily Weather Report Script

- **File:** `send_weather_report.sh`
- **Setup:** Ensure `sendmail` or an equivalent mail service is configured on your system.
- **Usage:** Run the script to send the current weather report to a specified email address.

### Anomaly Detection Script

- **File:** `check_anomaly.sh`
- **Setup:** Configure `sendmail` for sending alert emails.
- **Usage:** Run the script to check for weather anomalies and send an alert if any are detected.

### Setting Up Cron Jobs

- **Purpose:** To automate the running of the report and anomaly detection scripts.
- **Editing Crontab:** Use `crontab -e` to edit your cron jobs.
- **Example:** To run the report script daily at 8 AM and the anomaly script every 5 minutes, add:
  ```
  0 8 * * * /path/to/send_weather_report.sh
  */5 * * * * /path/to/check_anomaly.sh
  ```

## Additional Information

- **API Key:** Ensure you have a valid API key for the weather API used in the C program.
- **Email Configuration:** The scripts assume that your system's email sending capabilities are correctly set up.
- **Security:** Be cautious with sensitive information like API keys and email addresses. Avoid hardcoding them into scripts.

### Modifying the README

- Feel free to add more sections or details as needed, such as prerequisites, library dependencies, configuration details, or contact information.
