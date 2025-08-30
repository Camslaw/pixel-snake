#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "GameController.h"

int main(int argc, char *argv[])
{
  QGuiApplication app(argc, argv);

  GameController controller;

  QQmlApplicationEngine engine;
  engine.rootContext()->setContextProperty("controller", &controller);

  engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
  if (engine.rootObjects().isEmpty()) return -1;

  return app.exec();
}
