/**************************************************************************
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/.
**
**************************************************************************/

#include "exceptionerror.h"


ExceptionError::ExceptionError(const char *msg) : QException()
  , msg(msg)
{

}

ExceptionError::ExceptionError(const QString &msg) : QException()
  , msg(msg.toUtf8())
{

}

ExceptionError::~ExceptionError() throw()
{

}

ExceptionError::ExceptionError(const ExceptionError &other) : QException()
{
    *this = other;
}

ExceptionError &ExceptionError::operator=(const ExceptionError &other)
{
    this->msg = other.msg;
    return *this;
}

void ExceptionError::raise() const
{
    throw *this;
}

ExceptionError *ExceptionError::clone() const
{
    return new ExceptionError(*this);
}

QString ExceptionError::message() const
{
    return msg;
}

void ExceptionError::writeException() const
{
    writeExceptionToFile(msg);
}

void ExceptionError::writeException(std::exception &exception)
{
    writeExceptionToFile(exception.what());
}

void ExceptionError::writeException(const QByteArray &text)
{
    writeExceptionToFile(text);
}

void ExceptionError::writeException(const QByteArray &text, const QString &pathFile)
{
    writeExceptionToFile(text, pathFile);
}

void ExceptionError::writeExceptionToFile(const QByteArray &arr, const QString &pathFile)
{
    const QString pathFileException = pathFile.isEmpty() ? QString("Exception_%1.json").arg(QCoreApplication::applicationName()) : pathFile;
    qCritical() << QString("Write exception: (%1), pathFileException: (%2)").arg(arr.data(), pathFileException) << Qt::endl;
    QFile file(pathFileException);
    if (!file.open(QFile::WriteOnly | QFile::Append)){
        qCritical() << "Error QFile::WriteOnly | QFile::Append" << file.fileName() << file.errorString() << Qt::endl;
        return;
    }
    QJsonObject obj;
    obj.insert("exception", QString(arr));
    obj.insert("date_time", QDateTime::currentDateTime().toString("yyyy:MM:dd - hh:mm:ss:zzz"));
    file.write(QJsonDocument(obj).toJson());
    file.close();
}
