import QtQuick
import QtQuick.Controls

ApplicationWindow {
    id: win
    width: 1280
    height: 720
    visible: true
    color: "black"
    title: "Pixel Snake"

    Component.onCompleted: controller.setViewportSize(width, height)
    onWidthChanged:       controller.setViewportSize(width, height)
    onHeightChanged:      controller.setViewportSize(width, height)

    // 60 fps game loop
    Timer {
        interval: 16
        running: true
        repeat: true
        onTriggered: {
            controller.tick()
            gameCanvas.requestPaint()
        }
    }

    // Mouse steering
    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onPositionChanged: controller.setMouseTarget(mouse.x, mouse.y)
        onPressed:         controller.setMouseTarget(mouse.x, mouse.y)
        onMouseXChanged:   controller.setMouseTarget(mouseX, mouseY)
        onMouseYChanged:   controller.setMouseTarget(mouseX, mouseY)
    }

    Canvas {
        id: gameCanvas
        anchors.fill: parent
        antialiasing: true

        onPaint: {
            const ctx = getContext("2d")
            ctx.reset()
            ctx.save()

            // Clear
            ctx.fillStyle = "black"
            ctx.fillRect(0, 0, width, height)

            // Draw body polyline
            const pts = controller.body
            ctx.lineWidth = 8
            ctx.lineCap = "round"
            ctx.lineJoin = "round"
            ctx.strokeStyle = "#4FC3F7"

            if (pts.length > 1) {
                ctx.beginPath()
                ctx.moveTo(pts[0].x, pts[0].y)
                for (let i = 1; i < pts.length; ++i)
                    ctx.lineTo(pts[i].x, pts[i].y)
                ctx.stroke()
            }

            // Draw head
            const head = controller.head
            ctx.fillStyle = "#81C784"
            ctx.beginPath()
            ctx.arc(head.x, head.y, 10, 0, Math.PI * 2)
            ctx.fill()

            ctx.restore()
        }
    }

    // HUD
    Row {
        spacing: 12
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.margins: 10
    }
}
