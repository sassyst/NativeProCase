// NativeProCase.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "com_test_CppConfig.h"
#include "iostream"
#include <stdexcept>
#include "Deploy.h"
using namespace std;

/*
*方法声明声明，注意方法参数的env环境指针，第二个参数表示调用native
*方法的本地类对象（不是类的对象），前两个参数为默认的参数
*传入的第三个参数为ConfigTti类的对象（注意是类的对象）
* Class:     com_test_CppConfig
* Method:    setConfigCase0
* Signature: (Lcom/config/ConfigTti;)V
*/


JNIEXPORT void JNICALL Java_com_test_CppConfig_setConfiguration
(JNIEnv *env, jobject obj){
	Deploy1();
};