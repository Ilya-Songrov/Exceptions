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

#include "exceptionerror.h"

template<class T>
class ApplicationNotify : public T
{
public:
    ApplicationNotify(int &argc, char **argv, int flag = T::ApplicationFlags) : T(argc, argv, flag){}
    virtual ~ApplicationNotify(){}

    bool notify(QObject *receiver, QEvent *event) override {
        try {
            return T::notify(receiver, event);
        }
        catch (ExceptionError &exceptionError) {
            exceptionError.writeException();
            qFatal("Exception thrown: %s", exceptionError.what());
        }
        catch (std::exception &exception) {
            ExceptionError::writeException(exception);
            qFatal("Exception thrown: %s", exception.what());
        }
        catch (...) {
            ExceptionError::writeException("Unknown exception caught (...)");
            qFatal("Unknown exception caught.");
        }
        return false;
    }
};

