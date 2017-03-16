#ifndef _QUEUE_H
#define _QUEUE_H

#include <malloc.h>

typedef struct _Tree {
	unsigned char key;
	struct _Tree * left;
	struct _Tree * right;
	int weight;
} Tree;

typedef struct _ListNode {
	Tree * value;
	struct _ListNode * next;
} ListNode;

typedef struct _Queue {
	ListNode * tail;
	ListNode * head;
} Queue;

void enqueue(Queue * q, Tree * val);
Tree * dequeue(Queue * q);
#endif
