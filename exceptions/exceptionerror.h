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

#pragma once

#include <QObject>
#include <QCoreApplication>
#include <QFile>
#include <QDebug>
#include <QException>
#include <QVariant>
#include <QJsonDocument>
#include <QJsonObject>

class ExceptionError : public QException
{

public:
    explicit ExceptionError(const char* msg);
    explicit ExceptionError(const QString &msg = QString());
    virtual ~ExceptionError() throw();

    ExceptionError(const ExceptionError& other);
    ExceptionError& operator=(const ExceptionError& other);


    void raise() const override;
    ExceptionError* clone() const override;

    QString message() const;

    void writeException() const;
    static void writeException(std::exception &exception);
    static void writeException(const QByteArray &text);
    static void writeException(const QByteArray &text, const QString &pathFile);

private:
    static void writeExceptionToFile(const QByteArray &arr, const QString &pathFile = QString());

private:
    QByteArray msg;
};
