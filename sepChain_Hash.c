#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#define INITIAL 11

typedef struct node{
    char *key;
    char *val;
    Node* next;
    }Node;

typedef struct hashmap{
    size_t size;
    size_t capacity;
    Node **array;
    }HashMap;

size_t hash(char *key);
HashMap *create(); 
void destroy(HashMap *hashmap);
void insert(HashMap *hashmap, char *key, char *value);
void resizeIfLoaded(HahsMap *hashmap);
char *retrieve(HashMap *hashmap, char *key); 
void delete(HashMap *hashmap, char *key);
size_t lookup(HashMap * hashmap, char *key);
void print(HashMap *hashmap);
size_t nextPrime(size_t curr);



int main(void){
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
        if(hashmap->array[i]){
            while(hashmap->array[i] != NULL){
                next = hashmap->array[i]->next;
                free(hashmap->array[i]->key);
                free(hashmap->array[i]->val);
                free(hashmap->array[i]->next);
                hashmap->array[i] = next;
            }

        }
    }
    free(hashmap->array);
    free(hashmap);
}

void insert(HashMap* hashmap, char *key, char *value){
    size_t index = lookup(hashmap, key);
    bool exists = hashmap->array[index]->key;

    cur = hashmap->array[index];
    if(!exists){
        cur->val = malloc((strlen(value)+1)*sizeof(char)); 
        strcpy(cur->val,value);
        cur->key = malloc((strlen(key)+1)*sizeof(char)); 
        strcpy(cur->key,key);
        ++hashmap->size;
        resizeIfLoaded(hashmap);
        return;
    }
    while(cur != NULL){
        next = cur->next;
        if(exists && !strcmp(key, cur->key)){
            free(cur->val);
            cur->val = malloc((strlen(value)+1)*sizeof(char)); 
            strcpy(cur->val,value);
            return;
        }
        cur = next;
    }
    cur->val = malloc((strlen(value)+1)*sizeof(char)); 
    strcpy(cur->val,value);
    cur->key = malloc((strlen(key)+1)*sizeof(char)); 
    strcpy(cur->key,key);
    ++hashmap->size;
    resizeIfLoaded(hashmap);
    return;

}

void resizeIfLoaded(HashMap* hashmap){
    if(hashmap->size * 2 > hashmap->capacity){
        printf("resizing\n");
        hashmap->size = 0;
        size_t oldCap = hashmap->capacity;
        size_t index;
        hashmap->capacity =nextPrime(oldCap);
        Node* old = hashmap->array;
        hashmap->array = calloc(hashmap->capacity, sizeof(Node*));  //why isn't it sizeof(Node*)?
        for(size_t i = 0; i< oldCap; ++i){
            if(old[i].key){
                cur = hashmap->array[index];
                while(cur != NULL){
                    next = cur->next;
                    insert(hashmap, cur->key, cur->val);
                    ++hashmap->size;
                }
            }
        }
        free(old);    
    }
}   

char *retrieve(HashMap* hashmap, char *key){
    size_t index = lookup(hashmap, key);
    cur = hashmap->array[index];
    while(cur != NULL){
        next = cur->next;
        if(exists && !strcmp(key, cur->key)){
            return cur->val;
        }
        cur = next;
    }
    return "Not found";
}
//TODO fix delete func - return if key isnt present or if u managed to delete.
//decrement size if deleted
void delete(HashMap* hashmap, char *key){
    size_t index = lookup(hashmap, key);
    if(hashmap->array[index].key){
        hashmap->array[index].deleted = true;
        --hashmap->size;
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
