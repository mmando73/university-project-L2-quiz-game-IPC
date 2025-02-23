# 📖 Quiz Game with IPC and Ncurses

A **quiz game** implemented in C, utilizing **Inter-Process Communication (IPC)** through **pipes and shared memory**, with an ncurses-based UI for better interaction.

### 🚀 Features
- **Randomized quiz questions** (stored in `questions.txt`)
- **Inter-Process Communication (IPC)**
    - **Pipes** for communication between parent and child processes
    - **Shared memory** for storing and updating scores
- **Ncurses-based UI** for improved terminal interaction
- **Command-line options** (`-a`, `-q`, `-h`, etc.) for customization
- **Dynamic answer choices (2 to 4 options per question)**
- **Automated win/loss handling** using external programs (`success` & `failure`)
- **Makefile** for easy compilation

---

### 🛠️ Installation
Before compiling, ensure you have **ncurses** installed.

On **Debian/Ubuntu**:

```
sudo apt-get install libncurses5-dev libncursesw5-dev
```

On **Fedora**:

```
sudo dnf install ncurses-devel
```

On Arch Linux:
```
sudo pacman -S ncurses
```

---

### 🏗️ Compilation
Use the provided **Makefile** to build the project:

```
make
```
This will generate three executables:

- `quiz` (Main quiz game)
- `success` (Victory message)
- `failure` (Loss message)

---

### 🎮 Usage

Run the quiz game:
```
./quiz
```

### Available Options

| Option | Long Version | Description |
| :----- | :----------- | :-----------|
| `-h` | `--help` | Display help message |
| `-r` | `--rules`	| Show game rules |
| `-s` | `--student` | Display author(s) of the project |
| `-a N`| `--answers N` |Set the number of answer choices (Default: 2, Max: 4)|
| `-q N`| `--questions N` | Set the number of questions in the quiz (Default: 4, Max: 10)| 

Example:
```
./quiz -a 3 -q 5
```
This starts a quiz with **3 answer choices per question** and **5 total questions**.

---

### 📜 Game Rules
1. The game asks **random quiz questions** from `questions.txt`.
2. The player selects an answer by **typing the corresponding letter** (A, B, C, or D).
3. The **parent process** displays the questions, while the **child process** checks the answers and updates the score.
4. At the end, the program **calculates the score** and determines:
    - **Win** if score is **≥ 50%** (`success` program runs).
    - **Loss** if score is **< 50%** (`failure` program runs).

---
### 📂 Project Structure
<pre>
quiz-game/
│
├── src/
│   ├── main.c          # Main game logic (parent process)
│   ├── game.c/.h       # Game mechanics (answer checking, score updating)
│   ├── ipc.c/.h        # Inter-process communication (pipes & shared memory)
│   ├── options.c/.h    # Command-line arguments parsing
│   ├── questions.c/.h  # Question loading & random selection
│   ├── ui.c/.h         # Ncurses-based UI
│   ├── questions.txt   # Quiz database
|
├── externals/
│   ├── success.c       # Displays win message
│   ├── failure.c       # Displays loss message
│
├── include/
│   ├── quiz.h          # Common headers
│
├── Makefile            # Build automation
└── README.md           # Project documentation
</pre>
---

### 🛠️ Technical Details
- **Processes**: The parent process **displays the quiz**, while the child **handles logic** and **updates scores**.
- **IPC Mechanisms**:
    - **Pipes**: Used for communication between parent & child processes.
    - **Shared Memory (shm)**: Used for real-time score updates.
- **Ncurses UI**: Provides a cleaner text-based interface for user interaction.

---

### 📜 License
This project is open-source and free to use. Feel free to modify or extend it. 🚀