# 🎮 LAN Party Tournament Manager

A C implementation of a tournament management system using core data structures: **linked lists**, **queues**, **stacks**, and **binary search trees**.

Built as part of a Data Structures course assignment.

---

## 📋 Overview

The Liga Studenților organizes a LAN Party tournament where teams compete in a bracket-style format. This program automates team selection, match generation, round progression, and final ranking.

---

## 🗂️ Project Structure

```
sd_tema/
├── main.c          # Entry point and task dispatcher
├── task2.h         # Queue & stack logic (tournament rounds)
├── task3.h         # BST logic (final ranking)
├── common.h        # Shared structs (Player, Team)
├── Makefile        # Build & clean rules
├── checker.sh      # Automated test runner
├── date/           # Input test files (t1–t10)
│   └── tN/
│       ├── c.in    # Task number
│       └── d.in    # Input data
├── rezultate/      # Reference output files
└── out/            # Generated output (created at runtime)
```

---

## ⚙️ How to Build & Run

### Build
```bash
make build
```

### Run on a specific test
```bash
./lanParty ./date/t1/c.in ./date/t1/d.in ./out/out1.out
```

### Run the automated checker
```bash
bash checker.sh
```

### Clean
```bash
make clean
```

---

## 🧩 Tasks

### Task 1 — Team Selection (Linked List)
- Reads all registered teams from `d.in`
- Each team's score = arithmetic mean of its players' experience points
- Eliminates the lowest-scoring teams until the count is the nearest power of 2
- Outputs the surviving teams in list order

### Task 2 — Tournament Rounds (Queue + Stack)
- Pairs teams into matches using a **queue** (FIFO)
- Winners are pushed onto a **stack** and their players' scores are incremented
- Stack is popped back into the queue for the next round
- Tracks the top 8 teams and continues until a champion is found
- Outputs queue and stack contents after each round

### Task 3 — Final Ranking (Binary Search Tree)
- Inserts the top 8 teams into a **BST**, ordered by score (ties broken by name, descending)
- Performs a reverse in-order traversal to output rankings from highest to lowest

---

## 📦 Input Format

```
3
5 Local Area Name
Paul Ploiesteanu 3
Mircea Muresanu 2
...
```

- First line: number of teams
- For each team: `<player_count> <team_name>`, followed by `<last_name> <first_name> <score>` per player

---

## ✅ Example

**Input:**
```
3
5 Local Area Name
...
4 Unusual Suspects
...
5 Lando Nowins
...
```

**Output (Task 1):**
```
Unusual Suspects
Lando Nowins
```

---

## 🛠️ Data Structures Used

| Structure | Used in | Purpose |
|-----------|---------|---------|
| Linked List | Task 1 | Store and filter registered teams |
| Queue | Task 2 | Schedule matches in order |
| Stack | Task 2 | Collect round winners |
| BST | Task 3 | Rank top 8 teams by score |

---

## 📌 Notes

- The checker compares output character-by-character against reference files in `rezultate/`
- Do not modify the directory structure — the checker depends on it
- The executable must be named `lanParty`
