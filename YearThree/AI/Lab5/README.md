# **Laboratory Work №5 — Fuzzy Logic System (Clothes Drying Time)**

### **Mamdani Inference System**

---

## **1. Objective**

The purpose of this laboratory work is to study the principles of **fuzzy logic**, fuzzy sets, membership functions, rule-based inference, aggregation, and defuzzification.
As a practical case, we implement a fuzzy system for predicting **clothes drying time** based on the input parameters:

* Temperature (°C)
* Humidity (%)
* Wind Speed (km/h)

The system uses **Mamdani inference** and produces a crisp output: estimated drying time in hours.

---

## **2. Problem Description**

Drying time depends on multiple environmental factors that are not strictly linear and have smooth transitions.
Because of this, fuzzy logic is well-suited for the task.

### Input Variables

1. **Temperature**

   * Low
   * Medium
   * High

2. **Humidity**

   * Low
   * Medium
   * High

3. **Wind Speed**

   * Low
   * Medium
   * High

### Output Variable

**Dry Time (hours)**

* Short
* Medium
* Long

Each linguistic term is defined by its membership function (triangular/trapezoidal).

---

## **3. Membership Functions Implementation**

Membership functions are implemented in separate classes:

* `Temperature.Min/Medium/Max`
* `Humidity.Min/Medium/Max`
* `Wind.Min/Medium/Max`
* `DryTime.Short/Medium/Long`

Example use:

```python
Temperature.Medium(temp)
Humidity.Max(hum)
Wind.Min(wind)
```

Each function returns a value in the range **[0, 1]** — the degree of membership.

---

## **4. Inference Rules (Mamdani)**

Rules combine input fuzzy values using MIN and MAX operators.

Implemented rules:

### **Short drying time:**

* Temperature high AND Humidity low
* Wind high AND Humidity low

```python
short_rule = max(
    min(temp_high, hum_low),
    min(wind_high, hum_low)
)
```

### **Medium drying time:**

* Temp medium AND Humidity medium

```python
medium_rule = min(temp_med, hum_med)
```

### **Long drying time:**

* Temp low AND Humidity high
* Temp medium AND Humidity high
* Temp low AND Humidity medium

```python
long_rule = max(
    min(temp_low, hum_high),
    min(temp_med, hum_high),
    min(temp_low, hum_med)
)
```

The result of each rule is a fuzzy activation level for the output set.

---

## **5. Defuzzification (Centroid Method)**

After rule aggregation, the output membership functions are clipped, combined, and defuzzified.

Steps:

1. Compute membership values of Short, Medium, Long for the whole range `0–50 h`.
2. Aggregate them using MAX.
3. Apply weighted centroid:

```python
numerator = np.sum(x * aggregated)
denominator = np.sum(aggregated)
dry_time = numerator / denominator
```

If denominator = 0 → result is 0.

This produces a crisp drying time.

---

## **6. Graphical Visualization**

A 3D surface shows how drying time depends on:

* Temperature
* Humidity

Wind is fixed at 20 km/h.

```python
ax.plot_surface(T, H, Z, cmap='viridis')
```

Axes:

* X — Temperature
* Y — Humidity
* Z — Predicted Dry Time

This demonstrates the model's smooth transitions and fuzzy interactions.

---

## **7. Streamlit Application Structure**

The application provides:

* Sliders for Temperature, Humidity, Wind
* Membership values display
* Rule evaluation
* Defuzzification result
* Optional 3D surface plot

### Key function:

```python
short, medium, long = ApplyRules(temperature, humidity, windSpeed)
dry_time = Defuzzify(short, medium, long)
```

The app also outputs evaluations:

* `< 15 h` → fast drying
* `15–30 h` → moderate
* `> 30 h` → slow

---

## **8. Results**

The system produces realistic estimations of drying time based on environmental conditions.

Example:

| Temp (°C) | Hum (%) | Wind (km/h) | Dry Time |
| --------- | ------- | ----------- | -------- |
| 30        | 20      | 25          | ~8 h     |
| 15        | 60      | 10          | ~22 h    |
| 5         | 90      | 5           | ~40 h    |

The fuzzy system smoothly handles uncertain boundaries and combines all factors logically.

---

## **9. Conclusion**

During this laboratory work:

* Fuzzy logic concepts were studied (fuzzy sets, membership, inference rules)
* A full Mamdani system was implemented
* Defuzzification using centroid was applied
* A Streamlit interface was created
* Visualization of the output surface was performed

The resulting model successfully predicts drying time in a smooth, intuitive, and human-like manner — demonstrating the power of fuzzy logic for real-world continuous systems.

---