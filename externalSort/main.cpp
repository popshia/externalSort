// 10627130 林冠良 & 10627131 李峻瑋 // Code Blocks 17.12
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <iomanip>
#include <algorithm>
#include <time.h>
#include <math.h>
#include <set>

using namespace std;

typedef struct DataStruct {
    char putID[10];
    char getID[10];
    float weight;
} DataStruct;


static string FileNumber = "0";
static int Count = 0;
static int Command = 0;
static float searchWeight = 0.0;
static fstream input;
static fstream merge1;
static fstream merge2;
static fstream output;

class function1 {
    DataStruct temp;
public:
    vector<DataStruct> tempBuffer;
    vector<DataStruct> outputBuffer;
    int studentNo = 0 ;
    int outputTimes = 0;
    int totalTime = 0;
    static bool CompareWeight( const DataStruct weight1, const DataStruct weight2 ) {
        return weight1.weight > weight2.weight;
    } // CompareWeight()
    
    void InputUnsortedData() {
        DataStruct tempData;
        int countNo = 0;
        outputTimes = 0;
        clock_t time;
        
        input.seekg( 0, input.end );
        studentNo = input.tellg() / sizeof( tempData );
        input.seekg( 0, input.beg );
        int fullTimes = studentNo / 200 + 1 ;
        
        time = clock();
        for ( int i = 0 ; i < studentNo ; i++ ) {
            input.read( (char*)& tempData, sizeof( tempData ) );
            countNo++;
            if ( countNo < 200 ) tempBuffer.push_back( tempData );
            else {
                string outputFileName = "sorted" + FileNumber + "_" + to_string(fullTimes) + "_" + to_string(outputTimes) + ".bin";
                output.open( outputFileName.c_str(), fstream::out | fstream::binary );
                outputTimes++;
                
                tempBuffer.push_back( tempData );
                //sort( tempBuffer.begin(), tempBuffer.end(), CompareWeight );
                bubbleSort();
                for ( int k = 0 ; k < tempBuffer.size() ; k++ ) output.write( (char*)& tempBuffer[k], sizeof( tempBuffer[k] ) );
                
                countNo = 0 ;
                tempBuffer.clear();
                output.close();
            } // write output
        } // insert data
        
        
        string outputFileName = "sorted" + FileNumber + "_" + to_string(fullTimes) + "_" + to_string(outputTimes) + ".bin";
        output.open( outputFileName.c_str(), fstream::out | fstream::binary );
        outputTimes++;
        
        //sort( tempBuffer.begin(), tempBuffer.end(), CompareWeight );
        bubbleSort();
        for ( int i = 0 ; i < tempBuffer.size() ; i++ ) output.write( (char*)& tempBuffer[i], sizeof( tempBuffer[i] ) );
        
        time = clock() - time;
        cout << "Internal Sort: " << time << "ms"<< endl;
        totalTime = time;
        tempBuffer.clear();
        input.close();
        output.close();
    } // InputUnsortedData
    
    
    void MergeFile(){
        string openFile = "0" ;
        string binFileName1 = "0",binFileName2 = "0" ;
        string renameFile = "0";
        int mergeTimes = 0;
        DataStruct tempData;
        outputBuffer.clear();
        clock_t time;
        
        time = clock();
        for( int i = outputTimes+1 ; i != 1 ; i = i / 2 ) mergeTimes++;
        
        for( int i = 0 ; i <= mergeTimes ; i ++ ) {
            for ( int j = 0 ; j < outputTimes / 2 + 1 ; j++ ) {
                binFileName1 = "sorted" + FileNumber + "_" + to_string( outputTimes ) +"_" +  to_string( j * 2 ) + ".bin";
                merge1.open( binFileName1.c_str(), fstream::in | fstream::binary );
                
                binFileName2 = "sorted" + FileNumber + "_" + to_string( outputTimes ) +"_" +  to_string( j * 2 + 1 ) + ".bin";
                merge2.open( binFileName2.c_str(), fstream::in | fstream::binary );
                
                if( !merge2.is_open() ) {
                    merge1.close();
                    renameFile = "sorted" + FileNumber + "_" + to_string( outputTimes /2  ) +"_" +  to_string( outputTimes / 2  ) + ".bin";
                    rename( binFileName1.c_str(), renameFile.c_str() );
                } // if
                
                else {
                    int num = 0;
                    DataStruct compare1, compare2;
                    openFile = "sorted" + FileNumber + "_" + to_string(  outputTimes / 2   ) +"_" +  to_string( j ) + ".bin";
                    output.open( openFile.c_str(), fstream::out | fstream::binary );
                    
                    
                    merge1.read( (char*)& compare1, sizeof( compare1 ) )  ;
                    merge2.read( (char*)& compare2, sizeof( compare2 ) );
                    
                    while( !merge1.eof() || !merge2.eof() ) {
                        if( merge1.eof() ) {
                            output.write( (char*)& compare2, sizeof( compare2 ) );
                            merge2.read( (char*)& compare2, sizeof( compare2 ) )  ;
                        } // else
                        
                        else if( merge2.eof() ) {
                            output.write( (char*)& compare1, sizeof( compare1 ) );
                            merge1.read( (char*)& compare1, sizeof( compare1 ) )  ;
                        } // else
                        
                        else {
                            if ( compare1.weight > compare2.weight ) {
                                output.write( (char*)& compare1, sizeof( compare1 ) );
                                merge1.read( (char*)& compare1, sizeof( compare1 ) )  ;
                            } // if
                            
                            else if ( compare1.weight < compare2.weight ) {
                                output.write( (char*)& compare2, sizeof( compare2 ) );
                                merge2.read( (char*)& compare2, sizeof( compare2 ) )  ;
                            } // if
                            
                            else if ( compare1.weight == compare2.weight ) {
                                output.write( (char*)& compare1, sizeof( compare1 ) );
                                merge1.read( (char*)& compare1, sizeof( compare1 ) )  ;
                                
                            } //else
                        } //else
                    } // merge data*/
                    
                    merge1.close();
                    merge2.close();
                    remove( binFileName1.c_str() );
                    remove( binFileName2.c_str() );
                    //cout<<times<<endl;
                } // else
                
                
                merge1.close();
                merge2.close();
                output.close();
            } // for
            
            outputTimes = outputTimes / 2 ;
        } // for
        
        renameFile = "sorted" + FileNumber  + ".bin";
        rename ( openFile.c_str(), renameFile.c_str() );
        remove( openFile.c_str() );
        
        time = clock() - time;
        totalTime = totalTime + time;
        cout<< "External Sort: " << time << "ms" << endl;
        cout<< "Total Time: " << totalTime << "ms" << endl;
        totalTime = 0;
    } // MergeFile()
    
    
    void bubbleSort(){
        int i, j;
        DataStruct temp;
        for (i = 0; i < tempBuffer.size() - 1; i++){
            for (j = 0; j < tempBuffer.size() - 1 - i; j++){
                if( tempBuffer[j].weight < tempBuffer[j+1].weight) swap(tempBuffer[j], tempBuffer[j+1]);
            }
        }
    }
    
}; // class function1

