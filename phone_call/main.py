from twilio.rest import Client
import os
from dotenv import load_dotenv

# Load environment variables
load_dotenv()

# Twilio credentials
account_sid = ("  ")
auth_token = ("  ")
twilio_number = ("+14155238886")  # Replace with your Twilio number

# Function to make call
def make_call(to_number, message_url="http://demo.twilio.com/docs/voice.xml"):
    client = Client(account_sid, auth_token)
    
    call = client.calls.create(
        to=to_number,
        from_=twilio_number,
        url=message_url  # This XML file defines what Twilio says
    )
    print(f"Call initiated! SID: {call.sid}")

# Example usage
if __name__ == "__main__":
    to = "+91  "  # Replace with real number
    make_call(to)
