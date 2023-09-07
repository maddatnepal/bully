#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <conio.h> // For getch()
#include <windows.h> // For Sleep

// Simulated node structure
typedef struct Node {
    int id;
    int priority;
    bool active;
} Node;

// Simulated network of nodes
Node* nodes;

// Simulate sending a message with a random delay
void sendMessage(int sender, int receiver, const char* message) {
    printf("Node %d sends '%s' to Node %d\n", sender, message, receiver);
    int sleepDuration = 5000 + (rand() % 6000); // Random sleep between 5000 and 11000 milliseconds (5 to 11 seconds)
    Sleep(sleepDuration);
}

// Election process
void initiateElection(int coordinator, int numNodes) {
    printf("Node %d initiates election.\n", coordinator);

    int coordinatorPriority = nodes[coordinator].priority; // Get the priority of the coordinator

    // Sending election messages to nodes with lower priorities
    for (int i = 0; i < coordinator; ++i) {
        if (nodes[i].active) {
            printf("Node %d sends 'ELECTION' (Priority: %d) to Node %d\n", coordinator, coordinatorPriority, i);
            // sendMessage(coordinator, i, "ELECTION");
        }
    }

    // Waiting for responses or victory
    // Simulating receiving messages and handling them
    // ...
}

// Handling election messages
void handleElectionMessage(int sender) {
    printf("Node %d received ELECTION message.\n", nodes[sender].id);

    // Simulate responding with OK message if the node has a higher priority
    if (nodes[sender].priority < nodes[nodes[sender].id].priority) {
        sendMessage(nodes[sender].id, sender, "OK");
    }
}

// Handling victory message
void handleVictoryMessage(int newLeader) {
    printf("Node %d received VICTORY message. New leader is Node %d.\n", nodes[newLeader].id, nodes[newLeader].id);
}

int main() {
    int numNodes;

    // Get the total number of nodes from the user
    printf("Enter the total number of nodes: ");
    scanf("%d", &numNodes);

    // Allocate memory for nodes
    nodes = (Node*)malloc(numNodes * sizeof(Node));

    // Initialize nodes (IDs, priorities, and active status) based on user input
    for (int i = 0; i < numNodes; ++i) {
        nodes[i].id = i;
        printf("Enter priority for Node %d: ", i);
        scanf("%d", &nodes[i].priority);
        printf("Is Node %d active? (1 for active, 0 for inactive): ", i);
        scanf("%d", &nodes[i].active);
    }

    int coordinator = -1;

    // Find the initial coordinator with the highest priority
    for (int i = 0; i < numNodes; ++i) {
        if (nodes[i].active && (coordinator == -1 || nodes[i].priority > nodes[coordinator].priority)) {
            coordinator = i;
        }
    }

    if (coordinator != -1) {
        printf("Initial coordinator is Node %d with priority %d.\n", coordinator, nodes[coordinator].priority);
    } else {
        printf("No active nodes initially.\n");
        free(nodes); // Free memory and exit if there is no coordinator
        return 0;
    }

    while (1) {
        // Find and print the current coordinator
        if (coordinator != -1) {
            printf("Current coordinator is Node %d.\n", coordinator);
        } else {
            printf("No active coordinator.\n");
        }

        // Simulate sending messages between processes with random delays
        int sender, receiver;
        printf("Enter sender node (0-%d): ", numNodes - 1);
        scanf("%d", &sender);
        printf("Enter receiver node (0-%d): ", numNodes - 1);
        scanf("%d", &receiver);

        if (sender >= 0 && sender < numNodes && receiver >= 0 && receiver < numNodes) {
            char message[256];
            printf("Enter message: ");
            scanf("%s", message);

            sendMessage(sender, receiver, message);
        } else {
            printf("Invalid sender or receiver node.\n");
        }

        // Check if the user pressed 'f' to simulate coordinator failure during the delay
        if (_kbhit()) {
            char key = _getch();
            if (key == 'f') {
                if (coordinator != -1) {
                    nodes[coordinator].active = false;
                    printf("Coordinator Node %d marked as failed.\n", coordinator);

                    // Simulate election process initiated by the coordinator
                    initiateElection(coordinator, numNodes);

                    // Simulate handling of messages and determining new leader
                    // ...

                    // Find and print the new coordinator
                    int newCoordinator = -1;
                    for (int i = 0; i < numNodes; ++i) {
                        if (nodes[i].active) {
                            newCoordinator = i;
                            break;
                        }
                    }

                    if (newCoordinator != -1) {
                        printf("New coordinator is Node %d.\n", newCoordinator);
                    } else {
                        printf("No active nodes remaining.\n");
                    }

                    coordinator = newCoordinator;
                } else {
                    printf("No active coordinator to mark as failed.\n");
                }
            }
        }
    }

    // Free allocated memory
    free(nodes);

    return 0;
}
