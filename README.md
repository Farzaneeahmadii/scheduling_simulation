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
## sample input
 - 4
 - P1 0 6
 - P2 1 4
 - P3 2 9
 - P4 3 5
 - 3  --> quantom time

 - this works for all 3 algorithms

## sample output
===== FCFS Scheduling =====
- Order of execution: P1 P2 P3 P4

|process       | AT | BT | CT | TAT | WT | RT |
|--------------|----|----|----|-----|----|----|
|   p1         | 0  | 6  | 6  | 6   | 0  | 0  |
|   p2         | 1  | 4  | 10 | 9   | 5  | 5  |
|   p3         | 2  | 9  | 19 | 17  | 8  | 8  |
|   p4         | 3  | 5  | 24 | 21  | 16 | 16 |

- Average Turnaround Time: 13.25
- Average Waiting Time   : 7.25
- Average Response Time  : 7.25


===== SJF Scheduling =====
- Order of execution: P1 P2 P4 P3

|process       | AT | BT | CT | TAT | WT | RT |
|--------------|----|----|----|-----|----|----|
|  p1          | 0  | 6  | 6  | 6   | 0  | 0  |
|  p2          | 1  | 4  | 10 | 9   | 5  | 5  |
|  p3          | 3  | 5  | 15 | 12  | 7  | 7  |
|  p4          | 2  | 9  | 24 | 22  | 13 | 13 |

- Average Turnaround Time: 12.25
- Average Waiting Time   : 6.25
- Average Response Time  : 6.25


===== Round Robin Scheduling (Quantum = 3) =====
- Order of execution: P1 P2 P3 P4 P1 P2 P3 P4 P3

|process       | AT | BT | CT | TAT | WT | RT |
|--------------|----|----|----|-----|----|----|
|  p1          | 0  | 6  | 15 | 15  | 9  | 0  |
|  p2          | 1  | 4  | 16 | 15  | 11 | 2  |
|  p3          | 2  | 9  | 24 | 22  | 13 | 4  |
|  p4          | 3  | 5  | 21 | 18  | 13 | 6  |

- Average Turnaround Time: 17.5
- Average Waiting Time   : 11.5
- Average Response Time  : 3


---

## 🛠️ How to Compile

You can compile the code using `gcc`:

```bash
gcc -o cpu_scheduler cpu_scheduling.c
