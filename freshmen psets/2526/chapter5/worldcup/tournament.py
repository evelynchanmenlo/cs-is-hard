# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 1000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    teams = []
    # Read teams into memory from file
    # opens a file whose name is given at the command line
    with open(sys.argv[1]) as file:
        # creates a reader object to read the contents of the file as a dictionary
        reader = csv.DictReader(file)
        # iterates over each row in the CSV
        for row in reader:
            # creates a dictionary with the team name and the rating and adds it to the teams list
            teams.append({"team": row["team"], "rating": int(row["rating"])})

    counts = {}
    # Simulate N tournaments and keep track of win counts
    for i in range(N):
        # store the result into a variable so you can use the winning team's name
        winner = simulate_tournament(teams)
        # if the team has already won a game before, add one more to their win count
        if winner in counts:
            counts[winner] += 1
        # if this is their first win, then track their frist win
        else:
            counts[winner] = 1

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    # """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    # """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


def simulate_tournament(teams):
    # """Simulate a tournament. Return name of winning team."""
    # iterate until there is one winner left
    while (len(teams) > 1):
        teams = simulate_round(teams)
    # return name of winning team
    return teams[0]["team"]


if __name__ == "__main__":
    main()
