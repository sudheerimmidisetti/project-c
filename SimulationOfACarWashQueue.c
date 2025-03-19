#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// FOR WASHING

// to create stations
typedef struct {
    char (*Station)[20]; // Array of strings
    int front, rear, Station_Capacity;
} Washing_Queue;

void Creating_Washing_Queue(Washing_Queue *Stations, int Station_Size) {
    Stations->front = -1;
    Stations->rear = -1;
    Stations->Station_Capacity = Station_Size;
    Stations->Station = (char(*)[20])malloc(Station_Size * sizeof(char[20]));
}

int Washing_Station_isEmpty(Washing_Queue *Stations) {
    return (Stations->front == -1 && Stations->rear == -1);
}

int Washing_Station_isFull(Washing_Queue *Stations) {
    return ((Stations->rear + 1) % Stations->Station_Capacity == Stations->front);
}

void Washing_enqueue(Washing_Queue *Stations, char *value) {
    if (Washing_Station_isFull(Stations)) {
        printf("\nAll washing stations are currently occupied!\n");
        return;
    } else if (Washing_Station_isEmpty(Stations)) {
        Stations->front = 0;
        Stations->rear = 0;
    } else {
        Stations->rear = (Stations->rear + 1) % Stations->Station_Capacity;
    }
    strcpy(Stations->Station[Stations->rear], value);
    printf("\nCar %s has been sent for washing.\n", value);
}

char* Washing_dequeue(Washing_Queue *Stations) {
    if (Washing_Station_isEmpty(Stations)) {
        printf("\nNo cars available in the washing station.\n");
        return NULL;
    }
    char *dequeuedValue = Stations->Station[Stations->front];

    if (Stations->front == Stations->rear) {
        Stations->front = -1;
        Stations->rear = -1;
    } else {
        Stations->front = (Stations->front + 1) % Stations->Station_Capacity;
    }
    return dequeuedValue;
}

// FOR CALL LOG

typedef struct Node {
    char data[20];
    struct Node *next;
} Node;

typedef struct {
    Node *front;
    Node *rear;
} Log_Data;

void Create_Log_Data(Log_Data *Car_Queue) {
    Car_Queue->front = NULL;
    Car_Queue->rear = NULL;
}

int Call_log_isEmpty(Log_Data *Car_Queue) {
    return (Car_Queue->front == NULL);
}

void Call_log_enqueue(Log_Data *Car_Queue, char *value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("\nError: Memory allocation failed!\n");
        return;
    }
    strcpy(newNode->data, value);
    newNode->next = NULL;
    if (Call_log_isEmpty(Car_Queue)) {
        Car_Queue->front = newNode;
        Car_Queue->rear = newNode;
    } else {
        Car_Queue->rear->next = newNode;
        Car_Queue->rear = newNode;
    }
}

char* Call_log_dequeue(Log_Data *Car_Queue) {
    if (Call_log_isEmpty(Car_Queue)) {
        printf("\nNo cars in the waiting list.\n");
        return NULL;
    }
    Node *temp = Car_Queue->front;
    char *dequeuedValue = temp->data;
    Car_Queue->front = Car_Queue->front->next;
    if (Car_Queue->front == NULL) {
        Car_Queue->rear = NULL;
    }
    free(temp);
    return dequeuedValue;
}

void displayQueue(Log_Data *Car_Queue) {
    if (Call_log_isEmpty(Car_Queue)) {
        printf("\nNo cars are currently waiting.\n");
        return;
    }
    printf("\nCars in the waiting list:\n");
    Node *current = Car_Queue->front;
    while (current != NULL) {
        printf("%s\n", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    int size;
    while (1) {
        printf("\nEnter the total number of car washing stations: ");
        if (scanf("%d", &size) == 1) break;
        system("cls");
        printf("\nInvalid input. Please enter a valid number!\n");
        while (getchar() != '\n');
    }

    Washing_Queue Stations;
    Creating_Washing_Queue(&Stations, size);
    Log_Data Car_Queue;
    Create_Log_Data(&Car_Queue);

    int Decision;
    while (1) {
        printf("\n--------------------------------------------------------\n");
        printf("1. New Car Arrival\n2. Complete Wash & Invite Next Car\n3. View Next Car\n4. View Waiting List\n5. Exit\n");
        printf("\nChoose an option: ");
        if (scanf("%d", &Decision) != 1) {
            printf("\nInvalid input. Please enter a valid number!\n");
            while (getchar() != '\n');
            continue;
        }
        getchar();
        if (Decision == 1) {
            char Car[20];
            printf("\nEnter Car Number Plate: ");
            scanf("%s", Car);
            if (Washing_Station_isFull(&Stations)) {
                printf("\nAll stations are occupied! Car %s added to waiting list.\n", Car);
                Call_log_enqueue(&Car_Queue, Car);
            } else {
                Washing_enqueue(&Stations, Car);
            }
        } else if (Decision == 2) {
            if (Washing_Station_isEmpty(&Stations)) {
                printf("\nNo cars are currently being washed.\n");
                continue;
            }
            printf("\nCar %s has completed washing.\n", Washing_dequeue(&Stations));
            if (!Call_log_isEmpty(&Car_Queue)) {
                Washing_enqueue(&Stations, Call_log_dequeue(&Car_Queue));
            }
        } else if (Decision == 3) {
            if (Call_log_isEmpty(&Car_Queue)) {
                printf("\nNo cars are waiting for washing.\n");
            } else {
                printf("\nNext Car in Line: %s\n", Car_Queue.front->data);
            }
        } else if (Decision == 4) {
            displayQueue(&Car_Queue);
        } else {
            break;
        }
    }

    free(Stations.Station);
    Node *temp;
    while (Car_Queue.front) {
        temp = Car_Queue.front;
        Car_Queue.front = Car_Queue.front->next;
        free(temp);
    }

    printf("\nThank you for using the Car Wash Queue System!\n");
    return 0;
}
