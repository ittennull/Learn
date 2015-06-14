#include "RememberMode.h"
#include <algorithm>
#include <random>
#include "utils.h"


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

    utils::prepareIndices(_indices, _collection->size(), numLast, numOther);
	emit totalTaskNumberChanged();
	setCurrentRecordIndex(0);

	setLastRecord(nullptr);

	emit englishChanged();

	setNoMoreData(false);
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
