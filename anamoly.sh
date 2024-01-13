#!/bin/bash

# Define the path to the compiled C program relative to the script
SCRIPT_DIR=$(dirname "$0")
WEATHER_APP="$SCRIPT_DIR/weather_app"

# Define email details
RECIPIENT_EMAIL="XXXX@gmail.com"
SUBJECT="Weather Anomaly Alert"

# Run the weather application
ANOMALY_OUTPUT=$($WEATHER_APP)

# Check for anomalies and send an email if needed
if [[ $ANOMALY_OUTPUT == *"Anomaly Detected"* ]]; then
    # Prepare the email content with a subject and recipient
    EMAIL_CONTENT="Subject: $SUBJECT\nTo: $RECIPIENT_EMAIL\n\nAnomaly detected at $(date):\n$ANOMALY_OUTPUT"

    # Sending email using sendmail
    echo -e "$EMAIL_CONTENT" | sendmail -t
fi
