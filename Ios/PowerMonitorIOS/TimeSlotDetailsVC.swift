//
//  TimeSlotDetailsVC.swift
//  PowerMonitorIOS
//
//  Created by Alexandre Camilleri on 13/06/2015.
//  Copyright (c) 2015 Alexandre Camilleri. All rights reserved.
//

import UIKit

class TimeSlotDetailsVC: UIViewController {
	var timeslot: TimeSlot!
	var pd = ProfileDetails()
	@IBOutlet weak var startingPicker: TimeSlotPickerView!
	@IBOutlet weak var endingPicker: TimeSlotPickerView!
	@IBOutlet weak var onTimeLabel: UILabel!
	@IBOutlet weak var offTimeLabel: UILabel!

	override func viewDidLoad() {
		setInitialState()
	}
	
	func setInitialState() {
		startingPicker.selectRow(timeslot.beg.day, inComponent: 0, animated: false)
		startingPicker.selectRow(timeslot.beg.getHour() , inComponent: 1, animated: false)
		startingPicker.selectRow(timeslot.beg.getMinute() , inComponent: 2, animated: false)
		endingPicker.selectRow(timeslot.end.day, inComponent: 0, animated: false)
		endingPicker.selectRow(timeslot.end.getHour() , inComponent: 1, animated: false)
		endingPicker.selectRow(timeslot.end.getMinute() , inComponent: 2, animated: false)

		onTimeLabel.text = timeslot.beg.getHourString(timeslot.beg.day)
		offTimeLabel.text = timeslot.end.getHourString(timeslot.end.day)
	}

	// delete profile
	@IBAction func TouchRemoveTimeSlot(sender: UIButton) {
		let ret = pd.deleteTimeSlot(timeslot.id)

		if (ret != nil) {
			// display error
			popAlertView(self, ret!)
		}
		else {
			navigationController!.popViewControllerAnimated(true)
		}
	}

	// update timeslot
	@IBAction func touchUpdateTimeSlot() {
		var updatedTS: TimeSlot
		var spvalue = startingPicker.getValues()
		var epvalue = endingPicker.getValues()

		updatedTS = generateTimeSlotFromPicker(spvalue, epvalue)
		updatedTS.id = timeslot.id
		let valid = checkValidity(updatedTS)
		if (valid) {
			let ret = pd.updateTimeSlot(updatedTS)
			if (ret != nil) {
				popAlertView(self, ret!)
			}
			else {
				navigationController!.popViewControllerAnimated(true)
			}
		}
		else {
			popAlertView(self, ("Invalid time frames", "You probably made a mistake", "Ok"))
		}
	}

	private func checkValidity(ts: TimeSlot) -> Bool {
		if (ts.beg.day > ts.end.day) {
			return false
		}
		if (ts.beg.min >= ts.end.min) {
			return false
		}
		return true
	}
}