class function2 : public function1 {
    vector<DataStruct> tempBuffer;
public:
    void Calculate() {
        string file = "sorted" + FileNumber + ".bin";
        DataStruct tempData;
        float weight = 0;
        int position = 0, num = 1;
        
        
        input.open( file.c_str(), fstream::in | fstream::binary );
        input.seekg( 0, input.end );
        int studentNo = input.tellg() / sizeof( tempData );
        input.seekg( 0, input.beg );
        
        input.read( (char*)& tempData, sizeof( tempData ) );
        weight = tempData.weight;
        cout<< "[" << num << "] " << tempData.weight << ": " << position << endl;
        position++;
        num++;
        
        for ( int i = 0 ; i < studentNo ; i++ ) {
            input.read( (char*)& tempData, sizeof( tempData ) );
            if( weight != tempData.weight ) {
                cout<< "[" << num << "] " << tempData.weight << ": " << position << endl;
                weight = tempData.weight;
                num++;
            } // if
            position++;
        } // insert data
        
        input.close();
    } // Calculate()
}; // class function2

class function3: public function2 {
public:
    void Search() {
        string file = "sorted" + FileNumber + ".bin";
        DataStruct tempData;
        float weight = 0;
        int position = 0, num = 1;
        
        
        input.open( file.c_str(), fstream::in | fstream::binary );
        input.seekg( 0, input.end );
        int studentNo = input.tellg() / sizeof( tempData );
        input.seekg( 0, input.beg );
        input.read( (char*)& tempData, sizeof( tempData ) );
        weight = tempData.weight;
        if ( tempData.weight >= searchWeight ) cout<< "[" << num << "] " << "putID: " << tempData.putID << ", getID: " << tempData.getID << ", weight: " << tempData.weight << ", position: " << position << endl;
        position++;
        num++;
        
        for ( int i = 0 ; i < studentNo ; i++ ) {
            input.read( (char*)& tempData, sizeof( tempData ) );
            if( weight != tempData.weight ) {
                if ( tempData.weight >= searchWeight ) {
                    cout<< "[" << num << "] " << "putID: " << tempData.putID << ", getID: " << tempData.getID << ", weight: " << tempData.weight << ", position: " << position << endl;
                    weight = tempData.weight;
                    num++;
                } // found
            } // if
            position++;
        } // insert data
        
        input.close();
    } // Search()
}; // class function3


