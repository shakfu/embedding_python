#include <stdio.h>
#include <Python.h>

int main(int argc, char* argv[])
{

    wchar_t *program = Py_DecodeLocale(argv[0], NULL);
    if (program == NULL) {
        fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
        exit(1);
    }

    Py_SetProgramName(program);

    Py_Initialize();
    PyObject* sysPath = PySys_GetObject((char*) "path");
    PyList_Append(sysPath, PyUnicode_FromString("."));

    printf("Input two integers separated by space:\n");
    int a, b;
    scanf("%d %d", &a, &b);

    PyObject *pModule = NULL, *pFunc = NULL, *pArgs = NULL, *pValue = NULL;
    do
    {
        pModule = PyImport_ImportModule("func");
        if (pModule == NULL) break;

        pFunc = PyObject_GetAttrString(pModule, "multiply");
        if (pFunc == NULL) break;

        pArgs = Py_BuildValue("ii", a, b);
        if (pArgs == NULL) break;

        pValue = PyObject_Call(pFunc, pArgs, NULL);
        if (pValue == NULL) break;
        printf("Result of call: %ld\n", PyLong_AsLong(pValue));
    } while (0);

    Py_XDECREF(pValue);
    Py_XDECREF(pArgs);
    Py_XDECREF(pFunc);
    Py_XDECREF(pModule);

    Py_Finalize();
    PyMem_RawFree(program);
    return 0;
}
