// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#define IsUse 0
#ifdef IsUse

	/** 
	* A macro to declare a logging category as a C++ "extern", usually declared in the header and paired with DEFINE_LOG_CATEGORY in the source. Accessible by all files that include the header.
	* @param CategoryName, category to declare
	* @param DefaultVerbosity, default run time verbosity
	* @param CompileTimeVerbosity, maximum verbosity to compile into the code
	**/
	#define DECLARE_LOG_CATEGORY_EXTERN(CategoryName, DefaultVerbosity, CompileTimeVerbosity) \
	extern struct FLogCategory##CategoryName : public FLogCategory<ELogVerbosity::DefaultVerbosity, ELogVerbosity::CompileTimeVerbosity> \
	{ \
	FORCEINLINE FLogCategory##CategoryName() : FLogCategory(TEXT(#CategoryName)) {} \
	} CategoryName;

	/** 
	* A macro to define a logging category, usually paired with DECLARE_LOG_CATEGORY_EXTERN from the header.
	* @param CategoryName, category to define
	**/
	#define DEFINE_LOG_CATEGORY(CategoryName) FLogCategory##CategoryName CategoryName;
	
#endif

//定义一个日志分类
DECLARE_LOG_CATEGORY_EXTERN(LogVPBookmark, Log, Log);
