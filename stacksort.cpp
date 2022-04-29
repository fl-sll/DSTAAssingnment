#include <iostream>
#include <array>

using namespace std;


struct stack
{
	int data;
	struct stack *next;
};

// initialize stack
void initStack(struct stack **s) 
{
    *s = NULL;
}

// checks if empty or not
int isEmpty(struct stack *s)
{
	if (s == NULL)
		return 1;
	return 0;
}

// push to stack
void push(struct stack **s, int x)
{
	struct stack *p = (struct stack*)malloc(sizeof(*p));

	if (p == NULL) {
		fprintf(stderr, "Memory allocation failed.\n");
		return;
	}

	p->data = x;
	p->next = *s;
	*s = p;
}

// pop from stack
int pop(struct stack **s)
{
	int x;
	struct stack *temp;

	x = (*s)->data;
	temp = *s;
	(*s) = (*s)->next;
	free(temp);

	return x;
}

// find top
int top(struct stack *s)
{ 
    return (s->data);
}

// recursive function to insert an item x in sorted way
void sortedInsert(struct stack** s, int x)
{
	// base case: Either stack is empty or newly inserted item is greater than top (more than all existing)
	if (isEmpty(*s) || x > top(*s)) {
		push(s, x);
		return;
	}

	// if top is greater, remove the top item and recur
	int temp = pop(s);
	sortedInsert(s, x);

	// put back the top item removed earlier
	push(s, temp);
}

// sort the stack
void sortStack(struct stack **s)
{
	// If stack is not empty
	if (!isEmpty(*s)) {
		// Remove the top item
		int x = pop(s);

		// Sort remaining stack
		sortStack(s);

		// Push the top item back in sorted stack
		sortedInsert(s, x);
	}
}

void binarySearch(int n, int l, int r, int mid, struct stack **s)
{
	sortStack(s);
	std::array<int,5> myArr;
	
	if (!isEmpty(*s))
	{
		int x = pop(s);
		for (int i = 0; i < 5; i++)
		{
			myArr[i] = x;
		}

		while (r > 1)
		{
			if (n == myArr[mid])
			{
				cout << n << " is found in stack";
				break;
			}
			else if (n < myArr[mid])
			{
				r = mid - 1;
				binarySearch(n, l, r, mid, s);
				break;
			}
			else if (n > myArr[mid])
			{
				l = mid + 1;
				binarySearch(n, l, r, mid, s);
				break;
			}
			else
			{
				cout << n << " is not in stack";
			}
		}
	}
}

// print stack
void printStack(struct stack* s)
{
	while (s) {
		cout << s->data << " ";
		s = s->next;
	}
	cout << "\n";
}

int main(void)
{
	struct stack* myStack;

	initStack(&myStack);
	push(&myStack, 30);
	push(&myStack, 1);
	push(&myStack, 18);
	push(&myStack, 14);
	push(&myStack, 3);

	cout << "Stack elements before sorting:\n";
	printStack(myStack);

	sortStack(&myStack);

	cout << "Stack elements after sorting:\n";
	printStack(myStack);
	cout << endl;

	binarySearch(10, 0, 5, 3, &myStack);
}