# Multithreading Performance Analysis

### Project Objectives

Welcome to the project repository for the LINFO1252 course at UCLouvain, part of the Civil Engineering program in the field of computer science.
The primary goal of the project was to analyze the performance of multithreaded solutions to three classical problems (the `Reader-Writer` problem, the `Dining Philosophers` problem, and the `Producer-Consumer` problem), shedding light on the effectiveness and efficiency of different synchronization mechanisms. The three chosen problems are recognized challenges in concurrent programming, serving as benchmarks for evaluating the performance of synchronization primitives.

### Project Details
- **Grade and Feedback:** 20/20, with comments on Makefile and presentation.
- **Course:** LINFO1252, UCLouvain Engineering program, Computer Science track.

## Feedback
The Makefile was functional but could have been simplified, the presentation lacked clarity in comparison graphs, and the analysis suggested more depth, especially regarding the expected curves and the plateau effect in reader/writer scenarios.

### Synchronization Mechanisms

The project leveraged various synchronization primitives, including:

- **Test and Set (TS):** A synchronization technique where a processor tests a memory location and sets it to a value if specific conditions are met. TS was applied to enhance synchronization in critical sections of the multithreaded programs.

- **Test and Test and Set (TTS):** An extension of TS, involving an additional test before the set operation. This approach helps mitigate bus contention and was strategically utilized in specific scenarios within the project.

- **Backoff Test and Test and Set (BTTS):** A variant of TTS incorporating a backoff mechanism. In cases of contention, a thread delays its reattempt briefly, minimizing contention and optimizing efficiency in scenarios where TTS was applied.

- **POSIX (Portable Operating System Interface):** A family of standards ensuring compatibility between operating systems. In the project, POSIX synchronization primitives, such as pthread_mutex, pthread_rwlock, and semaphores, played a pivotal role in achieving thread safety and coordination.

## Structure

- **Scripts:**
  - `script_bash`: Contains Bash scripts used for performance analysis of the three well-known problems.
  - `script_python`: Includes scripts for creating comparison graphs using Matplotlib.
  - `script_c`: Houses all C programs ([details in this section](#c-code)).

- **Project Documents:**
  - `P1-Guidelines.pdf`: Assignment guidelines.
  - `P1-Report.pdf`: Project report.

- **Version Control:**
  - `.gitignore`: Specifies files to be ignored in the GitHub repository.

- **Project Management:**
  - `Makefile`: Automates build, run, and other project commands ([details in this section](#makefile-commands)).

- **Results and Visualization:**
  - `graphs`: Contains comparison graphs in PNG and PDF formats.
  - `csv_files`: Stores CSV files with performance analysis results.

## C Code

- **Mutex and Semaphores:**
  - `my_mutex.c`: Implementation of custom mutex.
  - `my_sem.c`: Implementation of custom semaphore.
  - `user_defined_sync.c`: Program defining mutexes and semaphores based on user input.
  - `main_my_mutex.c`: Program analyzing the overhead of wait primitives (custom mutex).

- **Three Well-Known Problems:**
  - `reader_writer.c`: Reader-writer problem with user-defined sync primitives.
  - `philosopher.c`: Dining philosophers problem with user-defined sync primitives.
  - `producer_consumer.c`: Producer-consumer problem with user-defined sync primitives.

## Makefile Commands

- `make build`: Build the project.
- `make run_all`: Run all programs.
- `make csv`: Generate CSV files with performance results.
- `make plot`: Create comparison graphs.
- `make clean`: Clean generated files for a specific program.
- `make clean_all`: Clean all generated files.

For the run commands in the Makefile, you can specify the number of threads using the option NB_THREADS=N, where N represents the desired number of threads (the default value is 1). Additionally, you can launch the programs with any synchronization mechanism by using examples such as run_philosopher_POSIX, run_philosopher_BTTS,...

## Contributions

Contributions, feedback, and suggestions are welcomed. Feel free to share your thoughts and improvements.

---
*This project is a part of the LINFO1252 course at UCLouvain in the Civil Engineering program, focusing on computer science.*