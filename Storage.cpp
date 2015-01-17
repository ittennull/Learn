#include "Storage.h"
#include "QFile"
#include "QDir"
#include "QStringList"
#include <stdexcept>
#include "QXmlStreamReader"
#include "QXmlStreamWriter"
#include "QFileInfo"


Storage::Storage()
{
    auto filename = getDatabasePath();
    QFile file(filename);
    if (!file.exists() || !file.open(QIODevice::ReadOnly))
        return;

    QXmlStreamReader xml(&file);

    while(!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();

        if (token == QXmlStreamReader::StartDocument)
            continue;

        if (token == QXmlStreamReader::StartElement)
        {
            if (xml.name() == "Record")
            {
                _records.push_back(parseRecord(xml));
            }
        }
    }

    if(xml.hasError())
    {
        throw std::runtime_error( xml.errorString().toStdString() );
    }

    xml.clear();
}

Record Storage::parseRecord(QXmlStreamReader& xml) const
{
	Record rec;
	const auto& attributes = xml.attributes();
	rec.Eng = attributes.value("Eng").toString();
	rec.Transcription = attributes.value("Transcription").toString();

	while(!xml.atEnd() && !xml.hasError())
	{
		QXmlStreamReader::TokenType token = xml.readNext();

        if (token == QXmlStreamReader::EndElement && xml.name() == "Record")
            break;

        if (token == QXmlStreamReader::StartElement && xml.name() == "Rus")
		{
			rec.RusList.push_back(xml.readElementText());
		}
	}

    return rec;
}

void Storage::save() const
{
    auto filename = getDatabasePath();
	QFile file(filename);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
	{
        std::string msg = std::string("can't open filename ") + filename.toStdString();
		throw std::invalid_argument(msg);
	}

	QXmlStreamWriter stream(&file);
	stream.setAutoFormatting(true);
	stream.writeStartDocument();

	stream.writeStartElement("Collection");

    for(const auto& rec: _records)
	{
		stream.writeStartElement("Record");
		stream.writeAttribute("Eng", rec.Eng);
		stream.writeAttribute("Transcription", rec.Transcription);

		for(auto rus: rec.RusList)
		{
			stream.writeTextElement("Rus", rus);
		}

		stream.writeEndElement(); //Record
	}

	stream.writeEndElement(); //Collection

	stream.writeEndDocument();
}

QString Storage::getDatabasePath() const
{
    return QDir::currentPath() + QDir::separator() + DatabaseName;
}
