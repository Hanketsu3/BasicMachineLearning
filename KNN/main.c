#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define IRIS_DATA_LEN 150

struct iris{
    float sepal_length;
    float sepal_width;
    float petal_length;
    float petal_width;
    char iris_class[17];
};
struct irisDist{
float distance;
char iris_class[17];
};
float calc_dist(struct iris data1, struct iris data2) {
    return sqrt(
                pow(data1.sepal_length-data2.sepal_length, 2)
                + pow(data1.sepal_width-data2.sepal_width, 2)
                + pow(data1.petal_length-data2.petal_length, 2)
                + pow(data1.petal_width-data2.petal_width, 2)
                );
}
void read_data(struct iris * data){
    FILE *cfPtr;

    if ((cfPtr = fopen("iris.txt", "r")) == NULL){
        puts("File could not be opened");
    }
    else{
        for(int i = 0; i < IRIS_DATA_LEN; i++) {
            fscanf(cfPtr, "%f%f%f%f%s", &data[i].sepal_length, &data[i].sepal_width,
               &data[i].petal_length, &data[i].petal_width, data[i].iris_class);
        }
        fclose(cfPtr);
    }
}
void selection_sort_data_distances(struct irisDist * data) {
     int i, j, min_idx;
     for (i = 0; i < IRIS_DATA_LEN-1; i++) {
        min_idx = i;
        for (j = i+1; j < IRIS_DATA_LEN; j++)
            if (data[j].distance < data[min_idx].distance)
                min_idx = j;
        struct irisDist temp = data[min_idx];
        data[min_idx] = data[i];
        data[i] = temp;
    }
}
void print_iris_data(struct iris * data) {
    printf("%12s %12s %12s %12s %16s\n", "sepal_length", "sepal_width",
           "petal_length", "petal_width", "iris_class");
           printf("%12s %12s %12s %12s %16s\n", "----------", "----------",
           "----------", "----------", "----------");
    for(int i = 0; i < IRIS_DATA_LEN; i++) {
        printf("%12.2f %12.2f %12.2f %12.2f %16s\n", data[i].sepal_length, data[i].sepal_width,
           data[i].petal_length, data[i].petal_width, data[i].iris_class);
    }
}
void knn_alg(struct iris data2,struct iris *data)
{
    int k,counterSetosa=0,counterVersicolor=0,counterVirginica=0;
    struct irisDist distances[IRIS_DATA_LEN];
    printf("Please enter k\n");
    scanf("%d",&k);
    for(int i=0;i<IRIS_DATA_LEN;i++)
    {
        distances[i].distance=calc_dist(data2,data[i]);
        strcpy(distances[i].iris_class,data[i].iris_class);
    }
    selection_sort_data_distances(distances);
for(int i=0;i<k;i++)
    {
        printf("%d) Dist: %f Label :%s\n",i+1,distances[i].distance,distances[i].iris_class);
        if(strcmp(distances[i].iris_class,"Iris-setosa")==0)
            counterSetosa++;
        if(strcmp(distances[i].iris_class,"Iris-versicolor")==0)
            counterVersicolor++;
        if(strcmp(distances[i].iris_class,"Iris-virginica")==0)
            counterVirginica++;
    }
    if(counterSetosa>counterVersicolor&&counterSetosa>counterVirginica)
        printf("Predicted label is setosa\n");
    if(counterVersicolor>counterSetosa&&counterVersicolor>counterVirginica)
        printf("Predicted label is versicolor\n");
    if(counterVirginica>counterVersicolor&&counterVirginica>counterSetosa)
        printf("Predicted label is virginica\n");
    if(counterVirginica==counterSetosa && counterVirginica>counterVersicolor)
        printf("Predicted label is either virginica or setosa");
    if(counterVersicolor==counterSetosa && counterVersicolor>counterVirginica)
        printf("Predicted label is either versicolor or setosa");
    if(counterVersicolor==counterVirginica && counterVersicolor>counterSetosa)
        printf("Predicted label is either versicolor or virginica");
    if(counterVersicolor==counterVirginica && counterVersicolor==counterSetosa)
        printf("Predicted label could be either one of them");

}
int main()
{
    struct iris data[IRIS_DATA_LEN];
    int choice;
    struct iris data2;
    read_data(data);
    do{
        printf("Enter your choice\n1)Print the listed data\n2)Predict new iris data\n3)Exit\n");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                print_iris_data(data);
            break;
            case 2:
                printf("Please enter sepal_length, sepal_width, petal_length, and petal_width\n");
                scanf("%f%f%f%f",&data2.sepal_length,&data2.sepal_width,&data2.petal_length,&data2.petal_width);
                knn_alg(data2,data);
            break;
            case 3:
                return 0;
            break;
            default:
                printf("invalid choice\n");
                break;
        }
    }while(1);
    return 0;
}
