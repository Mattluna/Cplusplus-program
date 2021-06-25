#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include<fstream>

using namespace std;

void MainMenu() {
	cout << "              Grocery Tracking" << endl;
	cout << "********************************************" << endl;
	cout << "1: List of items purchased in a day." << endl;
	cout << "2: A specific item purchased in a given day " << endl;
	cout << "3: Text-based histogram" << endl;
	cout << "4: Exit" << endl;
	cout << "Enter your selection as a number 1 - 4." << endl;
	cout << "********************************************" << endl;


}

int Openfile(){ // changes the amount of times to "*"
	ifstream inData;
	string itemName;
	int amountGot;
	int histoAdd =0;
	inData.open("frequency.dat");
	
	if (!inData.is_open()) {

		cout << "file failed" << endl;

	}

	else{
		while (!inData.eof() && inData.good()) {
			inData >> itemName;
			inData >> amountGot;

			cout << itemName << " ";
			
	

				while (histoAdd < amountGot) {

					cout << "*";
					++histoAdd;

				}
			
			histoAdd = 0;
			cout << endl;
		}


	}

	



	return 0;
}

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}


void main()// reads user input and call on python code that is needed
{
	int userNumSelect = 5;
	string userInput;
	int search;

	while (userNumSelect != 4) {
		system("cls");
		MainMenu();
		cin >> userNumSelect;
	


		if (userNumSelect == 1) {
			system("cls");
			CallProcedure("CountItem");
			system("pause");

				
		}

		if (userNumSelect == 2) {
			system("cls");
			cout << "What item are you looking for?" << endl;
			cin >> userInput;
			system("cls");
			search = callIntFunc("ItemSearch", userInput);
			system("pause");
		}

		if (userNumSelect == 3) {
			system("cls");
			CallProcedure("writeToFile");
			Openfile();
			system("pause");
		}
		

	}
	cout << "system shutdown. Goodbye!" << endl;
	system("pause");
}

