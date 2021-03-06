#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define LEARNING_RATE 0.1
#define TEST_SIZE 10000
#define TRAIN_SIZE 60000

typedef struct network{
    size_t numOfLayers;
    size_t *layerSizes;
    double ***weights; //lets us put matrices inside of arrays
    }Network;

typedef struct input{
    double data[784];
    double labels[10];
    }Input;    



Input test_set[10100];                  //made set larger than necessary incase
Input train_set[60100];

double logistic(double x);
double *softmax(double *a, size_t length);
double **matrixMultiply(double **a, double **b, size_t aRow, size_t ab, size_t bCol);
double *vectorByMatrix(double *a, double **b, size_t ab, size_t bCol);
void printMatrix(double **m, size_t rows, size_t cols);
void printVector(double* m, size_t len);
double **createMatrix(size_t rows, size_t cols);
Network *createNetwork(size_t numOfLayers, size_t *layerSizes);
void destroyNetwork(Network *network);
double *feedForward(Network *network, double *input);
void backPropagate(Network *network, double *input, double *expected, double learningRate);
double dotProduct(double *a, double*b, size_t length); 
double vectorByVector(double **m, size_t len);
void fileParser(char* file, Input *inputs);


int main(void){
/*    printf("%f\n", softmax(.2));

    double **a = createMatrix(3,10);
    double **b = createMatrix(10,3);

    for(size_t i = 0; i < 3; ++i){
        for(size_t j=0; j<10; ++j){
            a[i][j] = b[j][i] = j;
        }
    }
    printMatrix(a, 3, 10);
    puts("");
    printMatrix(b, 10, 3);
    puts("");
    double **c = matrixMultiply(a, b, 3, 10 3);
    printMatrix(c, 3, 3);
    puts("");
  */
    bzero(test_set, sizeof(test_set)); 
    bzero(test_set, sizeof(train_set)); 

    printf("reading test set...\n");
    fileParser("mnist_test.csv", test_set);
    printf("reading train set...\n");
    fileParser("mnist_train.csv", train_set);

    size_t layerSizes[] = {10,5,2};
    Network *ann = createNetwork(3,layerSizes);
    printMatrix(ann->weights[0],11,5);
    puts("");
    printMatrix(ann->weights[1],6,2);
    puts("");
    double in[11] = {0.73, 0.3, 0.5, 0.1, 0.11, 0.9, 0.67, 0.42, 0.1, 0.05, 0.09};
    double *out = feedForward(ann, in);
    puts("");
    double exp[2] = {0,1};
    printVector(out, 2);
    backPropagate(ann, in, exp, .5);
    out = feedForward(ann, in);
    printVector(out, 2);

  //  destroyNetwork(ann);
  //MNIST CLASSIFICATION
    puts("");
    size_t MNIST_layerSizes[] = {784,512,10};
    Network *mnistANN = createNetwork(3,MNIST_layerSizes);
    printf("\n%zu\n", MNIST_layerSizes[0]);
    for(size_t i=0; i < 10000; ++i){
        /*
        for(size_t j= 0; j<784; j++){
            printf("%d", test_set[i].data[j]);
            }
        puts("*********************************************"); */
        double* output = feedForward(mnistANN, test_set[i].data); 
        printVector(output, 10);
        }
    for(size_t i=0; i<60000; ++i){
        backPropagate(mnistANN,train_set[i].data,train_set[i].labels, .25);
        }
    for(size_t i=0; i < 10000; ++i){
        double* output = feedForward(mnistANN, test_set[i].data); 
        printVector(output, 10);
        }
//TODO loop thru total test cases on untrained network - calc error
// loop thru total trainset
//loop thru total test set again - calc error
//show the difference in error somehow
    return 0;
}

