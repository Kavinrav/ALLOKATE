#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_STUDENTS 100
#define MAX_INTERESTS 10
#define MAX_LEN 50

// Student structure
typedef struct {
    int id;
    char name[MAX_LEN];
    float marks;
    int interestCount;
    char interests[MAX_INTERESTS][MAX_LEN];
} Student;

Student students[MAX_STUDENTS];
int n;

// Graph adjacency matrix
int graph[MAX_STUDENTS][MAX_STUDENTS];
int visited[MAX_STUDENTS];

// Function to count common interests
int commonInterests(Student s1, Student s2) {
    int count = 0;
    int i, j;
    for (i = 0; i < s1.interestCount; i++) {
        for (j = 0; j < s2.interestCount; j++) {
            if (strcmp(s1.interests[i], s2.interests[j]) == 0) {
                count++;
            }
        }
    }
    return count;
}

// Similarity check function
int isSimilar(Student s1, Student s2) {
    float markDiff = fabs(s1.marks - s2.marks);
    int common = commonInterests(s1, s2);

    // Conditions (you can tune these)
    if (markDiff <= 5 && common >= 1)
        return 1;

    return 0;
}

// DFS to find groups
void dfs(int node) {
    visited[node] = 1;
    printf("%s ", students[node].name);

    int i;
    for (i = 0; i < n; i++) {
        if (graph[node][i] && !visited[i]) {
            dfs(i);
        }
    }
}

// Build similarity graph
void buildGraph() {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            graph[i][j] = 0;
        }
    }

    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (isSimilar(students[i], students[j])) {
                graph[i][j] = graph[j][i] = 1;
            }
        }
    }
}

// Input function
void inputStudents() {
    printf("Enter number of students: ");
    scanf("%d", &n);

    int i, j;
    for (i = 0; i < n; i++) {
        students[i].id = i;

        printf("\nStudent %d name: ", i + 1);
        scanf("%s", students[i].name);

        printf("Marks: ");
        scanf("%f", &students[i].marks);

        printf("Number of interests: ");
        scanf("%d", &students[i].interestCount);

        for (j = 0; j < students[i].interestCount; j++) {
            printf("Interest %d: ", j + 1);
            scanf("%s", students[i].interests[j]);
        }
    }
}

// Print groups
void findGroups() {
    int i;
    for (i = 0; i < n; i++) {
        visited[i] = 0;
    }

    printf("\nStudy Groups:\n");

    for (i = 0; i < n; i++) {
        if (!visited[i]) {
            printf("Group: ");
            dfs(i);
            printf("\n");
        }
    }
}

// Main function
int main() {
    inputStudents();
    buildGraph();
    findGroups();
    return 0;
}