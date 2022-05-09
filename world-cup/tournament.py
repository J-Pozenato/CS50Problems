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

    filename = sys.argv[1]
    teams = []
    # TODO: Read teams into memory from file
    with open(filename, newline='') as csvfile:
        reader = csv.DictReader(csvfile)

        for team in reader:
            #     READER TEST
            #     print(row['team'], row['rating'])
            #     print(int(row['rating']) * 2)
            team['rating'] = int(team['rating'])
            teams.append(team)

    counts = {}
    # TODO: Simulate N tournaments and keep track of win counts
    for i in range(N):
        twinner = simulate_tournament(teams)
        if twinner in counts:  # if the team is already in the counts just increase the count of wins
            counts[twinner] += 1
        else:  # if it is not give it a win count of 1
            counts[twinner] = 1

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    # TODO
    winners = teams
    # simulate each round until there is only one team left in the tournament
    while len(winners) > 1:
        winners = simulate_round(winners)

    winner = winners[0]['team']
    return winner


if __name__ == "__main__":
    main()
