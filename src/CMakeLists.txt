cmake_minimum_required(VERSION 3.8)

project(CPPSamples)


MACRO(SETUP_SAMPLE_START EXE_NAME)
	UNSET(SOURCE_FILES)
	UNSET(HEADER_FILES)
	UNSET(RESOURCE_FILES)
	UNSET(EFFECT_FILES)
ENDMACRO(SETUP_SAMPLE_START)

MACRO(SETUP_SAMPLE_END EXE_NAME)
	SOURCE_GROUP("Source Files" FILES ${SOURCE_FILES})
	SOURCE_GROUP("Header Files" FILES ${HEADER_FILES})
	SOURCE_GROUP("Resource Files" FILES ${RESOURCE_FILES})
	SOURCE_GROUP("Effect Files" FILES ${EFFECT_FILES})
	
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin/${EXE_NAME})
	
	ADD_EXECUTABLE(${EXE_NAME} ${SOURCE_FILES} ${HEADER_FILES} ${RESOURCE_FILES} ${EFFECT_FILES})

ENDMACRO(SETUP_SAMPLE_END)

SETUP_SAMPLE_START(FuncPtrSample)
	SET(SOURCE_FILES
		FuncPtrSample/ClassA.cpp
		FuncPtrSample/EventDispatch.cpp
		FuncPtrSample/FuncPtrTest.cpp
	)
	SET(HEADER_FILES
		FuncPtrSample/ClassA.h
		FuncPtrSample/Event.h
		FuncPtrSample/EventDispatcher.h
	)
SETUP_SAMPLE_END(FuncPtrSample)


SETUP_SAMPLE_START(SharedPtrSample)
	SET(SOURCE_FILES
		SharedPtrSample/SharedPtrSample.cpp
	)
	SET(HEADER_FILES
		SharedPtrSample/Student.h
		SharedPtrSample/Teacher.h
	)
SETUP_SAMPLE_END(SharedPtrSample)

SETUP_SAMPLE_START(ThreadsSample)
	SET(SOURCE_FILES
		Threads/main.cpp
		Threads/MutexSample.cpp
	)
SETUP_SAMPLE_END(ThreadsSample)

SETUP_SAMPLE_START(WMainSample)
	SET(SOURCE_FILES
		WMainSample/main.cpp
	)
SETUP_SAMPLE_END(WMainSample)

SETUP_SAMPLE_START(ValgrindUseSample)
	SET(SOURCE_FILES
		ValgrindUseSample/ValgrindUseSample.cpp
	)
SETUP_SAMPLE_END(ValgrindUseSample)

SETUP_SAMPLE_START(PragmaOnceSample)
	SET(SOURCE_FILES
		PragmaOnceSample/PragmaOnceSample.cpp
		PragmaOnceSample/Common.cpp
		PragmaOnceSample/Student.cpp
	)
	SET(HEADER_FILES
		PragmaOnceSample/Common.h
		PragmaOnceSample/Student.h
	)
SETUP_SAMPLE_END(PragmaOnceSample)

SETUP_SAMPLE_START(DestructorSample)
	SET(SOURCE_FILES
		DestructorSample/DestructorSample.cpp
	)
SETUP_SAMPLE_END(DestructorSample)

SETUP_SAMPLE_START(StlSample)
	SET(SOURCE_FILES
		StlSample/StlSample.cpp
	)
SETUP_SAMPLE_END(StlSample)

SETUP_SAMPLE_START(StringSample)
	SET(SOURCE_FILES
		StringSample/StringSample.cpp
	)
SETUP_SAMPLE_END(StringSample)

SETUP_SAMPLE_START(CastSample)
	SET(SOURCE_FILES
		CastSample/CastSample.cpp
	)
SETUP_SAMPLE_END(CastSample)

SETUP_SAMPLE_START(MultiInheritSample)
	SET(SOURCE_FILES
		MultiInheritSample/MultiInheritSample.cpp
	)
SETUP_SAMPLE_END(MultiInheritSample)

SETUP_SAMPLE_START(StackSample)
	SET(SOURCE_FILES
		StackSample/StackSample.cpp
	)
SETUP_SAMPLE_END(StackSample)

SETUP_SAMPLE_START(VectorBytesTest)
	SET(SOURCE_FILES
		VectorBytesTest/VectorBytesTest.cpp
		VectorBytesTest/FastByteArray.h
		VectorBytesTest/FastByteArray.cpp
	)
SETUP_SAMPLE_END(VectorBytesTest)
