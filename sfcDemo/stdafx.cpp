// stdafx.cpp : source file that includes just the standard includes
// sfcDemo.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

#if 0 
// TODO: reference any additional headers you need in STDAFX.H
// and not in this file

 //if (pRet)  
    //{  
    //    auto size = PyUnicode_GetLength(pRet);
    //    //int size = PyList_Size(pRet);//prrr Ϊ�б�  
    //    cout << "�����б�Ĵ�СΪ: " << size << endl;  
    //    for(int i=0;i<size;++i)  
    //    {  
    //        PyObject *pNewAge = PyList_GetItem(pRet, i);//�൱�� python�е�prrr[i]  
    //        char *  newAge;  
    //        PyArg_Parse(pNewAge, "s", &newAge);//��python���ַ���תΪc�ַ���  
    //        cout << newAge << endl;  
    //    }  
    //}
  
 
    if (pRet)  
    {  
        auto size = PyUnicode_GetLength(pRet);
        cout << "get len:" << size << endl;  
        char* ret_str;  
        int w = 0 , h = 0;  
        auto ret1 = PyArg_Parse(pRet, "s", &ret_str);
        
        //PyArg_ParseTuple(pRet, "s", &ret_str);  
        //PyArg_ParseTuple(pRet, "s,i,i",&ret_str, &w, &h);  
        
        printf("%s, %d, %d\n", ret_str, w, h);  
    }
#endif