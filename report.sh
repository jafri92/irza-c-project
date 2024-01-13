#!/bin/bash
set -e
# Define the path to the compiled C program
SCRIPT_DIR=$(dirname "$0")
WEATHER_APP="$SCRIPT_DIR/weather_app"

# Define the recipient email address
EMAIL="XXXX@gmail.com"

# Run the weather application and capture the output
WEATHER_REPORT=$($WEATHER_APP)

# Check if the weather report was generated successfully
if [ -n "$WEATHER_REPORT" ]; then
    # Create HTML content
    SUBJECT="Daily Weather Report"
    BODY="
    <html>
    <body>
    <h1>Daily Weather Report</h1>
    <p>$(echo "$WEATHER_REPORT" | sed 's/$/<br>/')</p>
    </body>
    </html>
    "

    # Send the email
    echo "Subject: $SUBJECT
MIME-Version: 1.0
Content-Type: text/html
Content-Disposition: inline

$BODY" | sendmail "$EMAIL"
else
    echo "Failed to generate weather report."
fi

