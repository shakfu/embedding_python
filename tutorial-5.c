#include <Python.h>
#include <stdio.h>

static PyObject* callback(PyObject* self, PyObject* args)
{
    long c;
    PyArg_ParseTuple(args, "l", &c);
    printf("Result of call: %ld\n", c);

    Py_RETURN_NONE;
}


PyMethodDef CFunctions[] = {
    {"callback", (PyCFunction)callback, METH_VARARGS, ""},
    {NULL},
};


static struct PyModuleDef cmodule = {
    PyModuleDef_HEAD_INIT,
    .m_name = "cmodule",
    .m_doc = PyDoc_STR("A demo cmodule"),
    .m_size = -1,
    .m_methods = CFunctions,
};

PyMODINIT_FUNC PyInit_cmodule(void)
{
    return PyModule_Create(&cmodule);
}

int main(int argc, char* argv[])
{

    PyImport_AppendInittab("cmodule", PyInit_cmodule);

    Py_Initialize();
    PyObject* sysPath = PySys_GetObject((char*) "path");
    PyList_Append(sysPath, PyUnicode_FromString("."));

    printf("Input two integers separated by space:\n");
    int a, b;
    scanf("%d %d", &a, &b);

    PyObject *pModule = NULL, *pFunc = NULL, *pArgs = NULL;
    do
    {
        pModule = PyImport_ImportModule("func-module");
        if (pModule == NULL) break;

        pFunc = PyObject_GetAttrString(pModule, "multiply");
        if (pFunc == NULL) break;

        pArgs = Py_BuildValue("ii", a, b);
        if (pArgs == NULL) break;

        PyObject_Call(pFunc, pArgs, NULL);
    } while (0);

    Py_XDECREF(pArgs);
    Py_XDECREF(pFunc);
    Py_XDECREF(pModule);

    Py_Finalize();
    return 0;
}
