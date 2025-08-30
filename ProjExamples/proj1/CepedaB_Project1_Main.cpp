/*
Name: Baldwin Cepeda
GitHub: BaldwinCepeda
Website: http://baldwincepeda.me/
Due date: Sep 8 @11:59


@note to self finish early for extra credit.
*/

// same import as last project
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Sort
{
public:
    int count;    // number of integers
    int *dataAry; // dynamically allocated array

    // Constructor to initialize array and count
    Sort() : count(0), dataAry(nullptr) {}

    // Destructor to free memory
    ~Sort()
    {
        delete[] dataAry;
    }

    // Method to count the number of elements
    int countData(ifstream &inFile, ofstream &logFile)
    {
        logFile << "Entering countData()" << endl;
        int count = 0, temp;

        // Read and count
        while (inFile >> temp)
        {
            count++;
        }

        logFile << "Leaving countData(), count = " << count << endl;
        return count;
    }

    // Method to insert data from file into an array
    void loadData(ifstream &inFile, ofstream &logFile)
    {
        logFile << "Entering loadData()" << endl;
        int index = 0;

        // Read data from file and load into the array
        while (index < count && inFile >> dataAry[index])
        {
            index++;
        }

        logFile << "Leaving loadData()" << endl;
    }

    // Selection sort algorithm implementation
    void selectionSort(ofstream &logFile)
    {
        logFile << "Entering selectionSort()" << endl;

        // Selection sort algorithm
        for (int i = 0; i < count - 1; i++)
        {
            int minIndex = i;
            // IGNORE logFile << "Debugging++I AM HERE+++++" << i << << endl;
            for (int j = i + 1; j < count; j++)
            {
                if (dataAry[j] < dataAry[minIndex])
                {
                    minIndex = j;
                }
            }
            // Swap the found minimum element with the first element
            if (minIndex != i)
            {

                // IGNORE logFile << "Debugging++I AM HERE+++++" << i << << endl;
                swap(dataAry[i], dataAry[minIndex]);
            }

            // Log each iteration of sorting

            // I believe the following approach might be clearer, and I would like to explain why.
            // If we have reached this point, it indicates that we are at least in the first iteration of the selection sort.
            // Displaying 'i' as 0 could be slightly misleading, in my opinion, as it might not accurately reflect the process.
            // I suggest keeping both options, but commenting out one for clarity in the output.

            // logFile << "** After " << i + 1 << " iteration of selection sort **" << endl;
            logFile << "** After " << i << " iteration of selection sort **" << endl;
            printDataAry(logFile);
        }

        // logFile << "Debugging++I AM HERE+++++" << endl;
        logFile << "Leaving selectionSort()" << endl;
    }

    // Print to the file
    void printDataAry(ofstream &outFile)
    {
        for (int i = 0; i < count; i++)
        {
            outFile << dataAry[i] << endl;
        }
    }
};

// Main function similar to Last project A0 and B0
int main(int argc, char *argv[])
{
    // Check if the correct number of arguments are passed
    // how to use ..File.txt File.txt logs.txt
    if (argc != 4)
    {
        cerr << "Usage: " << argv[0] << " <input file> <output file> <log file>" << endl;
        return 1;
    }

    // Open input, output, and log files
    ifstream inFile(argv[1]);
    ofstream outFile(argv[2]);
    ofstream logFile(argv[3]);

    // Check if files opened successfully
    if (!inFile || !outFile || !logFile)
    {
        cerr << "Error opening one of the files." << endl;
        return 1;
    }

    // Create a Sort object
    Sort sorter; // Class from above

    // Step 1: Count the data in the input file
    sorter.count = sorter.countData(inFile, logFile);

    // Step 2: Dynamically allocate an array of the correct size
    sorter.dataAry = new int[sorter.count];

    // Step 3: Re-open the input file to load data into the array
    inFile.close();
    inFile.open(argv[1]);

    sorter.loadData(inFile, logFile);

    // Step 4: Print data before sorting
    outFile << "** Printing data before sorting **" << endl;
    sorter.printDataAry(outFile);

    // Step 5: Sort the data using the selection sort algorithm
    sorter.selectionSort(logFile);

    // Step 6: Print data after sorting
    outFile << "** Printing data after sorting **" << endl;
    sorter.printDataAry(outFile);

    // Step 7: Close all files
    inFile.close();
    outFile.close();
    logFile.close();

    return 0;

    // ignore me Debugging
    // outFile << "** Printing data before sorting **" << endl;
    //
    // cout << "testing:  "
    //
}