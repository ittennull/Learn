#include "RememberMode.h"
#include <algorithm>
#include <random>
#include <numeric>


RememberMode::RememberMode(QObject *parent) :
	QObject(parent)
{
}

QString RememberMode::getEnglish() const
{
	if(_collection == nullptr)
		return QString();

	return currentRecord().Eng;
}

QString RememberMode::getLastEnglish() const
{
	return (_lastRecord != nullptr) ? _lastRecord->Eng : QString();
}

QString RememberMode::getLastTranscription() const
{
	return (_lastRecord != nullptr) ? _lastRecord->Transcription : QString();
}

QStringList RememberMode::getLastRussianList() const
{
	return (_lastRecord != nullptr) ? _lastRecord->RusList : QStringList();
}

void RememberMode::setCollection(const Collection *collection)
{
	_collection = collection;
}

void RememberMode::next()
{
	setLastRecord(&currentRecord());

	setCurrentRecordIndex(_currentIndex + 1);

	if(_currentIndex == (int)_indices.size())
	{
		setNoMoreData(true);
	}
	else
	{
		emit englishChanged();
	}
}

void RememberMode::prev()
{
	if(_currentIndex == 0)
		return;

	setCurrentRecordIndex(_currentIndex - 1);

	emit englishChanged();

	setLastRecord(nullptr);

	setNoMoreData(false);
}

void RememberMode::reset(int numLast, int numOther)
{
	if (_collection == nullptr || _collection->size() == 0)
	{
		setNoMoreData(true);
		return;
	}

    prepareIndices(numLast, numOther);
	emit totalTaskNumberChanged();
	setCurrentRecordIndex(0);

	setLastRecord(nullptr);

	emit englishChanged();

	setNoMoreData(false);
}

void RememberMode::prepareIndices(int numLast, int numOther)
{
    const auto max = _collection->size();

    if(numLast != -1)
    {
        if (numLast > max)
            numLast = max;
        if (numLast + numOther > max)
            numOther = max - numLast;
    }

    auto totalSize = (numLast == -1) ? max : numLast + numOther;
    _indices.resize(totalSize);

    if(numLast == -1)
    {
        std::iota(_indices.begin(), _indices.end(), 0);
    }
    else
    {
        std::iota(_indices.begin(), _indices.begin() + numLast, max - numLast);

        decltype(_indices) temp(numOther);
        std::iota(temp.begin(), temp.end(), 0);
        std::random_shuffle(temp.begin(), temp.end());
        std::copy_n(temp.begin(), numOther, _indices.begin() + numLast);
    }

    std::random_shuffle(_indices.begin(), _indices.end());
}

void RememberMode::setLastRecord(const Record *record)
{
	_lastRecord = record;
	emit lastEnglishChanged();
	emit lastRussianListChanged();
}

void RememberMode::setNoMoreData(bool noMoreData)
{
	if(_noMoreData == noMoreData)
		return;

	_noMoreData = noMoreData;
	emit noMoreDataChanged();
}

void RememberMode::setCurrentRecordIndex(int idx)
{
	if(_currentIndex != idx)
	{
		_currentIndex = idx;
		emit currentTaskNumberChanged();
	}
}
