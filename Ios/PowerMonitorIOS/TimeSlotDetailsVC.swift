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

	// TODO add la fonction pour delete un profile
//peut etre integrer profiledetails ici


	/* remove a timeslot from profile
	func removeTimeSlot() {

		let ret = pd.removeTimeSlot(timeSlotId)

		if (ret != nil) {
			// display error
			popAlertView(self, ret!)
		}
		else {
			// refresh table display
			self.refreshTimeSlotsArray()
		}
	}*/
}
