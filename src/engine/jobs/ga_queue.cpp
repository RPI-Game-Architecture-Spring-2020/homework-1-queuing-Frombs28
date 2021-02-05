/*
** RPI Game Architecture Engine
**
** Portions adapted from:
** Viper Engine - Copyright (C) 2016 Velan Studios - All Rights Reserved
**
** This file is distributed under the MIT License. See LICENSE.txt.
*/

#include "ga_queue.h"

ga_queue::ga_queue(int node_count)
{
	// TODO:
	// Initialize the queue.
	node_t* node = new node_t;
	node->next = NULL;
	Head = node;
	Tail = node;
	// For extra credit, preallocate 'node_count' elements (instead of
	// allocating on push).
	// See https://www.research.ibm.com/people/m/michael/podc-1996.pdf
}

ga_queue::~ga_queue()
{
	// TODO:
	// Free any resources held by the queue.
	node_t* node = Head;
	while (node != NULL) {
		node_t* next_node = node->next;
		delete node;
		node = next_node;
	}
	// See https://www.research.ibm.com/people/m/michael/podc-1996.pdf
}

void ga_queue::push(void* data)
{
	// TODO:
	// Push 'data' onto the queue in a thread-safe manner.
	node_t* node = new node_t;
	node->value = data;
	node->next = NULL;
	T_lock.lock();
	Tail->next = node;
	Tail = node;
	T_lock.unlock();
	// If you preallocated 'node_count' elements, and if the queue is full when
	// this function is called, you must block until another thread pops an
	// element off the queue.
	// See https://www.research.ibm.com/people/m/michael/podc-1996.pdf
}

bool ga_queue::pop(void** data)
{
	// TODO:
	// Pop one element off the queue in a thread-safe manner and place it in
	// the memory pointed to by 'data'.
	// If the queue is empty when this function is called, return false.
	// Otherwise return true.
	H_lock.lock();
	node_t* node = Head;
	node_t* new_head = node->next;
	if (new_head == NULL)
	{
		H_lock.unlock();
		return false;
	}
	*data = new_head->value;
	Head = new_head;
	H_lock.unlock();
	delete node;
	return true;
	// See https://www.research.ibm.com/people/m/michael/podc-1996.pdf
}

int ga_queue::get_count() const
{
	// TODO:
	// Get the number of elements currently in the queue.
	node_t* node = Head;
	int total = 0;
	while (node->next != NULL) {
		total++;
		node = node->next;
	}
	return total;
}
