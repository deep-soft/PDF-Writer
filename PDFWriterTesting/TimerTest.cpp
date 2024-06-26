/*
   Source File : TimerTest.cpp


   Copyright 2011 Gal Kahana PDFWriter

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

   
*/
#include "Trace.h"
#include "Singleton.h"
#include "TimersRegistry.h"

#include <time.h>

#include "testing/TestIO.h"


static void Sleep(double inSeconds)
{
	clock_t wait = (clock_t)(inSeconds * CLOCKS_PER_SEC);
	clock_t goal;
	goal = wait + clock();
	while(goal > clock())
		;
}

int TimerTest(int argc, char* argv[])
{
	Singleton<Trace>::GetInstance()->SetLogSettings(BuildRelativeOutputPath(argv,"timersTrace.txt"),true,true);

	TimersRegistry timersRegistry;

	timersRegistry.StartMeasure("TimerA");
	timersRegistry.StartMeasure("TimerB");
	Sleep(1);
	timersRegistry.StopMeasureAndAccumulate("TimerA");
	timersRegistry.StopMeasureAndAccumulate("TimerB");

	timersRegistry.StartMeasure("TimerC");
	timersRegistry.StartMeasure("TimerB");
	Sleep(1.80);
	timersRegistry.StopMeasureAndAccumulate("TimerC");
	timersRegistry.StopMeasureAndAccumulate("TimerB");

	timersRegistry.TraceAndReleaseAll();

	Singleton<Trace>::Reset();

	return 0;
}

