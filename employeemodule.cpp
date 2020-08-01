#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <iostream>
#include <typeinfo>
#include <algorithm>
#include <string>

using namespace std;
// struct employee{
//     string fname;
//     string sname;
//     string deptname;
//     int basic_salary;
//     string designation;
//     string dob;
//     string employee_type;

// };

static vector <string> emp_id (15);
static vector <string> first_name(15);
static vector<string> last_name(15);
static vector<string> department_name(15);
static vector<string> basic_salary_emp(15);
static vector<string> designation_emp(15);
static vector<string> dob_emp(15);
static vector<string> emp_type(15);
static void setup(){
    for (int i = 0; i < 6; i++){
        string id =  to_string(1000 + i);
        string fn = "First_Name " + to_string(i);
        string ln = "Last_Name " + to_string(i);
        string dn = "Department 1";
        string bs = "10000" + to_string(i);
        string des = "designation " + to_string(i);
        string db = "09-01-199" + to_string(i);
        string et = "permanent";
        emp_id.push_back(id);
        first_name.push_back(fn);
        last_name.push_back(ln);
        department_name.push_back(dn);
        basic_salary_emp.push_back(bs);
        designation_emp.push_back(des);
        dob_emp.push_back(db);
        emp_type.push_back(et);
    }
    for (int i = 6; i < 15; i++){
        string id =  to_string(1000 + i);
        string fn = "First_Name " + to_string(i);
        string ln = "Last_Name " + to_string(i);
        string dn = "Department 2";
        string bs = "10000" + to_string(i);
        string des = "designation " + to_string(i);
        string db = "09-01-199" + to_string(i);
        string et = "contractual";
        emp_id.push_back(id);
        first_name.push_back(fn);
        last_name.push_back(ln);
        department_name.push_back(dn);
        basic_salary_emp.push_back(bs);
        designation_emp.push_back(des);
        dob_emp.push_back(db);
        emp_type.push_back(et);
    }
}

extern "C"{
static PyObject *method_setupdb(PyObject *self, PyObject *args) {
    setup();
    return PyBool_FromLong(1);
}
}

extern "C"{
static PyObject *method_add(PyObject *self, PyObject *args) {
    char *efname = NULL;
    char *sname = NULL;
    char *deptname = NULL;
    char *basic_salary = NULL;
    char *designation = NULL;
    char *dob = NULL;
    char *employee_type = NULL;

    /* Parse arguments */
    if(!PyArg_ParseTuple(args, "sssssss", &efname, &sname, &deptname, &basic_salary, &designation, &dob, &employee_type)) {
        return NULL;
    }
    else{
    string e_id = to_string(1000 + (emp_type.size()));
    string fn = efname;
    string ln = sname;
    string dn = deptname;
    string bs = basic_salary;
    string desig = designation;
    string db = dob;
    string et = employee_type;

    emp_id.push_back(e_id);
    first_name.push_back(fn);
    last_name.push_back(ln);
    department_name.push_back(dn);
    basic_salary_emp.push_back(bs);
    designation_emp.push_back(desig);
    dob_emp.push_back(db);
    emp_type.push_back(et);
    return PyLong_FromLong(1);
    }
}
}


extern "C"{
static PyObject *method_search(PyObject *self, PyObject *args) {
    char *id = NULL;

    /* Parse arguments */
    if(!PyArg_ParseTuple(args, "s", &id)) {
        return NULL;
    }
    else{
    string e_id = id;

    long found = 0;
    int index = 0;
    for (string i: emp_id){
    if (i == e_id){
    found = 1;
    break;
    }
    index = index + 1;
    }
    if (found == 1){
    PyObject * result = Py_BuildValue("[ssssssss]",
    const_cast<char *>(emp_id[index].c_str()),
    const_cast<char *>(first_name[index].c_str()),
    const_cast<char *>(last_name[index].c_str()),
    const_cast<char *>(department_name[index].c_str()),
    const_cast<char *>(basic_salary_emp[index].c_str()),
    const_cast<char *>(designation_emp[index].c_str()),
    const_cast<char *>(dob_emp[index].c_str()),
    const_cast<char *>(emp_type[index].c_str()));
    return result;
    }
    else{
    return PyBool_FromLong(found);
    }
    }
}
}