void fileParser(char* file, Input *inputs){
    int i =0;
    char line[4096];
    FILE * f = fopen(file, "r");
    if(f==NULL){
        perror("error while opening file.\n");
        exit(EXIT_FAILURE);
    }

    while(!feof(f)){
        if(fgets(line, 4096-1,f)==NULL){
            break;
        }
        else{
          //  printf("%s\n",line);
            char* tok = strtok(line, ",");
            while(tok != NULL){
                if(i==0){
                    inputs->labels[atoi(tok)] = 1.0;
                    for(size_t j=0; j<10; j++)
                        printf("%f ", inputs->labels[j]);
                     puts(" ");   
                    //printf("label made\n");
                    i++;
                    continue;
                }
                inputs->data[i-1] = atof(tok);
          //      printf("%d", inputs->data[i-1]);

                tok = strtok(NULL,",");
                i++;
            }
        }

    }    
    fclose(f);

}

Network *createNetwork(size_t numOfLayers, size_t *layerSizes){
    srand(time(NULL));
    Network *out = malloc(sizeof(Network));
    out->numOfLayers = numOfLayers;
    out->layerSizes = malloc(sizeof(size_t)*numOfLayers);
    memcpy(out->layerSizes, layerSizes, sizeof(size_t)*numOfLayers);
    printf("creat layer size %zu\n", layerSizes[0]);
    printf("out layersize[0] %zu \n", out->layerSizes[0]);
    out -> weights = malloc(sizeof(double **)* (numOfLayers - 1));
    for(size_t m = 0; m < numOfLayers-1; ++m){
        out->weights[m] = createMatrix(layerSizes[m]+1, layerSizes[m+1]);
        for(size_t r=0; r< layerSizes[m]+1; ++r){
            for(size_t c=0; c<layerSizes[m+1]; ++c){
                out->weights[m][r][c] = (double)rand()/(double)(RAND_MAX/1);
            }
        }
    }
    return out;
}



void backPropagate(Network *network, double *input, double *expected, double learningRate){
    double **layers = malloc(sizeof(double*)*(network->numOfLayers-1)); //stores output signals of each layer
    layers[0] = malloc(sizeof(double)*(network->layerSizes[0]+1));
    memcpy(layers[0]+1, input, sizeof(double)*(network->layerSizes[0]));  //copying inputs into layer zero
    layers[0][0] = 1;                                                     //bias in the front

    size_t k,i, j;
    for(i = 0; i<network->numOfLayers-2; ++i){    //only iterates thru hidden layers
        layers[i+1] = vectorByMatrix(layers[i], network->weights[i], network->layerSizes[i+1], network->layerSizes[i]+1);
        layers[i+1] = realloc(layers[i+1], sizeof(double)*(network->layerSizes[i+1]+1));
        for(size_t j = network->layerSizes[i+1]; j>0; --j){
            layers[i+1][j] = logistic(layers[i+1][j-1]);  //move everything down by 1, and prepend a 1 for the rest of the layers (only have bias for input so far)
        }
        layers[i+1][0] = 1;
    }
    layers[i+1] = vectorByMatrix(layers[i], network->weights[i], network->layerSizes[i]+1, network->layerSizes[i+1]);
    for(size_t j = 0; j< network->layerSizes[i+1]; ++j){
        layers[i+1][j] = logistic(layers[i+1][j]);
    }

    double **deltas = malloc(sizeof(double*)*(i+1));
    deltas[i]=malloc(sizeof(double)* network->layerSizes[i+1]);
    for(j = 0 ; j<network->layerSizes[i+1]; ++j){
        deltas[i][j] = layers[i+1][j] * (1-layers[i+1][j]) *(expected[j]- layers[i+1][j]);//TODO check this line
    }
    //calculate deltas for hidden layers
    size_t bias = 0;
    for(--i; (int)i>=0 ; --i){
        deltas[i]=malloc(sizeof(double)* (1+network->layerSizes[i+1])); //plus 1 for the bias statement
        for(j =0; j<network->layerSizes[i+1]+1; ++j){
            deltas[i][j] = layers[i+1][j]*(1-layers[i+1][j])*(dotProduct(deltas[i+1],network->weights[i+1][j],network->layerSizes[i+2]+bias));//layers contains output from each node; we want to update weights coming from a node
        }
        bias = 1;
    }
    for(i = 0; i < network->numOfLayers-1; ++i){
        for(j=0; j< network->layerSizes[i]+1; ++j){
            for(k=0; k<network->layerSizes[i+1]+bias; ++k){
                network->weights[i][j][k] = network->weights[i][j][k] + learningRate*deltas[i][k]*layers[i][j];
            }
        }
        if(i == network->numOfLayers-2){
            bias = 0;
        }    
    }
}                                        

