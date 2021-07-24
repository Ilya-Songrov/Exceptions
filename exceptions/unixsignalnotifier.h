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
#include <QSocketNotifier>
#include <QDebug>

class UnixSignalNotifier : public QObject
{
    Q_OBJECT

    static int sighupFifeDescriptor[2];
    static int sigtermFifeDescriptor[2];

    QSocketNotifier *socketNotifierSIGHUP;
    QSocketNotifier *socketNotifierSIGTERM;
public:
    explicit UnixSignalNotifier(QObject *parent = nullptr);

public slots:
    // Qt signal handlers.
    void handleSIGHUP();
    void handleSIGTERM();
private:
    // Unix signal handlers.
    static void hupSignalHandler(int);
    static void termSignalHandler(int);
signals:
    void signalUnix();

};
