#pragma once

#include <cmath>
#include <limits>
#include <queue>
#include <stack>
#include "MyMath.h"

using namespace std;

namespace assignment3
{
	template<typename T>
	class QueueStack
	{
	public:
		QueueStack(unsigned int maxStackSize);
		virtual ~QueueStack();
		QueueStack(QueueStack<T>& other);
		QueueStack<T>& operator=(QueueStack<T>& other);

		void Enqueue(T number);
		T Peek() const;
		T Dequeue();
		T GetMax();
		T GetMin();
		double GetAverage() const;
		T GetSum() const;
		unsigned int GetCount() const;
		unsigned int GetStackCount() const;
	private:
		unsigned int mCount;
		unsigned int mMaxStackSize;
		double mSum;
		queue<stack<T>> mQueueStack;
	};

	template<typename T>
	QueueStack<T>::QueueStack(unsigned int maxStackSize)
		: mCount(0)
		, mMaxStackSize(maxStackSize)
		, mSum(0.0)
	{
	}

	template<typename T>
	QueueStack<T>::~QueueStack()
	{
		while (!mQueueStack.empty())
		{
			mQueueStack.pop();
		}
	}

	template<typename T>
	QueueStack<T>::QueueStack(QueueStack<T>& other)
		: mCount(other.mCount)
		, mMaxStackSize(other.mMaxStackSize)
		, mSum(other.mSum)
	{
		queue<stack<T>> tempQueueStack;

		while (!other.mQueueStack.empty())
		{
			stack<T>& tempStack = other.mQueueStack.front();

			tempQueueStack.push(tempStack);
			mQueueStack.push(tempStack);

			other.mQueueStack.pop();
		}

		while (!tempQueueStack.empty())
		{
			other.mQueueStack.push(tempQueueStack.front());
			tempQueueStack.pop();
		}
	}

	template<typename T>
	QueueStack<T>& QueueStack<T>::operator=(QueueStack<T>& other)
	{
		if (this == &other)
		{
			return *this;
		}

		while (!mQueueStack.empty())
		{
			mQueueStack.pop();
		}

		mCount = other.mCount;
		mMaxStackSize = other.mMaxStackSize;
		mSum = other.mSum;

		queue<stack<T>> tempQueueStack;
		while (!other.mQueueStack.empty())
		{
			stack<T>& tempStack = other.mQueueStack.front();

			tempQueueStack.push(tempStack);
			mQueueStack.push(tempStack);

			other.mQueueStack.pop();
		}

		while (!tempQueueStack.empty())
		{
			other.mQueueStack.push(tempQueueStack.front());
			tempQueueStack.pop();
		}

		return *this;
	}

	template<typename T>
	void QueueStack<T>::Enqueue(T number)
	{
		queue<stack<T>> tempQueueStack;

		if (mQueueStack.empty())
		{
			mQueueStack.push(stack<T>());
		}

		while (!mQueueStack.empty())
		{
			stack<T>& tempStack = mQueueStack.front();

			if (mQueueStack.size() == 1)
			{
				if (tempStack.size() < mMaxStackSize)
				{
					tempStack.push(number);
				}
				else
				{
					tempQueueStack.push(tempStack);
					mQueueStack.pop();

					stack<T> newStack;
					newStack.push(number);
					tempQueueStack.push(newStack);

					break;
				}
			}

			tempQueueStack.push(tempStack);
			mQueueStack.pop();
		}

		while (!tempQueueStack.empty())
		{
			mQueueStack.push(tempQueueStack.front());
			tempQueueStack.pop();
		}

		++mCount;
		mSum += static_cast<double>(number);
	}

	template<typename T>
	T QueueStack<T>::Peek() const
	{
		// ignore empty queue case

		stack<T> frontStack = mQueueStack.front();

		return frontStack.top();
	}

	template<typename T>
	T QueueStack<T>::Dequeue()
	{
		// ignore empty queue case

		stack<T>& frontStack = mQueueStack.front();
		T value = frontStack.top();
		frontStack.pop();
		
		if (frontStack.empty())
		{
			mQueueStack.pop();
		}

		if (mQueueStack.empty())
		{
			mCount = 0;
			mSum = 0.0;

			return value;
		}

		--mCount;
		mSum -= static_cast<double>(value);

		return value;
	}

	template<typename T>
	T QueueStack<T>::GetMax()
	{
		T maxValue = numeric_limits<T>::lowest();
		queue<stack<T>> tempQueueStack;

		while (!mQueueStack.empty())
		{
			stack<T> tempStack;
			stack<T>& tempFrontStack = mQueueStack.front();

			while (!tempFrontStack.empty())
			{
				T tempValue = tempFrontStack.top();
				tempFrontStack.pop();
				tempStack.push(tempValue);
				if (tempValue > maxValue)
				{
					maxValue = tempValue;
				}
			}

			while (!tempStack.empty())
			{
				tempFrontStack.push(tempStack.top());
				tempStack.pop();
			}

			tempQueueStack.push(tempFrontStack);
			mQueueStack.pop();
		}

		while (!tempQueueStack.empty())
		{
			mQueueStack.push(tempQueueStack.front());
			tempQueueStack.pop();
		}

		return maxValue;
	}

	template<typename T>
	T QueueStack<T>::GetMin()
	{
		T minValue = numeric_limits<T>::max();
		queue<stack<T>> tempQueueStack;

		while (!mQueueStack.empty())
		{
			stack<T> tempStack;
			stack<T>& tempFrontStack = mQueueStack.front();

			while (!tempFrontStack.empty())
			{
				T tempValue = tempFrontStack.top();
				tempFrontStack.pop();
				tempStack.push(tempValue);
				if (tempValue < minValue)
				{
					minValue = tempValue;
				}
			}

			while (!tempStack.empty())
			{
				tempFrontStack.push(tempStack.top());
				tempStack.pop();
			}

			tempQueueStack.push(tempFrontStack);
			mQueueStack.pop();
		}

		while (!tempQueueStack.empty())
		{
			mQueueStack.push(tempQueueStack.front());
			tempQueueStack.pop();
		}

		return minValue;
	}

	template<typename T>
	double QueueStack<T>::GetAverage() const
	{
		// ignore empty queue case
		if (mQueueStack.empty())
		{
			return 0.0;
		}

		return GetRoundOffTo3DecimalPlaces(mSum / mCount);
	}

	template<typename T>
	T QueueStack<T>::GetSum() const
	{
		if (mSum >= static_cast<double>(numeric_limits<T>::max()))
		{
			return numeric_limits<T>::max();
		}

		return static_cast<T>(mSum);
	}

	template<typename T>
	unsigned int QueueStack<T>::GetCount() const
	{
		return mCount;
	}

	template<typename T>
	unsigned int QueueStack<T>::GetStackCount() const
	{
		return static_cast<unsigned int>(mQueueStack.size());
	}
}