#include <stdio.h>
#include <stdlib.h>

// Anthony Le
// COP3502 Lab 4

typedef struct node {
	char letter;
	struct node* next;
} node;

// Returns number of nodes in the linkedList.
int length(node* head)
{
	int counter = 0;

	node* temp = head;

	// traverse list and add to counter
	while(temp!=NULL)
	{
		counter++;
		temp = temp->next;
	}

	return counter;
}

// parses the string in the linkedList
//  if the linked list is head -> |a|->|b|->|c|
//  then toCString function wil return "abc"
char* toCString(node* head)
{
	// dynamically allocate string of size of linked list
	int stringLength = length(head);
	char* string = malloc(sizeof(char)*stringLength);

	node* temp = head;

	// parse linked list letters to string
	int i;
	for(i=0; i<stringLength; i++)
	{
		string[i] = temp->letter;
		temp = temp->next;
	}

	// append null character to end of string
	string[i] = '\0';

	return string;
}

// inserts character to the linkedlist
// f the linked list is head -> |a|->|b|->|c|
// then insertChar(&head, 'x') will update the linked list as foolows:
// head -> |a|->|b|->|c|->|x|
void insertChar(node** pHead, char c)
{
	// create new node with passed character
	node* newNode = malloc(sizeof(node));

	newNode->letter = c;
	newNode->next = NULL;

	if(*pHead == NULL)
		*pHead = newNode;
	// traverse to end of list and insert new node with char
	else
	{
		node* temp = *pHead;

		while(temp->next!=NULL)
			temp = temp->next;

		temp->next = newNode;
	}
}

// deletes all nodes in the linkedList.
void deleteList(node** pHead)
{
	node* temp = *pHead;

	while(temp!=NULL)
	{
		*pHead = temp->next;
		free(temp);
		temp = *pHead;
	}

	*pHead = NULL;
}

int main(void)
{
	int i, strLen, numInputs;
	node* head = NULL;
	char* str;
	char c;
	FILE* inFile = fopen("input.txt","r");

	fscanf(inFile, " %d\n", &numInputs);
	
	while (numInputs-- > 0)
	{
		fscanf(inFile, " %d\n", &strLen);
		for (i = 0; i < strLen; i++)
		{
			fscanf(inFile," %c", &c);
			insertChar(&head, c);
		}

		str = toCString(head);
		printf("String is : %s\n", str);

		free(str);
		deleteList(&head);

		if (head != NULL)
		{
			printf("deleteList is not correct!");
			break;
		}
	}

	fclose(inFile);
}