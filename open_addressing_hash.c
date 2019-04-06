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
size_t lookup(HashMap* hashmap, char *key); //returns the index
void print(HashMap* hashmap);
size_t nextPrime(size_t curr);
void delete(HashMap* hashmap, char *key);


int main(void){
    printf("%zu\n", Hash("aa"));
    HashMap* hm = create();
    insert(hm, "f", "keethan");
    print(hm);
    insert(hm, "l", "kleiner");
    print(hm);
    insert(hm, "l", "k");
    print(hm);
/*    char test[2];
    test[1]=0;
    for(char cur = 'a'; cur <= 'z'; ++cur){
        test[0] = cur;
        insert(hm, test, test);
    } 
    printf("%s\n",retrieve(hm, "first"));
    printf("%s\n",retrieve(hm, "DNE"));
    print(hm);
    destroy(hm);
      */
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
    out->array = calloc(out->capacity, sizeof(Node));
    return out;
}

void destroy(HashMap* hashmap){
    for(size_t i = 0; i<hashmap->capacity; ++i){
        if(hashmap->array[i].key){
        free(hashmap->array[i].key);
        free(hashmap->array[i].val);
        }
    }
    free(hashmap->array);
    free(hashmap);
}

char *retrieve(HashMap* hashmap, char *key){
    size_t index = lookup(hashmap, key);
    if (hashmap->array[index].deleted){
        return NULL; 
    }
    return hashmap->array[index].val;
}

size_t lookup(HashMap* hashmap, char *key){
    size_t hashed = Hash(key), index = hashed % hashmap->capacity;
    char* nodeKey = hashmap->array[index].key;
    for(size_t i = 0; nodeKey != NULL; i++){
        index = (hashed + i*i) % hashmap->capacity;
        if(!strcmp(nodeKey, key)){  //when nodeKey and key are the same, strcmp = FALSE
          return index;
        }
        nodeKey = hashmap->array[index].key;

    }
    return hashed % hashmap->capacity;
}

void resizeIfLoaded(HashMap* hashmap){
    if(hashmap->size * 2 > hashmap->capacity){
        hashmap->size = 0;
        size_t oldCap = hashmap->capacity;
        size_t index;
        hashmap->capacity =nextPrime(oldCap);
        Node* old = hashmap->array;
        hashmap->array = calloc(hashmap->capacity, sizeof(Node));  //why isn't it sizeof(Node*)?
        for(size_t i = 0; i< oldCap; ++i){
            if(old[i].key){
                if(old[i].deleted){
                    free(old[i].val);
                    free(old[i].key);
                }   
                else{

                    index = lookup(hashmap, old[i].key);
                    hashmap->array[index].key =old[i].key;
                    hashmap->array[index].val = old[i].val;
                    ++hashmap->size;
                }  
                free(old);    
            }
        }
    }
}   

//TODO: this insert function just inserts every key at 0, pls get working func
void insert(HashMap* hashmap, char *key, char *value){
    //look up
    //increase size if necessary, if it is inserting a new key
    //insert the pair
    //resize if necessary

    size_t index = lookup(hashmap, key);
    bool exists = hashmap->array[index].key;
    hashmap->array[index].deleted = false;

    if(exists){
        free(hashmap->array[index].val);
    }

    hashmap->array[index].val = malloc((strlen(value)+1)*sizeof(char)); 
    strcpy(hashmap->array[index].val,value);

    if(!exists){
        hashmap->array[index].key = malloc((strlen(key)+1)*sizeof(char)); 
        //hashmap->array[index].val = malloc((strlen(value)+1)*sizeof(char)); 
        strcpy(hashmap->array[index].key,key);
        //strcpy(hashmap->array[index].val,value);
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

void delete(HashMap* hashmap, char *key){
    //lazy deletion - only mark things as deleted, don't actually free or replace any memory
    size_t index = lookup(hashmap, key);
    if(hashmap->array[index].key){
        hashmap->array[index].deleted = true;
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
