/*
 �� yyyymmdd-yyyymmdd.dayk ��� ��k�������Ѿ��������ļ���, ��ȱ�ٽ�����������׷�Ӳ�����;
    Ԥ�����������ݱ����� fcstlines.data �ļ���
    ѡ�ɳ��� ��ÿֻ��Ʊ�Ľ������µ�k�����ݽ��з����ó� Ԥ������, ѡ���ж�
*/

#include "stdafx.h"
#include <string>
#include <iostream>

#include "Python.h"
#include "frameobject.h"

#include <list>
#include <vector>

#include <algorithm>
#include <stdio.h>

#ifdef TO_GET_HISDATA_F2F

#ifdef _DEBUG
#undef Py_XDECREF
#define Py_XDECREF(a) (a)
#endif
//#pragma comment(lib, "python36.lib")

using namespace std;

void TestUseFunc();

int main()
{   
    /*std::string stk_data_dir_ = "sdfsf\\";
    if( stk_data_dir_.rfind("\\") == stk_data_dir_.length() - 1 )  //ok
    {
    stk_data_dir_ = stk_data_dir_;
    }*/
    //------------------
    int r = Py_IsInitialized();  //1Ϊ�Ѿ���ʼ����
    if (r != 0)
    {
        cout << "init python fail " << endl;
        return 0;
    }
      
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

    PyRun_SimpleString("import sys");
  
	char stk_py_dir[256] = {0};
	unsigned int ret_env_size = sizeof(stk_py_dir);
	getenv_s(&ret_env_size, stk_py_dir, ret_env_size, "STK_PY_DIR");
    string path = stk_py_dir;
    string chdir_cmd = string("sys.path.append(\"") + path + "\")";
    const char* cstr_cmd = chdir_cmd.c_str(); 
    PyRun_SimpleString(cstr_cmd);
#if 0 
    //����ģ��   
    PyObject* pModule = PyImport_ImportModule("get_stk_his_fill2file"); // get_stock_his.py
    if (!pModule)  
    {  
        cout<<"Python get get_stk_his_fill2file module failed." << endl;  
        return 0;  
    }  
    PyObject *pDic = PyModule_GetDict(pModule);
    if (!pDic)  
    {  
        cout<<"Python get pDic fail" << endl;  
        return 0;  
    }  

    PyObject* pcls = PyObject_GetAttrString(pModule, "STOCK");   
    if (!pcls || !PyCallable_Check(pcls))  
    {  
        cout << "Can't get class STOCK" << endl;  
        return 0;  
    }  
 
    PyObject* p_stock_obj = PyEval_CallObject(pcls, NULL);
    if( !p_stock_obj )
    {
        cout << "Can't create STOCK obj" << endl;  
        return 0;  
    }
    auto pFunc = PyObject_GetAttrString(p_stock_obj, "getAllFill2File");
    auto pArg = PyTuple_New(3);
    PyTuple_SetItem(pArg, 0, Py_BuildValue("s", "600487"));
    PyTuple_SetItem(pArg, 1, Py_BuildValue("s", "2017-12-07"));
    PyTuple_SetItem(pArg, 2, Py_BuildValue("s", "2017-12-08"));
    auto pRet = PyEval_CallObject(pFunc, pArg);
    char *result;
    PyArg_Parse(pRet, "s", &result);

    auto pFunc1 = PyObject_GetAttrString(p_stock_obj, "getTodayTicksByCode");
    auto pArg1 = PyTuple_New(1);
    PyTuple_SetItem(pArg1, 0, Py_BuildValue("s", "600487")); 
    auto pRet1 = PyEval_CallObject(pFunc1, pArg1);
    char *result1;
    if( pRet1 )
        PyArg_Parse(pRet1, "s", &result1);
    
    Py_XDECREF(result1);

    // follow is not ok ----------
    //PyObject* pRet = PyObject_CallMethod(pInstans_stock, "getAllFill2File", "sss", "600543", "2017-12-01", "2017-12-02");
    //PyObject* pv = PyObject_GetAttrString(pModule, "getAllFill2File");   
    //if (!pv || !PyCallable_Check(pv))  
    //{  
    //    cout << "Can't find funftion (_add)" << endl;  
    //    return 0;  
    //}  
   
#endif
#if 1
     //����ģ��   
    PyObject* pModule = PyImport_ImportModule("get_stk_kline"); // get_stock_his.py
    if (!pModule)  
    {  
        cout<<"Python get get_stk_his_fill2file module failed." << endl;  
        return 0;  
    }  
    PyObject *pDic = PyModule_GetDict(pModule);
    if (!pDic)  
    {  
        cout<<"Python get pDic fail" << endl;  
        return 0;  
    }  

    PyObject* pcls = PyObject_GetAttrString(pModule, "KLINE");   
    if (!pcls || !PyCallable_Check(pcls))  
    {  
        cout << "Can't get class KLINE" << endl;  
        return 0;  
    }  
 
    PyObject* p_stock_obj = PyEval_CallObject(pcls, NULL);
    if( !p_stock_obj )
    {
        cout << "Can't create KLINE obj" << endl;  
        return 0;  
    }
    auto pFunc = PyObject_GetAttrString(p_stock_obj, "getDayKline");
    auto pArg = PyTuple_New(3);
    PyTuple_SetItem(pArg, 0, Py_BuildValue("s", "601699"));
    PyTuple_SetItem(pArg, 1, Py_BuildValue("s", "2017-12-07"));
    PyTuple_SetItem(pArg, 2, Py_BuildValue("s", "2018-03-08"));
    auto pRet = PyEval_CallObject(pFunc, pArg);
    char *result;
    PyArg_Parse(pRet, "s", &result);
    Py_XDECREF(result);
     
#endif
    Py_Finalize();
    return 0;
}

void TestUseFunc()
{

}

#endif // TO_GET_DATA