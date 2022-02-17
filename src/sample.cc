#include "block_queue.h"
#include "bound_queue.h"

using namespace zziduo;

int fun()
{
	block_queue<int> b;
	bound_queue<int> bq(7);
	return 0;
}