#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <time.h>
#include "Dealership.h"
#include <ctime>
#include <string.h>

using namespace std;

#define N 100

#define NAME_STR 0
#define POSITION_STR 1
#define TEL_STR 2
#define EMAIL_STR 3

#define PATH_WORKERS "D:\\Dealership\\Workers data.txt"
#define SEPARATOR_STRING "------------------------------------\n"

void PrintArray(char** arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << arr[i];
    }
}

char** Add(char** strings, int* strCount, char* newStr)
{
    if ((*strCount) == 0)
    {
        strings = new char* [1];
        strings[0] = new char[N];
        (*strCount)++;
        strcpy(strings[0], newStr);
    }
    else
    {
        char** temp = new char* [*strCount];
        for (int i = 0; i < *strCount; i++)
        {
            temp[i] = new char[N];
            strcpy(temp[i], strings[i]);
            delete[] strings[i];
        }
        delete[] strings;



        (*strCount)++;
        strings = new char* [*strCount];
        for (int i = 0; i < *strCount - 1; i++)
        {
            strings[i] = new char[N];
            strcpy(strings[i], temp[i]);
            delete[] temp[i];
        }
        delete[] temp;
        strings[*strCount - 1] = new char[N];
        strcpy(strings[*strCount - 1], newStr);
        //(*strCount)++;
    }
    return strings;
}

Worker InitWorker()
{
    Worker worker;



    cout << "Enter worker`s name - ";
    cin >> worker.Name.name;
    cout << "Enter worker`s lastname - ";
    cin >> worker.Name.lastName;
    cout << "Enter worker`s middlename - ";
    cin >> worker.Name.middleName;



    cout << "Enter worker`s position - ";
    cin >> worker.position;



    cout << "Enter worker`s telephone number - ";
    cin >> worker.telephone;



    cout << "Enter worker`s E-mail - ";
    cin >> worker.Email;



    return worker;



}

Worker* Add(Worker* workers, int* workerCount, Worker newWorker)
{

    if (*workerCount == 0)
    {
        workers = new Worker[1];
        workers[0] = newWorker;
        (*workerCount)++;
    }
    else
    {
        Worker* temp = new Worker[*workerCount];
        for (int i = 0; i < *workerCount; i++)
        {
            temp[i] = workers[i];
        }
        delete[] workers;



        workers = new Worker[*workerCount + 1];



        for (int i = 0; i < *workerCount; i++)
        {
            workers[i] = temp[i];
        }
        delete[] temp;
        workers[*workerCount] = newWorker;
        (*workerCount)++;
    }



    return workers;
}

void RewriteWorkersDataToFile(Worker* workers, int workerCount)
{
    FILE* file = fopen(PATH_WORKERS, "w");
    for (int i = 0; i < workerCount; i++)
    {
        fprintf(file, "%s %s %s\n", workers[i].Name.name, workers[i].Name.lastName, workers[i].Name.middleName);
        fprintf(file, "%s\n", workers[i].position);
        fprintf(file, "%s\n", workers[i].telephone);
        fprintf(file, "%s\n", workers[i].Email);
        fprintf(file, "%s", SEPARATOR_STRING);
    }
    fclose(file);
}

Worker* AddNewWorker(Worker* workers, int* workerCount)
{
    Worker newWorker = InitWorker();
    workers = Add(workers, workerCount, newWorker);
    RewriteWorkersDataToFile(workers, *workerCount);
    return workers;
}

void GetWorkerDataString(char**& workerData, int* strCount, FILE* workerDataFile)
{
    char string[N];
    do
    {
        fgets(string, N, workerDataFile);
        workerData = Add(workerData, strCount, string);



    } while (strcmp(string, SEPARATOR_STRING) != 0);

}

void TransferDataFromArrayToWorker(Worker* worker, char** data)
{
    char temp[N];
    strcpy(temp, data[NAME_STR]);

    strcpy(worker->Name.name, strtok(data[NAME_STR], " \n"));
    //cout << worker->Name.name << endl;



    strcpy(data[NAME_STR], temp);
    strcpy(worker->Name.lastName, strtok(NULL, " \n"));
    //cout << worker->Name.lastName << endl;



    strcpy(data[NAME_STR], temp);
    strcpy(worker->Name.middleName, strtok(NULL, " \n"));
    //cout << worker->Name.middleName << endl;



    strcpy(worker->position, data[POSITION_STR]);
    strcpy(worker->telephone, data[TEL_STR]);
    strcpy(worker->Email, data[EMAIL_STR]);
}

int CountWorkersInFile(FILE* file)
{
    int count = 0;
    char string[N];
    char lastSymbol;
    
    do
    {
        fgets(string, N, file);
        if (strcmp(string, SEPARATOR_STRING) == 0)
        {
            count++;
        }
        lastSymbol = fgetc(file);
        fseek(file, -1, SEEK_CUR);
    } while (lastSymbol != EOF);
    fseek(file, 0, SEEK_SET);
    return count;
}

void GetWorkersDataFromFile(Worker*& workers, int* workerCount)
{
    FILE* workerDataFile = fopen(PATH_WORKERS, "r");

    char** workerDataStrings = nullptr;
    int strCount = 0;
    char lastSymbol = ' ';
    int workersInFile = CountWorkersInFile(workerDataFile);

    Worker worker;   

    for (int i = 0; i < workersInFile; i++)
    {
        GetWorkerDataString(workerDataStrings, &strCount, workerDataFile);
        //PrintArray(workerDataStrings, strCount);
        TransferDataFromArrayToWorker(&worker, workerDataStrings);
        workers = Add(workers, workerCount, worker);
        workerDataStrings = nullptr;
        strCount = 0;
    }
   
}

int main()
{
    FILE* workersData;
    FILE* carsData;
    FILE* sellsData;

    Worker* workers = nullptr;
    int workerCount = 0;

    Car* cars = nullptr;
    int carCount = 0;

    Sell* sells = nullptr;
    int sellCount = 0;

    GetWorkersDataFromFile(workers, &workerCount);

    //cout << "AAAA" << endl;

    return 0;
}