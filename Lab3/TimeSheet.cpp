#include <cmath>
#include "TimeSheet.h"

namespace lab3
{
	TimeSheet::TimeSheet(const char* name, unsigned int maxEntries)
		: mName(name)
		, mMaxEntryCount(maxEntries)
		, mCurrentEntryCount(0)
	{
		mWorkHours = new int[maxEntries];
	}

	TimeSheet::TimeSheet(const TimeSheet& origin)
		: mName(origin.mName)
		, mMaxEntryCount(origin.mMaxEntryCount)
		, mCurrentEntryCount(origin.mCurrentEntryCount)
	{
		mWorkHours = new int[mMaxEntryCount];
		memcpy(mWorkHours, origin.mWorkHours, mCurrentEntryCount * sizeof(int));
	}

	TimeSheet& TimeSheet::operator=(const TimeSheet& ref)
	{
		delete[] mWorkHours;

		mName = ref.mName;
		mMaxEntryCount = ref.mMaxEntryCount;
		mCurrentEntryCount = ref.mCurrentEntryCount;
		mWorkHours = new int[mMaxEntryCount];
		memcpy(mWorkHours, ref.mWorkHours, mCurrentEntryCount * sizeof(int));

		return *this;
	}

	TimeSheet::~TimeSheet(void)
	{
		delete[] mWorkHours;
	}

	void TimeSheet::AddTime(int timeInHours)
	{
		const int MIN_HOUR = 1;
		const int MAX_HOUR = 10;

		if (timeInHours < MIN_HOUR || timeInHours > MAX_HOUR)
		{
			return;
		}

		if (mCurrentEntryCount == mMaxEntryCount)
		{
			return;
		}

		mWorkHours[mCurrentEntryCount] = timeInHours;
		++mCurrentEntryCount;
	}

	int TimeSheet::GetTimeEntry(unsigned int index) const
	{
		if (index < 0 || index > mCurrentEntryCount - 1)
		{
			return FAILED;
		}

		return mWorkHours[index];
	}

	int TimeSheet::GetTotalTime() const
	{
		int totalTime = 0;

		for (size_t i = 0; i < mCurrentEntryCount; ++i)
		{
			totalTime += mWorkHours[i];
		}

		return totalTime;
	}

	float TimeSheet::GetAverageTime() const
	{
		int totalTime = GetTotalTime();
		float result = 0.0f;

		if (totalTime == 0)
		{
			return result;
		}

		result = static_cast<float>(totalTime);
		return result / mCurrentEntryCount;
	}

	float TimeSheet::GetStandardDeviation() const
	{
		float average = GetAverageTime();
		float result = 0.0f;

		if (average == 0.0f)
		{
			return result;
		}

		for (size_t i = 0; i < mCurrentEntryCount; ++i)
		{
			float tempDeviation = mWorkHours[i] - average;

			tempDeviation = abs(tempDeviation);

			result += pow(tempDeviation, 2);
		}

		result = result / mCurrentEntryCount;

		return sqrt(result);
	}

	const std::string& TimeSheet::GetName() const
	{
		return mName;
	}
}
