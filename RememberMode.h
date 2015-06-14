#ifndef REMEMBERMODE_H
#define REMEMBERMODE_H

#include <QObject>
#include <vector>
#include "Storage.h"

class RememberMode : public QObject
{
	Q_OBJECT

	int _currentIndex = -1;
	const Collection* _collection = nullptr;
	std::vector<int> _indices;
	bool _noMoreData = true;
	const Record* _lastRecord = nullptr;

public:
	explicit RememberMode(QObject *parent = 0);

	Q_PROPERTY(QString English READ getEnglish NOTIFY englishChanged)
	QString getEnglish() const;

	Q_PROPERTY(QString LastEnglish READ getLastEnglish NOTIFY lastEnglishChanged)
	QString getLastEnglish() const;

	Q_PROPERTY(QString LastTranscription READ getLastTranscription NOTIFY lastTranscriptionChanged)
	QString getLastTranscription() const;

	Q_PROPERTY(QStringList LastRussianList READ getLastRussianList NOTIFY lastRussianListChanged)
	QStringList getLastRussianList() const;

	Q_PROPERTY(bool NoMoreData READ getNoMoreData NOTIFY noMoreDataChanged)
	bool getNoMoreData() const {return _noMoreData;}

	Q_PROPERTY(int CurrentTaskNumber READ getCurrentTaskNumber NOTIFY currentTaskNumberChanged)
	int getCurrentTaskNumber() const {return _currentIndex;}

	Q_PROPERTY(int TotalTaskNumber READ getTotalTaskNumber NOTIFY totalTaskNumberChanged)
	int getTotalTaskNumber() const {return _indices.size();}


	void setCollection(const Collection* collection);
	const Collection* getCollection() const {return _collection;}

	Q_INVOKABLE void next();
	Q_INVOKABLE void prev();
    Q_INVOKABLE void reset(int numLast, int numOther);

signals:
	void englishChanged();
	void lastEnglishChanged();
	void lastTranscriptionChanged();
	void lastRussianListChanged();
	void noMoreDataChanged();
	void currentTaskNumberChanged();
	void totalTaskNumberChanged();

private:
	const Record& currentRecord() const {return (*_collection)[_indices[_currentIndex]];}

	void setLastRecord(const Record* record);
	void setNoMoreData(bool noMoreData);
    void setCurrentRecordIndex(int idx);
};

#endif // REMEMBERMODE_H
