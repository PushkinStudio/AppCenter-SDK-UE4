// Copyright 2015-2019 Mail.Ru Group. All Rights Reserved.

#include "AppCenter_Android.h"

#include "AppCenterDefines.h"

#if PLATFORM_ANDROID
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#endif // PLATFORM_ANDROID

UAppCenter_Android::UAppCenter_Android(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#if PLATFORM_ANDROID
void UAppCenter_Android::TestCrash()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_TestCrash", "()V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method);
	}
}
#endif // PLATFORM_ANDROID