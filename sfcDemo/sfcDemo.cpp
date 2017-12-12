// sfcDemo.cpp : Defines the entry point for the console application.
// some body say that tuple is not ok for python 3.5 3.6

//#pragma execution_character_set("utf-8")  // ��������ʱ,��˾�

#include "stdafx.h"
#include <string>
#include <iostream>

#include "Python.h"
#include "frameobject.h"

#include <list>
#include <vector>

#include <algorithm>

#pragma comment(lib, "python36.lib")

using namespace std;


class ListA
{
public:
    int val;
};

bool compare( ListA *left, ListA *right)
{
    return left->val < right->val;
}

bool compare2( ListA &left, ListA &right)
{
    return left.val < right.val;
}

//class ASorter
//{
//public:
//   operator () (const ListA& s1, const ListA& s2)
//    {
//
//    }
//
//};
int start()
{

#if 1 
    std::list<ListA> list_obj;
    //std::sort(list_obj.begin(),  list_obj.end(), compare2);
    list_obj.sort(compare2);

#endif
#if 0
    std::vector<ListA> vec_obj;
    std::sort(vec_obj.begin(),  vec_obj.end(), compare2);
#endif
    int r=Py_IsInitialized();  //1Ϊ�Ѿ���ʼ����
    if (r != 0)
    {
        cout << "init python fail " << endl;
        return 0;
    }
     
    //Py_SetPythonHome(L"C:\\Python35");
    Py_Initialize(); //��ʼ��
    auto p_main_Module = PyImport_ImportModule("__main__");
    if (!p_main_Module)
    {
        throw "";
    }
    auto pDict = PyModule_GetDict(p_main_Module);
    if ( !pDict ) 
    {          
        return -1;    
    }     
    //PyArg_ParseTuple(

    //PyObject *dic1;
    //PyArg_Parse(pDict, "O", &dic1);
    //PyObject* pDict = PyDict_New(); //new reference
     //assert(PyDict_Check(dic1));
     PyObject* pList = PyList_New(3); // new reference  
    bool ret = PyList_Check(pList);
    //assert(PyList_Check(pList)); 

    PyRun_SimpleString("print(\"hello\"\n)");
    PyRun_SimpleString("print('hello')");
         
#if 0
    PyRun_SimpleString("import sys");

    string path = "D:\\ProgramFilesBase\\Python\\Python36-32\\Lib";
    string chdir_cmd = string("sys.path.append(\"") + path + "\")";
    const char* cstr_cmd = chdir_cmd.c_str(); 
    PyRun_SimpleString(cstr_cmd);

    //����ģ��  
    //PyObject* pModule = PyImport_ImportModule("test"); 
    PyObject* pModule = PyImport_ImportModule("ddd"); 
    if (!pModule)  
    {  
        cout<<"Python get tushare module failed." << endl;  
        return 0;  
    }  
     
    PyObject* pv = PyObject_GetAttrString(pModule, "wwycreatefunc");   
    if (!pv || !PyCallable_Check(pv))  
    {  
        cout << "Can't find funftion (_add)" << endl;  
        return 0;  
    }  
      
    PyObject* pobj1 = Py_BuildValue("(s)", "hello");
    PyObject* pRet = PyEval_CallObject(pv, pobj1);  
     
   
#endif

       
#if 1
    // ��Python����·���л���������ģ������Ŀ¼��һ��Ҫ��֤·��������ȷ��
    string path = "D:\\ProgramFilesBase\\Python\\Python36-32\\Lib\\site-packages\\tushare";
    string chdir_cmd = string("sys.path.append(\"") + path + "\")";
    const char* cstr_cmd = chdir_cmd.c_str();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString(cstr_cmd);

    //����ģ��  
    PyObject* pModule = PyImport_ImportModule("tushare"); 
    if (!pModule)  
    {  
        cout<<"Python get tushare module failed." << endl;  
        return 0;  
    }  
    
    //��ȡInsertģ����_add����  
    PyObject* pv = PyObject_GetAttrString(pModule, "get_hist_data");  
    if (!pv || !PyCallable_Check(pv))  
    {  
        cout << "Can't find funftion (_add)" << endl;  
        return 0;  
    }  
    cout << "Get function (_add) succeed." << endl;  
     

    //PyObject* arg1 = Py_BuildValue("i", 100); // ��������
    //PyObject* arg2 = Py_BuildValue("f", 3.14); // ����������
    //PyObject* arg3 = Py_BuildValue("s", "hello"); // �ַ�������
#if 1
    PyObject* pobj1 = Py_BuildValue("(s)", "603040");
    PyObject* pRet = PyEval_CallObject(pv, pobj1);

#endif 
    if (pRet)  
    {  
        /*if(PyFrame_Check(pRet->ob_type))
        {
            printf( "yes it's frame\n" );
        }*/
        //if(PyList_Check(pRet))
       // PyObject* pList = PyList_New(3); // new reference  
       // assert(PyList_Check(pList)); 
        PyObject *list1;
        PyArg_Parse(pRet, "O", &list1);
        // PyList_CheckExact
        if(PyList_Check(list1))
        {
            printf( "yes it's list\n" );
        }
        char* ret_str;  
        int w = 0 , h = 0;  
        auto ret1 = PyArg_Parse(pRet, "s", &ret_str);
        //����Ԫ��   
        
        printf("%s, %d, %d\n", ret_str, w, h);  

        //������ֵת����long��  
        //long result = PyString_AsString(pRet);  // python 2
        //PyUnicode_FromString(
        //PyBytes_AS_STRING

        //pRet->encode('UTF-8')
       /* char *buf = nullptr;
        PyArg_Parse(pRet, "s", buf);
        cout << "result:" << buf;  */
    }  
#endif

#if 0

    //������ֵ:  
int size = PyList_Size(prrr);//prrr Ϊ�б�  
cout << "�����б�Ĵ�СΪ: " << size << endl;  
for(int i=0;i<size;++i)  
{  
    PyObject *pNewAge = PyList_GetItem(prrr,i);//�൱�� python�е�prrr[i]  
    char *  newAge;  
    PyArg_Parse(pNewAge, "s", &newAge);//��python���ַ���תΪc�ַ���  
    cout << newAge << endl;  
}  
  
#endif 
#if 0 
    //��ʼ��Ҫ����Ĳ�����args���óɴ�������������ģʽ  
    PyObject* pArgs = PyTuple_New(2);  
    //��Long������ת����Python�ɽ��յ�����  
    PyObject* arg1 = PyLong_FromLong(4);  
    PyObject* arg2 = PyLong_FromLong(3);  
  
    //��arg1����Ϊarg����ĵ�һ������  
    PyTuple_SetItem(pArgs, 0, arg1);  
    //��arg1����Ϊarg����ĵڶ�������  
    PyTuple_SetItem(pArgs, 1, arg2);  
  
    //����������ú���������ȡ����ֵ  
    PyObject* pRet = PyObject_CallObject(pv, pArgs);  
  
    if (pRet)  
    {  
        //������ֵת����long��  
        long result = PyLong_AsLong(pRet);  
        cout << "result:" << result;  
    }  
    //int retok = PyArg_Parse(pyRet, "i", &ok); // �ӷ���ֵ��ȡ��int�ͷ���ֵ  
#endif
     //Py_DECREF(pArgs);  
     //Py_DECREF(pModule); 
     //Py_DECREF(pModule); 
     return 0;
}
void end()
{
    Py_Finalize(); //����
}

int _tmain(int argc, _TCHAR* argv[])
{
    start();

    end();
    getchar();
	return 0;
}

