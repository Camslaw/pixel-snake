#include "GameController.h"
#include <QtMath>

GameController::GameController(QObject* parent) : QObject(parent) {
    m_body.reserve(2000);
    m_body.push_back(m_head);
}

void GameController::setViewportSize(double w, double h) {
    m_viewW = w; m_viewH = h;
}

void GameController::setMouseTarget(double x, double y) {
    m_mouseTarget = QPointF(x, y);
}

void GameController::tick() {
    // Fixed dt for simplicity (60 fps)
    integrate(1.0/60.0);
}

void GameController::integrate(double dt) {
    // One-time prefill so we start at full length (80 samples spaced by the per-frame step)
    if (m_body.size() == 1) {
        const int snakeLength = 80;
        const double segment = m_speed * dt; // pixels between samples at 60 fps
        const QPointF dir(std::cos(m_angleRad), std::sin(m_angleRad));
        // Prepend historical positions behind the head
        for (int i = snakeLength - 1; i > 0; --i) {
            m_body.prepend(m_head - dir * (segment * i));
        }
    }

    // Turn toward mouseTarget (slither feel: limited turn rate)
    const double maxTurnRate = qDegreesToRadians(220.0); // rad/s
    const double desiredAngle = std::atan2(m_mouseTarget.y() - m_head.y(),
                                           m_mouseTarget.x() - m_head.x());
    double delta = desiredAngle - m_angleRad;
    while (delta > M_PI)  delta -= 2*M_PI;
    while (delta < -M_PI) delta += 2*M_PI;
    const double maxStep = maxTurnRate * dt;
    if (delta >  maxStep) delta =  maxStep;
    if (delta < -maxStep) delta = -maxStep;
    m_angleRad += delta;

    // Move forward
    const double dx = std::cos(m_angleRad) * m_speed * dt;
    const double dy = std::sin(m_angleRad) * m_speed * dt;
    m_head += QPointF(dx, dy);
    wrapIfOutside();

    // Keep body length fixed and fluid
    const int snakeLength = 80;
    m_body.push_back(m_head);
    while (m_body.size() > snakeLength)
        m_body.remove(0);

    emit bodyChanged();
    emit headChanged();
}


void GameController::wrapIfOutside() {
    // Toroidal wrap (classic arcade feel)
    if (m_head.x() < 0)          m_head.setX(m_viewW + m_head.x());
    if (m_head.x() >= m_viewW)   m_head.setX(m_head.x() - m_viewW);
    if (m_head.y() < 0)          m_head.setY(m_viewH + m_head.y());
    if (m_head.y() >= m_viewH)   m_head.setY(m_head.y() - m_viewH);
}
