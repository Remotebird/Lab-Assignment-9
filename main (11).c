You are going to implement hashing with chaining with separate chaining. Please implement your hash function accordingly to distribute the data evenly in the array into the original code.

#include <stdio.h>

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
};

// Fill out this structure
struct HashType* initHashTable(int size) {
    struct HashType* ht = (struct HashType*)malloc(sizeof(struct HashType));
    if (!ht) return NULL;
    ht->size = size;
    ht->buckets = (struct Node**)malloc(sizeof(struct Node*) * size);
    if (!ht->buckets) {
        free(ht);
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        ht->buckets[i] = NULL;
    }
    return ht;
}

// Compute the hash function
int hash(int x) {
    return x % 23;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}
		fclose(inFile);
	}
	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType* ht) {
    for (int i = 0; i < ht->size; i++) {
        struct Node* node = ht->buckets[i];
        if (node) {
            printf("index %d ->", i);
            while (node) {
                printf(" %d, %c, %d ->", node->data.id, node->data.name, node->data.order);
                node = node->next;
            }
            printf(" NULL\n");
        }
    }
}


int main(void) {
    struct RecordType *pRecords;
    int recordSz = parseData("input.txt", &pRecords);

    printRecords(pRecords, recordSz);

    struct HashType* hashTable = initHashTable(23);

    for (int i = 0; i < recordSz; i++) {
        insertRecord(hashTable, pRecords[i]);
    }
    
    displayRecordsInHash(hashTable);

    return 0;
}
