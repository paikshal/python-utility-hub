import pywhatkit as kit
import datetime

# WhatsApp pe message bhejna
def send_whatsapp_message(phone_number, message, delay_minutes=1):
    now = datetime.datetime.now()
    hour = now.hour
    minute = now.minute + delay_minutes

    print(f"Sending message to {phone_number} at {hour}:{minute}")
    kit.sendwhatmsg(phone_number, message, hour, minute)

# Example usage
if __name__ == "__main__":
    # Phone number with country code
    phone = "+91   "  # Replace with real number
    msg = "Hello from Python script!"
    send_whatsapp_message(phone, msg)
