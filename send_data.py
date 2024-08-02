import firebase_admin
from firebase_admin import credentials, db
import random
import time

# Initialize Firebase with the service account key
cred = credentials.Certificate('smart-agriculture-system-191b4-firebase-adminsdk-a11tn-a1be86a11a.json')  # Replace with your actual path
firebase_admin.initialize_app(cred, {
    'databaseURL': 'https://smart-agriculture-system-191b4-default-rtdb.firebaseio.com/'  # Replace with your actual database URL
})

# Get a reference to the database service
ref = db.reference('sensor_data')

# Function to send dummy data to the database
def send_dummy_data():
    dummy_data = {
        'temperature': round(random.uniform(20.0, 30.0), 2),
        'humidity': round(random.uniform(40.0, 60.0), 2),
        'soilMoisture': round(random.uniform(30.0, 50.0), 2)
    }

    # Push the dummy data to the 'sensor_data' node
    ref.push(dummy_data)

# Send dummy data every 5 seconds (adjust as needed)
while True:
    send_dummy_data()
    time.sleep(60)
