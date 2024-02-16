import os
import psutil
import datetime
from google.oauth2.credentials import Credentials
from google_auth_oauthlib.flow import InstalledAppFlow
from google.auth.transport.requests import Request
from googleapiclient.discovery import build

# Google Calendar API scope
SCOPES = ['https://www.googleapis.com/auth/calendar']

# Function to calculate active time in Visual Studio Code
def calculate_vscode_active_time():
    vscode_process_name = "code"
    active_time = datetime.timedelta()

    for proc in psutil.process_iter():
        if proc.name() == vscode_process_name:
            active_time += datetime.datetime.now() - datetime.datetime.fromtimestamp(proc.create_time())

    return active_time

# Function to authorize with Google Calendar API
def authorize_google_calendar():
    creds = None
    if os.path.exists('token.json'):
        creds = Credentials.from_authorized_user_file('token.json')
    if not creds or not creds.valid:
        if creds and creds.expired and creds.refresh_token:
            creds.refresh(Request())
        else:
            flow = InstalledAppFlow.from_client_secrets_file(
                'credentials.json', SCOPES)
            creds = flow.run_local_server(port=0)
        with open('token.json', 'w') as token:
            token.write(creds.to_json())

    return build('calendar', 'v3', credentials=creds)

# Function to add event to Google Calendar
def add_event_to_calendar(service, event_summary, start_time, end_time):
    event = {
        'summary': event_summary,
        'start': {
            'dateTime': start_time,
            'timeZone': 'YourTimeZone',
        },
        'end': {
            'dateTime': end_time,
            'timeZone': 'YourTimeZone',
        },
    }

    event = service.events().insert(calendarId='primary', body=event).execute()
    print('Event created: %s' % (event.get('htmlLink')))

def main():
    # Calculate Visual Studio Code active time
    active_time = calculate_vscode_active_time()

    # Authorize with Google Calendar API
    service = authorize_google_calendar()

    # Add event to Google Calendar
    start_time = datetime.datetime.now().isoformat()
    end_time = (datetime.datetime.now() + active_time).isoformat()
    add_event_to_calendar(service, "Visual Studio Code Usage", start_time, end_time)

if __name__ == "__main__":
    main()
