#include <QCoreApplication>
#include <QCommandLineParser>
#include <QTimer>
#include <iostream>

#include "applicationnotify.h"

int main(int argc, char *argv[])
{
    try {
        ApplicationNotify<QCoreApplication> app(argc, argv);
        QCoreApplication::setApplicationVersion("0.0.2");

        QCommandLineParser parser;
        parser.setApplicationDescription("App description");
        parser.addHelpOption();
        parser.addVersionOption();
        parser.process(app);

        QTimer::singleShot(2000, [](){
            throw "Division by zero condition!";
        });

        return app.exec();
    }
    catch (ExceptionError &exceptionError) {
        std::cerr << qPrintable(exceptionError.message()) << std::endl;
    }
    catch (std::exception &exception) {
        std::cerr << exception.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Unknown exception caught (...)" << std::endl;
    }
    return EXIT_FAILURE;
}
