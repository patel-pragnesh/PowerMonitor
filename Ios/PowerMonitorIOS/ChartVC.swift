//
//  ChartVC.swift
//  PowerMonitorIOS
//
//  Created by Alexandre Camilleri on 30/08/2015.
//  Copyright (c) 2015 Alexandre Camilleri. All rights reserved.
//

import Foundation
import SwiftyJSON
import SwiftCharts

class ChartVC: UIViewController {
	@IBOutlet weak var begDate: UITextField!
	@IBOutlet weak var endDate: UITextField!
	@IBOutlet weak var modulesButton: UIButton!
	@IBOutlet weak var chartView: ChartBaseView!
	var c = Chartx()
	var moduleId: Int!
	var bd: NSDate?
	var ed: NSDate?

	func generateCurveFromJSON(dataJSON: JSON) {
		var points = [Double, Double]()

		for (index: String, data: JSON) in dataJSON {
			points.append(data["time"].doubleValue, data["value"].doubleValue)
		}

		////////////////
		let chartConfig = ChartConfigXY(
			xAxisConfig: ChartAxisConfig(from: 2, to: 14, by: 2),
			yAxisConfig: ChartAxisConfig(from: 0, to: 14, by: 2)
		)

		let chart = LineChart(
			frame: self.chartView.frame,
			chartConfig: chartConfig,
			xTitle: "X axis",
			yTitle: "Y axis",
			lines: [
				(chartPoints: [(2.0, 10.6), (4.2, 5.1), (7.3, 3.0), (8.1, 5.5), (14.0, 8.0)], color: UIColor.redColor()),
				(chartPoints: [(2.0, 2.6), (4.2, 4.1), (7.3, 1.0), (8.1, 11.5), (14.0, 3.0)], color: UIColor.blueColor())
			]
		)

		self.chartView.addSubview(chart.view)
	}

	func dataChanged() {
		let ret = c.getModuleConsumptionData(moduleId, beg: Int(bd!.timeIntervalSince1970), end: Int(ed!.timeIntervalSince1970), unit: 2)

		if (ret.avc != nil) {
			popAlertView(self, ret.avc!)
		}
		generateCurveFromJSON(ret.conso)
	}

	///////////////////////////////////////

	@IBAction func modulesTapped(sender: AnyObject) {
	}
	
	/*   Picker text fields   */
	@IBAction func begDateEdit(sender: UITextField) {
		var datePickerView = UIDatePicker()

		if (bd != nil) {
		  datePickerView.setDate(bd!, animated: true)
		}
		datePickerView.datePickerMode = UIDatePickerMode.Date
		sender.inputView = datePickerView
		datePickerView.addTarget(self, action: Selector("begDatePickerValueChanged:"), forControlEvents: UIControlEvents.ValueChanged)
	}

	@IBAction func endDateEdit(sender: UITextField) {
		var datePickerView = UIDatePicker()

		if (ed != nil) {
			datePickerView.setDate(ed!, animated: true)
		}
		datePickerView.datePickerMode = UIDatePickerMode.Date
		sender.inputView = datePickerView
		datePickerView.addTarget(self, action: Selector("endDatePickerValueChanged:"), forControlEvents: UIControlEvents.ValueChanged)
	}

	func begDatePickerValueChanged(sender: UIDatePicker) {
		var dateFormatter = NSDateFormatter()

		dateFormatter.dateStyle = NSDateFormatterStyle.ShortStyle
		dateFormatter.timeStyle = NSDateFormatterStyle.NoStyle
		begDate.text = dateFormatter.stringFromDate(sender.date)
		bd = sender.date
		if (ed != nil) {
			dataChanged()
			begDate.resignFirstResponder()
		}
	}


	func endDatePickerValueChanged(sender: UIDatePicker) {
		var dateFormatter = NSDateFormatter()

		dateFormatter.dateStyle = NSDateFormatterStyle.ShortStyle
		dateFormatter.timeStyle = NSDateFormatterStyle.NoStyle
		endDate.text = dateFormatter.stringFromDate(sender.date)
		ed = sender.date
		if (bd != nil) {
			dataChanged()
			endDate.resignFirstResponder()
		}
	}

