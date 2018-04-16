import QtQuick 2.9
import QtCharts 2.2
import QtQuick.Controls 2.3

//![1]
ChartView {
    id: chartView
    animationOptions: ChartView.NoAnimation
    theme: ChartView.ChartThemeDark
    property bool openGL: true
    Connections {
        target: ChartSource;
        onUpdateChart: {
            ChartSource.update(chartView.series(0), chartView.series(1))
        }
    }


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
        name: "RAW"
        axisX: axisX
        axisY: axisY
        useOpenGL: chartView.openGL
    }

    LineSeries {
        id: lineSeries2
        name: "Thresholding"
        color: "#66ccff"
        axisX: axisX
        axisY: axisY
        useOpenGL: chartView.openGL
    }
}
//![1]
