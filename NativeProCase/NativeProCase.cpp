// NativeProCase.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "com_test_CppConfig.h"
#include "iostream"
#include <stdexcept>
#include "Deploy.h"
using namespace std;

/*
*��������������ע�ⷽ��������env����ָ�룬�ڶ���������ʾ����native
*�����ı�������󣨲�����Ķ��󣩣�ǰ��������ΪĬ�ϵĲ���
*����ĵ���������ΪConfigTti��Ķ���ע������Ķ���
* Class:     com_test_CppConfig
* Method:    setConfigCase0
* Signature: (Lcom/config/ConfigTti;)V
*/


JNIEXPORT void JNICALL Java_com_test_CppConfig_setConfiguration
(JNIEnv *env, jobject obj){
	Deploy1();
};