	/* ------------------------------------------------------------------------ */

	func setModuleId(moduleId: Int) {
		self.moduleId = moduleId
	}

}

/*var iPhoneChartSettings: ChartSettings {
let chartSettings = ChartSettings()
chartSettings.leading = 10
chartSettings.top = 10
chartSettings.trailing = 10
chartSettings.bottom = 10
chartSettings.labelsToAxisSpacingX = 5
chartSettings.labelsToAxisSpacingY = 5
chartSettings.axisTitleLabelsToLabelsSpacing = 4
chartSettings.axisStrokeWidth = 0.2
chartSettings.spacingBetweenAxesX = 8
chartSettings.spacingBetweenAxesY = 8
return chartSettings
}

override func viewDidLoad() {
}

func generateCurveFromJSON(dataJSON: JSON) {
var points = [(Double, Double)]()

for (index: String, data: JSON) in dataJSON {
points.append((data["time"].doubleValue, data["value"].doubleValue))
}

////////////////

/***/let labelSettings = ChartLabelSettings(font: UIFont.systemFontOfSize(5.0))

let chartPoints = points.map{ChartPoint(x: ChartAxisValueFloat(CGFloat($0.0), labelSettings: labelSettings), y: ChartAxisValueFloat(CGFloat($0.1)))}

let xValues = chartPoints.map{$0.x}

let yValues = ChartAxisValuesGenerator.generateYAxisValuesWithChartPoints(chartPoints, minSegmentCount: 10, maxSegmentCount: 20, multiple: 2, axisValueGenerator: {ChartAxisValueFloat($0, labelSettings: labelSettings)}, addPaddingSegmentIfEdge: false)

let xModel = ChartAxisModel(axisValues: xValues, axisTitleLabel: ChartAxisLabel(text: "Axis title", settings: labelSettings))
let yModel = ChartAxisModel(axisValues: yValues, axisTitleLabel: ChartAxisLabel(text: "Axis title", settings: labelSettings.defaultVertical()))
/***/let chartFrame = self.chartView.frame //getChartFrame(self.view.bounds) //ExamplesDefaults.chartFrame(self.view.bounds)
let coordsSpace = ChartCoordsSpaceLeftBottomSingleAxis(chartSettings: iPhoneChartSettings, chartFrame: chartFrame, xModel: xModel, yModel: yModel)
let (xAxis, yAxis, innerFrame) = (coordsSpace.xAxis, coordsSpace.yAxis, coordsSpace.chartInnerFrame)

let lineModel = ChartLineModel(chartPoints: chartPoints, lineColor: UIColor.redColor(), animDuration: 1, animDelay: 0)
let chartPointsLineLayer = ChartPointsLineLayer(xAxis: xAxis, yAxis: yAxis, innerFrame: innerFrame, lineModels: [lineModel])


let trackerLayerSettings = ChartPointsLineTrackerLayerSettings(thumbSize: 20, thumbCornerRadius: 10, thumbBorderWidth: 2, infoViewFont: UIFont.systemFontOfSize(16), infoViewSize: CGSizeMake(160, 40), infoViewCornerRadius: 15)
let chartPointsTrackerLayer = ChartPointsLineTrackerLayer(xAxis: xAxis, yAxis: yAxis, innerFrame: innerFrame, chartPoints: chartPoints, lineColor: UIColor.blackColor(), animDuration: 1, animDelay: 2, settings: trackerLayerSettings)

var settings = ChartGuideLinesDottedLayerSettings(linesColor: UIColor.blackColor(), linesWidth: 0.1)
let guidelinesLayer = ChartGuideLinesDottedLayer(xAxis: xAxis, yAxis: yAxis, innerFrame: innerFrame, settings: settings)

let chart = Chart(
frame: chartFrame,
layers: [
xAxis,
yAxis,
guidelinesLayer,
chartPointsLineLayer,
chartPointsTrackerLayer
]
)

self.chartView.addSubview(chart.view)
}*/