double *feedForward(Network *network, double *input){
    double* old = malloc(sizeof(double)*(network->layerSizes[0]+1)), *new;
    printf("%zu", network->layerSizes[0]);
    memcpy(old+1, input, sizeof(double)*network->layerSizes[0]);
    old[0] = 1;

    size_t i, j;
    for(i = 0; i< network->numOfLayers -2; ++i){
        new = vectorByMatrix(old, network->weights[i], network->layerSizes[i]+1, network->layerSizes[i+1]);
        free(old);
        old = realloc(new, sizeof(double)*(network->layerSizes[i+1]+1));
        for(j = network->layerSizes[i+1]; j>0; --j){
            old[j] = logistic(old[j-1]);
        }
        old[0] = 1;
    }                                   
    new = vectorByMatrix(old, network->weights[i], network->layerSizes[i]+1, network->layerSizes[i+1]);
    printVector(new, 10);
    for(j = 0; j< network->layerSizes[i+1]; ++j){
        new[j] = logistic(new[j]);
        }
    softmax(new, network->layerSizes[i+1]);
    free(old);
    return new;
}

double *softmax(double *a, size_t length){ //INCORRECT
    double sum = 0;
    for(size_t i=0; i < length; ++i){
        sum+= exp(a[i]);
    }
    double *new = malloc(sizeof(double)*length);
    for(size_t j=0; j<length; j++){
        new[j]=exp(a[j])/sum;
        }
    return new;

}

double logistic(double x){               //this is not a true sigmoid, 
    x-=0.5;
    return 1 / (1 + exp(-(x)));
    //return .5 + (exp(x)-exp(-x))/(exp(x)+exp(-x));
}

double **matrixMultiply(double **a, double **b, size_t aRow, size_t ab, size_t bCol){
    double **out = malloc(aRow*sizeof(double*));
    for(size_t i = 0; i< aRow; ++i){
        out[i] = calloc(bCol, sizeof(double));
    }
    for(size_t i = 0; i< aRow; ++i){
        for(size_t j = 0; j<bCol; ++j){
            for(size_t k=0; k<ab; ++k){
                out[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return out;
}

double *vectorByMatrix(double *a, double **b, size_t ab, size_t bCol){
    return *matrixMultiply(&a, b, 1, ab, bCol);
    }
                                             /*
double* vectorByVector(double *m, double *n,size_t len){
    return *matrixMultiply(&m, &n, 1, len, len);
    }                                          */

void printMatrix(double **m, size_t rows, size_t cols){
    for(size_t i = 0; i<rows; ++i){
        for(size_t j= 0; j<cols; ++j){
            printf(" %.2f ", m[i][j]);
        }
        puts("");
    }
}

void printVector(double* m, size_t len){
    printMatrix(&m, 1, len);
}

double **createMatrix(size_t rows, size_t cols){
    double **out = malloc(rows *sizeof(double*));
    for(size_t i = 0; i<rows; ++i){
        out[i] = malloc(cols * sizeof(double*));
        }
    return out;
}
  /*                                          
void destroyNetwork(Network *network){                                
//    for(size_t m = 0; m<network->numOfLayers-1; ++m){
//        for(size_t r = 0; r< network->layerSizes[m]+1; ++r){
//            free(network->weights[m][r]);
//        }
//        free(network->weights[m]);
//    }                                                                  
    for(size_t m = 0; m<network->numOfLayers-1; ++m){
        destroyMatrix(&(network->weights[m]), network->layerSizes[m]+1);
    }
    
    free(network->weights);
    free(network->layerSizes);
    free(network);
}

void destroyMatrix(double** m,  )             */

double dotProduct(double *a, double*b, size_t length){
    double sum= 0;
    for(size_t i = 0; i<length; i++){
        sum += a[i]*b[i];
    }
    return sum;
}
