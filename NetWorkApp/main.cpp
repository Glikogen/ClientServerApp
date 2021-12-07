#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "viewmodel.h"
#include <QQmlContext>
#include <QStringListModel>
#include <QtQml>
#include "messagemodel.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    //ViewModel *viewModel = new ViewModel;
//    MessagesModel *model = new MessagesModel();
//    model->addMessage("you connected!");
//    model->addMessage("MYNAME|oke|14:45:12");
//    model->addMessage("NOTYOURNAME|bye1|14:45:23");
//    model->addMessage("MYNAME|bye2|14:45:24");
//    model->addMessage("NOTYOURNAME|bye3|14:45:25");
//    model->addMessage("you disconnected!");
//    engine.rootContext()->setContextProperty("listModel", model);
    qmlRegisterType<ViewModel>("ViewModel", 1, 0, "ViewModel");
    engine.load(url);

    return app.exec();
}
