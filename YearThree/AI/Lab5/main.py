import streamlit as st
from temperature import Temperature
from wind import Wind
from humidity import Humidity


def ApplyRules(temp, hum, wind):
    temp_high = Temperature.Max(temp)
    temp_med = Temperature.Medium(temp)
    temp_low = Temperature.Min(temp)

    hum_high = Humidity.Max(hum)
    hum_med = Humidity.Medium(hum)
    hum_low = Humidity.Min(hum)

    wind_high = Wind.Max(wind)
    wind_med = Wind.Medium(wind)
    wind_low = Wind.Min(wind)

    short_rule = max(min(temp_high, hum_low), min(wind_high, hum_low))
    medium_rule = min(temp_med, hum_med)
    long_rule = max(min(temp_low, hum_high), min(temp_med, hum_high), min(temp_low, hum_med))

    return short_rule, medium_rule, long_rule


def AppRun():
    st.title("Laboratory Work 5")

    temperature = st.slider("Choose temperature (°C)", 0, 35, 20)

    st.write(f"Chosen temperature: {temperature} °C")
    st.write(f"Temperature Min membership: {Temperature.Min(temperature)}")
    st.write(f"Temperature Medium membership: {Temperature.Medium(temperature)}")
    st.write(f"Temperature Max membership: {Temperature.Max(temperature)}")

    humidity = st.slider("Choose humidity (%)", 0, 100, 50)
    
    st.write(f"Chosen humidity: {humidity} %")
    st.write(f"Humidity Min membership: {Humidity.Min(humidity)}")
    st.write(f"Humidity Medium membership: {Humidity.Medium(humidity)}")
    st.write(f"Humidity Max membership: {Humidity.Max(humidity)}")

    windSpeed = st.slider("Choose wind speed (km/h)", 0, 50, 10)

    st.write(f"Chosen wind speed: {windSpeed} km/h")
    st.write(f"Wind speed Min membership: {Wind.Min(windSpeed)}")
    st.write(f"Wind speed Medium membership: {Wind.Medium(windSpeed)}")
    st.write(f"Wind speed Max membership: {Wind.Max(windSpeed)}")
    
AppRun()