<h1 align="center">Philosophers</h1>
<h3 align="center">42Paris School Project</h3>

<p align="center">
  <img src="https://img.shields.io/badge/Language-C-blue.svg" alt="Language">
  <img src="https://img.shields.io/badge/Status-Completed-brightgreen.svg" alt="Status">
</p>

## About the Project

`Philosophers` is a simulation of the dining philosophers problem, demonstrating synchronization in concurrent systems. Developed as part of the 42Paris curriculum, this project explores thread/process management and resource allocation using mutexes (mandatory) and semaphores (bonus). The goal is to prevent deadlocks while ensuring no philosopher starves.

## Features

- **Mandatory Part (Threads/Mutexes)**:
  - Thread-based philosophers with individual mutexes for forks.
  - Real-time status logging (eating, sleeping, thinking, death).
  - Configurable parameters: philosophers count, timings, meal goals.
  - Death detection within 10ms accuracy.

- **Bonus Part (Processes/Semaphores)**:
  - Process-based philosophers with central fork semaphores.
  - Shared memory synchronization via named semaphores.
  - Optional meal limit for automated simulation termination.

- **Error Handling**:
  - Validates input arguments (integers, overflow, formatting).
  - Graceful cleanup on exit (destroy mutexes/semaphores, free memory).

## Technical Details

- **Mandatory**:
  - **Language**: C
  - **Libraries**: `pthread`, `sys/time`
  - **Synchronization**: Mutexes for forks, global writing mutex

- **Bonus**:
  - **IPC**: Semaphores (`sem_open`, `sem_wait`, `sem_post`)
  - **Process Management**: `fork`, `kill`, `waitpid`
  - **Concurrency**: Monitor threads for death/meal tracking

## Getting Started

### Prerequisites

- C compiler (`gcc`)
- GNU Make

### Installation

1. Clone the repository:
   ```sh
   git clone https://github.com/<your-username>/philosophers.git
   cd philosophers
   ```

2. Compile both parts:
   ```sh
   # Mandatory
   cd philo && make
   # Bonus
   cd ../philo_bonus && make
   ```

### Usage

**Mandatory (Threads)**:
```sh
./philo/philo 5 800 200 200 7   # 5 philosophers, die after 800ms, eat 7 times
```

**Bonus (Processes)**:
```sh
./philo_bonus/philo_bonus 4 410 200 200   # 4 philosophers, no meal limit
```

**Arguments**:
1. `number_of_philosophers`  
2. `time_to_die` (ms)  
3. `time_to_eat` (ms)  
4. `time_to_sleep` (ms)  
5. `[meal_goal]` (optional)  

## Project Structure

```
philosophers/
├── philo/               # Mandatory (threads/mutexes)
│   ├── srcs/            # Source files
│   │   ├── eating.c     # Fork acquisition logic
│   │   ├── init.c       # Philosopher/mutex initialization
│   │   └── philo.c      # Simulation core
│   └── Makefile
└── philo_bonus/         # Bonus (processes/semaphores)
    ├── srcs/
    │   ├── free.c       # Resource cleanup
    │   ├── init.c       # Semaphore setup
    │   └── philo.c      # Process management
    └── Makefile
```

## Key Components

- **Death Monitor**: Checks philosopher last-meal times continuously.
- **Synchronization**:
  - *Mutexes*: Protect fork access and stdout writing (mandatory).
  - *Semaphores*: Manage fork availability and process communication (bonus).
- **Meal Counter**: Tracks meals per philosopher; stops simulation if goal met.

## Acknowledgements

Developed as part of the 42Paris curriculum. Special thanks to:
- 42 Network for pthread/semaphore documentation.
- Edsger Dijkstra for the original dining philosophers problem.
- Peer algorithms for deadlock avoidance strategies.

---

<p align="left">
  <a href="https://www.linkedin.com/in/your-profile" target="blank">
    <img align="center" src="https://raw.githubusercontent.com/rahuldkjain/github-profile-readme-generator/master/src/images/icons/Social/linked-in-alt.svg" alt="Your Name" height="30" width="40" />
  </a>
</p>
