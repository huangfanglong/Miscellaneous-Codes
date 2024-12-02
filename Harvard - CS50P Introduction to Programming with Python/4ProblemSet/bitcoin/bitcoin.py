"""
Bitcoin Price Index
Bitcoin is a form of digital currency, otherwise known as cryptocurrency. Rather than rely on a central authority like a bank, Bitcoin instead relies on a distributed network, otherwise known as a blockchain, to record transactions.

Because there’s demand for Bitcoin (i.e., users want it), users are willing to buy it, as by exchanging one currency (e.g., USD) for Bitcoin.

In a file called bitcoin.py, implement a program that:

Expects the user to specify as a command-line argument the number of Bitcoins, 
, that they would like to buy. If that argument cannot be converted to a float, the program should exit via sys.exit with an error message.
Queries the API for the CoinDesk Bitcoin Price Index at https://api.coindesk.com/v1/bpi/currentprice.json, which returns a JSON object, among whose nested keys is the current price of Bitcoin as a float. Be sure to catch any exceptions, as with code like:
Outputs the current cost of n Bitcoins in USD to four decimal places, using , as a thousands separator.
"""
import requests
import sys

def main():

    # if len(sys.argv) < 2:
    #     sys.exit("Missing command-line argument")
    if len(sys.argv) > 2:
        sys.exit("Too many command-line arguments")

    try:
        user_input = float(sys.argv[1])                 # Converts arg to float, also make sure it is a valid numbers which include decimals else handled by except ValueError

        response = requests.get("https://api.coindesk.com/v1/bpi/currentprice.json")
        json_obj = response.json()

        rate = float(json_obj["bpi"]["USD"]["rate_float"])
        print(f"${rate * user_input:,.4f}")             # Add commas for every thousandth and limit to 4 decimal places

    except requests.RequestException:
        print("RequestException")
    except ValueError:
        print("Command-line argument is not a number")
    except IndexError:
        print("Missing command-line argument")

if __name__ == "__main__":
    main()