#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// for Schmitt Trigger
float   VRef                =   0.0;
float   Ra                  =   0;
float   Rb                  =   0;
float   R1                  =   0;
float   Voltage             =   0.0;    //used for impedance & current
float   Voltage2            =   0.0;

// for parallel resistance
vector<float>   resistors;
int     nOfRes              =   0;
float   overallResistance   =   0.0;

// for impedance
float   resistance          =   0.0;    //used for current as well
float   impedance           =   0.0;    //used for current as well

string  helpstring          =   "-a, -A, -I, -i\t\tCalculate Impedance in Ampere\n-C, -c, -V, -v\t\tCalculate Current in Volts\n-R, -r\t\t\tCalculate Resistance in Ohms\n-RP, -rp\t\tCalculate Parallel Resistance\n-s, -S\t\t\tSchmitt Trigger\nUse -h -[command] for further info";
string  schmittstring       =   "SCHMITT TRIGGER RESISTOR CALC\nExpects 4 values:\nVRef, Ra, Rb, R1";
string  impedancestring     =   "IMPEDANCE IN AMPERE CALC\nExpects 2 values:\nCurrent in Volts, Resistance in Ohms";
string  voltagestring       =   "CURRENT IN VOLTS CALC\nExpects 2 values:\nImpedance in Amperes, Resistance in Ohms";
string  resistancestring    =   "RESISTANCE IN OHMS\nExpects 2 values:\nCurrent in Volts, Impedance in Amperes";
string  parallelstring      =   "PARALLEL RESISTANCE IN OHMS\nExpects n values:\nResistance 1 in Ohms, Resistance 2 in Ohms, ...";

float calcVoltage1() {
    return ((Ra+Rb)/(Ra+Rb+R1))*VRef;
}

float calcVoltage2() {
    return (Rb/(Rb+R1+Ra))*VRef;
}

float calcParallelResistance(int length) {
    float   multiply    =   resistors.at(0);
    float   additive    =   resistors.at(0);
    for(int i=1; i<length; i++) {
        multiply    =   multiply * resistors.at(i);
        additive    +=  resistors.at(i);
    }

    return (multiply/additive);
}

float calcResistance() {
    return (Voltage/impedance);
}

float calcImpedance() {
    return (Voltage/resistance);
}

float calcCurrent() {
    return (impedance * resistance);
}

void printResults(int type) {
    /*
    0 - Schmitt Trigger
    1 - Resistance Parallel
    2 - Resistance
    3 - Current
    4 - Impedance
    */
   if(type == 0) {
        cout << "Va: " << Voltage << endl;
        cout << "Trigger Voltage: " << Voltage2 << endl;
   } else if(type == 1) {
       cout << "Parallel Resistance: " << overallResistance << endl;
   } else if(type == 2) {
       cout << "Resistance in Ohms: " << resistance << endl;
   } else if(type == 3) {
       cout << "Current in Volts: " << Voltage << endl;
   } else if(type == 4) {
       cout << "Impedance in Ampere: " << impedance << endl;
   }
}

