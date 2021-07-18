#pragma once

#include <QObject>

#include "ExceptionError.h"

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

