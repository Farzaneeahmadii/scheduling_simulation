# 🖥️ CPU Scheduling Simulation

This project simulates three fundamental CPU scheduling algorithms:

- **First Come First Serve (FCFS)**
- **Shortest Job First (SJF)**
- **Round Robin (RR)**

It calculates and prints evaluation metrics such as:

- **Average Turnaround Time**
- **Average Waiting Time**
- **Average Response Time**

---

## 📂 Files

| File Name         | Description                              |
|------------------|------------------------------------------|
| `cpu_scheduling.c` | Main C program with all scheduling logic |
| `sample_input.txt`| Example input to test the program        |
| `sample_output.txt`| Sample output for the input              |
| `run_demo.sh`     | Shell script to compile and run easily   |

---

## 🛠️ How to Compile

You can compile the code using `gcc`:

```bash
gcc -o cpu_scheduler cpu_scheduling.c
