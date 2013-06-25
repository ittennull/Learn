#include "CollectionModel.h"
#include "QStringList"

CollectionModel::CollectionModel(Collection* collection) :
    _collection(collection)
{
}

QHash<int, QByteArray> CollectionModel::roleNames() const
{
	QHash<int, QByteArray> roles;
	roles[EngRole] = "eng";
	roles[RusListRole] = "ruslist";
    roles[Transcription] = "transcription";
	return roles;
}

int CollectionModel::rowCount(const QModelIndex &parent) const
{
	return parent.isValid() ? 0 : _collection->size();
}

int CollectionModel::columnCount(const QModelIndex &/*parent*/) const
{
	return 2;
}

QVariant CollectionModel::data(const QModelIndex &index, int role) const
{
	const auto& record = (*_collection)[index.row()];

	if (role == EngRole)
	{
		return QVariant(record.Eng);
	}
	else if (role == RusListRole)
	{
        return QVariant(record.RusList);
	}
    else if (role == Transcription)
    {
        return QVariant(record.Transcription);
    }

	return QVariant();
}

Qt::ItemFlags CollectionModel::flags(const QModelIndex& /*index*/) const
{
	return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

void CollectionModel::addRecord(const QString &eng, const QString& transcription, const QStringList &rusList)
{
	beginInsertRows(QModelIndex(), _collection->size(), _collection->size());

	auto rec = createRecord(eng, transcription, rusList);
	_collection->push_back(rec);

	endInsertRows();

	emit countChanged();
    emit makeDirty();
}

void CollectionModel::removeRecord(int index)
{
	beginRemoveRows(QModelIndex(), index, index);

	_collection->erase(_collection->begin() + index);

	endRemoveRows();

	emit countChanged();
    emit makeDirty();
}

void CollectionModel::setRecord(int idx, const QString &eng, const QString& transcription, const QStringList &rusList)
{
	(*_collection)[idx] = createRecord(eng, transcription, rusList);

	auto modelIndex = index(idx, 0);
	emit dataChanged(modelIndex, modelIndex);
    emit makeDirty();
}

QString CollectionModel::getEng(int index) const
{
	if(index < 0) return QString();
	return (*_collection)[index].Eng;
}

QString CollectionModel::getTranscription(int index) const
{
	if(index < 0) return QString();
	return (*_collection)[index].Transcription;
}

QStringList CollectionModel::getRusList(int index) const
{
	if(index < 0) return QStringList();
	return (*_collection)[index].RusList;
}

QString CollectionModel::prepareTranscription(const QString& str)
{
	QString s = str.trimmed();
	if (s.startsWith('['))
		s.remove(0, 1);
	if (s.endsWith(']'))
		s.chop(1);
	return s;
}

Record CollectionModel::createRecord(const QString &eng, const QString &transcription, const QStringList &rusList)
{
	Record rec;

	if(transcription.isEmpty())
	{
		int n = eng.indexOf('[');
		QString engPart = eng.left(n);
		rec.Eng = engPart.trimmed();

		if(n != -1)
		{
			QString transcriptionPart = eng.mid(n);
			rec.Transcription = prepareTranscription(transcriptionPart);
		}
	}
	else
	{
		rec.Eng = eng.trimmed();
		rec.Transcription = prepareTranscription(transcription);
	}

	rec.RusList = rusList;

	return rec;
}
