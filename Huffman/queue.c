#include "queue.h"

void enqueue(Queue * q, Tree * val)
{
	ListNode * tmp;
	if (!q->head) {
		ListNode * l = (ListNode *)malloc(sizeof(ListNode));
		l->value = val;
		l->next = NULL;
		q->head = l;
		q->tail = l;
		return;
	}

	tmp = q->head;

	if (val->weight <= tmp->value->weight) {							// если вставка в начало
		ListNode * l = (ListNode *)malloc(sizeof(ListNode));
		l->value = val;
		l->next = q->head;
		q->head = l;
		return;
	}
	while (tmp->next) {												// если вставка в середину
		if (val->weight <= tmp->next->value->weight) {
			ListNode * l = (ListNode *)malloc(sizeof(ListNode));
			l->value = val;
			l->next = tmp->next;
			tmp->next = l;
			return;
		}
		else
			tmp = tmp->next;
	}
	ListNode * l = (ListNode *)malloc(sizeof(ListNode));				// если вставка в конец
	l->value = val;
	l->next = NULL;
	q->tail->next = l;
	q->tail = l;
}

Tree * dequeue(Queue * q)
{
	Tree * res = q->head->value;
	ListNode * tmp = q->head;
	q->head = q->head->next;
	free(tmp);
	return res;
}