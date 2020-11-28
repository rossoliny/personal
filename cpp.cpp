

void insert(list* list, int key)
{
	// If height is H, then we will go down only H times.
	// If H = MAX_LVL then we must save at least MAX_LVL points.
	// But also we must save point at lvl 0 where we can't go down anymore
	// because we are at lvl 0, and we can't go right because next key is greater or euqal to new_key.
	//
	// This is the point after which we must insert new element at lvl 0
	// and it will be used to connect new_node with node_last;
	//
	// In other words this special point is the actuall node and we will asign new_node to its next member pointer
	// Let's call this point as last_node. 
	// pseude code: last_node->next = new_node;
	node* step_down_points[MAX_LVL + 1];

	node* curr = list->top_left;
	int curr_lvl = list->height;

	// step_down_point[height] will be the first node at which we went down.
	// but it will never be equal to top_left considering that top_left is -infinity
	while(curr_lvl >= 0)
	{
		// (curr != NULL) is the same as (curr < +infinity)
		// curr->next[i] is next node at level i
		while(curr != NULL && curr->next[i]->key < key)
		{
			// stay at lvl i and go right
			curr = curr->next[i];
		} 
		// curr is point where we went down from lvl i to lvl i-1
		// because if above loop is finished then we meet elemnt that is greater than key
		// and thus we must go 1 lvl down from curr node
		step_down_points[i] = curr;

		// actual index of current lvl
		// current lvl is lvl at which all logical operations we are currently doing
		--i;
	}

	// now curr points to element after which we must insert new node
	// curr->next[0] is the actuall position for new node
	// but curr->next[0] may already contain some element
	node* new_node_pos = curr->next[0];

	// if new_node_pos is NULL then this is the end of lvl 0 list
	// and we must insert new element. If it is not null then this
	// position already contains some element. If so then we must insert new key only if
	// this element has different key.
	// Because it is useless to insert already existing key;
	if(new_node_pos == NULL || new_node_pos->key != key)
	{
		int at_which_level_insert_new_node = random(0, MAX_LVL);
		int new_lvl = at_which_levels_insert_new_node;

		// If new_node goes to new_level, i.e forces the creationg of new level,
		// then we must connect it with top_left at all levels.
		// With the relation saying that new_node is next node after top_left
		//
		// To do that we must uset step_down_points at all positions
		// from new_lvl to height(not including) from NULL and set them to top_left,
		// where height is current height of list.
		while(list->height <= new_lvl)
		{
			list->height++;
			step_down_points[list->height] = list->top_left;
		}
		list->height--;

		node* new_node = node_init(key);

		int i = 0;
		// I claim that if list->height = K, then we have K additional lists above original list.
		// And the actual amount of layers in skiplist is K + 1;

		// At all lvls from 0 to top lvl(including), which is equal to list->height
		// we must take point/node where we went down, let's call it last_node,
		// and set last_node->next to new_node
		while(i < list->height + 1)
		{
			new_node->next[i] = step_down_points[i]->next[i];
			step_down_points[i]->next[i] = new_node;
			i++;
		}
	}
	else if (new_node_pos->key == key)
	{
		// TODO: update value. 
	}
}


void remove(list* list, int key)
{
	node* step_down_points[MAX_LVL + 1];
	int lvl = list->height;
	node* curr = list->top_left;

	while(lvl >= 0)
	{
		while(curr != NULL && curr->next[lvl] < key)
		{
			curr = curr->next[lvl];
		}
		step_down_points[lvl] = curr;
		lvl--;
	}
	curr = curr->next[0];

	if(curr != NULL && curr->key == key)
	{
		lvl = list->height;
		while(lvl >= 0)
		{
			step_down_points[lvl]->next[lvl] = curr->next[lvl];
		}
			
		while(list->height > 0 && list->top_left == NULL)
		{
			list->height--;
		}
	}
	else
	{
		// SUCH KEY DOES NO EXIST
	}
}