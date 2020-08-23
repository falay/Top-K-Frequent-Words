struct Node
{
    char* word ;
    int freq ;
    struct Node* next ;
} ;

int compare(const void* arg1, const void* arg2)
{
    struct Node* node1 = (struct Node*)arg1 ;
    struct Node* node2 = (struct Node*)arg2;
    int f1 = node1->freq ;
    int f2 = node2->freq ;
    char* w1 = node1->word ;
    char* w2 = node2->word ;
    if((f1 > f2) || (f1 == f2 && strcmp(w1, w2) < 0))
       return -1 ;
    else if(f1 == f2 && strcmp(w1, w2) == 0)
       return 0 ;
    else
       return 1 ;
}

int get_table_size(struct Node* head)
{
	struct Node* cur = head ;
    int size = 0 ;
    while(cur != NULL)
    {
        size ++ ;
        cur = cur->next ;
    }
    return size ;
}

struct Node* create_freq_table(char** words, int wordsSize)
{
    
    struct Node* head = (struct Node*)malloc(sizeof(struct Node)) ;
    head->word = strdup("") ;
    head->next = NULL ;
    head->freq = 0 ;
    for(int i=0; i<wordsSize; i++)
    {
        char* word = words[i] ;
        struct Node* cur = head ;
        while(cur != NULL)
        {
            if(cur->freq > 0 && strcmp(cur->word, word) == 0)
            {
                cur->freq ++ ;
                break ;
            }
            cur = cur->next ;
        }
        if(cur == NULL)
        {
            struct Node* insert = (struct Node*)malloc(sizeof(struct Node)) ;
            insert->word = strdup(word) ;
            insert->freq = 1 ; 
            struct Node* old_next = head->next ;
            head->next = insert ;
            insert->next = old_next ;
        }
    }             
    
    return head->next ;   
}
       

char** topKFrequent(char** words, int wordsSize, int k, int* returnSize)
{
    struct Node* head = create_freq_table(words, wordsSize) ;
    int size = get_table_size(head) ;
    *returnSize = k ;

    struct Node table[size] ;
    struct Node* cur = head ;
    for(int i=0; i<size; i++)
    {
    	table[i].word = strdup(cur->word) ;
    	table[i].freq = cur->freq ;
    	table[i].next = NULL ;
    	cur = cur->next ;
    }

    qsort(table, size, sizeof(struct Node), compare);
    
    char** res = (char**)malloc(sizeof(char*)*k) ;
    for(int i=0; i<k; i++)
    {
    	res[i] = strdup(table[i].word) ;
    }

    return res ;
}
