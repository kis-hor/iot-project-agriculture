import os
import matplotlib.pyplot as plt
from firebase_admin import credentials, db, initialize_app
import mpld3

# Initialize Firebase
cred = credentials.Certificate('smart-agriculture-system-191b4-firebase-adminsdk-a11tn-a1be86a11a.json')
initialize_app(cred, {'databaseURL': 'https://smart-agriculture-system-191b4-default-rtdb.firebaseio.com/'})

# Reference to the database
ref = db.reference('sensor_data')

# Fetch data
data = ref.get()

# Extract values for temperature, humidity, and soil moisture
temperature_values = [entry['temperature'] for entry in data.values()]
humidity_values = [entry['humidity'] for entry in data.values()]
soil_moisture_values = [entry['soilMoisture'] for entry in data.values()]

# Create a "plots" folder if it doesn't exist
if not os.path.exists("templates"):
    os.makedirs("templates")

# Plotting Temperature
plt.plot(temperature_values, label='Temperature (°C)')
plt.title('Temperature Over Time')
plt.xlabel('Time')
plt.ylabel('Temperature (°C)')
temperature_plot = mpld3.fig_to_html(plt.gcf())

# Save Temperature Plot in "plots" folder as JPG
plt.savefig('static/plots/temperature_plot.jpg')
plt.close()

# Plotting Humidity
plt.plot(humidity_values, label='Humidity (%)')
plt.title('Humidity Over Time')
plt.xlabel('Time')
plt.ylabel('Humidity (%)')
humidity_plot = mpld3.fig_to_html(plt.gcf())

# Save Humidity Plot in "plots" folder as JPG
plt.savefig('static/plots/humidity_plot.jpg')
plt.close()

# Plotting Soil Moisture
plt.plot(soil_moisture_values, label='Soil Moisture (%)')
plt.title('Soil Moisture Over Time')
plt.xlabel('Time')
plt.ylabel('Soil Moisture (%)')
soil_moisture_plot = mpld3.fig_to_html(plt.gcf())

# Save Soil Moisture Plot in "plots" folder as JPG
plt.savefig('static/plots/soil_moisture_plot.jpg')
plt.close()