int main(int argc, char *argv[]) {
    if(argc > 1) {
        if(strncmp(argv[1], "-h", 2) == 0 || strncmp(argv[1], "-help", 5) == 0 || strncmp(argv[1], "--h", 3) == 0 || strncmp(argv[1], "--help", 6) == 0) {
            if(argc > 2) {
                if(strncmp(argv[2], "-s", 2) == 0 || strncmp(argv[2], "-S", 2) == 0) {
                    cout << schmittstring << endl;
                } else if(strncmp(argv[2], "-RP", 3) == 0 || strncmp(argv[2], "-rp", 3) == 0) {
                    cout << parallelstring << endl;
                } else if(strncmp(argv[2], "-r", 2) == 0 || strncmp(argv[2], "-R", 2) == 0) {
                    cout << resistancestring << endl;
                } else if(strncmp(argv[2], "-v", 2) == 0 || strncmp(argv[2], "-V", 2) == 0 || strncmp(argv[2], "-c", 2) == 0 || strncmp(argv[2], "-C", 2) == 0) {
                    cout << voltagestring << endl;
                } else if(strncmp(argv[2], "-i", 2) == 0 || strncmp(argv[2], "-I", 2) == 0 || strncmp(argv[2], "-a", 2) == 0 || strncmp(argv[2], "-A", 2) == 0) {
                    cout << impedancestring << endl;
                }
            } else {
                cout << helpstring << endl;
            }
            exit(1);
        } else if(strncmp(argv[1], "-s", 2) == 0 || strncmp(argv[1], "-S", 2) == 0) {
            if(argc > 2) {
                VRef    =   stof(argv[2]);
                Ra      =   stof(argv[3]);
                Rb      =   stof(argv[4]);
                R1      =   stof(argv[5]);
            } else {
                cout << "VRef?" << endl << "> ";
                cin >> VRef;
                cout << "Ra?" << endl << "> ";
                cin >> Ra;
                cout << "Rb?" << endl << "> ";
                cin >> Rb;
                cout << "R1?" << endl << "> ";
                cin >> R1;
            }
            Voltage         =   calcVoltage1();
            Voltage2        =   calcVoltage2();
            printResults(0);
        } else if(strncmp(argv[1], "-rp", 3) == 0 || strncmp(argv[1], "-RP", 3) == 0) {
            if(argc > 2) {
                for(int i=2; i<argc; i++) {
                    resistors.push_back(stof(argv[i]));
                }
            overallResistance   =   calcParallelResistance(argc-2);
            } else {
                cout << "How many Resistors are there?" << endl << "> ";
                cin >> nOfRes;
                for(int i=0; i<nOfRes; i++) {
                    float   in  =   0;
                    cout << "Value of Resistor " << i+1 << "?" << endl << "> ";
                    cin >> in;
                    resistors.push_back(in);
                }
            overallResistance   =   calcParallelResistance(nOfRes);
            }
            printResults(1);
        } else if(strncmp(argv[1], "-r", 2) == 0 || strncmp(argv[1], "-R", 2) == 0) {
            if(argc > 2) {
                Voltage     =   stof(argv[2]);
                impedance   =   stof(argv[3]);
            } else {
                cout << "Calculating Resistance in Ohms" << endl;
                cout << "Current/Volts?" << endl << "> ";
                cin >> Voltage;
                cout << "Impedance/Ampere?" << endl << "> ";
                cin >> impedance;
            }
            resistance  =   calcResistance();
            printResults(2);
        } else if(strncmp(argv[1], "-v", 2) == 0 || strncmp(argv[1], "-V", 2) == 0 || strncmp(argv[1], "-c", 2) == 0 || strncmp(argv[1], "-C", 2) == 0) {
            if(argc > 2) {
                impedance   =   stof(argv[2]);
                resistance  =   stof(argv[3]);
            } else {
                cout << "Calculating Current in Volts" << endl;
                cout << "Impedance/Ampere?" << endl << "> ";
                cin >> impedance;
                cout << "Resistance?" << endl << "> ";
                cin >> resistance;
            }
            Voltage =   calcCurrent();
            printResults(3);
        } else if(strncmp(argv[1], "-i", 2) == 0 || strncmp(argv[1], "-I", 2) == 0 || strncmp(argv[1], "-a", 2) == 0 || strncmp(argv[1], "-A", 2) == 0) {
            if(argc > 2) {
                Voltage     =   stof(argv[2]);
                resistance  =   stof(argv[3]);
            } else {
                cout << "Calculating Impedance in Ampere" << endl;
                cout << "Current/Volts?" << endl << "> ";
                cin >> Voltage;
                cout << "Resistance?" << endl << "> ";
                cin >> resistance;
            }
            impedance   =   calcImpedance();
            printResults(4);
        }
    } else {
        cout << helpstring << endl;
    }

    exit(1);
}
