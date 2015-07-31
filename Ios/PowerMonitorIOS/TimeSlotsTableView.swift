//
//  TimeSlotsTableView.swift
//  PowerMonitorIOS
//
//  Created by Alexandre Camilleri on 09/06/2015.
//  Copyright (c) 2015 Alexandre Camilleri. All rights reserved.
//

import Foundation
import UIKit

class TimeSlotsTableView: UITableView, UITableViewDelegate, UITableViewDataSource {
	var day = 0
	private var profile: Profile!
	private var timeSlots =  Array(count: 7, repeatedValue: Array<TimeSlot>())
	private var pd = ProfileDetails()

	required init(coder aDecoder: NSCoder)
	{
		super.init(coder: aDecoder)
		delegate = self
		dataSource = self
	}

	/* ------------------------------------------------------------------------ */

	func prepareForSegue(segue: UIStoryboardSegue, sender: AnyObject?)
	{
		if segue.identifier == "showTimeSlotDetails" {
			if let timeSlotDetailsVC = segue.destinationViewController as? TimeSlotDetailsVC {
				if let rowIndex = self.indexPathForSelectedRow()?.row {
					timeSlotDetailsVC.timeslot = timeSlots[day][rowIndex]
				}
			}
		}
	}

	// return cell count
	func tableView(tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
		return timeSlots[day].count
	}

	// cell generation - called for each cell
	func tableView(tableView: UITableView, cellForRowAtIndexPath indexPath: NSIndexPath) -> UITableViewCell {
		var cell = self.dequeueReusableCellWithIdentifier("timeSlotCell", forIndexPath: indexPath) as! TimeSlotCell

		cell.onTime.text = timeSlots[day][indexPath.row].beg.getHourString(day)
		cell.offTime.text = timeSlots[day][indexPath.row].end.getHourString(day)
		return cell
	}

	// add an empty new Profile to Profiles
	func addNewTimeSlot() {
		var defaultTimeSlot = generateNewTimeSlot(day)
		let ret = pd.addNewTimeSlot(profile.id, timeslot: defaultTimeSlot)

		if (ret != nil) {
			// display error
			popAlertView(self, ret!)
		}
		else {
			// refresh table display
			self.refreshTimeSlotsArray()
		}
	}

	func render() {
		reloadSections(NSIndexSet(index: 0), withRowAnimation: UITableViewRowAnimation.Fade)
	}

	func refreshTimeSlotsArray() {
		loadProfileTimeSlots()
		for var iDay = 0; iDay < 7; iDay++ {
			timeSlots[iDay].removeAll(keepCapacity: false)
			for element in profile.timeSlots {
				if (iDay >= element.beg.day && iDay <= element.end.day) {
					(timeSlots[iDay]).append(element)
				}
			}
		}
	}

	private func loadProfileTimeSlots() {
		let ret = pd.getProfileTimeSlots(profile.id)

		if (ret.avc != nil) {
			popAlertView(self, ret.avc!)
		}
		profile.timeSlots = ret.timeSlots
	}

	func setProfile(profile: Profile) {
		self.profile = profile
		refreshTimeSlotsArray()
	}

	func changeDay(direction: Int) {
		day += direction
		if (day < 0) {
			day = 6
		}
		else if (day > 6) {
			day = 0
		}
	}
	
}