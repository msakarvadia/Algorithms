#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <math.h>           
#include <stdbool.h>

#define INITIAL 11

//keys are "strings", values will be "strings"
//treat key "string" as : s+tx31+rx31^2+ix31^3+nx31^4+gx31^5 - NVM this is a random hash, we used a slightly different variation
//use Java's hash function

typedef struct node{
    char *key;
    char *val; //char * means type string
    bool deleted;
}Node;

typedef struct hashMap{
    size_t size;
    size_t capacity;
    Node *array;
}HashMap;

size_t Hash(char *key);    //give where is hashes to; not necessarily the end destination based on collision resolution
HashMap *create();
void destroy(HashMap* hashmap);
void insert(HashMap* hashmap, char *key, char *value); //key and value are strings
void resizeIfLoaded(HashMap* hashmap);
char *retrieve(HashMap* hashmap, char *key);
void delete(HashMap* hashmap, char *key);
size_t lookup(HashMap* hashmap, char *key); //returns the index
void print(HashMap* hashmap);
size_t nextPrime(size_t curr);


int main(void){
    printf("%zu\n", Hash("aaa"));
    HashMap* hm = create();
    insert(hm, "first", "keethan");
    insert(hm, "last", "kleiner");
    insert(hm, "last", "k");
    print(hm);


    return 0;
}

size_t Hash(char *key){
    size_t out = 0;
    for(size_t i =0; key[i]!= (char)0; ++i){
        out=out*31 + key[i];

    }
    return out;
}

HashMap *create(){
    HashMap *out = malloc(sizeof(HashMap));
    out->size = 0;
    out->capacity = INITIAL;
    out->array = calloc(out->capacity, sizeof(Node));
    return out;
}

void destroy(HashMap* hashmap){
    free(hashmap->array);
    free(hashmap);
}

size_t lookup(HashMap* hashmap, char *key){
    size_t hashed = Hash(key);
    size_t index = hashed % hashmap->capacity;
    char* nodeKey = hashmap->array[index].key;
    for(size_t i = 0; nodeKey != NULL && strcmp(nodeKey, key); i++){
        index = (hashed + i*i) % hashmap->capacity;
        nodeKey = hashmap-> array[index].key;
    }
    return index;
}

void resizeIfLoaded(HashMap* hashmap){
    if(hashmap->size * 2 > hashmap->capacity){
        hashmap->size = 0;
        size_t oldCap = hashmap->capacity;
        //TODO find another prime
        hashmap->capacity *=2;
        Node* old = hashmap->array;
        hashmap->array = calloc(hashmap->capacity, sizeof(Node));
        for(size_t i = 0; i< oldCap; ++i){
            if(old[i].key && !old[i].deleted){
                insert(hashmap, old[i].key, old[i].val);
            }
        }
        free(old);    
    }
}

void insert(HashMap* hashmap, char *key, char *value){
    //look up
    //increase size if necessary, if it is inserting a new key
    //insert the pair
    //resize if necessary

    size_t index = lookup(hashmap, key);
    bool exists = hashmap->array[index].key;
    hashmap->array[index] = (Node){key, value, false};
    if(!exists){
        ++hashmap->size;
        resizeIfLoaded(hashmap);
    }
}

void print(HashMap* hashmap){
    Node bucket; 
    for(size_t i = 0; i< hashmap->capacity; ++i){
        bucket = hashmap->array[i];
        printf("%zu: %c | %s=>%s\n", i,bucket.deleted ? 'D' : ' ', bucket.key, bucket.val);
        
        }
    }

size_t nextPrime(size_t curr){
    size_t out = 2*curr +1;
    size_t tmp = out%6;
    out += 5-tmp;
    for(bool notPrime = true; notPrime ;out+=6){
        notPrime = false;
        root = floor(sqrt((double)out));
        for(i=5; i<=root ; i+=6){
            if(out%i==0 || out%(i+2)==0){
                notPrime = true;
                break;
            }
        }
    } 
    return out - 6;
}                 
