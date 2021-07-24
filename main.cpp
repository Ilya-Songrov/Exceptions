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

#include <QCoreApplication>
#include <QCommandLineParser>
#include <QTimer>
#include <iostream>

#include "applicationnotify.h"

int main(int argc, char *argv[])
{
    try {
        ApplicationNotify<QCoreApplication> app(argc, argv);
        QCoreApplication::setApplicationVersion("0.0.3");

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
