#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Simulated node structure
typedef struct Node {
    int id;
    int priority;
    bool active;
} Node;

// Simulated network of nodes
Node* nodes;

// Simulate sending a message
void sendMessage(int sender, int receiver, const char* message) {
    printf("Node %d sends '%s' to Node %d\n", sender, message, receiver);
}

// Election process
// Election process
void initiateElection(int coordinator, int numNodes) {
	printf("");
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

// ...

// ...

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

    // Find and print the initial coordinator
    int initialCoordinator = -1;
    for (int i = 0; i < numNodes; ++i) {
        if (nodes[i].active) {
            initialCoordinator = i;
            break;
        }
    }

    if (initialCoordinator != -1) {
        printf("Initial coordinator is Node %d.\n", initialCoordinator);
    } else {
        printf("No active nodes initially.\n");
    }

    // Ask the user which node to mark as failed
    int failedNode;
    printf("Enter the node number you want to mark as failed: ");
    scanf("%d", &failedNode);

    if (failedNode >= 0 && failedNode < numNodes) {
        nodes[failedNode].active = false;
        printf("Node %d marked as failed.\n", failedNode);
    } else {
        printf("Invalid node number.\n");
    }

    // Simulate election process initiated by the coordinator (Node 1)
    int coordinator = 1;
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

    // Free allocated memory
    free(nodes);

    return 0;
}


