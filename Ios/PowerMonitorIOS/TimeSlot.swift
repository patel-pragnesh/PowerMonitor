//
//  TimeSlot.swift
//  PowerMonitorIOS
//
//  Created by Alexandre Camilleri on 02/06/2015.
//  Copyright (c) 2015 Alexandre Camilleri. All rights reserved.
//

import SwiftyJSON

let D_DEFAULT_TIMESLOT_ID = 0 //Temporary id pour l'ajout de nouveau timeslots
let D_DEFAULT_TIMESLOT_STARTINGDAY = 0
let D_DEFAULT_TIMESLOT_STARTINGTIME = 0

struct TimeSlotTime {
	var day: Int
	var min: Int

	func getHourString(forDay: Int) -> String {
		let minutes = getMinute()
		let hours = getHour()
		var ret = String()

		ret += String(format: "%02d:%02d", hours, minutes)
		if (forDay != self.day) {
			ret += String(format: " (%s)", self.day)
		}
		return ret
	}

	func getHour() -> Int {
		let minutes = min % 60

		return (min - minutes) / 60
	}

	func getMinute() -> Int {
		return (min % 60)
	}
}

func getDay(day: Int) -> String {
	let dayString: String

	switch (day) {
	case 0:
		dayString = "Monday"
	case 1:
		dayString = "Tuesday"
	case 2:
		dayString = "Wednesday"
	case 3:
		dayString = "Thursday"
	case 4:
		dayString = "Friday"
	case 5:
		dayString = "Saturday"
	case 6:
		dayString = "Sunday"
	default:
		dayString = "Error"
	}
	return dayString
}

struct TimeSlot {
	var id: Int
	var beg: TimeSlotTime
	var end: TimeSlotTime
}

// convert JSON timeslot data into timeslot struct
func generateTimeSlotFromJSON(data: JSON) -> TimeSlot
{
	var timeSlot: TimeSlot
	let begData: JSON = data["beg"]
	let endData: JSON = data["end"]

	timeSlot = TimeSlot(id: data["id"].intValue,
		beg: TimeSlotTime(day: begData["day"].intValue, min: begData["minute"].intValue),
		end: TimeSlotTime(day: endData["day"].intValue, min: endData["minute"].intValue))
	return timeSlot
}

// when adding a new timeslot, generate the temporary newly created timeslots
//  before we add it by request
func generateNewTimeSlot() -> TimeSlot
{
	var timeSlot: TimeSlot

	timeSlot = TimeSlot(id: D_DEFAULT_TIMESLOT_ID,
		beg: TimeSlotTime(day: D_DEFAULT_TIMESLOT_STARTINGDAY, min: D_DEFAULT_TIMESLOT_STARTINGTIME),
		end: TimeSlotTime(day: D_DEFAULT_TIMESLOT_STARTINGDAY, min: D_DEFAULT_TIMESLOT_STARTINGTIME))
	return timeSlot
}