int main() {
    bool continueOrNot = false;
    bool function1Done = false;
    function1 One;
    function2 Two;
    function3 Three;
    
    do {
        cout << "***********************************************" << endl; // welcome message
        cout << "*****               DS2ex04               *****" << endl;
        cout << "***** 0 : Quit                            *****" << endl;
        cout << "***** 1 : External Sort                   *****" << endl;
        cout << "***** 2 : Create Primary Index            *****" << endl;
        cout << "***** 3 : Search Primary Index            *****" << endl;
        cout << "***********************************************" << endl;
        cout << endl << "Please enter your choice:" << endl;
        
        cin >> Command; // read in user command
        cout << endl;
        
        if ( Command == 0 ) { // bye :(((
            cout << "Bye :(((" << endl;
            return 0;
        } // quit
        
        else if ( Command > 3 || Command < 0 ) {
            cout << "Error command! please enter an acceptable command:" << endl << endl;
            continueOrNot = true;
        } // wrong command
        
        else if ( Command == 1 ) {
            bool function1Confirm = false;
            do {
                cout << "Please enter the file number you want to External Sort or [0] to quit:" << endl;
                cin >> FileNumber;
                
                if ( FileNumber == "0" ) {
                    function1Confirm = true;
                    continueOrNot = true;
                    cout << endl;
                } // quit
                
                else {
                    string binFileName = "pairs" + FileNumber + ".bin";
                    input.open( binFileName.c_str(), fstream::in | fstream::binary );
                    
                    if ( input.is_open() ) {
                        One.InputUnsortedData();
                        One.MergeFile();
                        function1Confirm = true;
                        continueOrNot = true;
                        function1Done = true;
                    } // binary file open successfully
                    
                    else {
                        cout << endl << "*****         file does not exist !       *****" << endl << endl;
                        function1Confirm = false;
                    } // no such file
                } // continue
            } while ( !function1Confirm );
            input.close();
            output.close();
            Count = 0;
        } // mission 1
        
        else if ( Command == 2 ) {
            bool function2Confirm = false;
            do {
                if ( function1Done ) {
                    Two.Calculate();
                    function2Confirm = true;
                    continueOrNot = true;
                    function1Done = false;
                } // open successfully
                
                else {
                    cout << "*****  Please proceed function 1 first !  *****" << endl;
                    function2Confirm = true;
                    continueOrNot = true;
                } // function1 first!
            } while ( !function2Confirm );
            
            Count = 0;
            FileNumber = "0";
        } // mission 2
        
        else if ( Command == 3 ) {
            bool function3Confirm = false;
            do {
                cout << "Please enter the weight you want to search or [0] to quit:" << endl;
                cin >> searchWeight;
                
                if ( searchWeight == 0.0 ) {
                    function3Confirm = true;
                    continueOrNot = true;
                    break;
                } // quit
                
                if ( function1Done ) {
                    Three.Search();
                    continueOrNot = true;
                    function1Done = false;
                } // open successfully
                
                else {
                    cout << "*****  Please proceed function 1 first !  *****" << endl;
                    function3Confirm = true;
                    continueOrNot = true;
                } // function1 first!
                
                cout << endl;
            } while ( !function3Confirm );
            
            Count = 0;
            FileNumber = "0";
        } // mission 2
        
        cout << endl;
    } while ( continueOrNot );
} // main
