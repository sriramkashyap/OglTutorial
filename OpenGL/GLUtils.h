#ifndef GLUTILS_H
#define GLUTILS_H

//Define this if C++11 features are available on the compiler
//#define USE_CHRONO

#include <string>

#ifdef USE_CHRONO
	#include <chrono>
#else
	#include <ctime>
#endif

void MsgAssert(bool assertion, const std::string &msg);
std::string LoadFileAsString(const std::string &fname);

class PerformanceCounter
{
protected:

#ifdef USE_CHRONO
	std::chrono::system_clock::time_point start;
#else
	clock_t start;
#endif

public:
	PerformanceCounter()
	{
		Start();
	}

	void Start()
	{
		// Get initial value
#ifdef USE_CHRONO
		start = std::chrono::high_resolution_clock::now();
#else
		start = clock();
#endif
	}

	long long GetTimeNanoSeconds()
	{
#ifdef USE_CHRONO
		auto end = std::chrono::high_resolution_clock::now();
		return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
#else
		return static_cast<long long>((clock() - start) * 1.0e9 / CLOCKS_PER_SEC);
#endif
	}

	double GetTimeMilliSeconds()
	{
		return GetTimeNanoSeconds() * 1e-6;
	}
	
	double GetTimeSeconds()
	{
		return GetTimeNanoSeconds() * 1e-9;
	}
};

#endif