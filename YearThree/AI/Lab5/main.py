import streamlit as st
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from temperature import Temperature
from wind import Wind
from humidity import Humidity
from dry import DryTime


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

    # Правила Мамдани
    short_rule = max(min(temp_high, hum_low), min(wind_high, hum_low))
    medium_rule = min(temp_med, hum_med)
    long_rule = max(min(temp_low, hum_high), min(temp_med, hum_high), min(temp_low, hum_med))

    return short_rule, medium_rule, long_rule


def Defuzzify(short, medium, long):
    x = np.linspace(0, 50, 100)
    short_membership = np.array([DryTime.Short(i) for i in x])
    medium_membership = np.array([DryTime.Medium(i) for i in x])
    long_membership = np.array([DryTime.Long(i) for i in x])

    aggregated = np.fmax(
        np.fmin(short, short_membership),
        np.fmax(np.fmin(medium, medium_membership),
                np.fmin(long, long_membership))
    )

    numerator = np.sum(x * aggregated)
    denominator = np.sum(aggregated)
    return numerator / denominator if denominator != 0 else 0


def PlotSurface():
    temps = np.linspace(0, 35, 10)
    hums = np.linspace(0, 100, 10)
    wind_fixed = 20  # фиксируем скорость ветра для 3D графика

    T, H = np.meshgrid(temps, hums)
    Z = np.zeros_like(T)

    for i in range(T.shape[0]):
        for j in range(T.shape[1]):
            s, m, l = ApplyRules(T[i, j], H[i, j], wind_fixed)
            Z[i, j] = Defuzzify(s, m, l)

    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    ax.plot_surface(T, H, Z, cmap='viridis')
    ax.set_xlabel("Temperature (°C)")
    ax.set_ylabel("Humidity (%)")
    ax.set_zlabel("Dry Time (h)")
    st.pyplot(fig)


def AppRun():
    st.title("🧺 Laboratory Work 5.3 — Predicting Clothes Drying Time")
    st.markdown("### Fuzzy Logic System (Mamdani Inference)")

    temperature = st.slider("Temperature (°C)", 0, 35, 20)
    humidity = st.slider("Humidity (%)", 0, 100, 50)
    windSpeed = st.slider("Wind Speed (km/h)", 0, 50, 10)

    # Показать степени принадлежности
    with st.expander("Membership values"):
        st.write(f"**Temperature:** Low={Temperature.Min(temperature):.2f}, "
                 f"Medium={Temperature.Medium(temperature):.2f}, "
                 f"High={Temperature.Max(temperature):.2f}")
        st.write(f"**Humidity:** Low={Humidity.Min(humidity):.2f}, "
                 f"Medium={Humidity.Medium(humidity):.2f}, "
                 f"High={Humidity.Max(humidity):.2f}")
        st.write(f"**Wind Speed:** Low={Wind.Min(windSpeed):.2f}, "
                 f"Medium={Wind.Medium(windSpeed):.2f}, "
                 f"High={Wind.Max(windSpeed):.2f}")

    # Применяем правила и дефаззифицируем
    short, medium, long = ApplyRules(temperature, humidity, windSpeed)
    dry_time = Defuzzify(short, medium, long)

    st.subheader(f"Predicted drying time: **{dry_time:.2f} hours**")

    if dry_time < 15:
        st.success("✅ Fast drying — great conditions!")
    elif dry_time < 30:
        st.info("🕐 Moderate drying speed.")
    else:
        st.warning("⚠️ Long drying time — consider increasing temperature or wind speed.")

    # Кнопка для отображения 3D графика
    if st.button("Show 3D Surface (Temp vs Humidity, Wind fixed at 20 km/h)"):
        PlotSurface()


if __name__ == "__main__":
    AppRun()
