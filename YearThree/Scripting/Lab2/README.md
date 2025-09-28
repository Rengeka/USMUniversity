# Currency Exchange Rate Script

This Python script allows you to query currency exchange rates from a local API service and save the results in JSON format. It also handles errors and logs them to a file.

---

## Installation

1. Make sure you have **Python 3.7+** installed.
2. The script automatically checks and installs required dependencies if they are missing.
3. Optionally, you can manually install dependencies with:

```bash
pip install sys
pip install datetime
pip install requests
pip install json
pip install os
```

## Usage

Run the script from the command line with the following syntax:

```bash
python currency_exchange_rate.py <FROM_CURRENCY> <TO_CURRENCY> <DATE>
```

Example:
```bash
python currency_exchange_rate.py USD EUR 2025-02-01
```

The script will send a request to the local API:
```http://localhost:8080/?from=USD&to=EUR&date=2025-02-01```

The response will be saved as a JSON file in the ```data/``` folder with a filename like ```USD_EUR_2025-02-01.json```.

Any errors will be logged in ```error.log```.

## Script Structure

Dependency Check (CheckDependency)

    Ensures required modules (requests, sys, os, json, datetime) are installed.

    Installs missing dependencies automatically using pip.

Command-line Arguments

    The script takes three arguments: from-currency, to-currency, and date.

HTTP Request

    Sends a POST request to the local currency exchange service with the API key.

    Receives JSON data containing the exchange rate or an error message.

Error Handling

    Handles HTTP errors (network issues, server errors) and invalid JSON responses.

    Logs all errors to `error.log