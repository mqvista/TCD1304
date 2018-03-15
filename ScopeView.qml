import QtQuick 2.0
import QtCharts 2.2

//![1]
ChartView {
    id: chartView
    animationOptions: ChartView.NoAnimation
    theme: ChartView.ChartThemeDark
    property bool openGL: true

    ValueAxis {
        id: axisY
        min: 0
        max: 50000
    }

    ValueAxis {
        id: axisX
        min: 0
        max: 3648
    }

    LineSeries {
        id: lineSeries1
        name: "signal 1"
        axisX: axisX
        axisY: axisY
        useOpenGL: chartView.openGL
    }
}
//![1]
