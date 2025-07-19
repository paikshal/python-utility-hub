from twilio.rest import Client
import os
from dotenv import load_dotenv

# Load Twilio credentials from .env file
load_dotenv()

# Twilio credentials
account_sid = ("your_account_sid_here")  # Replace with your actual Account SID
auth_token = ("your_auth_token_here")  # Replace with your actual Auth Token
twilio_number = ("+1234567890")  # Replace with your Twilio number

# Function to send SMS
def send_sms(to_number, message):
    client = Client(account_sid, auth_token)
    message = client.messages.create(
        body=message,
        from_=twilio_number,
        to=to_number
    )
    print(f"Message sent! SID: {message.sid}")

# Example usage
if __name__ == "__main__":
    to = "+91 "  # Replace with the target number
    msg = "Hello from Twilio SMS via Python 🚀"
    send_sms(to, msg)
