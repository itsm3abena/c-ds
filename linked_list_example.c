#include "linked_list.h"

int main() {
    Node* head = NULL;

    insertAtHead(&head, 10);
    insertAtHead(&head, 20);
    insertAtTail(&head, 30);

    printList(head);

    deleteNode(&head, 20);
    printList(head);

    freeList(head);

    return 0;
}
