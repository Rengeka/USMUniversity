def CheckDependency(dependency: str):
    try:
        module = __import__(dependency) 
        return module
    except ImportError:
        print(f"Dependency '{dependency}' not found. Installing...")
        os.system(f"{sys.executable} -m pip install {dependency}")
        module = __import__(dependency)  
        return module
    
CheckDependency("sys")
CheckDependency("json")
CheckDependency("requests")
CheckDependency("os")
CheckDependency("datetime")

import sys
import requests
import os
import json
from datetime import datetime

API_KEY = "123456abcdef"

cur1 = sys.argv[1]
cur2 = sys.argv[2]
date = sys.argv[3]

url = f"http://localhost:8080/?from={cur1}&to={cur2}&date={date}"
body = {"key": API_KEY}

try:
    response = requests.post(url, data=body)
    response.raise_for_status()  
    response_json = response.json()  

except requests.RequestException as e:
    error_msg = f"{datetime.now()} - HTTP error: {e}"
    print("Error:", error_msg)
    
    with open("error.log", "a", encoding="utf-8") as log_file:
        log_file.write(error_msg + "\n")
    sys.exit(1)

except json.JSONDecodeError:
    error_msg = f"{datetime.now()} - Invalid JSON response"
    print("Error:", error_msg)

    with open("error.log", "a", encoding="utf-8") as log_file:
        log_file.write(error_msg + "\n")
    sys.exit(1)

if response_json.get("error"):
    error_msg = f"{datetime.now()} - API error: {response_json['error']}"
    print("Error:", error_msg)

    with open("error.log", "a", encoding="utf-8") as log_file:
        log_file.write(error_msg + "\n")

else:
    output = response_json.get("data", [])
    os.makedirs("data", exist_ok=True)

    filename = f"data/{cur1}_{cur2}_{date}.json"

    with open(filename, "w", encoding="utf-8") as f:
        json.dump(output, f, ensure_ascii=False, indent=4)

    print(f"Request: from={cur1}, to={cur2}, date={date}")
    print("Response:", output)
    print(f"Saved to file: {filename}")