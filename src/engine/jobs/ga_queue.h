#pragma once

/*
** RPI Game Architecture Engine
**
** Portions adapted from:
** Viper Engine - Copyright (C) 2016 Velan Studios - All Rights Reserved
**
** This file is distributed under the MIT License. See LICENSE.txt.
*/

/*
** Thread-safe queue.
** https://www.research.ibm.com/people/m/michael/podc-1996.pdf
*/

#include <mutex>

struct node_t
{
	void* value;
	node_t* next;
};
class ga_queue
{
private:
	node_t* Head;
	node_t* Tail;
	std::mutex H_lock;
	std::mutex T_lock;

public:
	ga_queue(int node_count);
	~ga_queue();

	void push(void* data);
	bool pop(void** data);

	int get_count() const;
};
