//
//  TimeSlotPickerView.swift
//  PowerMonitorIOS
//
//  Created by Alexandre Camilleri on 13/06/2015.
//  Copyright (c) 2015 Alexandre Camilleri. All rights reserved.
//

import UIKit

class TimeSlotPickerView: UIPickerView, UIPickerViewDelegate, UIPickerViewDataSource {

	let days = ["Mon", "Tue", "Wed", "Thu", "Fry", "Sat", "Sun"]
	var hours = [Int]()
	var minutes = [Int]()

	required init(coder aDecoder: NSCoder)
	{
		super.init(coder: aDecoder)
		delegate = self
		dataSource = self
		for var i = 0; i < 24; i++ {
			hours.append(i)
		}
		for var i = 0; i < 60; i++ {
			minutes.append(i)
		}
	}

	enum components: Int {
		case days = 0
		case hours = 1
		case minutes = 2
	}

	func numberOfComponentsInPickerView(pickerView: UIPickerView) -> Int {
		return 3
	}

	func pickerView(pickerView: UIPickerView, numberOfRowsInComponent component: Int) -> Int {
		switch (component) {
		case components.days.rawValue:
			return days.count
		case components.hours.rawValue:
			return hours.count
		case components.minutes.rawValue:
			return minutes.count
		default:
			return 0
		}
	}

	func pickerView(pickerView: UIPickerView, titleForRow row: Int, forComponent component: Int) -> String! {
		switch (component) {
		case components.days.rawValue:
			return days[row]
		case components.hours.rawValue:
			return hours[row].description
		case components.minutes.rawValue:
			return minutes[row].description
		default:
			return "0"
		}
	}

	func getValues() -> (d: Int, h: Int, m: Int) {
		var ret: (Int, Int, Int)

		ret.0 = self.selectedRowInComponent(components.days.rawValue)
		ret.1 = self.selectedRowInComponent(components.hours.rawValue)
		ret.2 = self.selectedRowInComponent(components.minutes.rawValue)
		return ret
	}
}
