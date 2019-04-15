#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define INITIAL 11

typedef struct node{
    char *key;
    char *val;
    struct node *next;
    }Node;

typedef Node *Nodeprt;

typedef struct hashmap{
    size_t size;
    size_t capacity;
    Node **array;
    }HashMap;

size_t Hash(char *key);
HashMap *create(); 
void destroy(HashMap *hashmap);
void insert(HashMap *hashmap, char *key, char *value);
void resizeIfLoaded(HashMap *hashmap);
char *retrieve(HashMap *hashmap, char *key); 
void delete(HashMap *hashmap, char *key);
size_t lookup(HashMap * hashmap, char *key);
void print(HashMap *hashmap);
size_t nextPrime(size_t curr);



int main(void){
    printf("***Printing the hash values for keys: 'd', 'h', 'last', 'first'***\n");
    printf("d: %zu\n", Hash("d"));
    printf("h: %zu\n", Hash("h"));
    printf("last: %zu\n", Hash("last"));
    printf("first:%zu\n", Hash("first"));
    printf("***Inserting keys;values: first;keethan, last; keliner***\n");
    HashMap* hm = create();
    insert(hm, "first", "keethan");
    insert(hm, "last", "kleiner");
    print(hm);
    printf("***Reassigning value for key 'last' with value 'k' ***\n");
    insert(hm, "last", "k");
    print(hm);
    printf("***Deleting node at for key 'last' ***\n");
    delete(hm, "last");
    print(hm);
    printf("***Inserting key:value pairs of the alphabet (ie. a:a, b:b) ***\n");
    char test[2];
    test[1]=0;
    for(char cur = 'a'; cur <= 'z'; ++cur){
      test[0] = cur;
//      printf("%u\n", lookup(hm, test));
      insert(hm, test, test);
    } 
    print(hm);
    printf("***Deleting node at for key 'a' ***\n");
    delete(hm, "a");
    printf("***Retrieving a key that exsists in hash table: 'first'***\n ***retrieving a delted key: 'a'***\n*** retreiving key that DNE: 'DNE' ***\n");
    char* ret_first = retrieve(hm, "first");  
    char* ret_a = retrieve(hm, "a");  
    
    printf("retrieved value at key 'first':  %s\n",ret_first);
    printf("retrieved value at key 'a': %s\n",ret_a);

    char * tmp=retrieve(hm,"DNE"); 
    if (tmp)
        printf("Retriving DNE: %s\n",tmp);
    print(hm);
    destroy(hm);  
    return 0;
}

size_t Hash(char *key){
    size_t out = 0;
    for(size_t i = 0; key[i] != (char)0; ++i){
        out=out*31 + key[i];

    }
    return out;
}

HashMap *create(){
    HashMap *out = malloc(sizeof(HashMap));
    out->size = 0;
    out->capacity = INITIAL;
    out->array = calloc(out->capacity, sizeof(Node*));
    return out;
}


void destroy(HashMap* hashmap){
    for(size_t i = 0; i<hashmap->capacity; ++i){
        Node* cur = hashmap->array[i];
        while(cur){
            Node* next = cur->next;
            free(cur->key);
            free(cur->val);
            free(cur->next);
            cur = next;
        }
    }
    free(hashmap->array);
    free(hashmap);
}

void insert(HashMap* hashmap, char *key, char *value){
    size_t index = lookup(hashmap, key);
    bool exists = false;
    if(hashmap->array[index]){
        exists = true;
        }

    Node* cur = hashmap->array[index];
    if(!exists){
        cur = malloc(sizeof(Node));
        cur->val = malloc((strlen(value)+1)*sizeof(char)); 
        strcpy(cur->val,value);
        cur->key = malloc((strlen(key)+1)*sizeof(char)); 
        strcpy(cur->key,key);
        cur->next = NULL;
        hashmap->array[index] = cur;
        ++hashmap->size;
        resizeIfLoaded(hashmap);
        return;
    }
    while(cur){
        Node* next = cur->next;
        if(!strcmp(key, cur->key)){
            free(cur->val);
            cur->val = malloc((strlen(value)+1)*sizeof(char)); 
            strcpy(cur->val,value);
            return;
        }
        cur = next;
    }
    cur = malloc(sizeof(Node));
    cur->next = NULL;
    cur->key = malloc((strlen(key)+1)*sizeof(char)); 
    strcpy(cur->key,key);
    cur->val = malloc((strlen(value)+1)*sizeof(char)); 
    strcpy(cur->val,value);
    ++hashmap->size;
    resizeIfLoaded(hashmap);
    return;

}

void resizeIfLoaded(HashMap* hashmap){
    if(hashmap->size * 2 > hashmap->capacity){
        printf("resizing\n");
        hashmap->size = 0;
        size_t oldCap = hashmap->capacity;
        hashmap->capacity =nextPrime(oldCap);
        Node** old = hashmap->array;
        hashmap->array = calloc(hashmap->capacity, sizeof(Node*));  //why isn't it sizeof(Node*)?
        for(size_t i = 0; i< oldCap; ++i){
            if(old[i]){
                Node* cur = hashmap->array[i];
                while(cur != NULL){
                    Node* next = cur->next;
                    insert(hashmap, cur->key, cur->val);
                    ++hashmap->size;
                    cur = next;
                }
            }
        }
        free(old);    
    }
}   

char *retrieve(HashMap* hashmap, char *key){
    size_t index = lookup(hashmap, key);
    Node* cur = hashmap->array[index];
    while(cur){
        Node* next = cur->next;
        if(!strcmp(key, cur->key)){
            return cur->val;
        }
        cur = next;
    }
    return "Not found";
}

void delete(HashMap* hashmap, char *key){
    size_t index = lookup(hashmap, key);
    Node* prev = NULL;
    Node* cur = hashmap->array[index];
    while(cur){
        Node* next = cur->next;
        if(!strcmp(key, cur->key)){
            free(cur->val);
            free(cur->key);
            --hashmap->size;
            free(cur);
            if(prev){
                prev->next = next;
            }
            else{
                hashmap->array[index] = NULL;
            }
            return;
        }
        prev = cur;
        cur = next;
    }
    return;
}

size_t lookup(HashMap* hashmap, char *key){
    size_t hashed = Hash(key); 
    size_t index = hashed % hashmap->capacity;
    return index;
}

void print(HashMap* hashmap){
    for(size_t i = 0; i< hashmap->capacity; ++i){
        Node* cur = hashmap->array[i];
        printf("%zu:", i);
        while(cur){
            Node* next = cur->next;
            printf("|| %s=>%s ||",  cur->key, cur->val);
            cur = next;
        }
        puts("\n");
    }
}

size_t nextPrime(size_t curr){
    size_t out = 2*curr +1;
    size_t tmp = out%6;
    size_t i, root;
    out += 5-tmp;
    bool notPrime, notPrimePlus2;
    for(notPrime = true, notPrimePlus2 = true; notPrime && notPrimePlus2 ;out+=6){
        notPrime = false;                             
        notPrimePlus2 = false;                             
        root = floor(sqrt((double)(out)));
        for(i=5; i<=root && !notPrime ; i+=6){
            if(out%i==0 || out%(i+2)==0){
                notPrime = true;
            }
        }
        if(notPrime){
            root = floor(sqrt((double)out+2));
            for(i = 5; i<= root && !notPrime; i+=6){
                if((out+2)%1==0 || (out+2)%(i+2)==0){
                    notPrimePlus2 = true;
                }
            }
        }
    }
    return notPrime ? out-4 : out-6;
}                 
