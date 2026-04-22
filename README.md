# 🍈 OS Jackfruit --- Multi-Container Runtime (Detailed README)

## 👥 Team

-   Vishnu Maddirala (PES2UG24CS593)
-   Vedant Srivastava (PES2UG24CS578)

------------------------------------------------------------------------

## 📌 Overview

OS Jackfruit is a mini container runtime built in C that demonstrates
core Operating System concepts such as: - Process management -
Inter-process communication (IPC) - Synchronization
(Producer-Consumer) - Kernel module interaction - CPU scheduling

------------------------------------------------------------------------

# 🚀 HOW TO RUN (STEP-BY-STEP)

``` bash
make
./supervisor
```

### Start Containers

``` bash
./engine start alpha ./cpu_hog --soft-mib 48 --hard-mib 80
./engine start beta ./cpu_hog --soft-mib 64 --hard-mib 96
```

### View Running Containers

``` bash
./engine ps
```

### View Logs

``` bash
./engine logs alpha
```

------------------------------------------------------------------------

# 📸 TASK-WISE EXPLANATION

------------------------------------------------------------------------

## 🔹 1. Multi-Container Supervision

### 📌 What it does:

-   Runs multiple containers under ONE supervisor process
-   Each container is a child process

### 🧠 Concept:

-   fork()
-   process hierarchy

### 💻 Command:

``` bash
./engine start alpha ./cpu_hog
./engine start beta ./cpu_hog
```

### ✅ Expected Output:

-   Both containers appear running simultaneously

------------------------------------------------------------------------

## 🔹 2. Metadata Tracking

### 📌 What it does:

Tracks: - Container ID - PID - STATE (RUNNING / EXITED) - START TIME -
LOG FILE

### 🧠 Concept:

-   Data structures + process tracking

### 💻 Command:

``` bash
./engine ps
```

### ✅ Output Example:

    ID     PID    STATE     STARTED   LOG
    alpha  3619   RUNNING   11:26     logs/alpha.log

------------------------------------------------------------------------

## 🔹 3. Bounded Buffer Logging

### 📌 What it does:

-   Captures container output
-   Uses Producer-Consumer model

### 🧠 Concept:

-   Threads
-   Mutex + condition variables

### Flow:

Container → Producer → Buffer → Consumer → Log File

### 💻 Command:

``` bash
./engine logs alpha
cat logs/alpha.log
```

------------------------------------------------------------------------

## 🔹 4. CLI & IPC (UNIX Socket)

### 📌 What it does:

-   CLI communicates with supervisor using socket

### 🧠 Concept:

-   UNIX domain sockets

### 💻 Command:

``` bash
./engine logs alpha
```

### 📍 Socket Path:

    /tmp/mini_runtime.sock

------------------------------------------------------------------------

## 🔹 5. Soft Limit Warning (Kernel Module)

### 📌 What it does:

-   Warns when memory exceeds soft limit

### 🧠 Concept:

-   Kernel module
-   RSS tracking

### 💻 Command:

``` bash
dmesg | grep SOFT
```

### ✅ Output:

    SOFT LIMIT: container=memtest rss exceeded

------------------------------------------------------------------------

## 🔹 6. Hard Limit Enforcement

### 📌 What it does:

-   Kills container if memory exceeds hard limit

### 🧠 Concept:

-   Signals (SIGKILL)
-   Kernel enforcement

### 💻 Command:

``` bash
dmesg | grep HARD
```

### ✅ Output:

    HARD LIMIT: container killed

------------------------------------------------------------------------

## 🔹 7. Scheduling Experiment

### 📌 What it does:

-   Shows effect of priority on CPU usage

### 🧠 Concept:

-   CFS Scheduler
-   nice values

### 💻 Command:

``` bash
./engine start highpri ./cpu_hog --nice -10
./engine start lowpri ./cpu_hog --nice 10
```

### ✅ Result:

-   highpri runs faster than lowpri

------------------------------------------------------------------------

## 🔹 8. Clean Teardown

### 📌 What it does:

-   Proper shutdown of system

### 🧠 Concept:

-   wait()
-   thread join
-   resource cleanup

### 💻 Command:

``` bash
CTRL + C
```

### ✅ Output:

    [supervisor] Shutting down...
    [supervisor] Exited cleanly.

------------------------------------------------------------------------

## 📂 Project Structure

    OS-Jackfruit/
    ├── engine.c
    ├── supervisor.c
    ├── logging.c
    ├── metadata.c
    ├── ipc.c
    ├── monitor.c
    ├── cpu_hog.c
    ├── memtest.c
    ├── logs/
    └── Makefile

------------------------------------------------------------------------

## 🎯 Conclusion

This project successfully demonstrates a working mini container runtime
integrating user-space and kernel-space components.
