// Copyright 2015-2019 Mail.Ru Group. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class UAppCenterSettings;
class UAppCenterProxy;

class FAppCenterModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	/**
	 * Singleton-like access to this module's interface.  This is just for convenience!
	 * Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already.
	 *
	 * @return Returns singleton instance, loading the module on demand if needed
	 */
	static inline FAppCenterModule& Get()
	{
		return FModuleManager::LoadModuleChecked<FAppCenterModule>("AppCenter");
	}

	/**
	 * Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true.
	 *
	 * @return True if the module is loaded and ready to use
	 */
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("AppCenter");
	}

	/** Getter for internal settings object to support runtime configuration changes */
	UAppCenterSettings* GetSettings() const;

	/** AppCenterProxy accessor */
	UAppCenterProxy* GetProxy() const;

private:
	UAppCenterSettings* AppCenterSettings;

	/** Internal proxy object */
	UAppCenterProxy* AppCenterProxy;
};
