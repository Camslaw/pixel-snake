#pragma once
#include <QObject>
#include <QPointF>
#include <QVector>

class GameController : public QObject {
  Q_OBJECT
  Q_PROPERTY(QVector<QPointF> body READ body NOTIFY bodyChanged)
  Q_PROPERTY(QPointF head READ head NOTIFY headChanged)
public:
  explicit GameController(QObject* parent = nullptr);

  const QVector<QPointF>& body() const { return m_body; }
  QPointF head() const { return m_head; }

  Q_INVOKABLE void setViewportSize(double w, double h);
  Q_INVOKABLE void setMouseTarget(double x, double y);
  Q_INVOKABLE void tick();  // called ~60 fps

  signals:
    void bodyChanged();
    void headChanged();

private:
  void integrate(double dt);
  void wrapIfOutside();

  QPointF m_head{640.0, 360.0};
  double m_angleRad = 0.0;
  double m_speed = 180.0; // pixels/second
  QPointF m_mouseTarget{0, 0};
  double m_viewW = 1280.0, m_viewH = 720.0;

  QVector<QPointF> m_body; // simple polyline of past positions
  double m_segmentSpacing = 6.0; // distance between stored points
  double m_accumDist = 0.0;
};
