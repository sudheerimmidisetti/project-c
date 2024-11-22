#include <stdio.h>
#include <stdlib.h>
// FOR WASHING
//to create stations
typedef struct {
    int *Station;
    int front, rear, Station_Capacity;
} Washing_Queue;

// Function to initialize washing queue
void Creating_Washing_Queue(Washing_Queue *Stations, int Station_Size) {
    Stations->front = -1;
    Stations->rear = -1;
    Stations->Station_Capacity = Station_Size;
    Stations->Station = (int *)malloc(Station_Size * sizeof(int));
}

// Function to check if washing station is empty
int Washing_Station_isEmpty(Washing_Queue *Stations) {
    return (Stations->front == -1 && Stations->rear == -1);
}

// Function to check if washing station is full
int Washing_Station_isFull(Washing_Queue *Stations) {
    return ((Stations->rear + 1) % Stations->Station_Capacity == Stations->front);
}

// Function to enqueue a car for washing
void Washing_enqueue(Washing_Queue *Stations, int value) {
    if (Washing_Station_isFull(Stations)) {
        printf("Car Stations are occupied\n");
        return;
    } else if (Washing_Station_isEmpty(Stations)) {
        Stations->front = 0;
        Stations->rear = 0;
        printf("Car %d sent for Washing\n", value);
    } else {
        Stations->rear = (Stations->rear + 1) % Stations->Station_Capacity;
        printf("Car %d sent for Washing\n", value);
    }
    Stations->Station[Stations->rear] = value;
}

// Function to dequeue a car from the washing station
int Washing_dequeue(Washing_Queue *Stations) {
    int dequeuedValue;
    if (Washing_Station_isEmpty(Stations)) {
        printf("Waiting Hall is Empty\n");
        return -1;
    } else if (Stations->front == Stations->rear) {
        dequeuedValue = Stations->Station[Stations->front];
        Stations->front = -1;
        Stations->rear = -1;
    } else {
        dequeuedValue = Stations->Station[Stations->front];
        Stations->front = (Stations->front + 1) % Stations->Station_Capacity;
    }
    return dequeuedValue;
}

// FOR CALL LOG
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Queue structure for call log
typedef struct {
    Node *front;
    Node *rear;
} Log_Data;

// Function to initialize call log queue
void Create_Log_Data(Log_Data *Car_Queue) {
    Car_Queue->front = NULL;
    Car_Queue->rear = NULL;
}

// Function to check if call log is empty
int Call_log_isEmpty(Log_Data *Car_Queue) {
    return (Car_Queue->front == NULL);
}

// Function to enqueue a car to the waiting list (call log)
void Call_log_enqueue(Log_Data *Car_Queue, int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed. Unable to enqueue.\n");
        return;
    }
    newNode->data = value;
    newNode->next = NULL;
    if (Call_log_isEmpty(Car_Queue)) {
        Car_Queue->front = newNode;
        Car_Queue->rear = newNode;
    } else {
        Car_Queue->rear->next = newNode;
        Car_Queue->rear = newNode;
    }
}

// Function to dequeue a car from the waiting list (call log)
int Call_log_dequeue(Log_Data *Car_Queue) {
    if (Call_log_isEmpty(Car_Queue)) {
        printf("Queue is empty. Unable to dequeue.\n");
        return -1;
    }
    Node *temp = Car_Queue->front;
    int dequeuedValue = temp->data;
    Car_Queue->front = Car_Queue->front->next;
    if (Car_Queue->front == NULL) {
        Car_Queue->rear = NULL;
    }
    free(temp);
    return dequeuedValue;
}

// Function to display all cars in the waiting list (call log)
void displayQueue(Log_Data *Car_Queue) {
    if (Call_log_isEmpty(Car_Queue)) {
        printf("\nWaiting List is Empty.\n");
        return;
    }
    printf("\nCars in the waiting list:\n");
    Node *current = Car_Queue->front;
    while (current != NULL) {
        printf("%d\n", current->data);
        current = current->next;
    }
    printf("\n");
}

// Function to check if a car is already in the washing station
int CarinWashing(Washing_Queue *Stations, int value) {
    for (int i = Stations->front; i <= Stations->rear; i++) {
        if (Stations->Station[i] == value) {
            return 1;
        }
    }
    return 0;
}

// Function to check if a car is already in the call log
int CarinLogData(Log_Data *Car_Queue, int value) {
    Node *current = Car_Queue->front;
    while (current != NULL) {
        if (current->data == value) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

// Main function to handle user input and manage car washing and waiting lists
int main() {
    int size;
    printf("Enter the no of stations : ");
    scanf("%d", &size);
    printf("\n--------------------------------------------------------");
    Washing_Queue Stations;
    Creating_Washing_Queue(&Stations, size);
    
    Log_Data Car_Queue;
    Create_Log_Data(&Car_Queue);
    int Decision;
    while(1) {
        printf("\n--------------------------------------------------------\n");
        printf("1. New Car To The Station\n2. Complete Wash And Invite Next Car\n3. Next Car Data\n4. Call Log Data\nPRESS ANY KEY TO COMPLETE\nChoose Option To Perform :");
        scanf("%d", &Decision);
        if(Decision == 1) {
            int Car;
            printf("\nEnter Car Data(In Numbers): ");
            scanf("%d", &Car);
            printf("\n");
            if (CarinWashing(&Stations, Car) || CarinLogData(&Car_Queue, Car)) {
                printf("Car %d is already in the station\n", Car);
            } else {
                if (Washing_Station_isFull(&Stations)) {
                    printf("Car %d added to waiting list\n", Car);
                    Call_log_enqueue(&Car_Queue, Car);
                } else {
                    Washing_enqueue(&Stations, Car);
                }
            }
        } else if(Decision == 2) {
            if(Washing_Station_isEmpty(&Stations)) {
                printf("\nNo Cars in the station.\n");
                continue;
            }
            printf("\nCar %d Completed Washing\n", Washing_dequeue(&Stations));
            if(Call_log_isEmpty(&Car_Queue)) {
                printf("No Cars in the waiting list\n");
                continue;
            }
            Washing_enqueue(&Stations, Call_log_dequeue(&Car_Queue));  
        } else if(Decision == 3) {
            if (Call_log_isEmpty(&Car_Queue)) {
                printf("\nWaiting List is Empty.\n");
            } else {
                Node *current = Car_Queue.front;
                printf("\nCar %d - Next in Line for Washing.\n", current->data);
            }
        } else if(Decision == 4) {
            displayQueue(&Car_Queue);
        } else {
            break;
        }
    }
}
