#ifndef CHECKMODE_H
#define CHECKMODE_H

#include <QObject>
#include <vector>
#include "Storage.h"

class CheckMode : public QObject
{
	Q_OBJECT

    int _currentIndex = -1;
    const Collection* _collection = nullptr;
	std::vector<int> _indices;
	std::vector<int> _indicesToRepeat;
    std::vector<int> _russianIndices; //list of all translations in random order
    int _russianIndex = -1; //current translation from _russianIndices
    bool _noMoreData = true;
    const Record* _lastRecord = nullptr;

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

    Q_PROPERTY(bool HasManyTranslations READ hasManyTranslations NOTIFY hasManyTranslationsChanged)
    int hasManyTranslations() const {return _russianIndices.size() > 1;}

	void setCollection(const Collection* collection);
	const Collection* getCollection() const {return _collection;}


	Q_INVOKABLE bool checkAndGoFurtherIfCorrect(QString answer);
	Q_INVOKABLE void next();
    Q_INVOKABLE void reset(int numLast, int numOther);
    Q_INVOKABLE void nextRussian(bool forward);
	
signals:
	void russianChanged();
	void lastEnglishChanged();
	void lastTranscriptionChanged();
	void lastRussianListChanged();
	void noMoreDataChanged();
	void currentTaskNumberChanged();
    void totalTaskNumberChanged();
    void hasManyTranslationsChanged();

private:
	const Record& currentRecord() const {return (*_collection)[_indices[_currentIndex]];}

	void next(bool rememberCurrent);
	void setLastRecord(const Record* record);
	void setNoMoreData(bool noMoreData);
	void setRandomRussian();
    void setCurrentRecordIndex(int idx);
};

#endif // CHECKMODE_H
