import smtplib
from email.message import EmailMessage
import os
from dotenv import load_dotenv

# Load environment variables
load_dotenv()

EMAIL_ADDRESS = os.getenv("EMAIL_USER")
EMAIL_PASSWORD = os.getenv("EMAIL_PASS")

def send_email(to_email, subject, body):
    msg = EmailMessage()
    msg['From'] = EMAIL_ADDRESS
    msg['To'] = to_email
    msg['Subject'] = subject
    msg.set_content(body)

    with smtplib.SMTP_SSL('smtp.gmail.com', 465) as smtp:
        smtp.login(EMAIL_ADDRESS, EMAIL_PASSWORD)
        smtp.send_message(msg)

    print(f"✅ Email sent to {to_email}")

# Example usage
if __name__ == "__main__":
    send_email(
        to_email="your@gmail.com",  # Replace with real email
        subject="Hello from Python",
        body="This email was sent using Python's smtplib and Gmail SMTP!"
    )