extern "C"{
static PyObject *method_delete(PyObject *self, PyObject *args) {
    char *id = NULL;
    char *efname = NULL;
    char *sname = NULL;
    char *deptname = NULL;
    char *basic_salary = NULL;
    char *designation = NULL;
    char *dob = NULL;
    char *employee_type = NULL;

    /* Parse arguments */
    if(!PyArg_ParseTuple(args, "ssssssss", &id, &efname, &sname, &deptname, &basic_salary, &designation, &dob, &employee_type)) {
        return NULL;
    }
    else{
    string e_id = id;
    string fn = efname;
    string ln = sname;
    string dn = deptname;
    string bs = basic_salary;
    string desig = designation;
    string db = dob;
    string et = employee_type;

    long found = 0;
    vector<string>::iterator index;
    index = find(emp_id.begin(), emp_id.end(), e_id);
    int position;
    if (index != emp_id.end()){
        found = 1;
        emp_id.erase(index);
        position = distance(emp_id.begin(), index);
    }
    else{
        found = 0;
    }
    first_name.erase(first_name.begin() + position);
    last_name.erase(last_name.begin() + position);
    department_name.erase(department_name.begin() + position);
    basic_salary_emp.erase(basic_salary_emp.begin() + position);
    designation_emp.erase(designation_emp.begin() + position);
    dob_emp.erase(dob_emp.begin() + position);
    emp_type.erase(emp_type.begin() + position);

    return PyBool_FromLong(1);

//    if (found == 1){
////    delete *index;
////    first_name.erase(index);
////    last_name.erase(index);
////    department_name.erase(index);
////    basic_salary_emp.erase(index);
////    designation_emp.erase(index);
////    dob_emp.erase(index);
////    emp_type.erase(index);
//    return PyBool_FromLong(found);
//    }
//    else{
//    return PyBool_FromLong(found);
//    }
    }
}
}


extern "C"{
static PyObject *method_modify(PyObject *self, PyObject *args) {
    char *id = NULL;
    char *efname = NULL;
    char *sname = NULL;
    char *deptname = NULL;
    char *basic_salary = NULL;
    char *designation = NULL;
    char *dob = NULL;
    char *employee_type = NULL;

    /* Parse arguments */
    if(!PyArg_ParseTuple(args, "ssssssss", &id, &efname, &sname, &deptname, &basic_salary, &designation, &dob, &employee_type)) {
        return NULL;
    }
    else{
    string e_id = id;
    string fn = efname;
    string ln = sname;
    string dn = deptname;
    string bs = basic_salary;
    string desig = designation;
    string db = dob;
    string et = employee_type;

    long found = 0;
    int index = 0;
    for (string i: emp_id){
    if (i == e_id){
    found = 1;
    break;
    }
    index = index + 1;
    }
    if (found == 1){
    emp_id[index] = e_id;
    first_name[index] = fn;
    last_name[index] = ln;
    department_name[index] = dn;
    basic_salary_emp[index] = bs;
    designation_emp[index] = desig;
    dob_emp[index] = db;
    emp_type[index] = et;
    return PyBool_FromLong(found);
    }
    else{
    return PyBool_FromLong(found);
    }
    }
}
}

extern "C"{
static PyObject *method_report(PyObject *self, PyObject *args) {
    PyObject *result = PyList_New(0);
    PyErr_Print();
    for (unsigned long index = 0; index < emp_id.size(); index++){
    PyList_Append(result, Py_BuildValue("[ssssssss]",
    const_cast<char *>(emp_id[index].c_str()),
    const_cast<char *>(first_name[index].c_str()),
    const_cast<char *>(last_name[index].c_str()),
    const_cast<char *>(department_name[index].c_str()),
    const_cast<char *>(basic_salary_emp[index].c_str()),
    const_cast<char *>(designation_emp[index].c_str()),
    const_cast<char *>(dob_emp[index].c_str()),
    const_cast<char *>(emp_type[index].c_str())));
    }
    PyErr_Print();
    return result;

}
}

extern "C"{
static PyObject *method_cleardb(PyObject *self, PyObject *args) {
    emp_id.clear();
    first_name.clear();
    last_name.clear();
    department_name.clear();
    basic_salary_emp.clear();
    designation_emp.clear();
    dob_emp.clear();
    emp_type.clear();
    return PyBool_FromLong(1);
}
}







// // here I will put all the methods I define
static PyMethodDef empmethods[] = {
    {"setupdb", method_setupdb, METH_VARARGS, "Add some data to the database."},
    {"add", method_add, METH_VARARGS, "Adds a new employee to the database"},
    {"search", method_search, METH_VARARGS, "Searches an employee through his/her emp_id."},
    {"delete_emp", method_delete, METH_VARARGS, "Deletes an employee."},
    {"modify", method_modify, METH_VARARGS, "Modifies an employee data."},
    {"report", method_report, METH_VARARGS, "Reports employee data."},
    {"cleardb", method_cleardb, METH_VARARGS, "Deletes employee data."},
    {NULL, NULL, 0, NULL}
};


static struct PyModuleDef employee_module = {
    PyModuleDef_HEAD_INIT,
    "employeemodule",
    "Contains methods to add, remove, get employee details",
    -1,
    empmethods
};


PyMODINIT_FUNC PyInit_employeemodule(void) {
    return PyModule_Create(&employee_module);
}
