# Baccarat Simulator

A terminal-based Baccarat casino game built in C++17.

## Features

- Full baccarat rules with third-card drawing logic
- 8-deck shoe with 75% penetration and automatic reshuffle
- Player, Banker, and Tie bets with correct payouts (1:1, 0.95:1, 8:1)
- Push on tie when betting Player or Banker
- Casino-style Big Road scoreboard with colored markers
- Bead Plate history grid
- Session statistics: win rates, streaks, naturals, pairs, profit/loss
- ANSI-colored terminal UI with box-drawing characters
- Natural and pair detection
- Balance management with min/max bet limits

## Build

```
cmake -B build
cmake --build build
./build/baccarat
```

## Architecture

- `Card` — rank, suit, baccarat value
- `Deck` — multi-deck shoe with shuffle and penetration
- `BaccaratGame` — game engine with third-card rules
- `Player` — balance and bet management
- `Scoreboard` — Big Road and Bead Plate
- `Statistics` — session tracking
- `Display` — all terminal rendering
