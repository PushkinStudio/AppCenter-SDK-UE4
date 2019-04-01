// Copyright 2015-2019 Mail.Ru Group. All Rights Reserved.

#include "AppCenter_Android.h"

#include "AppCenterDefines.h"

#if PLATFORM_ANDROID
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#include <android_native_app_glue.h>

THIRD_PARTY_INCLUDES_START
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#include "client/linux/handler/exception_handler.h"
#include "client/linux/handler/minidump_descriptor.h"
#pragma clang diagnostic pop
THIRD_PARTY_INCLUDES_END
#endif // PLATFORM_ANDROID

#if PLATFORM_ANDROID

static google_breakpad::ExceptionHandler* exceptionHandler;
bool DumpCallback(const google_breakpad::MinidumpDescriptor& descriptor, void* context, bool succeeded)
{
	__android_log_print(ANDROID_LOG_INFO, "AppCenterUE4", "Wrote breakpad minidump at %s succeeded=%d\n", descriptor.path(), succeeded);

	return succeeded;
}

JNI_METHOD void Java_com_epicgames_ue4_GameActivity_setUpBreakpad(JNIEnv* env, jobject obj, jstring path)
{
	const char* dumpPath = env->GetStringUTFChars(path, 0);
	FString MyString = FString(UTF8_TO_TCHAR(dumpPath));
	FPlatformMisc::LowLevelOutputDebugStringf(TEXT("Java_com_epicgames_ue4_GameActivity_setUpBreakpad: %s"), *MyString);
	google_breakpad::MinidumpDescriptor descriptor(dumpPath);
	exceptionHandler = new google_breakpad::ExceptionHandler(descriptor, NULL, DumpCallback, NULL, true, -1);
	env->ReleaseStringUTFChars(path, dumpPath);
}

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

void UAppCenter_Android::TestNativeCrash()
{
	abort();
}

bool UAppCenter_Android::HasCrashedInLastSession()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_HasCrashedInLastSession", "()Z", false);
		return FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GameActivityThis, Method);
	}

	return false;
}

#endif // PLATFORM_ANDROID