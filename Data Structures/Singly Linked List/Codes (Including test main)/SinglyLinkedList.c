#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "SinglyLinkedList.h"

typedef struct Node {
	void *data;
	struct Node *next;
} Node;

typedef struct List {
	Node *head;
	Node *tail;
	int count;
}List;

static int listCount(const List *list) {
	if (list == NULL) {
		fprintf(stderr, "listCount:list is NULL");
		return -1;
	}

	return list->count;
}

int listRemove(List *list, int index, void *outData) {
	if (list == NULL) {
		fprintf(stderr, "listRemove:list is NULL");
		return -1;
	}

	if (list->count == 0) {
		fprintf(stderr, "listGet:list is empty.\n");
		return -1;
	}

	if (index < 0 || index >= list->count) {
		fprintf(stderr, "listGet:index is out of bound.\n");
		return -1;
	}

	if (outData == NULL) {
		fprintf(stderr, "listGet:outData is NULL.\n");
		return -1;
	}

	Node *prev = list->head;

	for (int i = 0; i < index; i++) {
		prev = prev->next;
	}
	Node *delNode = prev->next;
	(void *)outData = delNode->data;
	prev->next = delNode->next;
	return 0;
}

int listGet(const List *list, int index, void *outData) {
	if (list == NULL) {
		fprintf(stderr, "listGet:list is NULL");
		return -1;
	}

	if (list->count == 0) {
		fprintf(stderr, "listGet:list is empty.\n");
		return -1;
	}

	if (index < 0 || index >= list->count) {
		fprintf(stderr, "listGet:index is out of bound.\n");
		return -1;
	}

	if (outData == NULL) {
		fprintf(stderr, "listGet:outData is NULL.\n");
		return -1;
	}

	Node *node = list->head->next;
	for (int i = 0; i < index; i++) {
		node = node->next;
	}

	(void *)outData = node->data;
	return 0;

}

int listInsert(List *list, int index, void *data) {
	if (list == NULL) {
		fprintf(stderr, "listInsert:list is NULL");
		return -1;
	}

	if (list->count == 0) {
		fprintf(stderr, "listInsert:list is empty.\n");
		return -1;
	}

	if (index < 0 || index >= list->count) {
		fprintf(stderr, "listInsert:index is out of bound.\n");
		return -1;
	}

	Node *node = malloc(sizeof(Node));
	if (node == NULL) {
		fprintf(stderr, "listInsert:malloc failed.\n");
		return -1;
	}
	node->data = data;

	Node *prev = list->head;

	for (int i = 0; i < index; i++) {
		prev = prev->next;
	}

	node->next = prev->next;
	prev->next = node;
	++(list->count);
	return 0;
}

int listSet(List *list, int index, void *newData, void *oldData) {
	if (list == NULL) {
		fprintf(stderr, "listSet:list is NULL");
		return -1;
	}
	
	if (list->count == 0) {
		fprintf(stderr, "listSet:list is empty.\n");
		return -1;
	}

	if (oldData == NULL) {
		fprintf(stderr, "listSet:oldData is NULL.\n");
		return -1;
	}

	if (index < 0 || index >= list->count) {
		fprintf(stderr, "listSet:index is out of bound.\n");
		return -1;
	}

	Node *cur = list->head->next;
	for (int i = 0; i < index; i++)
		cur = cur->next;
	(void *)oldData = cur->data;
	cur->data = newData;
	return 0;
}

List *listInitialize() {

	List *list = calloc(1, sizeof(List));

	if (list == NULL) {
		fprintf(stderr, "listInitialize:calloc failed.\n");
		return NULL;
	}

	Node *head = malloc(sizeof(Node));
	if (head == NULL) {
		perror("listInitialize");
		return NULL;
	}

	Node *tail = malloc(sizeof(Node));
	if (tail == NULL) {
		perror("listInitialize");
		free(head);
		return NULL;
	}
	list->head = head;
	list->tail = tail;
	head->next = tail;
	tail->next = tail;
	list->count = 0;
	return list;
}

int listFinalize(List *list) {
	if (list == NULL) {
		fprintf(stderr, "listFinalize:list is NULL\n");
		return -1;
	}

	if (list->head == NULL || list->tail == NULL) {
		fprintf(stderr, "listFinalize: head or tail is NULL.\n");
		return -1;
	}

	while (list->head->next != list->tail) {
		Node *target = list->head->next;
		list->head->next = target->next;
		free(target);
	}
	free(list->head);
	free(list->tail);
	free(list);
	return 0;
}
int listAdd(List *list, void *data) {
	if (list == NULL) {
		fprintf(stderr, "listAdd:list is NULL");
		return -1;
	}

	Node *node = malloc(sizeof(Node));
	if (node == NULL) {
		perror("listAdd");
		return -1;
	}
	node->data = data;
	node->next = list->tail;

	Node *cur = list->head;
	while (cur->next != list->tail)
		cur = cur->next;
	cur->next = node;
	++(list->count);
	return 0;
}

void listDisplay(const List *list, const char *(*displayFunc)(const void *)) {
	if (list == NULL) {
		fprintf(stderr, "listDisplay:list is NULL.\n");
		return;
	}

	system("cls");
	printf("[head]");
	for (Node *node = list->head->next; node != list->tail; node = node->next)
		printf("->[%s]", displayFunc(node->data));
	printf("->[tail]");
	getchar();
}