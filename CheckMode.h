#ifndef CHECKMODE_H
#define CHECKMODE_H

#include <QObject>
#include <Collection.h>
#include <vector>

class CheckMode : public QObject
{
	Q_OBJECT

	int _currentIndex;
	const Collection* _collection;
	std::vector<int> _indices;
	std::vector<int> _indicesToRepeat;
	int _russianIndex;
	bool _noMoreData;
	const Record* _lastRecord;

public:
	explicit CheckMode(QObject *parent = 0);

	Q_PROPERTY(QString Russian READ getRussian NOTIFY russianChanged)
	QString getRussian() const;

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


	Q_INVOKABLE bool checkAndGoFurtherIfCorrect(QString answer);
	Q_INVOKABLE void next();
	Q_INVOKABLE void reset();
	
signals:
	void russianChanged();
	void lastEnglishChanged();
	void lastTranscriptionChanged();
	void lastRussianListChanged();
	void noMoreDataChanged();
	void currentTaskNumberChanged();
	void totalTaskNumberChanged();

private:
	const Record& currentRecord() const {return (*_collection)[_indices[_currentIndex]];}

	void next(bool rememberCurrent);
	void setLastRecord(const Record* record);
	void setNoMoreData(bool noMoreData);
	void setRandomRussian();
	void setCurrentRecordIndex(int idx);
};

#endif // CHECKMODE_H
