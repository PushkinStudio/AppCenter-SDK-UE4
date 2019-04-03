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

/////////////////////////////////////////////////////////////////////////
// AppCenter Other APIs

#if WITH_APPCENTER
void UAppCenter_Android::SetCustomPropertyAsString(const FString& Key, const FString& Value)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jstring KeyJava = Env->NewStringUTF(TCHAR_TO_UTF8(*Key));
		jstring ValueJava = Env->NewStringUTF(TCHAR_TO_UTF8(*Value));
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_SetCustomPropertyAsString", "(Ljava/lang/String;Ljava/lang/String;)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, KeyJava, ValueJava);
		Env->DeleteLocalRef(KeyJava);
		Env->DeleteLocalRef(ValueJava);
	}
}

void UAppCenter_Android::SetCustomPropertyAsInt(const FString& Key, int32 Value)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jstring KeyJava = Env->NewStringUTF(TCHAR_TO_UTF8(*Key));
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_SetCustomPropertyAsInt", "(Ljava/lang/String;I)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, KeyJava, Value);
		Env->DeleteLocalRef(KeyJava);
	}
}

void UAppCenter_Android::SetCustomPropertyAsFloat(const FString& Key, float Value)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jstring KeyJava = Env->NewStringUTF(TCHAR_TO_UTF8(*Key));
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_SetCustomPropertyAsFloat", "(Ljava/lang/String;F)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, KeyJava, Value);
		Env->DeleteLocalRef(KeyJava);
	}
}

void UAppCenter_Android::SetCustomPropertyAsBool(const FString& Key, bool Value)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jstring KeyJava = Env->NewStringUTF(TCHAR_TO_UTF8(*Key));
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_SetCustomPropertyAsBool", "(Ljava/lang/String;Z)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, KeyJava, Value);
		Env->DeleteLocalRef(KeyJava);
	}
}

void UAppCenter_Android::ClearCustomProperties(const TArray<FString>& Keys)
{
	UE_LOG(LogAppCenter, Warning, TEXT("%s: Not implemented yet"), *PS_FUNC_LINE);
}

void UAppCenter_Android::ClearCustomProperty(const FString& Key)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jstring KeyJava = Env->NewStringUTF(TCHAR_TO_UTF8(*Key));
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_ClearCustomProperty", "(Ljava/lang/String;)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, KeyJava);
		Env->DeleteLocalRef(KeyJava);
	}
}
#endif // WITH_APPCENTER

/////////////////////////////////////////////////////////////////////////
// Analytics

#if WITH_APPCENTER_ANALYTICS
void UAppCenter_Android::TrackEvent(FString Event, const TMap<FString, FString>& Properties, EAppCenterEventPersistence EventPersistence)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jstring KeyJava = Env->NewStringUTF(TCHAR_TO_UTF8(*Event));

		jclass mapClass = Env->FindClass("java/util/HashMap");
		jmethodID init = Env->GetMethodID(mapClass, "<init>", "()V");
		jobject hashMap = Env->NewObject(mapClass, init);
		jmethodID put = Env->GetMethodID(mapClass, "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");

		for (const auto& Elem : Properties)
		{
			jstring keyJava = Env->NewStringUTF(TCHAR_TO_UTF8(*Elem.Key));
			jstring valueJava = Env->NewStringUTF(TCHAR_TO_UTF8(*Elem.Value));

			Env->CallObjectMethod(hashMap, put, keyJava, valueJava);

			Env->DeleteLocalRef(keyJava);
			Env->DeleteLocalRef(valueJava);
		}

		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_TrackEvent", "(Ljava/lang/String;Ljava/util/HashMap;I)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, KeyJava, hashMap, static_cast<int32>(EventPersistence));

		Env->DeleteLocalRef(KeyJava);
		Env->DeleteLocalRef(mapClass);
		Env->DeleteLocalRef(hashMap);
	}
}
#endif // WITH_APPCENTER_ANALYTICS

/////////////////////////////////////////////////////////////////////////
// Crashes

#if WITH_APPCENTER_CRASHES
void UAppCenter_Android::GenerateTestCrash()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_GenerateTestCrash", "()V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method);
	}
}

void UAppCenter_Android::GenerateNativeCrash()
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
#endif // WITH_APPCENTER_CRASHES

#endif // PLATFORM_ANDROID