#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
    int finished;
} Process;

// تابع مقایسه برای FCFS و SJF
int compare_arrival(const void *a, const void *b) {
    Process *p1 = (Process *)a;
    Process *p2 = (Process *)b;
    return p1->arrival_time - p2->arrival_time;
}

int compare_burst(const void *a, const void *b) {
    Process *p1 = (Process *)a;
    Process *p2 = (Process *)b;
    return p1->burst_time - p2->burst_time;
}

// الگوریتم FCFS
void fcfs(Process p[], int n) {
    qsort(p, n, sizeof(Process), compare_arrival);
    int time = 0;
    float total_tat = 0, total_wt = 0, total_rt = 0;

    for (int i = 0; i < n; i++) {
        if (time < p[i].arrival_time)
            time = p[i].arrival_time;
        p[i].start_time = time;
        p[i].completion_time = time + p[i].burst_time;
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
        p[i].response_time = p[i].start_time - p[i].arrival_time;
        time = p[i].completion_time;

        total_tat += p[i].turnaround_time;
        total_wt += p[i].waiting_time;
        total_rt += p[i].response_time;
    }

    printf("\nFCFS:\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].arrival_time, p[i].burst_time,
               p[i].completion_time, p[i].turnaround_time,
               p[i].waiting_time, p[i].response_time);

    printf("Avg TAT: %.2f, Avg WT: %.2f, Avg RT: %.2f\n",
           total_tat / n, total_wt / n, total_rt / n);
}

// الگوریتم SJF (غیراستقراری)
void sjf(Process p[], int n) {
    int time = 0, completed = 0;
    float total_tat = 0, total_wt = 0, total_rt = 0;

    while (completed < n) {
        int idx = -1, min_burst = 99999;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= time && !p[i].finished) {
                if (p[i].burst_time < min_burst) {
                    min_burst = p[i].burst_time;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        p[idx].start_time = time;
        p[idx].completion_time = time + p[idx].burst_time;
        p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
        p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
        p[idx].response_time = p[idx].start_time - p[idx].arrival_time;
        time = p[idx].completion_time;
        p[idx].finished = 1;
        completed++;

        total_tat += p[idx].turnaround_time;
        total_wt += p[idx].waiting_time;
        total_rt += p[idx].response_time;
    }

    printf("\nSJF:\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].arrival_time, p[i].burst_time,
               p[i].completion_time, p[i].turnaround_time,
               p[i].waiting_time, p[i].response_time);

    printf("Avg TAT: %.2f, Avg WT: %.2f, Avg RT: %.2f\n",
           total_tat / n, total_wt / n, total_rt / n);
}

// الگوریتم Round Robin
void round_robin(Process p[], int n, int quantum) {
    int time = 0, completed = 0, queue[MAX], front = 0, rear = 0, visited[MAX] = {0};
    float total_tat = 0, total_wt = 0, total_rt = 0;

    for (int i = 0; i < n; i++) {
        p[i].remaining_time = p[i].burst_time;
    }

    queue[rear++] = 0;
    visited[0] = 1;

    while (completed < n) {
        int idx = queue[front++];
        if (p[idx].remaining_time == p[idx].burst_time)
            p[idx].start_time = time;

        if (p[idx].remaining_time <= quantum) {
            time += p[idx].remaining_time;
            p[idx].remaining_time = 0;
            p[idx].completion_time = time;
            p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
            p[idx].response_time = p[idx].start_time - p[idx].arrival_time;
            completed++;
        } else {
            time += quantum;
            p[idx].remaining_time -= quantum;
        }

        // اضافه کردن فرایندهای جدید به صف
        for (int i = 0; i < n; i++) {
            if (!visited[i] && p[i].arrival_time <= time && p[i].remaining_time > 0) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        // اگر فرایند هنوز تمام نشده، دوباره در صف قرار می‌گیرد
        if (p[idx].remaining_time > 0)
            queue[rear++] = idx;

        // اگر صف خالی شد ولی فرایندی باقی مانده بود
        if (front == rear && completed < n) {
            for (int i = 0; i < n; i++) {
                if (!visited[i]) {
                    queue[rear++] = i;
                    visited[i] = 1;
                    break;
                }
            }
        }
    }

    printf("\nRound Robin (Q=%d):\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n", quantum);
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].arrival_time, p[i].burst_time,
               p[i].completion_time, p[i].turnaround_time,
               p[i].waiting_time, p[i].response_time);

    for (int i = 0; i < n; i++) {
        total_tat += p[i].turnaround_time;
        total_wt += p[i].waiting_time;
        total_rt += p[i].response_time;
    }

    printf("Avg TAT: %.2f, Avg WT: %.2f, Avg RT: %.2f\n",
           total_tat / n, total_wt / n, total_rt / n);
}

int main() {
    int n, algo, quantum;
    Process p[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter Arrival Time and Burst Time for each process:\n");
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("P%d - Arrival Time: ", p[i].pid);
        scanf("%d", &p[i].arrival_time);
        printf("P%d - Burst Time: ", p[i].pid);
        scanf("%d", &p[i].burst_time);
        p[i].finished = 0;
    }

    printf("Select Scheduling Algorithm:\n1. FCFS\n2. SJF\n3. Round Robin\nChoice: ");
    scanf("%d", &algo);

    if (algo == 1) {
        fcfs(p, n);
    } else if (algo == 2) {
        sjf(p, n);
    } else if (algo == 3) {
        printf("Enter Time Quantum: ");
        scanf("%d", &quantum);
        round_robin(p, n, quantum);
    } else {
        printf("Invalid Choice.\n");
    }

    return 0;
}
