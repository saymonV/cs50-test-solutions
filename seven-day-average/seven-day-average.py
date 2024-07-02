import csv
import requests



def main():
    # Read NYTimes Covid Database
    download = requests.get(
        "https://raw.githubusercontent.com/nytimes/covid-19-data/master/us-states.csv"
    )
    decoded_content = download.content.decode("utf-8")
    file = decoded_content.splitlines()
    reader = csv.DictReader(file)


    # Construct 14 day liscts of new cases for each states
    new_cases = calculate(reader)

    # Create a list to store selected states
    states = []
    print("Choose one or more states to view average COVID cases.")
    print("Press enter when done.\n")

    while True:
        state = input("State: ")
        if state in new_cases:
            states.append(state)
        if len(state) == 0:
            break

    print(f"\nSeven-Day Averages")

    # Print out 7-day averages for this week vs last week
    comparative_averages(new_cases, states)


# TODO: Create a dictionary to store 14 most recent days of new cases by state
def calculate(reader):
    new_cases = dict()
    previous_cases = dict()
    for i in reader:
        state = i["state"]
        cur_cases = int(i["cases"])
        print(f"{cur_cases}")

        if state not in previous_cases:
            previous_cases[state] = cur_cases
            new_cases[state] = [0]
        else:
            previous_cases[state] = cur_cases

        new_cases[state].append()

            if len(new_cases[state]) > 14:
                ...


    return new_cases

# TODO: Calculate and print out seven day average for given state
def comparative_averages(new_cases, states):
    return 0



main()
