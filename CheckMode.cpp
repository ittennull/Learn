#include "CheckMode.h"
#include <algorithm>
#include <random>
#include <numeric>

CheckMode::CheckMode(QObject *parent) :
    QObject(parent)
{
}

QString CheckMode::getRussian() const
{
	if(_collection == nullptr)
		return QString();

	QString str = currentRecord().RusList[_russianIndex];
	return str.replace(currentRecord().Eng, QString::fromUtf8("∙∙∙"), Qt::CaseInsensitive);
}

QString CheckMode::getLastEnglish() const
{
	return (_lastRecord != nullptr) ? _lastRecord->Eng : QString();
}

QString CheckMode::getLastTranscription() const
{
	return (_lastRecord != nullptr) ? _lastRecord->Transcription : QString();
}

QStringList CheckMode::getLastRussianList() const
{
	return (_lastRecord != nullptr) ? _lastRecord->RusList : QStringList();
}

void CheckMode::setCollection(const Collection *collection)
{
	_collection = collection;
}

bool CheckMode::checkAndGoFurtherIfCorrect(QString answer)
{
	if(_noMoreData)
		return false;

	bool ok = (answer == currentRecord().Eng);
	if (ok)
	{
		next(false);
	}
	return ok;
}

void CheckMode::next()
{
	next(true);
}

void CheckMode::reset(int numLast, int numOther)
{
	if (_collection == nullptr || _collection->size() == 0)
	{
		setNoMoreData(true);
		return;
	}

    prepareIndices(numLast, numOther);
    emit totalTaskNumberChanged();
	setCurrentRecordIndex(0);

	_indicesToRepeat.clear();
	setLastRecord(nullptr);

	setRandomRussian();

	setNoMoreData(false);
}

void CheckMode::prepareIndices(int numLast, int numOther)
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

void CheckMode::next(bool rememberCurrent)
{
	if(rememberCurrent)
		_indicesToRepeat.push_back(_indices[_currentIndex]);


	setLastRecord(&currentRecord());

	setCurrentRecordIndex(_currentIndex + 1);

	if(_currentIndex == (int)_indices.size() && _indicesToRepeat.empty())
	{
		setNoMoreData(true);
	}
	else
	{
		if(_currentIndex == (int)_indices.size())
		{
			setCurrentRecordIndex(0);

			_indices = _indicesToRepeat;
			std::random_shuffle(_indices.begin(), _indices.end());
            emit totalTaskNumberChanged();

			_indicesToRepeat.clear();
		}

		setRandomRussian();
	}
}

void CheckMode::setLastRecord(const Record *record)
{
	_lastRecord = record;
	emit lastEnglishChanged();
	emit lastRussianListChanged();
}

void CheckMode::setNoMoreData(bool noMoreData)
{
	if(_noMoreData == noMoreData)
		return;

	_noMoreData = noMoreData;
	emit noMoreDataChanged();
}

void CheckMode::setRandomRussian()
{
	const auto& rusList = currentRecord().RusList;

	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, rusList.size() - 1);

	_russianIndex = dis(gen);

	emit russianChanged();
}

void CheckMode::setCurrentRecordIndex(int idx)
{
	if(_currentIndex != idx)
	{
		_currentIndex = idx;
		emit currentTaskNumberChanged();
	}
}

