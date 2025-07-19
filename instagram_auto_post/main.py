from instagrapi import Client

# Login credentials
USERNAME = "your_username"
PASSWORD = "your_password"

def post_image(image_path, caption):
    cl = Client()
    cl.login(USERNAME, PASSWORD)
    media = cl.photo_upload(image_path, caption)
    print(f"✅ Posted to Instagram: {media.dict().get('pk')}")

# Example usage
if __name__ == "__main__":
    image = "sample.jpg"  # Replace with your image file
    caption = "🚀 Auto-posted from Python using instagrapi!"
    post_image(image, caption)
