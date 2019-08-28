#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 5
int node_count = 0;

typedef struct queue_node
{
	int data;
	queue_node* next;
};

typedef struct queue
{
	queue_node* front;
	queue_node* tail;
};

void init_queue(queue* q)
{
	q->front = NULL;			// 只是指针 不必malloc分配空间来保存data
	q->tail = NULL;
}

bool is_queue_empty(queue* q)
{
	// 两种方式判断是否为空
	//if (q->front == NULL && q->tail == NULL)
	//{
	//	return true;
	//}

	if (node_count <= 0)
	{
		return true;
	}
	return false;
}


bool is_queue_full(queue* q)
{
	if (node_count >= MAX_SIZE)
	{
		return true;
	}
	return false;
}

queue* push_queue(queue* q, int value)
{
	queue_node* new_node = (queue_node*)malloc(1 * sizeof(queue_node));
	new_node->data = value;
	new_node->next = NULL;

	if (!is_queue_full(q))		// 队列满了
	{
		if (q->front == NULL && q->tail == NULL)
		{
			q->front = new_node;
		}
		else					// 队列没满
		{
			q->tail->next = new_node;
		}
		q->tail = new_node;
		node_count++;
	}
	else
	{
		printf("push %d failed, queue is full.\n", value);
	}

	return q;
}

void pop_queue(queue* q)
{
	queue_node* ptr_current = q->front;
	if (!is_queue_empty(q))
	{
		printf("pop value is: %d\n", q->front->data);
		q->front = q->front->next;
		if (q->front == NULL)	// 若不用计数器判断是否空，则加限制条件！！
		{
			q->tail = NULL;
		}
		free(ptr_current);
		ptr_current = NULL;
		node_count--;
	}
	else
	{
		printf("pop failed, queue is empty.\n");
	}
}

//返回队首元素值
int  get_queue_front_value(queue * qu)
{
	if (!is_queue_empty(qu))
	{
		return qu->front->data;
	}
	return -200;
}

//返回队尾元素值
int  get_queue_tail_value(queue*  qu)
{
	if (!is_queue_empty(qu))
	{
		return qu->tail->data;
	}
	return -200;
}

//返回队列的元素个数
int  get_queue_size(queue * qu)
{
	return node_count;
}

void printf_queue(queue* q)
{
	queue_node* ptr_current = q->front;
	while (ptr_current != NULL)
	{
		printf("%d\t", ptr_current->data);
		ptr_current = ptr_current->next;
	}
	printf("\n");
}

int main()
{
	queue* q = (queue*)malloc(1*sizeof(queue));
	init_queue(q);

	int i;
	for (i = 0; i < 5; i++)
	{
		push_queue(q, i);
	}
	push_queue(q, 999);
	printf("初始队列元素：\n");
	printf_queue(q);

	int frount_value = get_queue_front_value(q);
	int tail_value = get_queue_tail_value(q);
	get_queue_tail_value(q);
	int count = get_queue_size(q);
	printf("front_value=%d \t tail_value=%d \t count=%d\n", frount_value, tail_value, count);

	for (i = 0; i < 5; i++)
	{
		pop_queue(q);
	}
	printf("队列操作之后的元素：\n");
	printf_queue(q);
	pop_queue(q);

	getchar();
	return 0;
}
